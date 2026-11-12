#include "runtime.h"

volatile bool vlc_instance_seen = false;

static zend_object_handlers vlc_handle_handlers;

static zend_object *vlc_create_object(zend_class_entry *ce)
{
	vlc_handle *intern = zend_object_alloc(sizeof(vlc_handle), ce);

	zend_object_std_init(&intern->std, ce);
	object_properties_init(&intern->std, ce);
	intern->std.handlers = ce->default_object_handlers;
	intern->ptr = NULL;

	return &intern->std;
}

/*
 * The identity table key: address and class. libvlc embeds some objects at their parent's address
 * (a media's event manager is the media's first member), so the address alone is not an identity.
 */
typedef struct {
	void *ptr;
	zend_class_entry *ce;
} vlc_box_key;

#define VLC_KEY(k, p, c) vlc_box_key k; memset(&k, 0, sizeof(k)); k.ptr = (p); k.ce = (c)
#define VLC_KEY_ARGS(k) (const char *) &(k), sizeof(k)

static void vlc_free_object(zend_object *object)
{
	vlc_handle *intern = vlc_handle_from(object);

	if (intern->ptr != NULL) {
		VLC_KEY(key, intern->ptr, object->ce);
		zend_hash_str_del(&VLC_G(boxes), VLC_KEY_ARGS(key));
		intern->ptr = NULL;
	}
	zend_object_std_dtor(object);
}

zend_object_handlers *vlc_handlers(void)
{
	static bool ready = false;

	if (!ready) {
		memcpy(&vlc_handle_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
		vlc_handle_handlers.offset = XtOffsetOf(vlc_handle, std);
		vlc_handle_handlers.free_obj = vlc_free_object;
		vlc_handle_handlers.clone_obj = NULL;
		ready = true;
	}
	return &vlc_handle_handlers;
}

void vlc_handle_setup(zend_class_entry *ce, zend_object_handlers *handlers)
{
	ce->create_object = vlc_create_object;
	ce->default_object_handlers = handlers != NULL ? handlers : vlc_handlers();
	ce->ce_flags |= ZEND_ACC_NOT_SERIALIZABLE;
}

void vlc_box(zval *rv, void *ptr, zend_class_entry *ce)
{
	zend_object *existing;

	if (ptr == NULL) {
		ZVAL_NULL(rv);
		return;
	}

	VLC_KEY(key, ptr, ce);
	existing = zend_hash_str_find_ptr(&VLC_G(boxes), VLC_KEY_ARGS(key));
	if (existing != NULL) {
		ZVAL_OBJ_COPY(rv, existing);
		return;
	}

	object_init_ex(rv, ce);
	vlc_handle_from(Z_OBJ_P(rv))->ptr = ptr;
	zend_hash_str_update_ptr(&VLC_G(boxes), VLC_KEY_ARGS(key), Z_OBJ_P(rv));
}

void *vlc_handle_arg(zval *zv, uint32_t arg_num)
{
	void *ptr = vlc_handle_from(Z_OBJ_P(zv))->ptr;

	/* libvlc dereferences every handle these functions are given; a released one is NULL. */
	if (!VLC_PROBE_OFF("vlc-released-handle") && ptr == NULL) {
		zend_argument_value_error(arg_num, "%s has been released", ZSTR_VAL(Z_OBJCE_P(zv)->name)); /* binding:vlc-released-handle */
	}
	return ptr;
}

bool vlc_list_count(zend_long given, uint32_t length, uint32_t count_arg, uint32_t list_arg)
{
	/* libvlc reads count elements of the C array built from the list. */
	if (!VLC_PROBE_OFF("vlc-list-count") && (given < 0 || (zend_ulong) given > length)) {
		zend_argument_value_error(count_arg, "must be between 0 and the length of argument #%u ($%s)", list_arg, get_active_function_arg_name(list_arg)); /* binding:vlc-list-count */
		return false;
	}
	return true;
}

void **vlc_list_ptrs(HashTable *list, zend_long count, zend_class_entry *ce, uint32_t arg)
{
	void **out = calloc((size_t) count + 1, sizeof(void *));
	zval *element;
	zend_long i = 0;

	ZEND_HASH_FOREACH_VAL(list, element) {
		if (i == count) {
			break;
		}
		if (Z_TYPE_P(element) != IS_OBJECT || Z_OBJCE_P(element) != ce) {
			zend_argument_type_error(arg, "must be a list of %s, %s given at index " ZEND_LONG_FMT, ZSTR_VAL(ce->name), zend_zval_value_name(element), i);
			free(out);
			return NULL;
		}
		out[i] = vlc_handle_arg(element, arg);
		if (EG(exception)) {
			free(out);
			return NULL;
		}
		i++;
	} ZEND_HASH_FOREACH_END();

	return out;
}

const char **vlc_strings_from(HashTable *list, zend_long count, uint32_t arg)
{
	const char **out = ecalloc((size_t) count + 1, sizeof(char *));
	zval *element;
	zend_long i = 0;

	ZEND_HASH_FOREACH_VAL(list, element) {
		if (i == count) {
			break;
		}
		if (Z_TYPE_P(element) != IS_STRING) {
			zend_argument_type_error(arg, "must be a list of string, %s given at index " ZEND_LONG_FMT, zend_zval_value_name(element), i);
			efree(out);
			return NULL;
		}
		out[i++] = Z_STRVAL_P(element);
	} ZEND_HASH_FOREACH_END();

	return out;
}

void vlc_list_box(zval *rv, void **ptrs, unsigned count, zend_class_entry *ce)
{
	array_init_size(rv, count);
	for (unsigned i = 0; i < count; i++) {
		zval element;

		vlc_box(&element, ptrs[i], ce);
		add_next_index_zval(rv, &element);
	}
}

void vlc_string_or_null(zval *rv, const char *s)
{
	if (s == NULL) {
		ZVAL_NULL(rv);
	} else {
		ZVAL_STRING(rv, s);
	}
}

void vlc_owned_string(zval *rv, char *s)
{
	vlc_string_or_null(rv, s);
	libvlc_free(s);
}

void vlc_ref_add(void *ptr, zend_class_entry *ce)
{
	if (ptr == NULL) {
		return;
	}
	VLC_KEY(key, ptr, ce);
	zval *count = zend_hash_str_find(&VLC_G(refs), VLC_KEY_ARGS(key));
	if (count != NULL) {
		Z_LVAL_P(count)++;
	} else {
		/* A handle boxed but never counted (fromPointer, an event's pointer) is one reference already. */
		zval n;
		ZVAL_LONG(&n, zend_hash_str_exists(&VLC_G(boxes), VLC_KEY_ARGS(key)) ? 2 : 1);
		zend_hash_str_add(&VLC_G(refs), VLC_KEY_ARGS(key), &n);
	}
}

void vlc_box_new(zval *rv, void *ptr, zend_class_entry *ce)
{
	vlc_ref_add(ptr, ce);
	vlc_box(rv, ptr, ce);
}

void vlc_box_em(zval *rv, void *em, void *owner)
{
	vlc_box(rv, em, vlc_ce_libvlc_event_manager_t);
	if (Z_TYPE_P(rv) == IS_OBJECT) {
		vlc_handle_from(Z_OBJ_P(rv))->owner = owner;
	}
}

void vlc_ref_releasing(void *ptr, zend_class_entry *ce)
{
	VLC_KEY(key, ptr, ce);
	zval *count = zend_hash_str_find(&VLC_G(refs), VLC_KEY_ARGS(key));

	if (count == NULL || Z_LVAL_P(count) <= 1) {
		vlc_owner_releasing(ptr, ce);
	}
}

void vlc_ref_drop(void *ptr, zend_class_entry *ce)
{
	VLC_KEY(key, ptr, ce);
	zval *count = zend_hash_str_find(&VLC_G(refs), VLC_KEY_ARGS(key));

	if (count != NULL && --Z_LVAL_P(count) > 0) {
		return;
	}
	zend_hash_str_del(&VLC_G(refs), VLC_KEY_ARGS(key));
	vlc_release(ptr, ce);
	vlc_owner_dead(ptr, ce);
}

void *vlc_held_set(void *mlp, void *mi)
{
	zend_ulong key = (zend_ulong) (uintptr_t) mlp;
	void *old = zend_hash_index_find_ptr(&VLC_G(held), key);

	if (mi != NULL) {
		vlc_ref_add(mi, vlc_ce_libvlc_media_player_t);
		zend_hash_index_update_ptr(&VLC_G(held), key, mi);
	} else {
		zend_hash_index_del(&VLC_G(held), key);
	}
	if (old != NULL) {
		vlc_ref_releasing(old, vlc_ce_libvlc_media_player_t);
	}
	return old;
}

void vlc_held_released(void *old)
{
	if (old != NULL) {
		vlc_ref_drop(old, vlc_ce_libvlc_media_player_t);
	}
}

void vlc_held_seen(void *mlp, void *mi)
{
	zend_ulong key = (zend_ulong) (uintptr_t) mlp;

	if (mi != NULL && !zend_hash_index_exists(&VLC_G(held), key)) {
		vlc_ref_add(mi, vlc_ce_libvlc_media_player_t);
		zend_hash_index_add_ptr(&VLC_G(held), key, mi);
	}
}

void vlc_release(void *ptr, zend_class_entry *ce)
{
	VLC_KEY(key, ptr, ce);
	zend_object *existing = zend_hash_str_find_ptr(&VLC_G(boxes), VLC_KEY_ARGS(key));

	if (existing != NULL) {
		vlc_handle_from(existing)->ptr = NULL;
		zend_hash_str_del(&VLC_G(boxes), VLC_KEY_ARGS(key));
	}
}

#ifdef VLC_PROBES
bool vlc_probe_off(const char *id)
{
	const char *off = getenv("VLC_PROBE_OFF");

	return off != NULL && strcmp(off, id) == 0;
}
#endif
