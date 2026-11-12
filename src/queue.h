#ifndef VLC_QUEUE_H
#define VLC_QUEUE_H

#include "runtime.h"
#include <pthread.h>

/*
 * The callback queue. libvlc calls back on its own threads, and sometimes on the PHP thread inside
 * a binding call. A thread that is not the owning PHP thread never enters PHP: it posts a request
 * to the owner's queue, raises the owner's vm_interrupt, and waits until the owner has served it or
 * its deadline passes; then the request gets its no-op result. The owner serves the queue from
 * zend_interrupt_function. A callback fired on the owner thread itself is served at once.
 */

typedef struct vlc_queue vlc_queue;

/*
 * One callable set handed to libvlc as its opaque / user data. Freed when libvlc can no longer
 * call it: on detach or replacement, with its owner (vlc_owner_releasing / vlc_owner_dead), or for
 * callback media on libvlc_MediaFreed. A record whose request ended keeps its native part (its
 * callables are freed) until then; one whose owner the script never released lives as long as
 * that owner, as in C.
 */
typedef struct vlc_cb {
	vlc_queue *queue;            /* NULL once its request ended: every call gets its no-op */
	struct vlc_cb *next;         /* the owner request's list */
	void *target;                /* what it is attached to: event manager, instance, player, media */
	void *owner;                 /* the object whose end ends the record: target, or an event manager's object */
	int kind;                    /* VLC_CB_* */
	int event_type;              /* events only */
	bool dead;                   /* libvlc is done with it; the owner thread frees it (vlc_cb_lock) */
	zval callables[9];           /* owner thread only */
	void *native;                /* per-kind native state, malloc'd */
	void (*native_free)(void *native); /* NULL: free() */
} vlc_cb;

enum { VLC_CB_EVENT = 1, VLC_CB_LOG, VLC_CB_EXIT, VLC_CB_MEDIA, VLC_CB_AUDIO, VLC_CB_AUDIO_FORMAT, VLC_CB_VOLUME, VLC_CB_VIDEO, VLC_CB_VIDEO_FORMAT, VLC_CB_DIALOG };

typedef struct vlc_req {
	void (*serve)(struct vlc_req *r);     /* owner thread: build zvals, call PHP, write results */
	void (*fallback)(struct vlc_req *r);  /* any thread: the no-op result */
	vlc_cb *cb;
	struct vlc_req *next;
	int state;
	bool droppable;                       /* posted audio or video data: dropped past the backlog cap */
	pthread_cond_t done;
} vlc_req;

void vlc_queue_minit(void);
void vlc_queue_rinit(void);
void vlc_queue_rshutdown(void);

/* Serves r on the owner thread within deadline_ms, or applies its fallback. */
void vlc_queue_call(vlc_req *r, uint32_t deadline_ms);

/*
 * For a callback whose result libvlc does not need: r is malloc'd with its arguments copied in,
 * and the libvlc thread returns at once. The owner serves it at its next interrupt point and
 * free()s it; a request that can no longer be served is free()d unserved.
 */
void vlc_queue_post(vlc_req *r);

/* A new record owned by this request, attached to target. */
vlc_cb *vlc_cb_new(int kind, void *target);

/* The record of this request for (kind, target[, event_type, callable]); NULL when none. */
vlc_cb *vlc_cb_find(int kind, void *target, int event_type, zval *callable);

/* Unlinks and frees a record libvlc no longer holds. Owner thread. */
void vlc_cb_free(vlc_cb *cb);

/*
 * Any thread: libvlc will never call cb again. The owner thread frees it at its next interrupt
 * point; a record whose request ended is freed at once.
 */
void vlc_cb_dead(vlc_cb *cb);

/*
 * From a serve function: call cb's first callable with argv (ownership moves) once the libvlc
 * thread has been let go. For callbacks whose result libvlc does not wait for (events, the exit
 * handler): the callable may then call libvlc functions that join that very thread.
 */
void vlc_defer(vlc_cb *cb, uint32_t argc, zval *argv);

/* Calls callable with argv; false when it threw (the exception stays pending). */
bool vlc_cb_invoke(zval *callable, zval *ret, uint32_t argc, zval *argv);

#endif
