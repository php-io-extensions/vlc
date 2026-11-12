/*
 * The bound libvlc functions of libvlc.h and libvlc_media.h, by the C names.
 */
#include "runtime.h"
#include "../stubs/libvlc_arginfo.h"

/* libvlc.h */

PHP_FUNCTION(libvlc_errmsg)
{
	ZEND_PARSE_PARAMETERS_NONE();
	vlc_string_or_null(return_value, libvlc_errmsg());
}

PHP_FUNCTION(libvlc_clearerr)
{
	ZEND_PARSE_PARAMETERS_NONE();
	if (!VLC_PROBE_OFF("vlc-no-instance") && !vlc_instance_seen) {
		zend_throw_error(NULL, "libvlc_clearerr(): no libvlc_instance_t yet: libvlc sets up its error state in the first libvlc_new()"); /* binding:vlc-no-instance */
		RETURN_THROWS();
	}
	libvlc_clearerr();
}

PHP_FUNCTION(libvlc_printerr)
{
	zval *args = NULL, fname, formatted;
	uint32_t argc = 0;
	zend_string *fmt;

	ZEND_PARSE_PARAMETERS_START(1, -1)
		Z_PARAM_STR(fmt)
		Z_PARAM_VARIADIC('*', args, argc)
	ZEND_PARSE_PARAMETERS_END();
	if (!VLC_PROBE_OFF("vlc-printerr-no-instance") && !vlc_instance_seen) {
		zend_throw_error(NULL, "libvlc_printerr(): no libvlc_instance_t yet: libvlc sets up its error state in the first libvlc_new()"); /* binding:vlc-printerr-no-instance */
		RETURN_THROWS();
	}

	zval *params = safe_emalloc(argc + 1, sizeof(zval), 0);
	ZVAL_STR(&params[0], fmt);
	for (uint32_t i = 0; i < argc; i++) {
		ZVAL_COPY_VALUE(&params[i + 1], &args[i]);
	}
	ZVAL_STRING(&fname, "sprintf");
	call_user_function(NULL, NULL, &fname, &formatted, argc + 1, params);
	zval_ptr_dtor(&fname);
	efree(params);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETVAL_STRING(libvlc_printerr("%s", Z_STRVAL(formatted)));
	zval_ptr_dtor(&formatted);
}

PHP_FUNCTION(libvlc_new)
{
	zend_long argc;
	HashTable *argv;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(argc)
		Z_PARAM_ARRAY_HT(argv)
	ZEND_PARSE_PARAMETERS_END();

	if (!vlc_list_count(argc, zend_hash_num_elements(argv), 1, 2)) {
		RETURN_THROWS();
	}
	const char **c_argv = vlc_strings_from(argv, argc, 2);
	if (c_argv == NULL) {
		RETURN_THROWS();
	}
	libvlc_instance_t *instance = libvlc_new((int) argc, c_argv);
	efree(c_argv);
	if (instance != NULL) {
		vlc_instance_seen = true;
	}
	vlc_box_new(return_value, instance, vlc_ce_libvlc_instance_t);
}

PHP_FUNCTION(libvlc_release)
{
	zval *zi;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_instance, zi, 1);
	vlc_ref_releasing(p_instance, vlc_ce_libvlc_instance_t);
	libvlc_release(p_instance);
	vlc_ref_drop(p_instance, vlc_ce_libvlc_instance_t);
}

PHP_FUNCTION(libvlc_retain)
{
	zval *zi;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_instance, zi, 1);
	vlc_ref_add(p_instance, vlc_ce_libvlc_instance_t);
	libvlc_retain(p_instance);
}

PHP_FUNCTION(libvlc_add_intf)
{
	zval *zi;
	zend_string *name;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
		Z_PARAM_STR_OR_NULL(name)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_instance, zi, 1);
	RETURN_LONG(libvlc_add_intf(p_instance, name != NULL ? ZSTR_VAL(name) : NULL));
}

PHP_FUNCTION(libvlc_set_user_agent)
{
	zval *zi;
	zend_string *name, *http;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
		Z_PARAM_STR(name)
		Z_PARAM_STR(http)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_instance, zi, 1);
	libvlc_set_user_agent(p_instance, ZSTR_VAL(name), ZSTR_VAL(http));
}

PHP_FUNCTION(libvlc_set_app_id)
{
	zval *zi;
	zend_string *id, *version, *icon;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
		Z_PARAM_STR(id)
		Z_PARAM_STR(version)
		Z_PARAM_STR(icon)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_instance, zi, 1);
	libvlc_set_app_id(p_instance, ZSTR_VAL(id), ZSTR_VAL(version), ZSTR_VAL(icon));
}

PHP_FUNCTION(libvlc_free)
{
	zend_long ptr;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(ptr)
	ZEND_PARSE_PARAMETERS_END();
	libvlc_free((void *) (uintptr_t) ptr);
}

PHP_FUNCTION(libvlc_event_type_name)
{
	zend_long event_type;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(event_type)
	ZEND_PARSE_PARAMETERS_END();
	vlc_string_or_null(return_value, libvlc_event_type_name((libvlc_event_type_t) event_type));
}

PHP_FUNCTION(libvlc_module_description_list_release)
{
	zval *zl;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zl, vlc_ce_libvlc_module_description_t)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_module_description_t, p_list, zl, 1);
	for (libvlc_module_description_t *node = p_list; node != NULL; node = node->p_next) {
		vlc_release(node, vlc_ce_libvlc_module_description_t);
	}
	libvlc_module_description_list_release(p_list);
}

PHP_FUNCTION(libvlc_audio_filter_list_get)
{
	zval *zi;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_instance, zi, 1);
	vlc_box(return_value, libvlc_audio_filter_list_get(p_instance), vlc_ce_libvlc_module_description_t);
}

PHP_FUNCTION(libvlc_video_filter_list_get)
{
	zval *zi;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_instance, zi, 1);
	vlc_box(return_value, libvlc_video_filter_list_get(p_instance), vlc_ce_libvlc_module_description_t);
}

PHP_FUNCTION(libvlc_clock)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG(libvlc_clock());
}

/* libvlc_media.h */

/* A function taking the instance and one string. */
#define INSTANCE_AND_STRING(s) \
	zval *zi; \
	zend_string *s; \
	ZEND_PARSE_PARAMETERS_START(2, 2) \
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t) \
		Z_PARAM_STR(s) \
	ZEND_PARSE_PARAMETERS_END(); \
	VLC_ARG(libvlc_instance_t, p_instance, zi, 1)

PHP_FUNCTION(libvlc_media_new_location)
{
	INSTANCE_AND_STRING(psz_mrl);
	vlc_box_new(return_value, libvlc_media_new_location(p_instance, ZSTR_VAL(psz_mrl)), vlc_ce_libvlc_media_t);
}

PHP_FUNCTION(libvlc_media_new_path)
{
	INSTANCE_AND_STRING(path);
	vlc_box_new(return_value, libvlc_media_new_path(p_instance, ZSTR_VAL(path)), vlc_ce_libvlc_media_t);
}

PHP_FUNCTION(libvlc_media_new_as_node)
{
	INSTANCE_AND_STRING(psz_name);
	vlc_box_new(return_value, libvlc_media_new_as_node(p_instance, ZSTR_VAL(psz_name)), vlc_ce_libvlc_media_t);
}

PHP_FUNCTION(libvlc_media_new_fd)
{
	zval *zi;
	zend_long fd;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
		Z_PARAM_LONG(fd)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_instance, zi, 1);
	vlc_box_new(return_value, libvlc_media_new_fd(p_instance, (int) fd), vlc_ce_libvlc_media_t);
}

/* A function whose only parameter is the media. */
#define MEDIA_ARG_ONLY(zm) \
	zval *zm; \
	ZEND_PARSE_PARAMETERS_START(1, 1) \
		Z_PARAM_OBJECT_OF_CLASS(zm, vlc_ce_libvlc_media_t) \
	ZEND_PARSE_PARAMETERS_END(); \
	VLC_ARG(libvlc_media_t, p_md, zm, 1)

PHP_FUNCTION(libvlc_media_add_option)
{
	zval *zm;
	zend_string *options;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zm, vlc_ce_libvlc_media_t)
		Z_PARAM_STR(options)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_t, p_md, zm, 1);
	libvlc_media_add_option(p_md, ZSTR_VAL(options));
}

PHP_FUNCTION(libvlc_media_add_option_flag)
{
	zval *zm;
	zend_string *options;
	zend_long flags;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(zm, vlc_ce_libvlc_media_t)
		Z_PARAM_STR(options)
		Z_PARAM_LONG(flags)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_t, p_md, zm, 1);
	libvlc_media_add_option_flag(p_md, ZSTR_VAL(options), (unsigned) flags);
}

PHP_FUNCTION(libvlc_media_retain)
{
	MEDIA_ARG_ONLY(zm);
	vlc_ref_add(p_md, vlc_ce_libvlc_media_t);
	libvlc_media_retain(p_md);
}

PHP_FUNCTION(libvlc_media_release)
{
	MEDIA_ARG_ONLY(zm);
	vlc_ref_releasing(p_md, vlc_ce_libvlc_media_t);
	libvlc_media_release(p_md);
	vlc_ref_drop(p_md, vlc_ce_libvlc_media_t);
}

PHP_FUNCTION(libvlc_media_get_mrl)
{
	MEDIA_ARG_ONLY(zm);
	vlc_owned_string(return_value, libvlc_media_get_mrl(p_md));
}

PHP_FUNCTION(libvlc_media_duplicate)
{
	MEDIA_ARG_ONLY(zm);
	vlc_box_new(return_value, libvlc_media_duplicate(p_md), vlc_ce_libvlc_media_t);
}

PHP_FUNCTION(libvlc_media_get_meta)
{
	zval *zm;
	zend_long meta;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zm, vlc_ce_libvlc_media_t)
		Z_PARAM_LONG(meta)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_t, p_md, zm, 1);
	vlc_owned_string(return_value, libvlc_media_get_meta(p_md, (libvlc_meta_t) meta));
}

PHP_FUNCTION(libvlc_media_set_meta)
{
	zval *zm;
	zend_long meta;
	zend_string *value;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(zm, vlc_ce_libvlc_media_t)
		Z_PARAM_LONG(meta)
		Z_PARAM_STR_OR_NULL(value)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_t, p_md, zm, 1);
	libvlc_media_set_meta(p_md, (libvlc_meta_t) meta, value != NULL ? ZSTR_VAL(value) : NULL);
}

PHP_FUNCTION(libvlc_media_save_meta)
{
	MEDIA_ARG_ONLY(zm);
	RETURN_LONG(libvlc_media_save_meta(p_md));
}

PHP_FUNCTION(libvlc_media_get_state)
{
	MEDIA_ARG_ONLY(zm);
	RETURN_LONG(libvlc_media_get_state(p_md));
}

PHP_FUNCTION(libvlc_media_get_stats)
{
	zval *zm, *zs;
	libvlc_media_stats_t s;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zm, vlc_ce_libvlc_media_t)
		Z_PARAM_OBJECT_OF_CLASS(zs, vlc_ce_libvlc_media_stats_t)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_t, p_md, zm, 1);

	memset(&s, 0, sizeof(s));
	int result = libvlc_media_get_stats(p_md, &s);
	zend_object *o = Z_OBJ_P(zs);
	zend_class_entry *ce = vlc_ce_libvlc_media_stats_t;
#define STAT_L(f) zend_update_property_long(ce, o, #f, sizeof(#f) - 1, s.f)
#define STAT_D(f) zend_update_property_double(ce, o, #f, sizeof(#f) - 1, s.f)
	STAT_L(i_read_bytes); STAT_D(f_input_bitrate); STAT_L(i_demux_read_bytes); STAT_D(f_demux_bitrate);
	STAT_L(i_demux_corrupted); STAT_L(i_demux_discontinuity); STAT_L(i_decoded_video); STAT_L(i_decoded_audio);
	STAT_L(i_displayed_pictures); STAT_L(i_lost_pictures); STAT_L(i_played_abuffers); STAT_L(i_lost_abuffers);
	STAT_L(i_sent_packets); STAT_L(i_sent_bytes); STAT_D(f_send_bitrate);
#undef STAT_L
#undef STAT_D
	RETURN_LONG(result);
}

PHP_FUNCTION(libvlc_media_subitems)
{
	MEDIA_ARG_ONLY(zm);
	vlc_box_new(return_value, libvlc_media_subitems(p_md), vlc_ce_libvlc_media_list_t);
}

PHP_FUNCTION(libvlc_media_event_manager)
{
	MEDIA_ARG_ONLY(zm);
	vlc_box_em(return_value, libvlc_media_event_manager(p_md), p_md);
}

PHP_FUNCTION(libvlc_media_get_duration)
{
	MEDIA_ARG_ONLY(zm);
	RETURN_LONG(libvlc_media_get_duration(p_md));
}

PHP_FUNCTION(libvlc_media_parse_with_options)
{
	zval *zm;
	zend_long flag, timeout;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(zm, vlc_ce_libvlc_media_t)
		Z_PARAM_LONG(flag)
		Z_PARAM_LONG(timeout)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_t, p_md, zm, 1);
	RETURN_LONG(libvlc_media_parse_with_options(p_md, (libvlc_media_parse_flag_t) flag, (int) timeout));
}

PHP_FUNCTION(libvlc_media_parse_stop)
{
	MEDIA_ARG_ONLY(zm);
	libvlc_media_parse_stop(p_md);
}

PHP_FUNCTION(libvlc_media_get_parsed_status)
{
	MEDIA_ARG_ONLY(zm);
	RETURN_LONG(libvlc_media_get_parsed_status(p_md));
}

PHP_FUNCTION(libvlc_media_set_user_data)
{
	zval *zm;
	zend_long data;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zm, vlc_ce_libvlc_media_t)
		Z_PARAM_LONG(data)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_t, p_md, zm, 1);
	libvlc_media_set_user_data(p_md, (void *) (uintptr_t) data);
}

PHP_FUNCTION(libvlc_media_get_user_data)
{
	MEDIA_ARG_ONLY(zm);
	RETURN_LONG((zend_long) (uintptr_t) libvlc_media_get_user_data(p_md));
}

PHP_FUNCTION(libvlc_media_tracks_get)
{
	zval *zm, *ztracks;
	libvlc_media_track_t **tracks = NULL;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zm, vlc_ce_libvlc_media_t)
		Z_PARAM_ZVAL(ztracks)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_t, p_md, zm, 1);

	unsigned count = libvlc_media_tracks_get(p_md, &tracks);
	zval list;
	vlc_list_box(&list, (void **) tracks, count, vlc_ce_libvlc_media_track_t);
	/* The elements stay libvlc's until libvlc_media_tracks_release(); only the array goes now. */
	free(tracks);
	ZEND_TRY_ASSIGN_REF_VALUE(ztracks, &list);
	RETURN_LONG(count);
}

PHP_FUNCTION(libvlc_media_get_codec_description)
{
	zend_long type, codec;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(type)
		Z_PARAM_LONG(codec)
	ZEND_PARSE_PARAMETERS_END();
	vlc_string_or_null(return_value, libvlc_media_get_codec_description((libvlc_track_type_t) type, (uint32_t) codec));
}

PHP_FUNCTION(libvlc_media_tracks_release)
{
	HashTable *list;
	zend_long count;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ARRAY_HT(list)
		Z_PARAM_LONG(count)
	ZEND_PARSE_PARAMETERS_END();
	if (!vlc_list_count(count, zend_hash_num_elements(list), 2, 1)) {
		RETURN_THROWS();
	}
	libvlc_media_track_t **tracks = (libvlc_media_track_t **) vlc_list_ptrs(list, count, vlc_ce_libvlc_media_track_t, 1);
	if (tracks == NULL) {
		RETURN_THROWS();
	}
	for (zend_long i = 0; i < count; i++) {
		vlc_release(tracks[i]->audio, vlc_ce_libvlc_audio_track_t);
		vlc_release(tracks[i]->video, vlc_ce_libvlc_video_track_t);
		vlc_release(tracks[i]->subtitle, vlc_ce_libvlc_subtitle_track_t);
		vlc_release(tracks[i], vlc_ce_libvlc_media_track_t);
	}
	libvlc_media_tracks_release(tracks, (unsigned) count);
}

PHP_FUNCTION(libvlc_media_get_type)
{
	MEDIA_ARG_ONLY(zm);
	RETURN_LONG(libvlc_media_get_type(p_md));
}

PHP_FUNCTION(libvlc_media_slaves_add)
{
	zval *zm;
	zend_long type, priority;
	zend_string *uri;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(zm, vlc_ce_libvlc_media_t)
		Z_PARAM_LONG(type)
		Z_PARAM_LONG(priority)
		Z_PARAM_STR(uri)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_t, p_md, zm, 1);
	RETURN_LONG(libvlc_media_slaves_add(p_md, (libvlc_media_slave_type_t) type, (unsigned) priority, ZSTR_VAL(uri)));
}

PHP_FUNCTION(libvlc_media_slaves_clear)
{
	MEDIA_ARG_ONLY(zm);
	libvlc_media_slaves_clear(p_md);
}

PHP_FUNCTION(libvlc_media_slaves_get)
{
	zval *zm, *zslaves;
	libvlc_media_slave_t **slaves = NULL;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zm, vlc_ce_libvlc_media_t)
		Z_PARAM_ZVAL(zslaves)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_t, p_md, zm, 1);

	unsigned count = libvlc_media_slaves_get(p_md, &slaves);
	zval list;
	vlc_list_box(&list, (void **) slaves, count, vlc_ce_libvlc_media_slave_t);
	free(slaves);
	ZEND_TRY_ASSIGN_REF_VALUE(zslaves, &list);
	RETURN_LONG(count);
}

PHP_FUNCTION(libvlc_media_slaves_release)
{
	HashTable *list;
	zend_long count;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ARRAY_HT(list)
		Z_PARAM_LONG(count)
	ZEND_PARSE_PARAMETERS_END();
	if (!vlc_list_count(count, zend_hash_num_elements(list), 2, 1)) {
		RETURN_THROWS();
	}
	libvlc_media_slave_t **slaves = (libvlc_media_slave_t **) vlc_list_ptrs(list, count, vlc_ce_libvlc_media_slave_t, 1);
	if (slaves == NULL) {
		RETURN_THROWS();
	}
	for (zend_long i = 0; i < count; i++) {
		vlc_release(slaves[i], vlc_ce_libvlc_media_slave_t);
	}
	libvlc_media_slaves_release(slaves, (unsigned) count);
}

void vlc_register_libvlc(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
