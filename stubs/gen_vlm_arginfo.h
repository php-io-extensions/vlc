/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: df04f3672c165663ff0b5a4f93d2737d018b63d1 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_vlm_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_vlm_del_media, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_name, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_vlm_set_enabled, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_name, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, b_enabled, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_vlm_set_output, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_name, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, psz_output, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_vlm_set_input, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_name, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, psz_input, IS_STRING, 1)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_vlm_add_input arginfo_libvlc_vlm_set_input

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_vlm_set_loop, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_name, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, b_loop, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_vlm_set_mux, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_name, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, psz_mux, IS_STRING, 1)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_vlm_play_media arginfo_libvlc_vlm_del_media

#define arginfo_libvlc_vlm_stop_media arginfo_libvlc_vlm_del_media

#define arginfo_libvlc_vlm_pause_media arginfo_libvlc_vlm_del_media

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_vlm_seek_media, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_name, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, f_percentage, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_vlm_show_media, 0, 2, IS_STRING, 1)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_name, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_vlm_get_media_instance_position, 0, 3, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_name, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, i_instance, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_vlm_get_media_instance_time, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_name, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, i_instance, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_vlm_get_media_instance_length arginfo_libvlc_vlm_get_media_instance_time

#define arginfo_libvlc_vlm_get_media_instance_rate arginfo_libvlc_vlm_get_media_instance_time

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_vlm_get_event_manager, 0, 1, libvlc_event_manager_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(libvlc_vlm_release);
ZEND_FUNCTION(libvlc_vlm_del_media);
ZEND_FUNCTION(libvlc_vlm_set_enabled);
ZEND_FUNCTION(libvlc_vlm_set_output);
ZEND_FUNCTION(libvlc_vlm_set_input);
ZEND_FUNCTION(libvlc_vlm_add_input);
ZEND_FUNCTION(libvlc_vlm_set_loop);
ZEND_FUNCTION(libvlc_vlm_set_mux);
ZEND_FUNCTION(libvlc_vlm_play_media);
ZEND_FUNCTION(libvlc_vlm_stop_media);
ZEND_FUNCTION(libvlc_vlm_pause_media);
ZEND_FUNCTION(libvlc_vlm_seek_media);
ZEND_FUNCTION(libvlc_vlm_show_media);
ZEND_FUNCTION(libvlc_vlm_get_media_instance_position);
ZEND_FUNCTION(libvlc_vlm_get_media_instance_time);
ZEND_FUNCTION(libvlc_vlm_get_media_instance_length);
ZEND_FUNCTION(libvlc_vlm_get_media_instance_rate);
ZEND_FUNCTION(libvlc_vlm_get_event_manager);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(libvlc_vlm_release, arginfo_libvlc_vlm_release)
	ZEND_FE(libvlc_vlm_del_media, arginfo_libvlc_vlm_del_media)
	ZEND_FE(libvlc_vlm_set_enabled, arginfo_libvlc_vlm_set_enabled)
	ZEND_FE(libvlc_vlm_set_output, arginfo_libvlc_vlm_set_output)
	ZEND_FE(libvlc_vlm_set_input, arginfo_libvlc_vlm_set_input)
	ZEND_FE(libvlc_vlm_add_input, arginfo_libvlc_vlm_add_input)
	ZEND_FE(libvlc_vlm_set_loop, arginfo_libvlc_vlm_set_loop)
	ZEND_FE(libvlc_vlm_set_mux, arginfo_libvlc_vlm_set_mux)
	ZEND_FE(libvlc_vlm_play_media, arginfo_libvlc_vlm_play_media)
	ZEND_FE(libvlc_vlm_stop_media, arginfo_libvlc_vlm_stop_media)
	ZEND_FE(libvlc_vlm_pause_media, arginfo_libvlc_vlm_pause_media)
	ZEND_FE(libvlc_vlm_seek_media, arginfo_libvlc_vlm_seek_media)
	ZEND_FE(libvlc_vlm_show_media, arginfo_libvlc_vlm_show_media)
	ZEND_FE(libvlc_vlm_get_media_instance_position, arginfo_libvlc_vlm_get_media_instance_position)
	ZEND_FE(libvlc_vlm_get_media_instance_time, arginfo_libvlc_vlm_get_media_instance_time)
	ZEND_FE(libvlc_vlm_get_media_instance_length, arginfo_libvlc_vlm_get_media_instance_length)
	ZEND_FE(libvlc_vlm_get_media_instance_rate, arginfo_libvlc_vlm_get_media_instance_rate)
	ZEND_FE(libvlc_vlm_get_event_manager, arginfo_libvlc_vlm_get_event_manager)
	ZEND_FE_END
};
