/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 5cbe440d68bc948cd8b59223410106644c785958 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_list_new, 0, 1, libvlc_media_list_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_list_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_ml, libvlc_media_list_t, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_list_retain arginfo_libvlc_media_list_release

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_list_set_media, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_ml, libvlc_media_list_t, 0)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_list_media, 0, 1, libvlc_media_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_ml, libvlc_media_list_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_list_add_media, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_ml, libvlc_media_list_t, 0)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_list_insert_media, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_ml, libvlc_media_list_t, 0)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_pos, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_list_remove_index, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_ml, libvlc_media_list_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_pos, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_list_count, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_ml, libvlc_media_list_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_list_item_at_index, 0, 2, libvlc_media_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_ml, libvlc_media_list_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_pos, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_list_index_of_item arginfo_libvlc_media_list_add_media

#define arginfo_libvlc_media_list_is_readonly arginfo_libvlc_media_list_count

#define arginfo_libvlc_media_list_lock arginfo_libvlc_media_list_release

#define arginfo_libvlc_media_list_unlock arginfo_libvlc_media_list_release

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_list_event_manager, 0, 1, libvlc_event_manager_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_ml, libvlc_media_list_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_list_player_new, 0, 1, libvlc_media_list_player_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_list_player_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mlp, libvlc_media_list_player_t, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_list_player_retain arginfo_libvlc_media_list_player_release

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_list_player_event_manager, 0, 1, libvlc_event_manager_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_mlp, libvlc_media_list_player_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_list_player_set_media_player, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mlp, libvlc_media_list_player_t, 0)
	ZEND_ARG_OBJ_INFO(0, p_mi, libvlc_media_player_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_list_player_get_media_player, 0, 1, libvlc_media_player_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_mlp, libvlc_media_list_player_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_list_player_set_media_list, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mlp, libvlc_media_list_player_t, 0)
	ZEND_ARG_OBJ_INFO(0, p_mlist, libvlc_media_list_t, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_list_player_play arginfo_libvlc_media_list_player_release

#define arginfo_libvlc_media_list_player_pause arginfo_libvlc_media_list_player_release

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_list_player_set_pause, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mlp, libvlc_media_list_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, do_pause, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_list_player_is_playing, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mlp, libvlc_media_list_player_t, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_list_player_get_state arginfo_libvlc_media_list_player_is_playing

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_list_player_play_item_at_index, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mlp, libvlc_media_list_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_list_player_play_item, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mlp, libvlc_media_list_player_t, 0)
	ZEND_ARG_OBJ_INFO(0, p_md, libvlc_media_t, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_list_player_stop arginfo_libvlc_media_list_player_release

#define arginfo_libvlc_media_list_player_next arginfo_libvlc_media_list_player_is_playing

#define arginfo_libvlc_media_list_player_previous arginfo_libvlc_media_list_player_is_playing

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_list_player_set_playback_mode, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mlp, libvlc_media_list_player_t, 0)
	ZEND_ARG_TYPE_INFO(0, e_mode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_library_new, 0, 1, libvlc_media_library_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_library_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mlib, libvlc_media_library_t, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_library_retain arginfo_libvlc_media_library_release

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_library_load, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mlib, libvlc_media_library_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_library_media_list, 0, 1, libvlc_media_list_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_mlib, libvlc_media_library_t, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(libvlc_media_list_new);
ZEND_FUNCTION(libvlc_media_list_release);
ZEND_FUNCTION(libvlc_media_list_retain);
ZEND_FUNCTION(libvlc_media_list_set_media);
ZEND_FUNCTION(libvlc_media_list_media);
ZEND_FUNCTION(libvlc_media_list_add_media);
ZEND_FUNCTION(libvlc_media_list_insert_media);
ZEND_FUNCTION(libvlc_media_list_remove_index);
ZEND_FUNCTION(libvlc_media_list_count);
ZEND_FUNCTION(libvlc_media_list_item_at_index);
ZEND_FUNCTION(libvlc_media_list_index_of_item);
ZEND_FUNCTION(libvlc_media_list_is_readonly);
ZEND_FUNCTION(libvlc_media_list_lock);
ZEND_FUNCTION(libvlc_media_list_unlock);
ZEND_FUNCTION(libvlc_media_list_event_manager);
ZEND_FUNCTION(libvlc_media_list_player_new);
ZEND_FUNCTION(libvlc_media_list_player_release);
ZEND_FUNCTION(libvlc_media_list_player_retain);
ZEND_FUNCTION(libvlc_media_list_player_event_manager);
ZEND_FUNCTION(libvlc_media_list_player_set_media_player);
ZEND_FUNCTION(libvlc_media_list_player_get_media_player);
ZEND_FUNCTION(libvlc_media_list_player_set_media_list);
ZEND_FUNCTION(libvlc_media_list_player_play);
ZEND_FUNCTION(libvlc_media_list_player_pause);
ZEND_FUNCTION(libvlc_media_list_player_set_pause);
ZEND_FUNCTION(libvlc_media_list_player_is_playing);
ZEND_FUNCTION(libvlc_media_list_player_get_state);
ZEND_FUNCTION(libvlc_media_list_player_play_item_at_index);
ZEND_FUNCTION(libvlc_media_list_player_play_item);
ZEND_FUNCTION(libvlc_media_list_player_stop);
ZEND_FUNCTION(libvlc_media_list_player_next);
ZEND_FUNCTION(libvlc_media_list_player_previous);
ZEND_FUNCTION(libvlc_media_list_player_set_playback_mode);
ZEND_FUNCTION(libvlc_media_library_new);
ZEND_FUNCTION(libvlc_media_library_release);
ZEND_FUNCTION(libvlc_media_library_retain);
ZEND_FUNCTION(libvlc_media_library_load);
ZEND_FUNCTION(libvlc_media_library_media_list);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(libvlc_media_list_new, arginfo_libvlc_media_list_new)
	ZEND_FE(libvlc_media_list_release, arginfo_libvlc_media_list_release)
	ZEND_FE(libvlc_media_list_retain, arginfo_libvlc_media_list_retain)
	ZEND_FE(libvlc_media_list_set_media, arginfo_libvlc_media_list_set_media)
	ZEND_FE(libvlc_media_list_media, arginfo_libvlc_media_list_media)
	ZEND_FE(libvlc_media_list_add_media, arginfo_libvlc_media_list_add_media)
	ZEND_FE(libvlc_media_list_insert_media, arginfo_libvlc_media_list_insert_media)
	ZEND_FE(libvlc_media_list_remove_index, arginfo_libvlc_media_list_remove_index)
	ZEND_FE(libvlc_media_list_count, arginfo_libvlc_media_list_count)
	ZEND_FE(libvlc_media_list_item_at_index, arginfo_libvlc_media_list_item_at_index)
	ZEND_FE(libvlc_media_list_index_of_item, arginfo_libvlc_media_list_index_of_item)
	ZEND_FE(libvlc_media_list_is_readonly, arginfo_libvlc_media_list_is_readonly)
	ZEND_FE(libvlc_media_list_lock, arginfo_libvlc_media_list_lock)
	ZEND_FE(libvlc_media_list_unlock, arginfo_libvlc_media_list_unlock)
	ZEND_FE(libvlc_media_list_event_manager, arginfo_libvlc_media_list_event_manager)
	ZEND_FE(libvlc_media_list_player_new, arginfo_libvlc_media_list_player_new)
	ZEND_FE(libvlc_media_list_player_release, arginfo_libvlc_media_list_player_release)
	ZEND_FE(libvlc_media_list_player_retain, arginfo_libvlc_media_list_player_retain)
	ZEND_FE(libvlc_media_list_player_event_manager, arginfo_libvlc_media_list_player_event_manager)
	ZEND_FE(libvlc_media_list_player_set_media_player, arginfo_libvlc_media_list_player_set_media_player)
	ZEND_FE(libvlc_media_list_player_get_media_player, arginfo_libvlc_media_list_player_get_media_player)
	ZEND_FE(libvlc_media_list_player_set_media_list, arginfo_libvlc_media_list_player_set_media_list)
	ZEND_FE(libvlc_media_list_player_play, arginfo_libvlc_media_list_player_play)
	ZEND_FE(libvlc_media_list_player_pause, arginfo_libvlc_media_list_player_pause)
	ZEND_FE(libvlc_media_list_player_set_pause, arginfo_libvlc_media_list_player_set_pause)
	ZEND_FE(libvlc_media_list_player_is_playing, arginfo_libvlc_media_list_player_is_playing)
	ZEND_FE(libvlc_media_list_player_get_state, arginfo_libvlc_media_list_player_get_state)
	ZEND_FE(libvlc_media_list_player_play_item_at_index, arginfo_libvlc_media_list_player_play_item_at_index)
	ZEND_FE(libvlc_media_list_player_play_item, arginfo_libvlc_media_list_player_play_item)
	ZEND_FE(libvlc_media_list_player_stop, arginfo_libvlc_media_list_player_stop)
	ZEND_FE(libvlc_media_list_player_next, arginfo_libvlc_media_list_player_next)
	ZEND_FE(libvlc_media_list_player_previous, arginfo_libvlc_media_list_player_previous)
	ZEND_FE(libvlc_media_list_player_set_playback_mode, arginfo_libvlc_media_list_player_set_playback_mode)
	ZEND_FE(libvlc_media_library_new, arginfo_libvlc_media_library_new)
	ZEND_FE(libvlc_media_library_release, arginfo_libvlc_media_library_release)
	ZEND_FE(libvlc_media_library_retain, arginfo_libvlc_media_library_retain)
	ZEND_FE(libvlc_media_library_load, arginfo_libvlc_media_library_load)
	ZEND_FE(libvlc_media_library_media_list, arginfo_libvlc_media_library_media_list)
	ZEND_FE_END
};
