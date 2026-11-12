/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: af3bbb7dfec8f93af389fff1488806006143e4af */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_player_new, 0, 1, libvlc_media_player_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_libvlc_instance, libvlc_instance_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_player_new_from_media, 0, 1, libvlc_media_player_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_player_retain arginfo_libvlc_media_player_release

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_set_media, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_player_get_media, 0, 1, libvlc_media_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_player_event_manager, 0, 1, libvlc_event_manager_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_is_playing, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_player_play arginfo_libvlc_media_player_is_playing

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_set_pause, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, mp, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, do_pause, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_player_pause arginfo_libvlc_media_player_release

#define arginfo_libvlc_media_player_stop arginfo_libvlc_media_player_release

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_set_renderer, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_OBJ_INFO(0, p_item, libvlc_renderer_item_t, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_set_nsobject, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, drawable, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_player_get_nsobject arginfo_libvlc_media_player_is_playing

#define arginfo_libvlc_media_player_set_xwindow arginfo_libvlc_media_player_set_nsobject

#define arginfo_libvlc_media_player_get_xwindow arginfo_libvlc_media_player_is_playing

#define arginfo_libvlc_media_player_set_hwnd arginfo_libvlc_media_player_set_nsobject

#define arginfo_libvlc_media_player_get_hwnd arginfo_libvlc_media_player_is_playing

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_set_android_context, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, p_awindow_handler, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_player_get_length arginfo_libvlc_media_player_is_playing

#define arginfo_libvlc_media_player_get_time arginfo_libvlc_media_player_is_playing

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_set_time, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_time, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_get_position, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_set_position, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, f_pos, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_set_chapter, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_chapter, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_player_get_chapter arginfo_libvlc_media_player_is_playing

#define arginfo_libvlc_media_player_get_chapter_count arginfo_libvlc_media_player_is_playing

#define arginfo_libvlc_media_player_will_play arginfo_libvlc_media_player_is_playing

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_get_chapter_count_for_title, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_title, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_set_title, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_title, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_player_get_title arginfo_libvlc_media_player_is_playing

#define arginfo_libvlc_media_player_get_title_count arginfo_libvlc_media_player_is_playing

#define arginfo_libvlc_media_player_previous_chapter arginfo_libvlc_media_player_release

#define arginfo_libvlc_media_player_next_chapter arginfo_libvlc_media_player_release

#define arginfo_libvlc_media_player_get_rate arginfo_libvlc_media_player_get_position

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_set_rate, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, rate, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_player_get_state arginfo_libvlc_media_player_is_playing

#define arginfo_libvlc_media_player_has_vout arginfo_libvlc_media_player_is_playing

#define arginfo_libvlc_media_player_is_seekable arginfo_libvlc_media_player_is_playing

#define arginfo_libvlc_media_player_can_pause arginfo_libvlc_media_player_is_playing

#define arginfo_libvlc_media_player_program_scrambled arginfo_libvlc_media_player_is_playing

#define arginfo_libvlc_media_player_next_frame arginfo_libvlc_media_player_release

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_navigate, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, navigate, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_set_video_title_display, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, position, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, timeout, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_add_slave, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, psz_uri, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, b_select, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_toggle_fullscreen arginfo_libvlc_media_player_release

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_set_fullscreen, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, b_fullscreen, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_get_fullscreen arginfo_libvlc_media_player_is_playing

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_set_key_input, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, on, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_video_set_mouse_input arginfo_libvlc_video_set_key_input

#define arginfo_libvlc_video_get_scale arginfo_libvlc_media_player_get_position

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_set_scale, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, f_factor, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_get_aspect_ratio, 0, 1, IS_STRING, 1)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_set_aspect_ratio, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_aspect, IS_STRING, 1)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_video_get_spu arginfo_libvlc_media_player_is_playing

#define arginfo_libvlc_video_get_spu_count arginfo_libvlc_media_player_is_playing

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_video_get_spu_description, 0, 1, libvlc_track_description_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_set_spu, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_spu, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_video_get_spu_delay arginfo_libvlc_media_player_is_playing

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_set_spu_delay, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_delay, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_video_get_crop_geometry arginfo_libvlc_video_get_aspect_ratio

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_set_crop_geometry, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_geometry, IS_STRING, 1)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_video_get_teletext arginfo_libvlc_media_player_is_playing

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_set_teletext, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_page, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_video_get_track_count arginfo_libvlc_media_player_is_playing

#define arginfo_libvlc_video_get_track_description arginfo_libvlc_video_get_spu_description

#define arginfo_libvlc_video_get_track arginfo_libvlc_media_player_is_playing

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_set_track, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_track, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_take_snapshot, 0, 5, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, num, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, psz_filepath, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, i_width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, i_height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_set_deinterlace, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_mode, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_get_marquee_int, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, option, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_get_marquee_string, 0, 2, IS_STRING, 1)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, option, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_set_marquee_int, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, option, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, i_val, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_set_marquee_string, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, option, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, psz_text, IS_STRING, 1)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_video_get_logo_int arginfo_libvlc_video_get_marquee_int

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_set_logo_int, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, option, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_set_logo_string, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, option, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, psz_value, IS_STRING, 1)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_video_get_adjust_int arginfo_libvlc_video_get_marquee_int

#define arginfo_libvlc_video_set_adjust_int arginfo_libvlc_video_set_logo_int

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_get_adjust_float, 0, 2, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, option, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_video_set_adjust_float, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, option, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_audio_output_list_get, 0, 1, libvlc_audio_output_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_output_set, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_name, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_audio_output_device_enum, 0, 1, libvlc_audio_output_device_t, 1)
	ZEND_ARG_OBJ_INFO(0, mp, libvlc_media_player_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_audio_output_device_list_get, 0, 2, libvlc_audio_output_device_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, aout, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_output_device_set, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, mp, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, module, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, device_id, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_output_device_get, 0, 1, IS_STRING, 1)
	ZEND_ARG_OBJ_INFO(0, mp, libvlc_media_player_t, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_audio_toggle_mute arginfo_libvlc_media_player_release

#define arginfo_libvlc_audio_get_mute arginfo_libvlc_media_player_is_playing

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_set_mute, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, status, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_audio_get_volume arginfo_libvlc_media_player_is_playing

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_set_volume, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_volume, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_audio_get_track_count arginfo_libvlc_media_player_is_playing

#define arginfo_libvlc_audio_get_track_description arginfo_libvlc_video_get_spu_description

#define arginfo_libvlc_audio_get_track arginfo_libvlc_media_player_is_playing

#define arginfo_libvlc_audio_set_track arginfo_libvlc_video_set_track

#define arginfo_libvlc_audio_get_channel arginfo_libvlc_media_player_is_playing

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_set_channel, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, channel, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_audio_get_delay arginfo_libvlc_media_player_is_playing

#define arginfo_libvlc_audio_set_delay arginfo_libvlc_video_set_spu_delay

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_equalizer_get_preset_count, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_equalizer_get_preset_name, 0, 1, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, u_index, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_audio_equalizer_get_band_count arginfo_libvlc_audio_equalizer_get_preset_count

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_equalizer_get_band_frequency, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, u_index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_audio_equalizer_new, 0, 0, libvlc_equalizer_t, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_audio_equalizer_new_from_preset, 0, 1, libvlc_equalizer_t, 1)
	ZEND_ARG_TYPE_INFO(0, u_index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_equalizer_set_preamp, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_equalizer, libvlc_equalizer_t, 0)
	ZEND_ARG_TYPE_INFO(0, f_preamp, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_equalizer_get_preamp, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, p_equalizer, libvlc_equalizer_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_equalizer_set_amp_at_index, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_equalizer, libvlc_equalizer_t, 0)
	ZEND_ARG_TYPE_INFO(0, f_amp, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, u_band, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_audio_equalizer_get_amp_at_index, 0, 2, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, p_equalizer, libvlc_equalizer_t, 0)
	ZEND_ARG_TYPE_INFO(0, u_band, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_set_equalizer, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_OBJ_INFO(0, p_equalizer, libvlc_equalizer_t, 1)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_player_get_role arginfo_libvlc_media_player_is_playing

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_player_set_role, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, role, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(libvlc_media_player_new);
ZEND_FUNCTION(libvlc_media_player_new_from_media);
ZEND_FUNCTION(libvlc_media_player_release);
ZEND_FUNCTION(libvlc_media_player_retain);
ZEND_FUNCTION(libvlc_media_player_set_media);
ZEND_FUNCTION(libvlc_media_player_get_media);
ZEND_FUNCTION(libvlc_media_player_event_manager);
ZEND_FUNCTION(libvlc_media_player_is_playing);
ZEND_FUNCTION(libvlc_media_player_play);
ZEND_FUNCTION(libvlc_media_player_set_pause);
ZEND_FUNCTION(libvlc_media_player_pause);
ZEND_FUNCTION(libvlc_media_player_stop);
ZEND_FUNCTION(libvlc_media_player_set_renderer);
ZEND_FUNCTION(libvlc_media_player_set_nsobject);
ZEND_FUNCTION(libvlc_media_player_get_nsobject);
ZEND_FUNCTION(libvlc_media_player_set_xwindow);
ZEND_FUNCTION(libvlc_media_player_get_xwindow);
ZEND_FUNCTION(libvlc_media_player_set_hwnd);
ZEND_FUNCTION(libvlc_media_player_get_hwnd);
ZEND_FUNCTION(libvlc_media_player_set_android_context);
ZEND_FUNCTION(libvlc_media_player_get_length);
ZEND_FUNCTION(libvlc_media_player_get_time);
ZEND_FUNCTION(libvlc_media_player_set_time);
ZEND_FUNCTION(libvlc_media_player_get_position);
ZEND_FUNCTION(libvlc_media_player_set_position);
ZEND_FUNCTION(libvlc_media_player_set_chapter);
ZEND_FUNCTION(libvlc_media_player_get_chapter);
ZEND_FUNCTION(libvlc_media_player_get_chapter_count);
ZEND_FUNCTION(libvlc_media_player_will_play);
ZEND_FUNCTION(libvlc_media_player_get_chapter_count_for_title);
ZEND_FUNCTION(libvlc_media_player_set_title);
ZEND_FUNCTION(libvlc_media_player_get_title);
ZEND_FUNCTION(libvlc_media_player_get_title_count);
ZEND_FUNCTION(libvlc_media_player_previous_chapter);
ZEND_FUNCTION(libvlc_media_player_next_chapter);
ZEND_FUNCTION(libvlc_media_player_get_rate);
ZEND_FUNCTION(libvlc_media_player_set_rate);
ZEND_FUNCTION(libvlc_media_player_get_state);
ZEND_FUNCTION(libvlc_media_player_has_vout);
ZEND_FUNCTION(libvlc_media_player_is_seekable);
ZEND_FUNCTION(libvlc_media_player_can_pause);
ZEND_FUNCTION(libvlc_media_player_program_scrambled);
ZEND_FUNCTION(libvlc_media_player_next_frame);
ZEND_FUNCTION(libvlc_media_player_navigate);
ZEND_FUNCTION(libvlc_media_player_set_video_title_display);
ZEND_FUNCTION(libvlc_media_player_add_slave);
ZEND_FUNCTION(libvlc_toggle_fullscreen);
ZEND_FUNCTION(libvlc_set_fullscreen);
ZEND_FUNCTION(libvlc_get_fullscreen);
ZEND_FUNCTION(libvlc_video_set_key_input);
ZEND_FUNCTION(libvlc_video_set_mouse_input);
ZEND_FUNCTION(libvlc_video_get_scale);
ZEND_FUNCTION(libvlc_video_set_scale);
ZEND_FUNCTION(libvlc_video_get_aspect_ratio);
ZEND_FUNCTION(libvlc_video_set_aspect_ratio);
ZEND_FUNCTION(libvlc_video_get_spu);
ZEND_FUNCTION(libvlc_video_get_spu_count);
ZEND_FUNCTION(libvlc_video_get_spu_description);
ZEND_FUNCTION(libvlc_video_set_spu);
ZEND_FUNCTION(libvlc_video_get_spu_delay);
ZEND_FUNCTION(libvlc_video_set_spu_delay);
ZEND_FUNCTION(libvlc_video_get_crop_geometry);
ZEND_FUNCTION(libvlc_video_set_crop_geometry);
ZEND_FUNCTION(libvlc_video_get_teletext);
ZEND_FUNCTION(libvlc_video_set_teletext);
ZEND_FUNCTION(libvlc_video_get_track_count);
ZEND_FUNCTION(libvlc_video_get_track_description);
ZEND_FUNCTION(libvlc_video_get_track);
ZEND_FUNCTION(libvlc_video_set_track);
ZEND_FUNCTION(libvlc_video_take_snapshot);
ZEND_FUNCTION(libvlc_video_set_deinterlace);
ZEND_FUNCTION(libvlc_video_get_marquee_int);
ZEND_FUNCTION(libvlc_video_get_marquee_string);
ZEND_FUNCTION(libvlc_video_set_marquee_int);
ZEND_FUNCTION(libvlc_video_set_marquee_string);
ZEND_FUNCTION(libvlc_video_get_logo_int);
ZEND_FUNCTION(libvlc_video_set_logo_int);
ZEND_FUNCTION(libvlc_video_set_logo_string);
ZEND_FUNCTION(libvlc_video_get_adjust_int);
ZEND_FUNCTION(libvlc_video_set_adjust_int);
ZEND_FUNCTION(libvlc_video_get_adjust_float);
ZEND_FUNCTION(libvlc_video_set_adjust_float);
ZEND_FUNCTION(libvlc_audio_output_list_get);
ZEND_FUNCTION(libvlc_audio_output_set);
ZEND_FUNCTION(libvlc_audio_output_device_enum);
ZEND_FUNCTION(libvlc_audio_output_device_list_get);
ZEND_FUNCTION(libvlc_audio_output_device_set);
ZEND_FUNCTION(libvlc_audio_output_device_get);
ZEND_FUNCTION(libvlc_audio_toggle_mute);
ZEND_FUNCTION(libvlc_audio_get_mute);
ZEND_FUNCTION(libvlc_audio_set_mute);
ZEND_FUNCTION(libvlc_audio_get_volume);
ZEND_FUNCTION(libvlc_audio_set_volume);
ZEND_FUNCTION(libvlc_audio_get_track_count);
ZEND_FUNCTION(libvlc_audio_get_track_description);
ZEND_FUNCTION(libvlc_audio_get_track);
ZEND_FUNCTION(libvlc_audio_set_track);
ZEND_FUNCTION(libvlc_audio_get_channel);
ZEND_FUNCTION(libvlc_audio_set_channel);
ZEND_FUNCTION(libvlc_audio_get_delay);
ZEND_FUNCTION(libvlc_audio_set_delay);
ZEND_FUNCTION(libvlc_audio_equalizer_get_preset_count);
ZEND_FUNCTION(libvlc_audio_equalizer_get_preset_name);
ZEND_FUNCTION(libvlc_audio_equalizer_get_band_count);
ZEND_FUNCTION(libvlc_audio_equalizer_get_band_frequency);
ZEND_FUNCTION(libvlc_audio_equalizer_new);
ZEND_FUNCTION(libvlc_audio_equalizer_new_from_preset);
ZEND_FUNCTION(libvlc_audio_equalizer_set_preamp);
ZEND_FUNCTION(libvlc_audio_equalizer_get_preamp);
ZEND_FUNCTION(libvlc_audio_equalizer_set_amp_at_index);
ZEND_FUNCTION(libvlc_audio_equalizer_get_amp_at_index);
ZEND_FUNCTION(libvlc_media_player_set_equalizer);
ZEND_FUNCTION(libvlc_media_player_get_role);
ZEND_FUNCTION(libvlc_media_player_set_role);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(libvlc_media_player_new, arginfo_libvlc_media_player_new)
	ZEND_FE(libvlc_media_player_new_from_media, arginfo_libvlc_media_player_new_from_media)
	ZEND_FE(libvlc_media_player_release, arginfo_libvlc_media_player_release)
	ZEND_FE(libvlc_media_player_retain, arginfo_libvlc_media_player_retain)
	ZEND_FE(libvlc_media_player_set_media, arginfo_libvlc_media_player_set_media)
	ZEND_FE(libvlc_media_player_get_media, arginfo_libvlc_media_player_get_media)
	ZEND_FE(libvlc_media_player_event_manager, arginfo_libvlc_media_player_event_manager)
	ZEND_FE(libvlc_media_player_is_playing, arginfo_libvlc_media_player_is_playing)
	ZEND_FE(libvlc_media_player_play, arginfo_libvlc_media_player_play)
	ZEND_FE(libvlc_media_player_set_pause, arginfo_libvlc_media_player_set_pause)
	ZEND_FE(libvlc_media_player_pause, arginfo_libvlc_media_player_pause)
	ZEND_FE(libvlc_media_player_stop, arginfo_libvlc_media_player_stop)
	ZEND_FE(libvlc_media_player_set_renderer, arginfo_libvlc_media_player_set_renderer)
	ZEND_FE(libvlc_media_player_set_nsobject, arginfo_libvlc_media_player_set_nsobject)
	ZEND_FE(libvlc_media_player_get_nsobject, arginfo_libvlc_media_player_get_nsobject)
	ZEND_FE(libvlc_media_player_set_xwindow, arginfo_libvlc_media_player_set_xwindow)
	ZEND_FE(libvlc_media_player_get_xwindow, arginfo_libvlc_media_player_get_xwindow)
	ZEND_FE(libvlc_media_player_set_hwnd, arginfo_libvlc_media_player_set_hwnd)
	ZEND_FE(libvlc_media_player_get_hwnd, arginfo_libvlc_media_player_get_hwnd)
	ZEND_FE(libvlc_media_player_set_android_context, arginfo_libvlc_media_player_set_android_context)
	ZEND_FE(libvlc_media_player_get_length, arginfo_libvlc_media_player_get_length)
	ZEND_FE(libvlc_media_player_get_time, arginfo_libvlc_media_player_get_time)
	ZEND_FE(libvlc_media_player_set_time, arginfo_libvlc_media_player_set_time)
	ZEND_FE(libvlc_media_player_get_position, arginfo_libvlc_media_player_get_position)
	ZEND_FE(libvlc_media_player_set_position, arginfo_libvlc_media_player_set_position)
	ZEND_FE(libvlc_media_player_set_chapter, arginfo_libvlc_media_player_set_chapter)
	ZEND_FE(libvlc_media_player_get_chapter, arginfo_libvlc_media_player_get_chapter)
	ZEND_FE(libvlc_media_player_get_chapter_count, arginfo_libvlc_media_player_get_chapter_count)
	ZEND_FE(libvlc_media_player_will_play, arginfo_libvlc_media_player_will_play)
	ZEND_FE(libvlc_media_player_get_chapter_count_for_title, arginfo_libvlc_media_player_get_chapter_count_for_title)
	ZEND_FE(libvlc_media_player_set_title, arginfo_libvlc_media_player_set_title)
	ZEND_FE(libvlc_media_player_get_title, arginfo_libvlc_media_player_get_title)
	ZEND_FE(libvlc_media_player_get_title_count, arginfo_libvlc_media_player_get_title_count)
	ZEND_FE(libvlc_media_player_previous_chapter, arginfo_libvlc_media_player_previous_chapter)
	ZEND_FE(libvlc_media_player_next_chapter, arginfo_libvlc_media_player_next_chapter)
	ZEND_FE(libvlc_media_player_get_rate, arginfo_libvlc_media_player_get_rate)
	ZEND_FE(libvlc_media_player_set_rate, arginfo_libvlc_media_player_set_rate)
	ZEND_FE(libvlc_media_player_get_state, arginfo_libvlc_media_player_get_state)
	ZEND_FE(libvlc_media_player_has_vout, arginfo_libvlc_media_player_has_vout)
	ZEND_FE(libvlc_media_player_is_seekable, arginfo_libvlc_media_player_is_seekable)
	ZEND_FE(libvlc_media_player_can_pause, arginfo_libvlc_media_player_can_pause)
	ZEND_FE(libvlc_media_player_program_scrambled, arginfo_libvlc_media_player_program_scrambled)
	ZEND_FE(libvlc_media_player_next_frame, arginfo_libvlc_media_player_next_frame)
	ZEND_FE(libvlc_media_player_navigate, arginfo_libvlc_media_player_navigate)
	ZEND_FE(libvlc_media_player_set_video_title_display, arginfo_libvlc_media_player_set_video_title_display)
	ZEND_FE(libvlc_media_player_add_slave, arginfo_libvlc_media_player_add_slave)
	ZEND_FE(libvlc_toggle_fullscreen, arginfo_libvlc_toggle_fullscreen)
	ZEND_FE(libvlc_set_fullscreen, arginfo_libvlc_set_fullscreen)
	ZEND_FE(libvlc_get_fullscreen, arginfo_libvlc_get_fullscreen)
	ZEND_FE(libvlc_video_set_key_input, arginfo_libvlc_video_set_key_input)
	ZEND_FE(libvlc_video_set_mouse_input, arginfo_libvlc_video_set_mouse_input)
	ZEND_FE(libvlc_video_get_scale, arginfo_libvlc_video_get_scale)
	ZEND_FE(libvlc_video_set_scale, arginfo_libvlc_video_set_scale)
	ZEND_FE(libvlc_video_get_aspect_ratio, arginfo_libvlc_video_get_aspect_ratio)
	ZEND_FE(libvlc_video_set_aspect_ratio, arginfo_libvlc_video_set_aspect_ratio)
	ZEND_FE(libvlc_video_get_spu, arginfo_libvlc_video_get_spu)
	ZEND_FE(libvlc_video_get_spu_count, arginfo_libvlc_video_get_spu_count)
	ZEND_FE(libvlc_video_get_spu_description, arginfo_libvlc_video_get_spu_description)
	ZEND_FE(libvlc_video_set_spu, arginfo_libvlc_video_set_spu)
	ZEND_FE(libvlc_video_get_spu_delay, arginfo_libvlc_video_get_spu_delay)
	ZEND_FE(libvlc_video_set_spu_delay, arginfo_libvlc_video_set_spu_delay)
	ZEND_FE(libvlc_video_get_crop_geometry, arginfo_libvlc_video_get_crop_geometry)
	ZEND_FE(libvlc_video_set_crop_geometry, arginfo_libvlc_video_set_crop_geometry)
	ZEND_FE(libvlc_video_get_teletext, arginfo_libvlc_video_get_teletext)
	ZEND_FE(libvlc_video_set_teletext, arginfo_libvlc_video_set_teletext)
	ZEND_FE(libvlc_video_get_track_count, arginfo_libvlc_video_get_track_count)
	ZEND_FE(libvlc_video_get_track_description, arginfo_libvlc_video_get_track_description)
	ZEND_FE(libvlc_video_get_track, arginfo_libvlc_video_get_track)
	ZEND_FE(libvlc_video_set_track, arginfo_libvlc_video_set_track)
	ZEND_FE(libvlc_video_take_snapshot, arginfo_libvlc_video_take_snapshot)
	ZEND_FE(libvlc_video_set_deinterlace, arginfo_libvlc_video_set_deinterlace)
	ZEND_FE(libvlc_video_get_marquee_int, arginfo_libvlc_video_get_marquee_int)
	ZEND_FE(libvlc_video_get_marquee_string, arginfo_libvlc_video_get_marquee_string)
	ZEND_FE(libvlc_video_set_marquee_int, arginfo_libvlc_video_set_marquee_int)
	ZEND_FE(libvlc_video_set_marquee_string, arginfo_libvlc_video_set_marquee_string)
	ZEND_FE(libvlc_video_get_logo_int, arginfo_libvlc_video_get_logo_int)
	ZEND_FE(libvlc_video_set_logo_int, arginfo_libvlc_video_set_logo_int)
	ZEND_FE(libvlc_video_set_logo_string, arginfo_libvlc_video_set_logo_string)
	ZEND_FE(libvlc_video_get_adjust_int, arginfo_libvlc_video_get_adjust_int)
	ZEND_FE(libvlc_video_set_adjust_int, arginfo_libvlc_video_set_adjust_int)
	ZEND_FE(libvlc_video_get_adjust_float, arginfo_libvlc_video_get_adjust_float)
	ZEND_FE(libvlc_video_set_adjust_float, arginfo_libvlc_video_set_adjust_float)
	ZEND_FE(libvlc_audio_output_list_get, arginfo_libvlc_audio_output_list_get)
	ZEND_FE(libvlc_audio_output_set, arginfo_libvlc_audio_output_set)
	ZEND_FE(libvlc_audio_output_device_enum, arginfo_libvlc_audio_output_device_enum)
	ZEND_FE(libvlc_audio_output_device_list_get, arginfo_libvlc_audio_output_device_list_get)
	ZEND_FE(libvlc_audio_output_device_set, arginfo_libvlc_audio_output_device_set)
	ZEND_FE(libvlc_audio_output_device_get, arginfo_libvlc_audio_output_device_get)
	ZEND_FE(libvlc_audio_toggle_mute, arginfo_libvlc_audio_toggle_mute)
	ZEND_FE(libvlc_audio_get_mute, arginfo_libvlc_audio_get_mute)
	ZEND_FE(libvlc_audio_set_mute, arginfo_libvlc_audio_set_mute)
	ZEND_FE(libvlc_audio_get_volume, arginfo_libvlc_audio_get_volume)
	ZEND_FE(libvlc_audio_set_volume, arginfo_libvlc_audio_set_volume)
	ZEND_FE(libvlc_audio_get_track_count, arginfo_libvlc_audio_get_track_count)
	ZEND_FE(libvlc_audio_get_track_description, arginfo_libvlc_audio_get_track_description)
	ZEND_FE(libvlc_audio_get_track, arginfo_libvlc_audio_get_track)
	ZEND_FE(libvlc_audio_set_track, arginfo_libvlc_audio_set_track)
	ZEND_FE(libvlc_audio_get_channel, arginfo_libvlc_audio_get_channel)
	ZEND_FE(libvlc_audio_set_channel, arginfo_libvlc_audio_set_channel)
	ZEND_FE(libvlc_audio_get_delay, arginfo_libvlc_audio_get_delay)
	ZEND_FE(libvlc_audio_set_delay, arginfo_libvlc_audio_set_delay)
	ZEND_FE(libvlc_audio_equalizer_get_preset_count, arginfo_libvlc_audio_equalizer_get_preset_count)
	ZEND_FE(libvlc_audio_equalizer_get_preset_name, arginfo_libvlc_audio_equalizer_get_preset_name)
	ZEND_FE(libvlc_audio_equalizer_get_band_count, arginfo_libvlc_audio_equalizer_get_band_count)
	ZEND_FE(libvlc_audio_equalizer_get_band_frequency, arginfo_libvlc_audio_equalizer_get_band_frequency)
	ZEND_FE(libvlc_audio_equalizer_new, arginfo_libvlc_audio_equalizer_new)
	ZEND_FE(libvlc_audio_equalizer_new_from_preset, arginfo_libvlc_audio_equalizer_new_from_preset)
	ZEND_FE(libvlc_audio_equalizer_set_preamp, arginfo_libvlc_audio_equalizer_set_preamp)
	ZEND_FE(libvlc_audio_equalizer_get_preamp, arginfo_libvlc_audio_equalizer_get_preamp)
	ZEND_FE(libvlc_audio_equalizer_set_amp_at_index, arginfo_libvlc_audio_equalizer_set_amp_at_index)
	ZEND_FE(libvlc_audio_equalizer_get_amp_at_index, arginfo_libvlc_audio_equalizer_get_amp_at_index)
	ZEND_FE(libvlc_media_player_set_equalizer, arginfo_libvlc_media_player_set_equalizer)
	ZEND_FE(libvlc_media_player_get_role, arginfo_libvlc_media_player_get_role)
	ZEND_FE(libvlc_media_player_set_role, arginfo_libvlc_media_player_set_role)
	ZEND_FE_END
};
