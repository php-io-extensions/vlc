/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 44397f08758536cda97a4bc3f9178df8a6ce41a3 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_errmsg, 0, 0, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_clearerr, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_printerr, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, fmt, IS_STRING, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(0, args, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_new, 0, 2, libvlc_instance_t, 1)
	ZEND_ARG_TYPE_INFO(0, argc, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, argv, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_retain arginfo_libvlc_release

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_add_intf, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_set_user_agent, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, http, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_set_app_id, 0, 4, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, version, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, icon, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_free, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, ptr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_event_type_name, 0, 1, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, event_type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_module_description_list_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_list, libvlc_module_description_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_audio_filter_list_get, 0, 1, libvlc_module_description_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_video_filter_list_get arginfo_libvlc_audio_filter_list_get

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_clock, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_new_location, 0, 2, libvlc_media_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_mrl, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_new_path, 0, 2, libvlc_media_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_new_fd, 0, 2, libvlc_media_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_new_as_node, 0, 2, libvlc_media_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_add_option, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_options, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_add_option_flag, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_options, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, i_flags, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_retain, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_release arginfo_libvlc_media_retain

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_get_mrl, 0, 1, IS_STRING, 1)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_duplicate, 0, 1, libvlc_media_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_get_meta, 0, 2, IS_STRING, 1)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
	ZEND_ARG_TYPE_INFO(0, e_meta, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_set_meta, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
	ZEND_ARG_TYPE_INFO(0, e_meta, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, psz_value, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_save_meta, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_get_state arginfo_libvlc_media_save_meta

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_get_stats, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
	ZEND_ARG_OBJ_INFO(0, p_stats, libvlc_media_stats_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_subitems, 0, 1, libvlc_media_list_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_event_manager, 0, 1, libvlc_event_manager_t, 0)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_get_duration arginfo_libvlc_media_save_meta

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_parse_with_options, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
	ZEND_ARG_TYPE_INFO(0, parse_flag, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, timeout, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_parse_stop arginfo_libvlc_media_retain

#define arginfo_libvlc_media_get_parsed_status arginfo_libvlc_media_save_meta

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_set_user_data, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
	ZEND_ARG_TYPE_INFO(0, p_new_user_data, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_get_user_data arginfo_libvlc_media_save_meta

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_tracks_get, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
	ZEND_ARG_TYPE_INFO(1, tracks, IS_ARRAY, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_get_codec_description, 0, 2, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, i_type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, i_codec, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_tracks_release, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, p_tracks, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, i_count, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_get_type arginfo_libvlc_media_save_meta

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_slaves_add, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, i_priority, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, psz_uri, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_slaves_clear arginfo_libvlc_media_retain

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_slaves_get, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
	ZEND_ARG_TYPE_INFO(1, ppp_slaves, IS_ARRAY, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_slaves_release, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, pp_slaves, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, i_count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(libvlc_errmsg);
ZEND_FUNCTION(libvlc_clearerr);
ZEND_FUNCTION(libvlc_printerr);
ZEND_FUNCTION(libvlc_new);
ZEND_FUNCTION(libvlc_release);
ZEND_FUNCTION(libvlc_retain);
ZEND_FUNCTION(libvlc_add_intf);
ZEND_FUNCTION(libvlc_set_user_agent);
ZEND_FUNCTION(libvlc_set_app_id);
ZEND_FUNCTION(libvlc_free);
ZEND_FUNCTION(libvlc_event_type_name);
ZEND_FUNCTION(libvlc_module_description_list_release);
ZEND_FUNCTION(libvlc_audio_filter_list_get);
ZEND_FUNCTION(libvlc_video_filter_list_get);
ZEND_FUNCTION(libvlc_clock);
ZEND_FUNCTION(libvlc_media_new_location);
ZEND_FUNCTION(libvlc_media_new_path);
ZEND_FUNCTION(libvlc_media_new_fd);
ZEND_FUNCTION(libvlc_media_new_as_node);
ZEND_FUNCTION(libvlc_media_add_option);
ZEND_FUNCTION(libvlc_media_add_option_flag);
ZEND_FUNCTION(libvlc_media_retain);
ZEND_FUNCTION(libvlc_media_release);
ZEND_FUNCTION(libvlc_media_get_mrl);
ZEND_FUNCTION(libvlc_media_duplicate);
ZEND_FUNCTION(libvlc_media_get_meta);
ZEND_FUNCTION(libvlc_media_set_meta);
ZEND_FUNCTION(libvlc_media_save_meta);
ZEND_FUNCTION(libvlc_media_get_state);
ZEND_FUNCTION(libvlc_media_get_stats);
ZEND_FUNCTION(libvlc_media_subitems);
ZEND_FUNCTION(libvlc_media_event_manager);
ZEND_FUNCTION(libvlc_media_get_duration);
ZEND_FUNCTION(libvlc_media_parse_with_options);
ZEND_FUNCTION(libvlc_media_parse_stop);
ZEND_FUNCTION(libvlc_media_get_parsed_status);
ZEND_FUNCTION(libvlc_media_set_user_data);
ZEND_FUNCTION(libvlc_media_get_user_data);
ZEND_FUNCTION(libvlc_media_tracks_get);
ZEND_FUNCTION(libvlc_media_get_codec_description);
ZEND_FUNCTION(libvlc_media_tracks_release);
ZEND_FUNCTION(libvlc_media_get_type);
ZEND_FUNCTION(libvlc_media_slaves_add);
ZEND_FUNCTION(libvlc_media_slaves_clear);
ZEND_FUNCTION(libvlc_media_slaves_get);
ZEND_FUNCTION(libvlc_media_slaves_release);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(libvlc_errmsg, arginfo_libvlc_errmsg)
	ZEND_FE(libvlc_clearerr, arginfo_libvlc_clearerr)
	ZEND_FE(libvlc_printerr, arginfo_libvlc_printerr)
	ZEND_FE(libvlc_new, arginfo_libvlc_new)
	ZEND_FE(libvlc_release, arginfo_libvlc_release)
	ZEND_FE(libvlc_retain, arginfo_libvlc_retain)
	ZEND_FE(libvlc_add_intf, arginfo_libvlc_add_intf)
	ZEND_FE(libvlc_set_user_agent, arginfo_libvlc_set_user_agent)
	ZEND_FE(libvlc_set_app_id, arginfo_libvlc_set_app_id)
	ZEND_FE(libvlc_free, arginfo_libvlc_free)
	ZEND_FE(libvlc_event_type_name, arginfo_libvlc_event_type_name)
	ZEND_FE(libvlc_module_description_list_release, arginfo_libvlc_module_description_list_release)
	ZEND_FE(libvlc_audio_filter_list_get, arginfo_libvlc_audio_filter_list_get)
	ZEND_FE(libvlc_video_filter_list_get, arginfo_libvlc_video_filter_list_get)
	ZEND_FE(libvlc_clock, arginfo_libvlc_clock)
	ZEND_FE(libvlc_media_new_location, arginfo_libvlc_media_new_location)
	ZEND_FE(libvlc_media_new_path, arginfo_libvlc_media_new_path)
	ZEND_FE(libvlc_media_new_fd, arginfo_libvlc_media_new_fd)
	ZEND_FE(libvlc_media_new_as_node, arginfo_libvlc_media_new_as_node)
	ZEND_FE(libvlc_media_add_option, arginfo_libvlc_media_add_option)
	ZEND_FE(libvlc_media_add_option_flag, arginfo_libvlc_media_add_option_flag)
	ZEND_FE(libvlc_media_retain, arginfo_libvlc_media_retain)
	ZEND_FE(libvlc_media_release, arginfo_libvlc_media_release)
	ZEND_FE(libvlc_media_get_mrl, arginfo_libvlc_media_get_mrl)
	ZEND_FE(libvlc_media_duplicate, arginfo_libvlc_media_duplicate)
	ZEND_FE(libvlc_media_get_meta, arginfo_libvlc_media_get_meta)
	ZEND_FE(libvlc_media_set_meta, arginfo_libvlc_media_set_meta)
	ZEND_FE(libvlc_media_save_meta, arginfo_libvlc_media_save_meta)
	ZEND_FE(libvlc_media_get_state, arginfo_libvlc_media_get_state)
	ZEND_FE(libvlc_media_get_stats, arginfo_libvlc_media_get_stats)
	ZEND_FE(libvlc_media_subitems, arginfo_libvlc_media_subitems)
	ZEND_FE(libvlc_media_event_manager, arginfo_libvlc_media_event_manager)
	ZEND_FE(libvlc_media_get_duration, arginfo_libvlc_media_get_duration)
	ZEND_FE(libvlc_media_parse_with_options, arginfo_libvlc_media_parse_with_options)
	ZEND_FE(libvlc_media_parse_stop, arginfo_libvlc_media_parse_stop)
	ZEND_FE(libvlc_media_get_parsed_status, arginfo_libvlc_media_get_parsed_status)
	ZEND_FE(libvlc_media_set_user_data, arginfo_libvlc_media_set_user_data)
	ZEND_FE(libvlc_media_get_user_data, arginfo_libvlc_media_get_user_data)
	ZEND_FE(libvlc_media_tracks_get, arginfo_libvlc_media_tracks_get)
	ZEND_FE(libvlc_media_get_codec_description, arginfo_libvlc_media_get_codec_description)
	ZEND_FE(libvlc_media_tracks_release, arginfo_libvlc_media_tracks_release)
	ZEND_FE(libvlc_media_get_type, arginfo_libvlc_media_get_type)
	ZEND_FE(libvlc_media_slaves_add, arginfo_libvlc_media_slaves_add)
	ZEND_FE(libvlc_media_slaves_clear, arginfo_libvlc_media_slaves_clear)
	ZEND_FE(libvlc_media_slaves_get, arginfo_libvlc_media_slaves_get)
	ZEND_FE(libvlc_media_slaves_release, arginfo_libvlc_media_slaves_release)
	ZEND_FE_END
};
