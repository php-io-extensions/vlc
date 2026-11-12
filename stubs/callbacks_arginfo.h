/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: bb9941181f51e0a34197c4fd3c8b964f87095596 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_event_attach, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_event_manager, libvlc_event_manager_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_event_type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, f_callback, IS_CALLABLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_event_detach, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_event_manager, libvlc_event_manager_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_event_type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, f_callback, IS_CALLABLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_log_set, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, cb, IS_CALLABLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_log_unset, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_log_set_file, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_log_get_object, 0, 4, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, ctx, libvlc_log_t, 0)
	ZEND_ARG_TYPE_INFO(1, name, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(1, header, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(1, id, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_log_get_context, 0, 4, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, ctx, libvlc_log_t, 0)
	ZEND_ARG_TYPE_INFO(1, module, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(1, file, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(1, line, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_new_callbacks, 0, 5, libvlc_media_t, 1)
	ZEND_ARG_OBJ_INFO(0, instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, open_cb, IS_CALLABLE, 0)
	ZEND_ARG_TYPE_INFO(0, read_cb, IS_CALLABLE, 0)
	ZEND_ARG_TYPE_INFO(0, seek_cb, IS_CALLABLE, 1)
	ZEND_ARG_TYPE_INFO(0, close_cb, IS_CALLABLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_set_callbacks, 0, 6, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, mp, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, play, IS_CALLABLE, 0)
	ZEND_ARG_TYPE_INFO(0, pause, IS_CALLABLE, 1)
	ZEND_ARG_TYPE_INFO(0, resume, IS_CALLABLE, 1)
	ZEND_ARG_TYPE_INFO(0, flush, IS_CALLABLE, 1)
	ZEND_ARG_TYPE_INFO(0, drain, IS_CALLABLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_set_volume_callback, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, mp, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, set_volume, IS_CALLABLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_set_format_callbacks, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, mp, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, setup, IS_CALLABLE, 0)
	ZEND_ARG_TYPE_INFO(0, cleanup, IS_CALLABLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_set_format, 0, 4, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, mp, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, rate, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, channels, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_set_callbacks, 0, 4, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, mp, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, lock, IS_CALLABLE, 0)
	ZEND_ARG_TYPE_INFO(0, unlock, IS_CALLABLE, 1)
	ZEND_ARG_TYPE_INFO(0, display, IS_CALLABLE, 1)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_video_set_format_callbacks arginfo_libvlc_audio_set_format_callbacks

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_set_format, 0, 5, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, mp, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, chroma, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pitch, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_dialog_set_callbacks, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_OBJ_INFO(0, p_cbs, libvlc_dialog_cbs, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_set_exit_handler, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, cb, IS_CALLABLE, 1)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(libvlc_event_attach);
ZEND_FUNCTION(libvlc_event_detach);
ZEND_FUNCTION(libvlc_log_set);
ZEND_FUNCTION(libvlc_log_unset);
ZEND_FUNCTION(libvlc_log_set_file);
ZEND_FUNCTION(libvlc_log_get_object);
ZEND_FUNCTION(libvlc_log_get_context);
ZEND_FUNCTION(libvlc_media_new_callbacks);
ZEND_FUNCTION(libvlc_audio_set_callbacks);
ZEND_FUNCTION(libvlc_audio_set_volume_callback);
ZEND_FUNCTION(libvlc_audio_set_format_callbacks);
ZEND_FUNCTION(libvlc_audio_set_format);
ZEND_FUNCTION(libvlc_video_set_callbacks);
ZEND_FUNCTION(libvlc_video_set_format_callbacks);
ZEND_FUNCTION(libvlc_video_set_format);
ZEND_FUNCTION(libvlc_dialog_set_callbacks);
ZEND_FUNCTION(libvlc_set_exit_handler);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(libvlc_event_attach, arginfo_libvlc_event_attach)
	ZEND_FE(libvlc_event_detach, arginfo_libvlc_event_detach)
	ZEND_FE(libvlc_log_set, arginfo_libvlc_log_set)
	ZEND_FE(libvlc_log_unset, arginfo_libvlc_log_unset)
	ZEND_FE(libvlc_log_set_file, arginfo_libvlc_log_set_file)
	ZEND_FE(libvlc_log_get_object, arginfo_libvlc_log_get_object)
	ZEND_FE(libvlc_log_get_context, arginfo_libvlc_log_get_context)
	ZEND_FE(libvlc_media_new_callbacks, arginfo_libvlc_media_new_callbacks)
	ZEND_FE(libvlc_audio_set_callbacks, arginfo_libvlc_audio_set_callbacks)
	ZEND_FE(libvlc_audio_set_volume_callback, arginfo_libvlc_audio_set_volume_callback)
	ZEND_FE(libvlc_audio_set_format_callbacks, arginfo_libvlc_audio_set_format_callbacks)
	ZEND_FE(libvlc_audio_set_format, arginfo_libvlc_audio_set_format)
	ZEND_FE(libvlc_video_set_callbacks, arginfo_libvlc_video_set_callbacks)
	ZEND_FE(libvlc_video_set_format_callbacks, arginfo_libvlc_video_set_format_callbacks)
	ZEND_FE(libvlc_video_set_format, arginfo_libvlc_video_set_format)
	ZEND_FE(libvlc_dialog_set_callbacks, arginfo_libvlc_dialog_set_callbacks)
	ZEND_FE(libvlc_set_exit_handler, arginfo_libvlc_set_exit_handler)
	ZEND_FE_END
};
