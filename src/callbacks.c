/*
 * The libvlc functions that take callbacks, and their trampolines. Each trampoline runs on the
 * thread libvlc calls it on and hands the call to the owner PHP thread through src/queue.c.
 */
#include "queue.h"
#include <stdio.h>
#include "../stubs/callbacks_arginfo.h"

#define VLC_EVENT_DEADLINE_MS 1000
#define VLC_LOG_DEADLINE_MS 1000
#define VLC_EXIT_DEADLINE_MS 1000

static void vlc_nop(vlc_req *r)
{
	(void) r;
}

/* ---- events ---------------------------------------------------------- */

typedef struct {
	vlc_req base;
	const libvlc_event_t *ev;
} vlc_event_req;

static void vlc_u_handle(zval *u, const char *name, void *ptr, zend_class_entry *ce)
{
	zval h;

	vlc_box(&h, ptr, ce);
	add_property_zval(u, name, &h);
	zval_ptr_dtor(&h);
}

static void vlc_u_string(zval *u, const char *name, const char *s)
{
	if (s == NULL) {
		add_property_null(u, name);
	} else {
		add_property_string(u, name, s);
	}
}

/* libvlc_event_t.u: the union member for ev->type, as an object of that member's fields. */
static void vlc_event_union(const libvlc_event_t *ev, zval *u)
{
	ZVAL_NULL(u);
#define U object_init(u)
	switch (ev->type) {
		case libvlc_MediaMetaChanged: U; add_property_long(u, "meta_type", ev->u.media_meta_changed.meta_type); break;
		case libvlc_MediaSubItemAdded: U; vlc_u_handle(u, "new_child", ev->u.media_subitem_added.new_child, vlc_ce_libvlc_media_t); break;
		case libvlc_MediaDurationChanged: U; add_property_long(u, "new_duration", ev->u.media_duration_changed.new_duration); break;
		case libvlc_MediaParsedChanged: U; add_property_long(u, "new_status", ev->u.media_parsed_changed.new_status); break;
		case libvlc_MediaFreed: U; vlc_u_handle(u, "md", ev->u.media_freed.md, vlc_ce_libvlc_media_t); break;
		case libvlc_MediaStateChanged: U; add_property_long(u, "new_state", ev->u.media_state_changed.new_state); break;
		case libvlc_MediaSubItemTreeAdded: U; vlc_u_handle(u, "item", ev->u.media_subitemtree_added.item, vlc_ce_libvlc_media_t); break;
		case libvlc_MediaPlayerMediaChanged: U; vlc_u_handle(u, "new_media", ev->u.media_player_media_changed.new_media, vlc_ce_libvlc_media_t); break;
		case libvlc_MediaPlayerBuffering: U; add_property_double(u, "new_cache", ev->u.media_player_buffering.new_cache); break;
		case libvlc_MediaPlayerChapterChanged: U; add_property_long(u, "new_chapter", ev->u.media_player_chapter_changed.new_chapter); break;
		case libvlc_MediaPlayerPositionChanged: U; add_property_double(u, "new_position", ev->u.media_player_position_changed.new_position); break;
		case libvlc_MediaPlayerTimeChanged: U; add_property_long(u, "new_time", ev->u.media_player_time_changed.new_time); break;
		case libvlc_MediaPlayerTitleChanged: U; add_property_long(u, "new_title", ev->u.media_player_title_changed.new_title); break;
		case libvlc_MediaPlayerSeekableChanged: U; add_property_long(u, "new_seekable", ev->u.media_player_seekable_changed.new_seekable); break;
		case libvlc_MediaPlayerPausableChanged: U; add_property_long(u, "new_pausable", ev->u.media_player_pausable_changed.new_pausable); break;
		case libvlc_MediaPlayerScrambledChanged: U; add_property_long(u, "new_scrambled", ev->u.media_player_scrambled_changed.new_scrambled); break;
		case libvlc_MediaPlayerVout: U; add_property_long(u, "new_count", ev->u.media_player_vout.new_count); break;
		case libvlc_MediaPlayerSnapshotTaken: U; vlc_u_string(u, "psz_filename", ev->u.media_player_snapshot_taken.psz_filename); break;
		case libvlc_MediaPlayerLengthChanged: U; add_property_long(u, "new_length", ev->u.media_player_length_changed.new_length); break;
		case libvlc_MediaPlayerESAdded:
		case libvlc_MediaPlayerESDeleted:
		case libvlc_MediaPlayerESSelected:
			U;
			add_property_long(u, "i_type", ev->u.media_player_es_changed.i_type);
			add_property_long(u, "i_id", ev->u.media_player_es_changed.i_id);
			break;
		case libvlc_MediaPlayerAudioVolume: U; add_property_double(u, "volume", ev->u.media_player_audio_volume.volume); break;
		case libvlc_MediaPlayerAudioDevice: U; vlc_u_string(u, "device", ev->u.media_player_audio_device.device); break;
		case libvlc_MediaListItemAdded:
		case libvlc_MediaListViewItemAdded:
			U;
			vlc_u_handle(u, "item", ev->u.media_list_item_added.item, vlc_ce_libvlc_media_t);
			add_property_long(u, "index", ev->u.media_list_item_added.index);
			break;
		case libvlc_MediaListWillAddItem:
		case libvlc_MediaListViewWillAddItem:
			U;
			vlc_u_handle(u, "item", ev->u.media_list_will_add_item.item, vlc_ce_libvlc_media_t);
			add_property_long(u, "index", ev->u.media_list_will_add_item.index);
			break;
		case libvlc_MediaListItemDeleted:
		case libvlc_MediaListViewItemDeleted:
			U;
			vlc_u_handle(u, "item", ev->u.media_list_item_deleted.item, vlc_ce_libvlc_media_t);
			add_property_long(u, "index", ev->u.media_list_item_deleted.index);
			break;
		case libvlc_MediaListWillDeleteItem:
		case libvlc_MediaListViewWillDeleteItem:
			U;
			vlc_u_handle(u, "item", ev->u.media_list_will_delete_item.item, vlc_ce_libvlc_media_t);
			add_property_long(u, "index", ev->u.media_list_will_delete_item.index);
			break;
		case libvlc_MediaListPlayerNextItemSet: U; vlc_u_handle(u, "item", ev->u.media_list_player_next_item_set.item, vlc_ce_libvlc_media_t); break;
		case libvlc_RendererDiscovererItemAdded: U; vlc_u_handle(u, "item", ev->u.renderer_discoverer_item_added.item, vlc_ce_libvlc_renderer_item_t); break;
		case libvlc_RendererDiscovererItemDeleted: U; vlc_u_handle(u, "item", ev->u.renderer_discoverer_item_deleted.item, vlc_ce_libvlc_renderer_item_t); break;
		case libvlc_VlmMediaAdded:
		case libvlc_VlmMediaRemoved:
		case libvlc_VlmMediaChanged:
		case libvlc_VlmMediaInstanceStarted:
		case libvlc_VlmMediaInstanceStopped:
		case libvlc_VlmMediaInstanceStatusInit:
		case libvlc_VlmMediaInstanceStatusOpening:
		case libvlc_VlmMediaInstanceStatusPlaying:
		case libvlc_VlmMediaInstanceStatusPause:
		case libvlc_VlmMediaInstanceStatusEnd:
		case libvlc_VlmMediaInstanceStatusError:
			U;
			vlc_u_string(u, "psz_media_name", ev->u.vlm_media_event.psz_media_name);
			vlc_u_string(u, "psz_instance_name", ev->u.vlm_media_event.psz_instance_name);
			break;
		default:
			break;
	}
#undef U
}

static void vlc_event_serve(vlc_req *base)
{
	vlc_event_req *r = (vlc_event_req *) base;
	zend_class_entry *ce = vlc_ce_libvlc_event_t;
	zval event, u;

	object_init_ex(&event, ce);
	zend_update_property_long(ce, Z_OBJ(event), "type", sizeof("type") - 1, r->ev->type);
	zend_update_property_long(ce, Z_OBJ(event), "p_obj", sizeof("p_obj") - 1, (zend_long) (uintptr_t) r->ev->p_obj);
	vlc_event_union(r->ev, &u);
	zend_update_property(ce, Z_OBJ(event), "u", sizeof("u") - 1, &u);
	zval_ptr_dtor(&u);

	/* Everything is copied: the callable runs once libvlc's thread is let go, so it may stop the player. */
	vlc_defer(base->cb, 1, &event);
}

static void vlc_event_tramp(const libvlc_event_t *ev, void *data)
{
	vlc_event_req r = {{vlc_event_serve, vlc_nop, data}, ev};

	vlc_queue_call(&r.base, VLC_EVENT_DEADLINE_MS);
}

PHP_FUNCTION(libvlc_event_attach)
{
	zval *zem, *callable;
	zend_long type;
	zend_fcall_info fci;
	zend_fcall_info_cache fcc;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(zem, vlc_ce_libvlc_event_manager_t)
		Z_PARAM_LONG(type)
		Z_PARAM_FUNC(fci, fcc)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_event_manager_t, p_event_manager, zem, 1);
	callable = &fci.function_name;

	vlc_cb *cb = vlc_cb_new(VLC_CB_EVENT, p_event_manager);
	cb->owner = vlc_handle_from(Z_OBJ_P(zem))->owner; /* NULL for a manager from fromPointer(): freed on detach or request end */
	cb->event_type = (int) type;
	ZVAL_COPY(&cb->callables[0], callable);
	int result = libvlc_event_attach(p_event_manager, (libvlc_event_type_t) type, vlc_event_tramp, cb);
	if (result != 0) {
		vlc_cb_free(cb);
	}
	RETURN_LONG(result);
}

PHP_FUNCTION(libvlc_event_detach)
{
	zval *zem, *callable;
	zend_long type;
	zend_fcall_info fci;
	zend_fcall_info_cache fcc;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(zem, vlc_ce_libvlc_event_manager_t)
		Z_PARAM_LONG(type)
		Z_PARAM_FUNC(fci, fcc)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_event_manager_t, p_event_manager, zem, 1);
	callable = &fci.function_name;

	vlc_cb *cb = vlc_cb_find(VLC_CB_EVENT, p_event_manager, (int) type, callable);
	if (cb != NULL) {
		libvlc_event_detach(p_event_manager, (libvlc_event_type_t) type, vlc_event_tramp, cb);
		vlc_cb_free(cb);
	}
}

/* ---- log ------------------------------------------------------------- */

typedef struct {
	vlc_req base;
	int level;
	const libvlc_log_t *ctx;
	char message[4096];
} vlc_log_req;

static void vlc_log_serve(vlc_req *base)
{
	vlc_log_req *r = (vlc_log_req *) base;
	zval argv[3], ret;

	ZVAL_LONG(&argv[0], r->level);
	vlc_box(&argv[1], (void *) r->ctx, vlc_ce_libvlc_log_t);
	ZVAL_STRING(&argv[2], r->message);
	if (vlc_cb_invoke(&base->cb->callables[0], &ret, 3, argv)) {
		zval_ptr_dtor(&ret);
	}
	/* libvlc's context is gone when the callback returns. */
	vlc_release((void *) r->ctx, vlc_ce_libvlc_log_t);
	zval_ptr_dtor(&argv[1]);
	zval_ptr_dtor(&argv[2]);
}

static void vlc_log_tramp(void *data, int level, const libvlc_log_t *ctx, const char *fmt, va_list args)
{
	vlc_log_req r = {{vlc_log_serve, vlc_nop, data}, level, ctx, {0}};

	vsnprintf(r.message, sizeof(r.message), fmt, args);
	vlc_queue_call(&r.base, VLC_LOG_DEADLINE_MS);
}

/* libvlc no longer calls the instance's log record once libvlc_log_unset() returns. */
static void vlc_log_drop(libvlc_instance_t *p_instance)
{
	vlc_cb *old = vlc_cb_find(VLC_CB_LOG, p_instance, 0, NULL);

	if (old != NULL) {
		vlc_cb_free(old);
	}
}

PHP_FUNCTION(libvlc_log_set)
{
	zval *zi, *callable;
	zend_fcall_info fci;
	zend_fcall_info_cache fcc;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
		Z_PARAM_FUNC(fci, fcc)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_instance, zi, 1);
	callable = &fci.function_name;

	libvlc_log_unset(p_instance);
	vlc_log_drop(p_instance);
	vlc_cb *cb = vlc_cb_new(VLC_CB_LOG, p_instance);
	ZVAL_COPY(&cb->callables[0], callable);
	libvlc_log_set(p_instance, vlc_log_tramp, cb);
}

PHP_FUNCTION(libvlc_log_unset)
{
	zval *zi;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_instance, zi, 1);
	libvlc_log_unset(p_instance);
	vlc_log_drop(p_instance);
}

PHP_FUNCTION(libvlc_log_set_file)
{
	zval *zi;
	zend_long stream;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
		Z_PARAM_LONG(stream)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_instance, zi, 1);
	/* libvlc_log_set_file unsets the previous callback first: its record goes too. */
	libvlc_log_set_file(p_instance, (FILE *) (uintptr_t) stream);
	vlc_log_drop(p_instance);
}

PHP_FUNCTION(libvlc_log_get_object)
{
	zval *zctx, *zname, *zheader, *zid;
	const char *name = NULL, *header = NULL;
	uintptr_t id = 0;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(zctx, vlc_ce_libvlc_log_t)
		Z_PARAM_ZVAL(zname)
		Z_PARAM_ZVAL(zheader)
		Z_PARAM_ZVAL(zid)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_log_t, ctx, zctx, 1);

	libvlc_log_get_object(ctx, &name, &header, &id);
	if (name != NULL) {
		ZEND_TRY_ASSIGN_REF_STRING(zname, name);
	} else {
		ZEND_TRY_ASSIGN_REF_NULL(zname);
	}
	if (header != NULL) {
		ZEND_TRY_ASSIGN_REF_STRING(zheader, header);
	} else {
		ZEND_TRY_ASSIGN_REF_NULL(zheader);
	}
	ZEND_TRY_ASSIGN_REF_LONG(zid, (zend_long) id);
}

PHP_FUNCTION(libvlc_log_get_context)
{
	zval *zctx, *zmodule, *zfile, *zline;
	const char *module = NULL, *file = NULL;
	unsigned line = 0;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(zctx, vlc_ce_libvlc_log_t)
		Z_PARAM_ZVAL(zmodule)
		Z_PARAM_ZVAL(zfile)
		Z_PARAM_ZVAL(zline)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_log_t, ctx, zctx, 1);

	libvlc_log_get_context(ctx, &module, &file, &line);
	if (module != NULL) {
		ZEND_TRY_ASSIGN_REF_STRING(zmodule, module);
	} else {
		ZEND_TRY_ASSIGN_REF_NULL(zmodule);
	}
	if (file != NULL) {
		ZEND_TRY_ASSIGN_REF_STRING(zfile, file);
	} else {
		ZEND_TRY_ASSIGN_REF_NULL(zfile);
	}
	ZEND_TRY_ASSIGN_REF_LONG(zline, line);
}

/* ---- exit handler ---------------------------------------------------- */

static void vlc_exit_serve(vlc_req *base)
{
	vlc_defer(base->cb, 0, NULL);
}

static void vlc_exit_tramp(void *data)
{
	vlc_req r = {vlc_exit_serve, vlc_nop, data};

	vlc_queue_call(&r, VLC_EXIT_DEADLINE_MS);
}

PHP_FUNCTION(libvlc_set_exit_handler)
{
	zval *zi, *callable;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
		Z_PARAM_FUNC_OR_NULL(fci, fcc)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_instance, zi, 1);
	callable = ZEND_FCI_INITIALIZED(fci) ? &fci.function_name : NULL;

	vlc_cb *old = vlc_cb_find(VLC_CB_EXIT, p_instance, 0, NULL);
	if (callable == NULL) {
		libvlc_set_exit_handler(p_instance, NULL, NULL);
	} else {
		vlc_cb *cb = vlc_cb_new(VLC_CB_EXIT, p_instance);
		ZVAL_COPY(&cb->callables[0], callable);
		libvlc_set_exit_handler(p_instance, vlc_exit_tramp, cb);
	}
	if (old != NULL) {
		vlc_cb_free(old);
	}
}

/* ---- shared ------------------------------------------------------------ */

#define VLC_SLOW_DEADLINE_MS 5000
#define VLC_FRAME_DEADLINE_MS 100

/* Replaces a record's callable in slot with fci's, or with nothing. */
static void vlc_cb_set(vlc_cb *cb, int slot, zend_fcall_info *fci)
{
	zval_ptr_dtor(&cb->callables[slot]);
	if (fci != NULL && ZEND_FCI_INITIALIZED(*fci)) {
		ZVAL_COPY(&cb->callables[slot], &fci->function_name);
	} else {
		ZVAL_UNDEF(&cb->callables[slot]);
	}
}

static bool vlc_cb_has(vlc_cb *cb, int slot)
{
	return Z_TYPE(cb->callables[slot]) != IS_UNDEF;
}

/* The player's audio or video record, made on first use with a zeroed native state of size bytes. */
static vlc_cb *vlc_player_cb(int kind, libvlc_media_player_t *mp, size_t size)
{
	vlc_cb *cb = vlc_cb_find(kind, mp, 0, NULL);

	if (cb == NULL) {
		cb = vlc_cb_new(kind, mp);
		cb->native = calloc(1, size);
	}
	return cb;
}

/*
 * A posted call: one callable slot of a record. The libvlc thread fills argv with scalars and
 * copies any bytes; the owner turns the bytes into argv[bytes_at] (a string, or with as_planes a
 * list of the non-null addresses of a void *[5]).
 */
typedef struct {
	vlc_req base;
	int slot;
	int argc;
	zval argv[3];
	int bytes_at;        /* -1: no bytes argument */
	bool as_planes;
	size_t len;
	char bytes[];
} vlc_post_req;

static void vlc_post_serve(vlc_req *base)
{
	vlc_post_req *r = (vlc_post_req *) base;
	zval ret;

	if (!vlc_cb_has(base->cb, r->slot)) {
		return;
	}
	if (r->bytes_at >= 0 && r->as_planes) {
		void *const *planes = (void *const *) r->bytes;
		array_init(&r->argv[r->bytes_at]);
		for (size_t i = 0; i < r->len / sizeof(void *) && planes[i] != NULL; i++) {
			add_next_index_long(&r->argv[r->bytes_at], (zend_long) (uintptr_t) planes[i]);
		}
	} else if (r->bytes_at >= 0) {
		ZVAL_STRINGL(&r->argv[r->bytes_at], r->bytes, r->len);
	}
	if (vlc_cb_invoke(&base->cb->callables[r->slot], &ret, (uint32_t) r->argc, r->argv)) {
		zval_ptr_dtor(&ret);
	}
	if (r->bytes_at >= 0) {
		zval_ptr_dtor(&r->argv[r->bytes_at]);
	}
}

static vlc_post_req *vlc_post_new(void *data, int slot, int argc, size_t len)
{
	vlc_post_req *r = calloc(1, sizeof(*r) + len);

	r->base.serve = vlc_post_serve;
	r->base.fallback = vlc_nop;
	r->base.cb = data;
	r->slot = slot;
	r->argc = argc;
	r->bytes_at = -1;
	r->len = len;
	r->base.droppable = len > 0;
	return r;
}

/* ---- media callbacks --------------------------------------------------- */

enum { MEDIA_OPEN, MEDIA_READ, MEDIA_SEEK, MEDIA_CLOSE };

typedef struct {
	vlc_req base;
	uint64_t *size;
	int result;
} vlc_open_req;

static void vlc_open_fallback(vlc_req *base)
{
	((vlc_open_req *) base)->result = -1;
}

static void vlc_open_serve(vlc_req *base)
{
	vlc_open_req *r = (vlc_open_req *) base;
	zval size, ret;

	ZVAL_NEW_REF(&size, &EG(uninitialized_zval));
	ZVAL_NULL(Z_REFVAL(size));
	if (!vlc_cb_invoke(&base->cb->callables[MEDIA_OPEN], &ret, 1, &size)) {
		zval_ptr_dtor(&size);
		vlc_open_fallback(base);
		return;
	}
	if (Z_TYPE_P(Z_REFVAL(size)) == IS_LONG) {
		*r->size = (uint64_t) Z_LVAL_P(Z_REFVAL(size));
	}
	r->result = (int) zval_get_long(&ret);
	zval_ptr_dtor(&ret);
	zval_ptr_dtor(&size);
}

static int vlc_open_tramp(void *opaque, void **datap, uint64_t *sizep)
{
	vlc_open_req r = {{vlc_open_serve, vlc_open_fallback, opaque}, sizep, -1};

	*datap = opaque;
	*sizep = UINT64_MAX;
	vlc_queue_call(&r.base, VLC_SLOW_DEADLINE_MS);
	return r.result;
}

typedef struct {
	vlc_req base;
	unsigned char *buf;
	size_t len;
	ssize_t result;
} vlc_read_req;

static void vlc_read_fallback(vlc_req *base)
{
	((vlc_read_req *) base)->result = -1;
}

static void vlc_read_serve(vlc_req *base)
{
	vlc_read_req *r = (vlc_read_req *) base;
	zval len, ret;

	ZVAL_LONG(&len, (zend_long) r->len);
	if (!vlc_cb_invoke(&base->cb->callables[MEDIA_READ], &ret, 1, &len)) {
		vlc_read_fallback(base);
		return;
	}
	if (Z_TYPE(ret) == IS_STRING) {
		size_t n = Z_STRLEN(ret) < r->len ? Z_STRLEN(ret) : r->len;
		memcpy(r->buf, Z_STRVAL(ret), n);
		r->result = (ssize_t) n;
	} else {
		r->result = (ssize_t) zval_get_long(&ret);
	}
	zval_ptr_dtor(&ret);
}

static ssize_t vlc_read_tramp(void *opaque, unsigned char *buf, size_t len)
{
	vlc_read_req r = {{vlc_read_serve, vlc_read_fallback, opaque}, buf, len, -1};

	vlc_queue_call(&r.base, VLC_SLOW_DEADLINE_MS);
	return r.result;
}

typedef struct {
	vlc_req base;
	uint64_t offset;
	int result;
} vlc_seek_req;

static void vlc_seek_fallback(vlc_req *base)
{
	((vlc_seek_req *) base)->result = -1;
}

static void vlc_seek_serve(vlc_req *base)
{
	vlc_seek_req *r = (vlc_seek_req *) base;
	zval offset, ret;

	ZVAL_LONG(&offset, (zend_long) r->offset);
	if (!vlc_cb_invoke(&base->cb->callables[MEDIA_SEEK], &ret, 1, &offset)) {
		vlc_seek_fallback(base);
		return;
	}
	r->result = (int) zval_get_long(&ret);
	zval_ptr_dtor(&ret);
}

static int vlc_seek_tramp(void *opaque, uint64_t offset)
{
	vlc_seek_req r = {{vlc_seek_serve, vlc_seek_fallback, opaque}, offset, -1};

	vlc_queue_call(&r.base, VLC_SLOW_DEADLINE_MS);
	return r.result;
}

static void vlc_close_tramp(void *opaque)
{
	vlc_queue_post(&vlc_post_new(opaque, MEDIA_CLOSE, 0, 0)->base);
}

/* libvlc_MediaFreed, on whichever thread dropped the media's last reference. */
static void vlc_media_freed_tramp(const libvlc_event_t *ev, void *data)
{
	(void) ev;
	vlc_cb_dead(data);
}

PHP_FUNCTION(libvlc_media_new_callbacks)
{
	zval *zi;
	zend_fcall_info open_fci, read_fci, seek_fci = empty_fcall_info, close_fci = empty_fcall_info;
	zend_fcall_info_cache open_fcc, read_fcc, seek_fcc = empty_fcall_info_cache, close_fcc = empty_fcall_info_cache;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
		Z_PARAM_FUNC(open_fci, open_fcc)
		Z_PARAM_FUNC(read_fci, read_fcc)
		Z_PARAM_FUNC_OR_NULL(seek_fci, seek_fcc)
		Z_PARAM_FUNC_OR_NULL(close_fci, close_fcc)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, instance, zi, 1);

	vlc_cb *cb = vlc_cb_new(VLC_CB_MEDIA, NULL);
	vlc_cb_set(cb, MEDIA_OPEN, &open_fci);
	vlc_cb_set(cb, MEDIA_READ, &read_fci);
	vlc_cb_set(cb, MEDIA_SEEK, &seek_fci);
	vlc_cb_set(cb, MEDIA_CLOSE, &close_fci);
	libvlc_media_t *media = libvlc_media_new_callbacks(instance, vlc_open_tramp, vlc_read_tramp,
		vlc_cb_has(cb, MEDIA_SEEK) ? vlc_seek_tramp : NULL, vlc_close_tramp, cb);
	/* libvlc holds the record as long as the media lives, wherever it is released: libvlc_MediaFreed says when. */
	if (media != NULL && libvlc_event_attach(libvlc_media_event_manager(media), libvlc_MediaFreed, vlc_media_freed_tramp, cb) != 0) {
		libvlc_media_release(media);
		media = NULL;
	}
	if (media == NULL) {
		vlc_cb_free(cb);
	} else {
		cb->target = cb->owner = media;
	}
	vlc_box_new(return_value, media, vlc_ce_libvlc_media_t);
}

/* ---- audio callbacks --------------------------------------------------- */

enum { AUDIO_PLAY, AUDIO_PAUSE, AUDIO_RESUME, AUDIO_FLUSH, AUDIO_DRAIN, AUDIO_VOLUME, AUDIO_SETUP, AUDIO_CLEANUP };

typedef struct {
	unsigned bytes_per_frame;  /* 0 until a format is known */
} vlc_audio_native;

/* Bytes per sample of a libvlc audio format code: S16N, S32N, FL32, FL64, U8, S24N ... */
static unsigned vlc_sample_bytes(const char *format)
{
	if (strncmp(format, "FL64", 4) == 0) {
		return 8;
	}
	if (strstr(format, "16") != NULL) {
		return 2;
	}
	if (strstr(format, "24") != NULL) {
		return 3;
	}
	if (strstr(format, "32") != NULL) {
		return 4;
	}
	if (strncmp(format, "U8", 2) == 0 || strncmp(format, "S8", 2) == 0) {
		return 1;
	}
	return 0;
}

static void vlc_play_tramp(void *data, const void *samples, unsigned count, int64_t pts)
{
	vlc_cb *cb = data;
	size_t len = (size_t) count * ((vlc_audio_native *) cb->native)->bytes_per_frame;
	vlc_post_req *r = vlc_post_new(data, AUDIO_PLAY, 3, len);

	memcpy(r->bytes, samples, len);
	r->bytes_at = 0;
	ZVAL_LONG(&r->argv[1], count);
	ZVAL_LONG(&r->argv[2], pts);
	vlc_queue_post(&r->base);
}

static void vlc_audio_pts_post(void *data, int slot, int64_t pts)
{
	vlc_post_req *r = vlc_post_new(data, slot, 1, 0);

	ZVAL_LONG(&r->argv[0], pts);
	vlc_queue_post(&r->base);
}

static void vlc_pause_tramp(void *data, int64_t pts) { vlc_audio_pts_post(data, AUDIO_PAUSE, pts); }
static void vlc_resume_tramp(void *data, int64_t pts) { vlc_audio_pts_post(data, AUDIO_RESUME, pts); }
static void vlc_flush_tramp(void *data, int64_t pts) { vlc_audio_pts_post(data, AUDIO_FLUSH, pts); }
static void vlc_drain_tramp(void *data) { vlc_queue_post(&vlc_post_new(data, AUDIO_DRAIN, 0, 0)->base); }
static void vlc_audio_cleanup_tramp(void *data) { vlc_queue_post(&vlc_post_new(data, AUDIO_CLEANUP, 0, 0)->base); }

static void vlc_volume_tramp(void *data, float volume, bool mute)
{
	vlc_post_req *r = vlc_post_new(data, AUDIO_VOLUME, 2, 0);

	ZVAL_DOUBLE(&r->argv[0], volume);
	ZVAL_BOOL(&r->argv[1], mute);
	vlc_queue_post(&r->base);
}

typedef struct {
	vlc_req base;
	char *format;
	unsigned *rate, *channels;
	int result;
} vlc_setup_req;

static void vlc_setup_fallback(vlc_req *base)
{
	((vlc_setup_req *) base)->result = -1;
}

static void vlc_setup_serve(vlc_req *base)
{
	vlc_setup_req *r = (vlc_setup_req *) base;
	zval argv[3], ret;

	ZVAL_NEW_REF(&argv[0], &EG(uninitialized_zval));
	ZVAL_STRINGL(Z_REFVAL(argv[0]), r->format, strnlen(r->format, 4));
	ZVAL_NEW_REF(&argv[1], &EG(uninitialized_zval));
	ZVAL_LONG(Z_REFVAL(argv[1]), *r->rate);
	ZVAL_NEW_REF(&argv[2], &EG(uninitialized_zval));
	ZVAL_LONG(Z_REFVAL(argv[2]), *r->channels);

	if (vlc_cb_invoke(&base->cb->callables[AUDIO_SETUP], &ret, 3, argv)) {
		zend_string *format = zval_get_string(Z_REFVAL(argv[0]));
		memset(r->format, 0, 4);
		memcpy(r->format, ZSTR_VAL(format), ZSTR_LEN(format) < 4 ? ZSTR_LEN(format) : 4);
		zend_string_release(format);
		*r->rate = (unsigned) zval_get_long(Z_REFVAL(argv[1]));
		*r->channels = (unsigned) zval_get_long(Z_REFVAL(argv[2]));
		r->result = (int) zval_get_long(&ret);
		((vlc_audio_native *) base->cb->native)->bytes_per_frame = vlc_sample_bytes(r->format) * *r->channels;
		zval_ptr_dtor(&ret);
	} else {
		vlc_setup_fallback(base);
	}
	for (int i = 0; i < 3; i++) {
		zval_ptr_dtor(&argv[i]);
	}
}

static int vlc_setup_tramp(void **data, char *format, unsigned *rate, unsigned *channels)
{
	vlc_setup_req r = {{vlc_setup_serve, vlc_setup_fallback, *data}, format, rate, channels, -1};

	vlc_queue_call(&r.base, VLC_SLOW_DEADLINE_MS);
	return r.result;
}

/* The player's audio record; a new one starts at libvlc's default format, S16N stereo. */
static vlc_cb *vlc_audio_cb(libvlc_media_player_t *mp)
{
	bool fresh = vlc_cb_find(VLC_CB_AUDIO, mp, 0, NULL) == NULL;
	vlc_cb *cb = vlc_player_cb(VLC_CB_AUDIO, mp, sizeof(vlc_audio_native));

	if (fresh) {
		((vlc_audio_native *) cb->native)->bytes_per_frame = 2 * 2;
	}
	return cb;
}

PHP_FUNCTION(libvlc_audio_set_callbacks)
{
	zval *zmp;
	zend_fcall_info fci[5] = {empty_fcall_info, empty_fcall_info, empty_fcall_info, empty_fcall_info, empty_fcall_info};
	zend_fcall_info_cache fcc[5] = {empty_fcall_info_cache, empty_fcall_info_cache, empty_fcall_info_cache, empty_fcall_info_cache, empty_fcall_info_cache};

	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(zmp, vlc_ce_libvlc_media_player_t)
		Z_PARAM_FUNC(fci[0], fcc[0])
		Z_PARAM_FUNC_OR_NULL(fci[1], fcc[1])
		Z_PARAM_FUNC_OR_NULL(fci[2], fcc[2])
		Z_PARAM_FUNC_OR_NULL(fci[3], fcc[3])
		Z_PARAM_FUNC_OR_NULL(fci[4], fcc[4])
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_player_t, mp, zmp, 1);

	vlc_cb *cb = vlc_audio_cb(mp);
	for (int i = 0; i < 5; i++) {
		vlc_cb_set(cb, AUDIO_PLAY + i, &fci[i]);
	}
	libvlc_audio_set_callbacks(mp, vlc_play_tramp,
		vlc_cb_has(cb, AUDIO_PAUSE) ? vlc_pause_tramp : NULL,
		vlc_cb_has(cb, AUDIO_RESUME) ? vlc_resume_tramp : NULL,
		vlc_cb_has(cb, AUDIO_FLUSH) ? vlc_flush_tramp : NULL,
		vlc_cb_has(cb, AUDIO_DRAIN) ? vlc_drain_tramp : NULL, cb);
}

PHP_FUNCTION(libvlc_audio_set_volume_callback)
{
	zval *zmp;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zmp, vlc_ce_libvlc_media_player_t)
		Z_PARAM_FUNC_OR_NULL(fci, fcc)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_player_t, mp, zmp, 1);

	vlc_cb *cb = vlc_audio_cb(mp);
	vlc_cb_set(cb, AUDIO_VOLUME, &fci);
	libvlc_audio_set_volume_callback(mp, vlc_cb_has(cb, AUDIO_VOLUME) ? vlc_volume_tramp : NULL);
}

PHP_FUNCTION(libvlc_audio_set_format_callbacks)
{
	zval *zmp;
	zend_fcall_info setup, cleanup = empty_fcall_info;
	zend_fcall_info_cache setup_fcc, cleanup_fcc = empty_fcall_info_cache;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(zmp, vlc_ce_libvlc_media_player_t)
		Z_PARAM_FUNC(setup, setup_fcc)
		Z_PARAM_FUNC_OR_NULL(cleanup, cleanup_fcc)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_player_t, mp, zmp, 1);

	vlc_cb *cb = vlc_audio_cb(mp);
	vlc_cb_set(cb, AUDIO_SETUP, &setup);
	vlc_cb_set(cb, AUDIO_CLEANUP, &cleanup);
	libvlc_audio_set_format_callbacks(mp, vlc_setup_tramp, vlc_cb_has(cb, AUDIO_CLEANUP) ? vlc_audio_cleanup_tramp : NULL);
}

PHP_FUNCTION(libvlc_audio_set_format)
{
	zval *zmp;
	zend_string *format;
	zend_long rate, channels;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(zmp, vlc_ce_libvlc_media_player_t)
		Z_PARAM_STR(format)
		Z_PARAM_LONG(rate)
		Z_PARAM_LONG(channels)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_player_t, mp, zmp, 1);

	vlc_cb *cb = vlc_audio_cb(mp);
	((vlc_audio_native *) cb->native)->bytes_per_frame = vlc_sample_bytes(ZSTR_VAL(format)) * (unsigned) channels;
	libvlc_audio_set_format(mp, ZSTR_VAL(format), (unsigned) rate, (unsigned) channels);
}

/* ---- video callbacks --------------------------------------------------- */

enum { VIDEO_LOCK, VIDEO_UNLOCK, VIDEO_DISPLAY, VIDEO_SETUP, VIDEO_CLEANUP };

#define VLC_PLANES 5

typedef struct {
	size_t size;     /* bytes of one picture in the current format; 0 until known */
	size_t planes[VLC_PLANES]; /* bytes of each plane, in order; all 0 until known */
	size_t scratch_size;
	void *scratch;   /* where libvlc renders when the lock callable does not answer */
} vlc_video_native;

static void vlc_video_native_free(void *native)
{
	if (native != NULL) {
		free(((vlc_video_native *) native)->scratch);
	}
	free(native);
}

static vlc_cb *vlc_video_cb(libvlc_media_player_t *mp)
{
	vlc_cb *cb = vlc_player_cb(VLC_CB_VIDEO, mp, sizeof(vlc_video_native));

	cb->native_free = vlc_video_native_free;
	return cb;
}

typedef struct {
	vlc_req base;
	void **planes;
	void *picture;
} vlc_lock_req;

static void vlc_lock_fallback(vlc_req *base)
{
	vlc_lock_req *r = (vlc_lock_req *) base;
	vlc_video_native *v = base->cb->native;

	/* Format unknown: vmem's defaults (RV16, 320 x 200, pitch 640). */
	size_t size = v->size > 0 ? v->size : 640 * 200;

	if (v->scratch_size != size) {
		free(v->scratch);
		v->scratch = calloc(1, size);
		v->scratch_size = v->scratch != NULL ? size : 0;
	}
	/* libvlc writes every plane of the picture: each gets its own part of the scratch picture. */
	size_t at = 0;
	for (int i = 0; i < VLC_PLANES; i++) {
		r->planes[i] = v->scratch != NULL && (i == 0 || v->planes[i] > 0) ? (char *) v->scratch + at : NULL;
		at += v->planes[i];
	}
	r->picture = v->scratch;
}

static void vlc_lock_serve(vlc_req *base)
{
	vlc_lock_req *r = (vlc_lock_req *) base;
	zval ret, *plane;
	int i = 0;

	if (!vlc_cb_invoke(&base->cb->callables[VIDEO_LOCK], &ret, 0, NULL)) {
		vlc_lock_fallback(base);
		return;
	}
	if (Z_TYPE(ret) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL(ret), plane) {
			if (i == VLC_PLANES) {
				break;
			}
			r->planes[i++] = (void *) (uintptr_t) zval_get_long(plane);
		} ZEND_HASH_FOREACH_END();
	}
	zval_ptr_dtor(&ret);
	if (i == 0) {
		vlc_lock_fallback(base);
		return;
	}
	r->picture = r->planes[0];
}

static void *vlc_lock_tramp(void *opaque, void **planes)
{
	vlc_lock_req r = {{vlc_lock_serve, vlc_lock_fallback, opaque}, planes, NULL};

	vlc_queue_call(&r.base, VLC_FRAME_DEADLINE_MS);
	return r.picture;
}

static void vlc_unlock_tramp(void *opaque, void *picture, void *const *planes)
{
	vlc_post_req *r = vlc_post_new(opaque, VIDEO_UNLOCK, 2, sizeof(void *) * VLC_PLANES);

	memcpy(r->bytes, planes, sizeof(void *) * VLC_PLANES);
	ZVAL_LONG(&r->argv[0], (zend_long) (uintptr_t) picture);
	r->bytes_at = 1;
	r->as_planes = true;
	vlc_queue_post(&r->base);
}

static void vlc_display_tramp(void *opaque, void *picture)
{
	vlc_post_req *r = vlc_post_new(opaque, VIDEO_DISPLAY, 1, 0);

	ZVAL_LONG(&r->argv[0], (zend_long) (uintptr_t) picture);
	vlc_queue_post(&r->base);
}

static void vlc_video_cleanup_tramp(void *opaque) { vlc_queue_post(&vlc_post_new(opaque, VIDEO_CLEANUP, 0, 0)->base); }

typedef struct {
	vlc_req base;
	char *chroma;
	unsigned *width, *height, *pitches, *lines;
	unsigned result;
} vlc_format_req;

static void vlc_format_fallback(vlc_req *base)
{
	((vlc_format_req *) base)->result = 0;
}

static void vlc_list_of(zval *list, const unsigned *values)
{
	array_init_size(list, VLC_PLANES);
	for (int i = 0; i < VLC_PLANES; i++) {
		add_next_index_long(list, values[i]);
	}
}

static void vlc_list_into(zval *list, unsigned *values)
{
	zval *v;
	int i = 0;

	memset(values, 0, sizeof(unsigned) * VLC_PLANES);
	if (Z_TYPE_P(list) != IS_ARRAY) {
		return;
	}
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(list), v) {
		if (i == VLC_PLANES) {
			break;
		}
		values[i++] = (unsigned) zval_get_long(v);
	} ZEND_HASH_FOREACH_END();
}

static void vlc_format_serve(vlc_req *base)
{
	vlc_format_req *r = (vlc_format_req *) base;
	zval argv[5], ret;

	ZVAL_NEW_REF(&argv[0], &EG(uninitialized_zval));
	ZVAL_STRINGL(Z_REFVAL(argv[0]), r->chroma, strnlen(r->chroma, 4));
	ZVAL_NEW_REF(&argv[1], &EG(uninitialized_zval));
	ZVAL_LONG(Z_REFVAL(argv[1]), *r->width);
	ZVAL_NEW_REF(&argv[2], &EG(uninitialized_zval));
	ZVAL_LONG(Z_REFVAL(argv[2]), *r->height);
	ZVAL_NEW_REF(&argv[3], &EG(uninitialized_zval));
	vlc_list_of(Z_REFVAL(argv[3]), r->pitches);
	ZVAL_NEW_REF(&argv[4], &EG(uninitialized_zval));
	vlc_list_of(Z_REFVAL(argv[4]), r->lines);

	if (vlc_cb_invoke(&base->cb->callables[VIDEO_SETUP], &ret, 5, argv)) {
		zend_string *chroma = zval_get_string(Z_REFVAL(argv[0]));
		memset(r->chroma, 0, 4);
		memcpy(r->chroma, ZSTR_VAL(chroma), ZSTR_LEN(chroma) < 4 ? ZSTR_LEN(chroma) : 4);
		zend_string_release(chroma);
		*r->width = (unsigned) zval_get_long(Z_REFVAL(argv[1]));
		*r->height = (unsigned) zval_get_long(Z_REFVAL(argv[2]));
		vlc_list_into(Z_REFVAL(argv[3]), r->pitches);
		vlc_list_into(Z_REFVAL(argv[4]), r->lines);
		r->result = (unsigned) zval_get_long(&ret);
		vlc_video_native *v = base->cb->native;
		v->size = 0;
		for (int i = 0; i < VLC_PLANES; i++) {
			v->planes[i] = (size_t) r->pitches[i] * r->lines[i];
			v->size += v->planes[i];
		}
		zval_ptr_dtor(&ret);
	} else {
		vlc_format_fallback(base);
	}
	for (int i = 0; i < 5; i++) {
		zval_ptr_dtor(&argv[i]);
	}
}

static unsigned vlc_format_tramp(void **opaque, char *chroma, unsigned *width, unsigned *height, unsigned *pitches, unsigned *lines)
{
	vlc_format_req r = {{vlc_format_serve, vlc_format_fallback, *opaque}, chroma, width, height, pitches, lines, 0};

	vlc_queue_call(&r.base, VLC_SLOW_DEADLINE_MS);
	return r.result;
}

PHP_FUNCTION(libvlc_video_set_callbacks)
{
	zval *zmp;
	zend_fcall_info fci[3] = {empty_fcall_info, empty_fcall_info, empty_fcall_info};
	zend_fcall_info_cache fcc[3] = {empty_fcall_info_cache, empty_fcall_info_cache, empty_fcall_info_cache};

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(zmp, vlc_ce_libvlc_media_player_t)
		Z_PARAM_FUNC(fci[0], fcc[0])
		Z_PARAM_FUNC_OR_NULL(fci[1], fcc[1])
		Z_PARAM_FUNC_OR_NULL(fci[2], fcc[2])
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_player_t, mp, zmp, 1);

	vlc_cb *cb = vlc_video_cb(mp);
	for (int i = 0; i < 3; i++) {
		vlc_cb_set(cb, VIDEO_LOCK + i, &fci[i]);
	}
	libvlc_video_set_callbacks(mp, vlc_lock_tramp,
		vlc_cb_has(cb, VIDEO_UNLOCK) ? vlc_unlock_tramp : NULL,
		vlc_cb_has(cb, VIDEO_DISPLAY) ? vlc_display_tramp : NULL, cb);
}

PHP_FUNCTION(libvlc_video_set_format_callbacks)
{
	zval *zmp;
	zend_fcall_info setup, cleanup = empty_fcall_info;
	zend_fcall_info_cache setup_fcc, cleanup_fcc = empty_fcall_info_cache;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(zmp, vlc_ce_libvlc_media_player_t)
		Z_PARAM_FUNC(setup, setup_fcc)
		Z_PARAM_FUNC_OR_NULL(cleanup, cleanup_fcc)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_player_t, mp, zmp, 1);

	vlc_cb *cb = vlc_video_cb(mp);
	vlc_cb_set(cb, VIDEO_SETUP, &setup);
	vlc_cb_set(cb, VIDEO_CLEANUP, &cleanup);
	libvlc_video_set_format_callbacks(mp, vlc_format_tramp, vlc_cb_has(cb, VIDEO_CLEANUP) ? vlc_video_cleanup_tramp : NULL);
}

PHP_FUNCTION(libvlc_video_set_format)
{
	zval *zmp;
	zend_string *chroma;
	zend_long width, height, pitch;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(zmp, vlc_ce_libvlc_media_player_t)
		Z_PARAM_STR(chroma)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_LONG(pitch)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_player_t, mp, zmp, 1);

	/* A planar chroma's further planes follow the first: three planes' worth covers every libvlc chroma. */
	vlc_cb *cb = vlc_video_cb(mp);
	vlc_video_native *v = cb->native;
	for (int i = 0; i < VLC_PLANES; i++) {
		v->planes[i] = i < 3 ? (size_t) pitch * (size_t) height : 0;
	}
	v->size = v->planes[0] * 3;
	libvlc_video_set_format(mp, ZSTR_VAL(chroma), (unsigned) width, (unsigned) height, (unsigned) pitch);
}

/* ---- dialogs ----------------------------------------------------------- */

enum { DIALOG_ERROR, DIALOG_LOGIN, DIALOG_QUESTION, DIALOG_PROGRESS, DIALOG_CANCEL, DIALOG_UPDATE };

#define VLC_DIALOG_ARGS 8

/* A posted dialog call: its arguments by a shape string (S string, L int, D float, B bool, H dialog id), strings copied after the struct. */
typedef struct {
	vlc_req base;
	int slot;
	const char *shape;
	union { const char *s; zend_long l; double d; bool b; void *h; } args[VLC_DIALOG_ARGS];
	char strings[];
} vlc_dialog_req;

static void vlc_dialog_serve(vlc_req *base)
{
	vlc_dialog_req *r = (vlc_dialog_req *) base;
	zval argv[VLC_DIALOG_ARGS], ret;
	uint32_t n = (uint32_t) strlen(r->shape);

	if (!vlc_cb_has(base->cb, r->slot)) {
		return;
	}
	for (uint32_t i = 0; i < n; i++) {
		switch (r->shape[i]) {
			case 'S': vlc_string_or_null(&argv[i], r->args[i].s); break;
			case 'L': ZVAL_LONG(&argv[i], r->args[i].l); break;
			case 'D': ZVAL_DOUBLE(&argv[i], r->args[i].d); break;
			case 'B': ZVAL_BOOL(&argv[i], r->args[i].b); break;
			case 'H': vlc_box(&argv[i], r->args[i].h, vlc_ce_libvlc_dialog_id); break;
		}
	}
	if (vlc_cb_invoke(&base->cb->callables[r->slot], &ret, n, argv)) {
		zval_ptr_dtor(&ret);
	}
	for (uint32_t i = 0; i < n; i++) {
		zval_ptr_dtor(&argv[i]);
	}
	if (r->slot == DIALOG_CANCEL) {
		vlc_release(r->args[0].h, vlc_ce_libvlc_dialog_id); /* libvlc drops the dialog after cancel */
	}
}

static void vlc_dialog_post(void *data, int slot, const char *shape, ...)
{
	va_list ap;
	size_t total = 0, n = strlen(shape);

	va_start(ap, shape);
	for (size_t i = 0; i < n; i++) {
		switch (shape[i]) {
			case 'S': { const char *s = va_arg(ap, const char *); total += s != NULL ? strlen(s) + 1 : 0; break; }
			case 'L': case 'B': (void) va_arg(ap, int); break;
			case 'D': (void) va_arg(ap, double); break;
			case 'H': (void) va_arg(ap, void *); break;
		}
	}
	va_end(ap);

	vlc_dialog_req *r = calloc(1, sizeof(*r) + total);
	char *out = r->strings;
	r->base.serve = vlc_dialog_serve;
	r->base.fallback = vlc_nop;
	r->base.cb = data;
	r->slot = slot;
	r->shape = shape;
	va_start(ap, shape);
	for (size_t i = 0; i < n; i++) {
		switch (shape[i]) {
			case 'S': {
				const char *s = va_arg(ap, const char *);
				if (s != NULL) {
					size_t len = strlen(s) + 1;
					memcpy(out, s, len);
					r->args[i].s = out;
					out += len;
				}
				break;
			}
			case 'L': r->args[i].l = va_arg(ap, int); break;
			case 'B': r->args[i].b = va_arg(ap, int) != 0; break;
			case 'D': r->args[i].d = va_arg(ap, double); break;
			case 'H': r->args[i].h = va_arg(ap, void *); break;
		}
	}
	va_end(ap);
	vlc_queue_post(&r->base);
}

static void vlc_dialog_error_tramp(void *p_data, const char *psz_title, const char *psz_text)
{
	vlc_dialog_post(p_data, DIALOG_ERROR, "SS", psz_title, psz_text);
}

static void vlc_dialog_login_tramp(void *p_data, libvlc_dialog_id *p_id, const char *psz_title, const char *psz_text, const char *psz_default_username, bool b_ask_store)
{
	vlc_dialog_post(p_data, DIALOG_LOGIN, "HSSSB", p_id, psz_title, psz_text, psz_default_username, (int) b_ask_store);
}

static void vlc_dialog_question_tramp(void *p_data, libvlc_dialog_id *p_id, const char *psz_title, const char *psz_text, libvlc_dialog_question_type i_type, const char *psz_cancel, const char *psz_action1, const char *psz_action2)
{
	vlc_dialog_post(p_data, DIALOG_QUESTION, "HSSLSSS", p_id, psz_title, psz_text, (int) i_type, psz_cancel, psz_action1, psz_action2);
}

static void vlc_dialog_progress_tramp(void *p_data, libvlc_dialog_id *p_id, const char *psz_title, const char *psz_text, bool b_indeterminate, float f_position, const char *psz_cancel)
{
	vlc_dialog_post(p_data, DIALOG_PROGRESS, "HSSBDS", p_id, psz_title, psz_text, (int) b_indeterminate, (double) f_position, psz_cancel);
}

static void vlc_dialog_cancel_tramp(void *p_data, libvlc_dialog_id *p_id)
{
	vlc_dialog_post(p_data, DIALOG_CANCEL, "H", p_id);
}

static void vlc_dialog_update_tramp(void *p_data, libvlc_dialog_id *p_id, float f_position, const char *psz_text)
{
	vlc_dialog_post(p_data, DIALOG_UPDATE, "HDS", p_id, (double) f_position, psz_text);
}

PHP_FUNCTION(libvlc_dialog_set_callbacks)
{
	zval *zi, *zcbs;
	static const char *const fields[] = {"pf_display_error", "pf_display_login", "pf_display_question", "pf_display_progress", "pf_cancel", "pf_update_progress"};

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(zcbs, vlc_ce_libvlc_dialog_cbs)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_instance, zi, 1);

	vlc_cb *old = vlc_cb_find(VLC_CB_DIALOG, p_instance, 0, NULL);
	if (zcbs == NULL) {
		libvlc_dialog_set_callbacks(p_instance, NULL, NULL);
	} else {
		vlc_cb *cb = vlc_cb_new(VLC_CB_DIALOG, p_instance);
		libvlc_dialog_cbs *cbs = calloc(1, sizeof(*cbs));
		cb->native = cbs;
		for (int i = 0; i < 6; i++) {
			zval *v = zend_read_property(vlc_ce_libvlc_dialog_cbs, Z_OBJ_P(zcbs), fields[i], strlen(fields[i]), true, NULL);
			if (Z_TYPE_P(v) == IS_OBJECT) {
				ZVAL_COPY(&cb->callables[i], v);
			}
		}
		cbs->pf_display_error = vlc_cb_has(cb, DIALOG_ERROR) ? vlc_dialog_error_tramp : NULL;
		cbs->pf_display_login = vlc_cb_has(cb, DIALOG_LOGIN) ? vlc_dialog_login_tramp : NULL;
		cbs->pf_display_question = vlc_cb_has(cb, DIALOG_QUESTION) ? vlc_dialog_question_tramp : NULL;
		cbs->pf_display_progress = vlc_cb_has(cb, DIALOG_PROGRESS) ? vlc_dialog_progress_tramp : NULL;
		cbs->pf_cancel = vlc_cb_has(cb, DIALOG_CANCEL) ? vlc_dialog_cancel_tramp : NULL;
		cbs->pf_update_progress = vlc_cb_has(cb, DIALOG_UPDATE) ? vlc_dialog_update_tramp : NULL;
		libvlc_dialog_set_callbacks(p_instance, cbs, cb);
	}
	if (old != NULL) {
		vlc_cb_free(old);
	}
}

/* ---- record lifetimes ------------------------------------------------------ */

/* A live record of kind (any kind when 0) whose owner is owner. */
static vlc_cb *vlc_cb_owned(int kind, void *owner)
{
	for (vlc_cb *cb = VLC_G(cbs); cb != NULL; cb = cb->next) {
		if (!cb->dead && cb->owner == owner && (kind == 0 || cb->kind == kind)) {
			return cb;
		}
	}
	return NULL;
}

void vlc_events_gone(void *owner)
{
	vlc_cb *cb;

	/* libvlc_event_detach() takes the manager's lock, which libvlc holds while it calls listeners. */
	while ((cb = vlc_cb_owned(VLC_CB_EVENT, owner)) != NULL) {
		libvlc_event_detach(cb->target, (libvlc_event_type_t) cb->event_type, vlc_event_tramp, cb);
		vlc_cb_free(cb);
	}
}

void vlc_owner_releasing(void *ptr, zend_class_entry *ce)
{
	vlc_cb *cb;

	vlc_events_gone(ptr);
	if (ce == vlc_ce_libvlc_instance_t) {
		/* Each unset returns once no call of the old callback is running. */
		if ((cb = vlc_cb_find(VLC_CB_LOG, ptr, 0, NULL)) != NULL) {
			libvlc_log_unset(ptr);
			vlc_cb_free(cb);
		}
		if ((cb = vlc_cb_find(VLC_CB_EXIT, ptr, 0, NULL)) != NULL) {
			libvlc_set_exit_handler(ptr, NULL, NULL);
			vlc_cb_free(cb);
		}
		if ((cb = vlc_cb_find(VLC_CB_DIALOG, ptr, 0, NULL)) != NULL) {
			libvlc_dialog_set_callbacks(ptr, NULL, NULL);
			vlc_cb_free(cb);
		}
	} else if (ce == vlc_ce_libvlc_media_list_player_t) {
		void *mp = zend_hash_index_find_ptr(&VLC_G(held), (zend_ulong) (uintptr_t) ptr);
		if (mp != NULL) {
			vlc_ref_releasing(mp, vlc_ce_libvlc_media_player_t);
		}
	}
}

void vlc_owner_dead(void *ptr, zend_class_entry *ce)
{
	vlc_cb *cb;

	if (ce == vlc_ce_libvlc_media_player_t) {
		/* libvlc destroyed the player (its count includes list players' holds): nothing of it calls any more. */
		while ((cb = vlc_cb_owned(0, ptr)) != NULL) {
			vlc_cb_free(cb);
		}
	} else if (ce == vlc_ce_libvlc_media_list_player_t) {
		zend_ulong key = (zend_ulong) (uintptr_t) ptr;
		void *mp = zend_hash_index_find_ptr(&VLC_G(held), key);
		if (mp != NULL) {
			zend_hash_index_del(&VLC_G(held), key);
			vlc_ref_drop(mp, vlc_ce_libvlc_media_player_t);
		}
	}
}

void vlc_register_callbacks(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
