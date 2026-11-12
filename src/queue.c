/*
 * The callback queue: ported from php-io-extensions/miniaudio src/callbacks.c.
 */
#include "queue.h"

#include <errno.h>
#include <time.h>

enum { REQ_QUEUED = 0, REQ_TAKEN = 1, REQ_DONE = 2, REQ_DROPPED = 3, REQ_POSTED = 4 };

typedef struct vlc_deferred {
	struct vlc_deferred *next;
	zval callable;
	uint32_t argc;
	zval argv[3];
} vlc_deferred;

struct vlc_queue {
	vlc_deferred *deferred, *deferred_tail; /* owner thread only */
	pthread_mutex_t lock;
	pthread_cond_t idle;           /* a dispatching thread left */
	vlc_req *head, *tail;
	zend_atomic_bool *vm_interrupt;
	pthread_t thread;
	int users;                     /* libvlc threads inside vlc_queue_call on this queue */
	bool closing;
	bool dead;                     /* this process is a fork child: libvlc's threads are gone */
};

/* Guards every record's queue pointer: a libvlc thread reads it while the owner's request ends. */
static pthread_mutex_t vlc_cb_lock = PTHREAD_MUTEX_INITIALIZER;
/* Every live queue, for the fork child. */
static vlc_queue *vlc_queues[256];
static int vlc_queue_count = 0;

static void (*vlc_prev_interrupt)(zend_execute_data *execute_data);

static void vlc_serve_pending(void);
static void vlc_run_deferred(vlc_queue *q);
static vlc_cb *vlc_cb_take_dead(void);
static void vlc_cb_finish_all(vlc_cb *list);

static void vlc_interrupt(zend_execute_data *execute_data)
{
	vlc_serve_pending();
	if (vlc_prev_interrupt) {
		vlc_prev_interrupt(execute_data);
	}
}

static void vlc_atfork_child(void)
{
	/* Only the forking thread exists in the child: a libvlc thread will never answer or ask. */
	for (int i = 0; i < vlc_queue_count; i++) {
		vlc_queues[i]->dead = true;
	}
	pthread_mutex_init(&vlc_cb_lock, NULL);
}

void vlc_queue_minit(void)
{
	vlc_prev_interrupt = zend_interrupt_function;
	zend_interrupt_function = vlc_interrupt;
	pthread_atfork(NULL, NULL, vlc_atfork_child);
}

void vlc_queue_rinit(void)
{
	vlc_queue *q = pecalloc(1, sizeof(*q), 1);

	pthread_mutex_init(&q->lock, NULL);
	pthread_cond_init(&q->idle, NULL);
	q->vm_interrupt = &EG(vm_interrupt);
	q->thread = pthread_self();
	VLC_G(queue) = q;
	VLC_G(cbs) = NULL;

	pthread_mutex_lock(&vlc_cb_lock);
	if (vlc_queue_count < (int) (sizeof(vlc_queues) / sizeof(vlc_queues[0]))) {
		vlc_queues[vlc_queue_count++] = q;
	}
	pthread_mutex_unlock(&vlc_cb_lock);
}

void vlc_queue_rshutdown(void)
{
	vlc_queue *q = VLC_G(queue);

	if (q == NULL) {
		return;
	}

	/* Every record of this request gives its no-op from now on; libvlc may still hold them. */
	pthread_mutex_lock(&vlc_cb_lock);
	vlc_cb *dead = vlc_cb_take_dead();
	for (vlc_cb *cb = VLC_G(cbs); cb != NULL; cb = cb->next) {
		cb->queue = NULL;
	}
	for (int i = 0; i < vlc_queue_count; i++) {
		if (vlc_queues[i] == q) {
			vlc_queues[i] = vlc_queues[--vlc_queue_count];
			break;
		}
	}
	pthread_mutex_unlock(&vlc_cb_lock);

	pthread_mutex_lock(&q->lock);
	q->closing = true;
	while (q->head) {
		vlc_req *r = q->head;
		q->head = r->next;
		if (r->state == REQ_POSTED) {
			free(r);
			continue;
		}
		r->state = REQ_DROPPED;
		pthread_cond_signal(&r->done);
	}
	q->tail = NULL;
	while (q->users > 0) {
		pthread_cond_wait(&q->idle, &q->lock);
	}
	pthread_mutex_unlock(&q->lock);
	vlc_run_deferred(q); /* closing: frees them uncalled */
	vlc_cb_finish_all(dead);

	for (vlc_cb *cb = VLC_G(cbs); cb != NULL; cb = cb->next) {
		for (size_t i = 0; i < sizeof(cb->callables) / sizeof(cb->callables[0]); i++) {
			zval_ptr_dtor(&cb->callables[i]);
			ZVAL_UNDEF(&cb->callables[i]);
		}
	}
	VLC_G(cbs) = NULL;

	pthread_mutex_destroy(&q->lock);
	pthread_cond_destroy(&q->idle);
	pefree(q, 1);
	VLC_G(queue) = NULL;
}

static void vlc_deadline(struct timespec *ts, uint32_t ms)
{
	clock_gettime(CLOCK_REALTIME, ts);
	ts->tv_sec += ms / 1000;
	ts->tv_nsec += (long) (ms % 1000) * 1000000L;
	if (ts->tv_nsec >= 1000000000L) {
		ts->tv_sec++;
		ts->tv_nsec -= 1000000000L;
	}
}

void vlc_defer(vlc_cb *cb, uint32_t argc, zval *argv)
{
	vlc_queue *q = VLC_G(queue);
	vlc_deferred *d = ecalloc(1, sizeof(*d));

	ZVAL_COPY(&d->callable, &cb->callables[0]);
	d->argc = argc;
	for (uint32_t i = 0; i < argc; i++) {
		ZVAL_COPY_VALUE(&d->argv[i], &argv[i]);
	}
	if (q->deferred_tail) {
		q->deferred_tail->next = d;
	} else {
		q->deferred = d;
	}
	q->deferred_tail = d;
}

/* Owner thread, no libvlc thread waiting on it: the deferred calls, in order. A throw drops the rest. */
static void vlc_run_deferred(vlc_queue *q)
{
	while (q->deferred) {
		vlc_deferred *d = q->deferred;
		zval ret;

		q->deferred = d->next;
		if (!q->deferred) {
			q->deferred_tail = NULL;
		}
		if (!EG(exception) && !q->closing && vlc_cb_invoke(&d->callable, &ret, d->argc, d->argv)) {
			zval_ptr_dtor(&ret);
		}
		zval_ptr_dtor(&d->callable);
		for (uint32_t i = 0; i < d->argc; i++) {
			zval_ptr_dtor(&d->argv[i]);
		}
		efree(d);
	}
}

static void vlc_serve_one(vlc_queue *q, vlc_req *r)
{
	if (EG(exception) || q->closing) {
		r->fallback(r); /* a callback never runs while an exception is pending */
	} else {
		r->serve(r);
	}
}

void vlc_queue_call(vlc_req *r, uint32_t deadline_ms)
{
	pthread_mutex_lock(&vlc_cb_lock);
	vlc_queue *q = r->cb->queue;
	if (q == NULL || q->dead) {
		pthread_mutex_unlock(&vlc_cb_lock);
		r->fallback(r);
		return;
	}
	if (pthread_equal(pthread_self(), q->thread)) {
		/* libvlc called back on the PHP thread itself, inside a binding call */
		pthread_mutex_unlock(&vlc_cb_lock);
		vlc_serve_one(q, r);
		vlc_run_deferred(q);
		return;
	}
	pthread_mutex_lock(&q->lock);
	pthread_mutex_unlock(&vlc_cb_lock);

	if (q->closing) {
		pthread_mutex_unlock(&q->lock);
		r->fallback(r);
		return;
	}
	q->users++;
	pthread_cond_init(&r->done, NULL);
	r->next = NULL;
	r->state = REQ_QUEUED;
	if (q->tail) {
		q->tail->next = r;
	} else {
		q->head = r;
	}
	q->tail = r;
	zend_atomic_bool_store(q->vm_interrupt, true);

	struct timespec ts;
	vlc_deadline(&ts, deadline_ms);
	bool dropped = false;
	while (r->state != REQ_DONE) {
		if (r->state == REQ_DROPPED) {
			dropped = true;
			break;
		}
		if (r->state == REQ_QUEUED) {
			if (pthread_cond_timedwait(&r->done, &q->lock, &ts) == ETIMEDOUT && r->state == REQ_QUEUED) {
				/* not started in time: withdraw it so the owner never serves a stale request */
				vlc_req **pp = &q->head, *prev = NULL;
				while (*pp && *pp != r) {
					prev = *pp;
					pp = &(*pp)->next;
				}
				if (*pp) {
					*pp = r->next;
					if (q->tail == r) {
						q->tail = prev;
					}
				}
				dropped = true;
				break;
			}
		} else {
			pthread_cond_wait(&r->done, &q->lock); /* being served: its arguments must stay valid */
		}
	}
	q->users--;
	pthread_cond_signal(&q->idle);
	pthread_mutex_unlock(&q->lock);
	pthread_cond_destroy(&r->done);
	if (dropped) {
		r->fallback(r);
	}
}

void vlc_queue_post(vlc_req *r)
{
	pthread_mutex_lock(&vlc_cb_lock);
	vlc_queue *q = r->cb->queue;
	if (q == NULL || q->dead) {
		pthread_mutex_unlock(&vlc_cb_lock);
		free(r);
		return;
	}
	if (pthread_equal(pthread_self(), q->thread)) {
		pthread_mutex_unlock(&vlc_cb_lock);
		vlc_serve_one(q, r);
		free(r);
		return;
	}
	pthread_mutex_lock(&q->lock);
	pthread_mutex_unlock(&vlc_cb_lock);
	if (q->closing) {
		pthread_mutex_unlock(&q->lock);
		free(r);
		return;
	}
	r->next = NULL;
	r->state = REQ_POSTED;
	if (q->tail) {
		q->tail->next = r;
	} else {
		q->head = r;
	}
	q->tail = r;
	zend_atomic_bool_store(q->vm_interrupt, true);
	pthread_mutex_unlock(&q->lock);
}

static void vlc_serve_pending(void)
{
	vlc_queue *q = VLC_G(queue);

	if (q == NULL) {
		return;
	}
	/* Taken first: every call libvlc posted for them is queued already and is served below before they go. */
	pthread_mutex_lock(&vlc_cb_lock);
	vlc_cb *dead = vlc_cb_take_dead();
	pthread_mutex_unlock(&vlc_cb_lock);

	pthread_mutex_lock(&q->lock);
	while (q->head) {
		vlc_req *r = q->head;
		q->head = r->next;
		if (!q->head) {
			q->tail = NULL;
		}
		if (r->state == REQ_POSTED) {
			pthread_mutex_unlock(&q->lock);
			vlc_serve_one(q, r);
			free(r);
			pthread_mutex_lock(&q->lock);
			continue;
		}
		r->state = REQ_TAKEN;
		pthread_mutex_unlock(&q->lock);
		vlc_serve_one(q, r);
		pthread_mutex_lock(&q->lock);
		r->state = REQ_DONE;
		pthread_cond_signal(&r->done);
	}
	pthread_mutex_unlock(&q->lock);
	vlc_cb_finish_all(dead);
	vlc_run_deferred(q);
}

vlc_cb *vlc_cb_new(int kind, void *target)
{
	vlc_cb *cb = pecalloc(1, sizeof(*cb), 1);

	cb->queue = VLC_G(queue);
	cb->kind = kind;
	cb->target = target;
	cb->owner = target;
	for (size_t i = 0; i < sizeof(cb->callables) / sizeof(cb->callables[0]); i++) {
		ZVAL_UNDEF(&cb->callables[i]);
	}
	pthread_mutex_lock(&vlc_cb_lock);
	cb->next = VLC_G(cbs);
	VLC_G(cbs) = cb;
	pthread_mutex_unlock(&vlc_cb_lock);

	return cb;
}

vlc_cb *vlc_cb_find(int kind, void *target, int event_type, zval *callable)
{
	for (vlc_cb *cb = VLC_G(cbs); cb != NULL; cb = cb->next) {
		if (!cb->dead && cb->kind == kind && cb->target == target && cb->event_type == event_type
			&& (callable == NULL || zend_is_identical(&cb->callables[0], callable))) {
			return cb;
		}
	}
	return NULL;
}

static void vlc_cb_free_native(vlc_cb *cb)
{
	if (cb->native_free != NULL) {
		cb->native_free(cb->native);
	} else {
		free(cb->native);
	}
	pefree(cb, 1);
}

/* Frees an unlinked record on the owner thread. */
static void vlc_cb_finish(vlc_cb *cb)
{
	/* Posted calls for this record would reach freed memory: they go unserved. */
	vlc_queue *q = VLC_G(queue);
	if (q != NULL) {
		pthread_mutex_lock(&q->lock);
		vlc_req **pp = &q->head, *prev = NULL;
		while (*pp != NULL) {
			vlc_req *r = *pp;
			if (r->state == REQ_POSTED && r->cb == cb) {
				*pp = r->next;
				free(r);
				continue;
			}
			prev = r;
			pp = &r->next;
		}
		q->tail = prev;
		pthread_mutex_unlock(&q->lock);
	}

	for (size_t i = 0; i < sizeof(cb->callables) / sizeof(cb->callables[0]); i++) {
		zval_ptr_dtor(&cb->callables[i]);
	}
	vlc_cb_free_native(cb);
}

void vlc_cb_free(vlc_cb *cb)
{
	pthread_mutex_lock(&vlc_cb_lock);
	for (vlc_cb **pp = (vlc_cb **) &VLC_G(cbs); *pp != NULL; pp = &(*pp)->next) {
		if (*pp == cb) {
			*pp = cb->next;
			break;
		}
	}
	pthread_mutex_unlock(&vlc_cb_lock);
	vlc_cb_finish(cb);
}

void vlc_cb_dead(vlc_cb *cb)
{
	pthread_mutex_lock(&vlc_cb_lock);
	vlc_queue *q = cb->queue;
	if (q != NULL) {
		cb->dead = true;
		zend_atomic_bool_store(q->vm_interrupt, true);
	}
	pthread_mutex_unlock(&vlc_cb_lock);
	if (q == NULL) {
		vlc_cb_free_native(cb); /* its request ended: its callables are gone already */
	}
}

/* Unlinks the records libvlc is done with (vlc_cb_lock held); the caller vlc_cb_finish_all()s them. */
static vlc_cb *vlc_cb_take_dead(void)
{
	vlc_cb *dead = NULL;

	for (vlc_cb **pp = (vlc_cb **) &VLC_G(cbs); *pp != NULL;) {
		vlc_cb *cb = *pp;
		if (cb->dead) {
			*pp = cb->next;
			cb->next = dead;
			dead = cb;
		} else {
			pp = &cb->next;
		}
	}
	return dead;
}

static void vlc_cb_finish_all(vlc_cb *list)
{
	while (list != NULL) {
		vlc_cb *cb = list;
		list = cb->next;
		vlc_cb_finish(cb);
	}
}

bool vlc_cb_invoke(zval *callable, zval *ret, uint32_t argc, zval *argv)
{
	ZVAL_UNDEF(ret);
	if (call_user_function(NULL, NULL, callable, ret, argc, argv) == FAILURE || EG(exception)) {
		zval_ptr_dtor(ret);
		ZVAL_UNDEF(ret);
		return false;
	}
	return true;
}
