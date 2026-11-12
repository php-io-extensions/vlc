#ifndef VLC_RUNTIME_H
#define VLC_RUNTIME_H

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdbool.h>
#include <stdint.h>
#include "php.h"
#include "zend_exceptions.h"
#include "php_vlc.h"

#include <vlc/vlc.h>
#include <vlc/libvlc_version.h>

ZEND_BEGIN_MODULE_GLOBALS(vlc)
	HashTable boxes;                 /* (native address, class) => zend_object*, live handles only, not refcounted */
	HashTable refs;                  /* (native address, class) => the libvlc references this thread holds */
	struct vlc_queue *queue;         /* this request's callback queue (src/queue.c) */
	struct vlc_cb *cbs;              /* this request's callback records */
	HashTable held;                  /* list player address => the player it holds (a reference counted in refs) */
ZEND_END_MODULE_GLOBALS(vlc)

ZEND_EXTERN_MODULE_GLOBALS(vlc)
#define VLC_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(vlc, v)

typedef struct {
	void *ptr;                       /* the native object; NULL once released */
	void *owner;                     /* event managers: the object they belong to, when the binding boxed them from it */
	zend_object std;
} vlc_handle;

static zend_always_inline vlc_handle *vlc_handle_from(zend_object *obj)
{
	return (vlc_handle *) ((char *) obj - XtOffsetOf(vlc_handle, std));
}

/* Handle object model: not constructable from PHP, not cloneable, not serializable. */
void vlc_handle_setup(zend_class_entry *ce, zend_object_handlers *handlers);

/* The handlers every handle class starts from. */
zend_object_handlers *vlc_handlers(void);

/* The PHP object for ptr in class ce, the one already boxed when there is one; null for NULL. */
void vlc_box(zval *rv, void *ptr, zend_class_entry *ce);

/* The native object goes away: its PHP object of class ce reads 0 from pointer() from now on. */
void vlc_release(void *ptr, zend_class_entry *ce);

/*
 * Reference-counted objects (instance, media, player, media list, list player, media library,
 * renderer item): the references this thread was handed. vlc_ref_add on creation, *_retain /
 * _hold and the getters libvlc documents as returning a new reference; vlc_ref_drop on *_release,
 * and the drop that reaches zero releases the handle. An object the binding never counted
 * (fromPointer, an event's pointer) counts as one reference. A list player's player counts the
 * list player's hold too, so a player's count reaches zero only when libvlc destroys it.
 *
 * Every *_release of a counted object runs vlc_ref_releasing before libvlc's release and
 * vlc_ref_drop after it.
 */
void vlc_ref_add(void *ptr, zend_class_entry *ce);
void vlc_ref_drop(void *ptr, zend_class_entry *ce);
void vlc_ref_releasing(void *ptr, zend_class_entry *ce);

/*
 * Callback record lifetimes (src/callbacks.c). vlc_owner_releasing: the binding's last reference
 * to ptr is about to go and libvlc still holds ptr, so its event callables are detached and an
 * instance's log, exit and dialog callables are unset, then freed. vlc_owner_dead: libvlc
 * destroyed ptr, so its remaining records go. vlc_events_gone: detaches and frees the event
 * callables on the event managers of owner.
 */
void vlc_owner_releasing(void *ptr, zend_class_entry *ce);
void vlc_owner_dead(void *ptr, zend_class_entry *ce);
void vlc_events_gone(void *owner);

/*
 * libvlc_media_list_player_set_media_player: vlc_held_set before libvlc's call (mi is held from
 * now on; returns the player the list player held), vlc_held_released after it.
 * libvlc_media_list_player_get_media_player: vlc_held_seen with the player it returned.
 */
void *vlc_held_set(void *mlp, void *mi);
void vlc_held_released(void *old);
void vlc_held_seen(void *mlp, void *mi);

/* vlc_box for a result that is a new reference: boxes it and counts it. */
void vlc_box_new(zval *rv, void *ptr, zend_class_entry *ce);

/* vlc_box for the event manager of owner. */
void vlc_box_em(zval *rv, void *em, void *owner);

/*
 * pointer() and fromPointer() for a handle class: the address as is, 0 once released;
 * fromPointer(0) is null. __construct is private, so PHP refuses `new` before its body runs.
 */
#define VLC_POINTER_METHODS(cls) \
	ZEND_METHOD(cls, pointer) { ZEND_PARSE_PARAMETERS_NONE(); RETURN_LONG((zend_long) (uintptr_t) vlc_handle_from(Z_OBJ_P(ZEND_THIS))->ptr); } \
	ZEND_METHOD(cls, fromPointer) { zend_long p; ZEND_PARSE_PARAMETERS_START(1, 1) Z_PARAM_LONG(p) ZEND_PARSE_PARAMETERS_END(); \
		vlc_box(return_value, (void *) (uintptr_t) p, zend_get_called_scope(execute_data)); } \
	ZEND_METHOD(cls, __construct) { ZEND_PARSE_PARAMETERS_NONE(); }

extern zend_class_entry *vlc_ce_libvlc_instance_t;
extern zend_class_entry *vlc_ce_libvlc_media_t;
extern zend_class_entry *vlc_ce_libvlc_media_player_t;
extern zend_class_entry *vlc_ce_libvlc_media_list_t;
extern zend_class_entry *vlc_ce_libvlc_media_list_player_t;
extern zend_class_entry *vlc_ce_libvlc_media_library_t;
extern zend_class_entry *vlc_ce_libvlc_media_discoverer_t;
extern zend_class_entry *vlc_ce_libvlc_renderer_discoverer_t;
extern zend_class_entry *vlc_ce_libvlc_renderer_item_t;
extern zend_class_entry *vlc_ce_libvlc_event_manager_t;
extern zend_class_entry *vlc_ce_libvlc_equalizer_t;
extern zend_class_entry *vlc_ce_libvlc_log_t;
extern zend_class_entry *vlc_ce_libvlc_dialog_id;
extern zend_class_entry *vlc_ce_libvlc_audio_output_t;
extern zend_class_entry *vlc_ce_libvlc_audio_output_device_t;
extern zend_class_entry *vlc_ce_libvlc_track_description_t;
extern zend_class_entry *vlc_ce_libvlc_module_description_t;
extern zend_class_entry *vlc_ce_libvlc_media_track_t;
extern zend_class_entry *vlc_ce_libvlc_audio_track_t;
extern zend_class_entry *vlc_ce_libvlc_video_track_t;
extern zend_class_entry *vlc_ce_libvlc_subtitle_track_t;
extern zend_class_entry *vlc_ce_libvlc_title_description_t;
extern zend_class_entry *vlc_ce_libvlc_chapter_description_t;
extern zend_class_entry *vlc_ce_libvlc_media_slave_t;
extern zend_class_entry *vlc_ce_libvlc_media_discoverer_description_t;
extern zend_class_entry *vlc_ce_libvlc_rd_description_t;
extern zend_class_entry *vlc_ce_libvlc_video_viewpoint_t;
extern zend_class_entry *vlc_ce_libvlc_media_stats_t;
extern zend_class_entry *vlc_ce_libvlc_event_t;
extern zend_class_entry *vlc_ce_libvlc_dialog_cbs;

/*
 * A handle parameter libvlc dereferences: its native pointer, or a ValueError when the handle was
 * released (site vlc-released-handle). Callers RETURN_THROWS on EG(exception).
 */
void *vlc_handle_arg(zval *zv, uint32_t arg_num);
#define VLC_ARG(type, var, zv, n) type *var = vlc_handle_arg(zv, n); if (EG(exception)) { RETURN_THROWS(); }

/* A list's C count, given as its own parameter: false (and a ValueError) when it is past the list (site vlc-list-count). */
bool vlc_list_count(zend_long given, uint32_t length, uint32_t count_arg, uint32_t list_arg);

/*
 * The first count elements of a list of handles of class ce, as a malloc'd C array of their
 * pointers: the shape libvlc's *_release(array, count) frees with free(). NULL on a TypeError, or
 * on a released element (vlc_handle_arg).
 */
void **vlc_list_ptrs(HashTable *list, zend_long count, zend_class_entry *ce, uint32_t arg);

/* The first count strings of a list as an emalloc'd C array (NULL-terminated); NULL on a TypeError. */
const char **vlc_strings_from(HashTable *list, zend_long count, uint32_t arg);

/* A list of the handles of class ce for count C pointers. */
void vlc_list_box(zval *rv, void **ptrs, unsigned count, zend_class_entry *ce);

/* A const char * result: a copy, null for NULL. */
void vlc_string_or_null(zval *rv, const char *s);

/* A char * result the caller frees: a copy, null for NULL; libvlc_free()s s. */
void vlc_owned_string(zval *rv, char *s);

/* libvlc_video_viewpoint_t <-> its value class. */
void vlc_viewpoint_to(const libvlc_video_viewpoint_t *in, zval *rv);

void vlc_register_types(void);
void vlc_register_constants(int module_number);

/*
 * The probe switch. A kept refusal site reads `if (!VLC_PROBE_OFF("<id>") && (<check>))`.
 * A build configured with --enable-vlc-probes lets env VLC_PROBE_OFF=<id> turn that one site
 * off, so tests/Probes can show the crash the site prevents; any other build compiles the
 * switch out.
 */
#ifdef VLC_PROBES
bool vlc_probe_off(const char *id);
# define VLC_PROBE_OFF(id) vlc_probe_off(id)
#else
# define VLC_PROBE_OFF(id) 0
#endif

/*
 * libvlc creates its per-thread error key in the first libvlc_new(); before that, libvlc_errmsg()
 * reads an unrelated thread-specific slot and libvlc_clearerr() aborts. libvlc_new sets this
 * once it returns an instance; libvlc_clearerr refuses until then (site vlc-no-instance).
 */
extern volatile bool vlc_instance_seen;

void vlc_register_libvlc(void);
void vlc_register_gen_player(void);
void vlc_register_player(void);
void vlc_register_gen_lists(void);
void vlc_register_gen_discovery(void);
void vlc_register_discovery(void);
void vlc_register_gen_vlm(void);
void vlc_register_vlm(void);
void vlc_register_gen_dialog(void);
void vlc_register_callbacks(void);

#endif
