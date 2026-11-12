/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: d1935cbdbd83b14c03595f3c23283b092792a21b */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_track_description_list_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_track_description, libvlc_track_description_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_output_list_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_list, libvlc_audio_output_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_output_device_list_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_list, libvlc_audio_output_device_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_equalizer_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_equalizer, libvlc_equalizer_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_get_size, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, num, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, px, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, py, IS_LONG, 1)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_video_get_cursor arginfo_libvlc_video_get_size

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_video_new_viewpoint, 0, 0, libvlc_video_viewpoint_t, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_update_viewpoint, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_OBJ_INFO(0, p_viewpoint, libvlc_video_viewpoint_t, 0)
	ZEND_ARG_TYPE_INFO(0, b_absolute, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_get_full_title_descriptions, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(1, titles, IS_ARRAY, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_title_descriptions_release, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, p_titles, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, i_count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_get_full_chapter_descriptions, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_chapters_of_title, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, pp_chapters, IS_ARRAY, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_chapter_descriptions_release, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, p_chapters, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, i_count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(libvlc_track_description_list_release);
ZEND_FUNCTION(libvlc_audio_output_list_release);
ZEND_FUNCTION(libvlc_audio_output_device_list_release);
ZEND_FUNCTION(libvlc_audio_equalizer_release);
ZEND_FUNCTION(libvlc_video_get_size);
ZEND_FUNCTION(libvlc_video_get_cursor);
ZEND_FUNCTION(libvlc_video_new_viewpoint);
ZEND_FUNCTION(libvlc_video_update_viewpoint);
ZEND_FUNCTION(libvlc_media_player_get_full_title_descriptions);
ZEND_FUNCTION(libvlc_title_descriptions_release);
ZEND_FUNCTION(libvlc_media_player_get_full_chapter_descriptions);
ZEND_FUNCTION(libvlc_chapter_descriptions_release);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(libvlc_track_description_list_release, arginfo_libvlc_track_description_list_release)
	ZEND_FE(libvlc_audio_output_list_release, arginfo_libvlc_audio_output_list_release)
	ZEND_FE(libvlc_audio_output_device_list_release, arginfo_libvlc_audio_output_device_list_release)
	ZEND_FE(libvlc_audio_equalizer_release, arginfo_libvlc_audio_equalizer_release)
	ZEND_FE(libvlc_video_get_size, arginfo_libvlc_video_get_size)
	ZEND_FE(libvlc_video_get_cursor, arginfo_libvlc_video_get_cursor)
	ZEND_FE(libvlc_video_new_viewpoint, arginfo_libvlc_video_new_viewpoint)
	ZEND_FE(libvlc_video_update_viewpoint, arginfo_libvlc_video_update_viewpoint)
	ZEND_FE(libvlc_media_player_get_full_title_descriptions, arginfo_libvlc_media_player_get_full_title_descriptions)
	ZEND_FE(libvlc_title_descriptions_release, arginfo_libvlc_title_descriptions_release)
	ZEND_FE(libvlc_media_player_get_full_chapter_descriptions, arginfo_libvlc_media_player_get_full_chapter_descriptions)
	ZEND_FE(libvlc_chapter_descriptions_release, arginfo_libvlc_chapter_descriptions_release)
	ZEND_FE_END
};
