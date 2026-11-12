/*
 * The handle and value classes. A list element's properties are its C struct's fields, read from
 * the native struct on every access through one table per class.
 */
#include "runtime.h"
#include "../stubs/types_arginfo.h"

zend_class_entry *vlc_ce_libvlc_instance_t;
zend_class_entry *vlc_ce_libvlc_media_t;
zend_class_entry *vlc_ce_libvlc_media_player_t;
zend_class_entry *vlc_ce_libvlc_media_list_t;
zend_class_entry *vlc_ce_libvlc_media_list_player_t;
zend_class_entry *vlc_ce_libvlc_media_library_t;
zend_class_entry *vlc_ce_libvlc_media_discoverer_t;
zend_class_entry *vlc_ce_libvlc_renderer_discoverer_t;
zend_class_entry *vlc_ce_libvlc_renderer_item_t;
zend_class_entry *vlc_ce_libvlc_event_manager_t;
zend_class_entry *vlc_ce_libvlc_equalizer_t;
zend_class_entry *vlc_ce_libvlc_log_t;
zend_class_entry *vlc_ce_libvlc_dialog_id;
zend_class_entry *vlc_ce_libvlc_audio_output_t;
zend_class_entry *vlc_ce_libvlc_audio_output_device_t;
zend_class_entry *vlc_ce_libvlc_track_description_t;
zend_class_entry *vlc_ce_libvlc_module_description_t;
zend_class_entry *vlc_ce_libvlc_media_track_t;
zend_class_entry *vlc_ce_libvlc_audio_track_t;
zend_class_entry *vlc_ce_libvlc_video_track_t;
zend_class_entry *vlc_ce_libvlc_subtitle_track_t;
zend_class_entry *vlc_ce_libvlc_title_description_t;
zend_class_entry *vlc_ce_libvlc_chapter_description_t;
zend_class_entry *vlc_ce_libvlc_media_slave_t;
zend_class_entry *vlc_ce_libvlc_media_discoverer_description_t;
zend_class_entry *vlc_ce_libvlc_rd_description_t;
zend_class_entry *vlc_ce_libvlc_video_viewpoint_t;
zend_class_entry *vlc_ce_libvlc_media_stats_t;
zend_class_entry *vlc_ce_libvlc_event_t;
zend_class_entry *vlc_ce_libvlc_dialog_cbs;

VLC_POINTER_METHODS(libvlc_instance_t)
VLC_POINTER_METHODS(libvlc_media_t)
VLC_POINTER_METHODS(libvlc_media_player_t)
VLC_POINTER_METHODS(libvlc_media_list_t)
VLC_POINTER_METHODS(libvlc_media_list_player_t)
VLC_POINTER_METHODS(libvlc_media_library_t)
VLC_POINTER_METHODS(libvlc_media_discoverer_t)
VLC_POINTER_METHODS(libvlc_renderer_discoverer_t)
VLC_POINTER_METHODS(libvlc_renderer_item_t)
VLC_POINTER_METHODS(libvlc_event_manager_t)
VLC_POINTER_METHODS(libvlc_equalizer_t)
VLC_POINTER_METHODS(libvlc_log_t)
VLC_POINTER_METHODS(libvlc_dialog_id)
VLC_POINTER_METHODS(libvlc_audio_output_t)
VLC_POINTER_METHODS(libvlc_audio_output_device_t)
VLC_POINTER_METHODS(libvlc_track_description_t)
VLC_POINTER_METHODS(libvlc_module_description_t)
VLC_POINTER_METHODS(libvlc_media_track_t)
VLC_POINTER_METHODS(libvlc_audio_track_t)
VLC_POINTER_METHODS(libvlc_video_track_t)
VLC_POINTER_METHODS(libvlc_subtitle_track_t)
VLC_POINTER_METHODS(libvlc_title_description_t)
VLC_POINTER_METHODS(libvlc_chapter_description_t)
VLC_POINTER_METHODS(libvlc_media_slave_t)
VLC_POINTER_METHODS(libvlc_media_discoverer_description_t)
VLC_POINTER_METHODS(libvlc_rd_description_t)

typedef enum {
	VLC_F_INT,       /* int, and enums */
	VLC_F_UINT,      /* unsigned, uint32_t */
	VLC_F_I64,       /* int64_t */
	VLC_F_STR,       /* char *, null for NULL */
	VLC_F_HANDLE,    /* pointer to another list element, null for NULL */
	VLC_F_TRACK,     /* libvlc_media_track_t's union member: null unless i_type is `match` */
	VLC_F_VIEWPOINT  /* embedded libvlc_video_viewpoint_t, as a value copy */
} vlc_field_kind;

typedef struct {
	const char *name;
	size_t offset;
	vlc_field_kind kind;
	zend_class_entry **ce;
	int match;
} vlc_field;

#define F(st, field, kind) { #field, offsetof(st, field), kind, NULL, 0 }
#define H(st, field, ce) { #field, offsetof(st, field), VLC_F_HANDLE, &ce, 0 }
#define T(field, ce, type) { #field, offsetof(libvlc_media_track_t, field), VLC_F_TRACK, &ce, type }
#define END { NULL, 0, 0, NULL, 0 }

static const vlc_field vlc_audio_output_fields[] = {
	F(libvlc_audio_output_t, psz_name, VLC_F_STR),
	F(libvlc_audio_output_t, psz_description, VLC_F_STR),
	H(libvlc_audio_output_t, p_next, vlc_ce_libvlc_audio_output_t),
	END
};

static const vlc_field vlc_audio_output_device_fields[] = {
	H(libvlc_audio_output_device_t, p_next, vlc_ce_libvlc_audio_output_device_t),
	F(libvlc_audio_output_device_t, psz_device, VLC_F_STR),
	F(libvlc_audio_output_device_t, psz_description, VLC_F_STR),
	END
};

static const vlc_field vlc_track_description_fields[] = {
	F(libvlc_track_description_t, i_id, VLC_F_INT),
	F(libvlc_track_description_t, psz_name, VLC_F_STR),
	H(libvlc_track_description_t, p_next, vlc_ce_libvlc_track_description_t),
	END
};

static const vlc_field vlc_module_description_fields[] = {
	F(libvlc_module_description_t, psz_name, VLC_F_STR),
	F(libvlc_module_description_t, psz_shortname, VLC_F_STR),
	F(libvlc_module_description_t, psz_longname, VLC_F_STR),
	F(libvlc_module_description_t, psz_help, VLC_F_STR),
	H(libvlc_module_description_t, p_next, vlc_ce_libvlc_module_description_t),
	END
};

static const vlc_field vlc_media_track_fields[] = {
	F(libvlc_media_track_t, i_codec, VLC_F_UINT),
	F(libvlc_media_track_t, i_original_fourcc, VLC_F_UINT),
	F(libvlc_media_track_t, i_id, VLC_F_INT),
	F(libvlc_media_track_t, i_type, VLC_F_INT),
	F(libvlc_media_track_t, i_profile, VLC_F_INT),
	F(libvlc_media_track_t, i_level, VLC_F_INT),
	T(audio, vlc_ce_libvlc_audio_track_t, libvlc_track_audio),
	T(video, vlc_ce_libvlc_video_track_t, libvlc_track_video),
	T(subtitle, vlc_ce_libvlc_subtitle_track_t, libvlc_track_text),
	F(libvlc_media_track_t, i_bitrate, VLC_F_UINT),
	F(libvlc_media_track_t, psz_language, VLC_F_STR),
	F(libvlc_media_track_t, psz_description, VLC_F_STR),
	END
};

static const vlc_field vlc_audio_track_fields[] = {
	F(libvlc_audio_track_t, i_channels, VLC_F_UINT),
	F(libvlc_audio_track_t, i_rate, VLC_F_UINT),
	END
};

static const vlc_field vlc_video_track_fields[] = {
	F(libvlc_video_track_t, i_height, VLC_F_UINT),
	F(libvlc_video_track_t, i_width, VLC_F_UINT),
	F(libvlc_video_track_t, i_sar_num, VLC_F_UINT),
	F(libvlc_video_track_t, i_sar_den, VLC_F_UINT),
	F(libvlc_video_track_t, i_frame_rate_num, VLC_F_UINT),
	F(libvlc_video_track_t, i_frame_rate_den, VLC_F_UINT),
	F(libvlc_video_track_t, i_orientation, VLC_F_INT),
	F(libvlc_video_track_t, i_projection, VLC_F_INT),
	F(libvlc_video_track_t, pose, VLC_F_VIEWPOINT),
	END
};

static const vlc_field vlc_subtitle_track_fields[] = {
	F(libvlc_subtitle_track_t, psz_encoding, VLC_F_STR),
	END
};

static const vlc_field vlc_title_description_fields[] = {
	F(libvlc_title_description_t, i_duration, VLC_F_I64),
	F(libvlc_title_description_t, psz_name, VLC_F_STR),
	F(libvlc_title_description_t, i_flags, VLC_F_UINT),
	END
};

static const vlc_field vlc_chapter_description_fields[] = {
	F(libvlc_chapter_description_t, i_time_offset, VLC_F_I64),
	F(libvlc_chapter_description_t, i_duration, VLC_F_I64),
	F(libvlc_chapter_description_t, psz_name, VLC_F_STR),
	END
};

static const vlc_field vlc_media_slave_fields[] = {
	F(libvlc_media_slave_t, psz_uri, VLC_F_STR),
	F(libvlc_media_slave_t, i_type, VLC_F_INT),
	F(libvlc_media_slave_t, i_priority, VLC_F_UINT),
	END
};

static const vlc_field vlc_media_discoverer_description_fields[] = {
	F(libvlc_media_discoverer_description_t, psz_name, VLC_F_STR),
	F(libvlc_media_discoverer_description_t, psz_longname, VLC_F_STR),
	F(libvlc_media_discoverer_description_t, i_cat, VLC_F_INT),
	END
};

static const vlc_field vlc_rd_description_fields[] = {
	F(libvlc_rd_description_t, psz_name, VLC_F_STR),
	F(libvlc_rd_description_t, psz_longname, VLC_F_STR),
	END
};

/* One handlers copy per list-element class: its read_property knows its field table. */
typedef struct {
	zend_object_handlers handlers;
	const vlc_field *fields;
} vlc_element_handlers;

#define VLC_ELEMENT_CLASSES 13
static vlc_element_handlers vlc_elements[VLC_ELEMENT_CLASSES];

static const vlc_field *vlc_fields_of(zend_object *obj)
{
	return ((const vlc_element_handlers *) obj->handlers)->fields;
}

static const vlc_field *vlc_field_named(const vlc_field *fields, zend_string *name)
{
	for (; fields->name != NULL; fields++) {
		if (zend_string_equals_cstr(name, fields->name, strlen(fields->name))) {
			return fields;
		}
	}
	return NULL;
}

void vlc_viewpoint_to(const libvlc_video_viewpoint_t *in, zval *rv)
{
	zend_class_entry *ce = vlc_ce_libvlc_video_viewpoint_t;

	object_init_ex(rv, ce);
	zend_update_property_double(ce, Z_OBJ_P(rv), "f_yaw", sizeof("f_yaw") - 1, in->f_yaw);
	zend_update_property_double(ce, Z_OBJ_P(rv), "f_pitch", sizeof("f_pitch") - 1, in->f_pitch);
	zend_update_property_double(ce, Z_OBJ_P(rv), "f_roll", sizeof("f_roll") - 1, in->f_roll);
	zend_update_property_double(ce, Z_OBJ_P(rv), "f_field_of_view", sizeof("f_field_of_view") - 1, in->f_field_of_view);
}

static void vlc_field_read(const vlc_field *f, const char *base, zval *rv)
{
	const void *at = base + f->offset;

	switch (f->kind) {
		case VLC_F_INT:
			ZVAL_LONG(rv, *(const int *) at);
			break;
		case VLC_F_UINT:
			ZVAL_LONG(rv, *(const unsigned *) at);
			break;
		case VLC_F_I64:
			ZVAL_LONG(rv, *(const int64_t *) at);
			break;
		case VLC_F_STR:
			if (*(char * const *) at == NULL) {
				ZVAL_NULL(rv);
			} else {
				ZVAL_STRING(rv, *(char * const *) at);
			}
			break;
		case VLC_F_HANDLE:
			vlc_box(rv, *(void * const *) at, *f->ce);
			break;
		case VLC_F_TRACK:
			if (((const libvlc_media_track_t *) base)->i_type != (libvlc_track_type_t) f->match) {
				ZVAL_NULL(rv);
			} else {
				vlc_box(rv, *(void * const *) at, *f->ce);
			}
			break;
		case VLC_F_VIEWPOINT:
			vlc_viewpoint_to((const libvlc_video_viewpoint_t *) at, rv);
			break;
	}
}

static zval *vlc_element_read(zend_object *obj, zend_string *name, int type, void **cache_slot, zval *rv)
{
	const vlc_field *f = vlc_field_named(vlc_fields_of(obj), name);
	const char *base = vlc_handle_from(obj)->ptr;

	if (f != NULL && base != NULL) {
		vlc_field_read(f, base, rv);
		return rv;
	}
	return zend_std_read_property(obj, name, type, cache_slot, rv);
}

static int vlc_element_has(zend_object *obj, zend_string *name, int check_empty, void **cache_slot)
{
	zval rv, *value;
	int result;

	if (vlc_field_named(vlc_fields_of(obj), name) == NULL || vlc_handle_from(obj)->ptr == NULL) {
		return zend_std_has_property(obj, name, check_empty, cache_slot);
	}
	value = vlc_element_read(obj, name, BP_VAR_IS, cache_slot, &rv);
	result = check_empty == ZEND_PROPERTY_NOT_EMPTY ? zend_is_true(value) : Z_TYPE_P(value) != IS_NULL;
	zval_ptr_dtor(&rv);

	return result;
}

static zend_object_handlers *vlc_element_handlers_for(int i, const vlc_field *fields)
{
	vlc_element_handlers *h = &vlc_elements[i];

	memcpy(&h->handlers, vlc_handlers(), sizeof(zend_object_handlers));
	h->handlers.read_property = vlc_element_read;
	h->handlers.has_property = vlc_element_has;
	h->fields = fields;

	return &h->handlers;
}

#define HANDLE(cls) \
	vlc_ce_##cls = register_class_##cls(); \
	vlc_handle_setup(vlc_ce_##cls, NULL)

#define ELEMENT(i, cls, fields) \
	vlc_ce_##cls = register_class_##cls(); \
	vlc_handle_setup(vlc_ce_##cls, vlc_element_handlers_for(i, fields))

void vlc_register_types(void)
{
	HANDLE(libvlc_instance_t);
	HANDLE(libvlc_media_t);
	HANDLE(libvlc_media_player_t);
	HANDLE(libvlc_media_list_t);
	HANDLE(libvlc_media_list_player_t);
	HANDLE(libvlc_media_library_t);
	HANDLE(libvlc_media_discoverer_t);
	HANDLE(libvlc_renderer_discoverer_t);
	HANDLE(libvlc_renderer_item_t);
	HANDLE(libvlc_event_manager_t);
	HANDLE(libvlc_equalizer_t);
	HANDLE(libvlc_log_t);
	HANDLE(libvlc_dialog_id);

	ELEMENT(0, libvlc_audio_output_t, vlc_audio_output_fields);
	ELEMENT(1, libvlc_audio_output_device_t, vlc_audio_output_device_fields);
	ELEMENT(2, libvlc_track_description_t, vlc_track_description_fields);
	ELEMENT(3, libvlc_module_description_t, vlc_module_description_fields);
	ELEMENT(4, libvlc_media_track_t, vlc_media_track_fields);
	ELEMENT(5, libvlc_audio_track_t, vlc_audio_track_fields);
	ELEMENT(6, libvlc_video_track_t, vlc_video_track_fields);
	ELEMENT(7, libvlc_subtitle_track_t, vlc_subtitle_track_fields);
	ELEMENT(8, libvlc_title_description_t, vlc_title_description_fields);
	ELEMENT(9, libvlc_chapter_description_t, vlc_chapter_description_fields);
	ELEMENT(10, libvlc_media_slave_t, vlc_media_slave_fields);
	ELEMENT(11, libvlc_media_discoverer_description_t, vlc_media_discoverer_description_fields);
	ELEMENT(12, libvlc_rd_description_t, vlc_rd_description_fields);

	vlc_ce_libvlc_video_viewpoint_t = register_class_libvlc_video_viewpoint_t();
	vlc_ce_libvlc_media_stats_t = register_class_libvlc_media_stats_t();
	vlc_ce_libvlc_event_t = register_class_libvlc_event_t();
	vlc_ce_libvlc_dialog_cbs = register_class_libvlc_dialog_cbs();
}
