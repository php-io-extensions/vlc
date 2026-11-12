/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: d012213a1114570c57b8694d1184f654bc8cbf31 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_discoverer_new, 0, 2, libvlc_media_discoverer_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_inst, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_name, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_discoverer_start, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_mdis, libvlc_media_discoverer_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_discoverer_stop, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mdis, libvlc_media_discoverer_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_media_discoverer_media_list, 0, 1, libvlc_media_list_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_mdis, libvlc_media_discoverer_t, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_media_discoverer_is_running arginfo_libvlc_media_discoverer_start

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_renderer_item_hold, 0, 1, libvlc_renderer_item_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_item, libvlc_renderer_item_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_renderer_item_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_item, libvlc_renderer_item_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_renderer_item_name, 0, 1, IS_STRING, 1)
	ZEND_ARG_OBJ_INFO(0, p_item, libvlc_renderer_item_t, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_renderer_item_type arginfo_libvlc_renderer_item_name

#define arginfo_libvlc_renderer_item_icon_uri arginfo_libvlc_renderer_item_name

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_renderer_item_flags, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_item, libvlc_renderer_item_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_renderer_discoverer_new, 0, 2, libvlc_renderer_discoverer_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_inst, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_name, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_renderer_discoverer_start, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_rd, libvlc_renderer_discoverer_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_renderer_discoverer_stop, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_rd, libvlc_renderer_discoverer_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_libvlc_renderer_discoverer_event_manager, 0, 1, libvlc_event_manager_t, 1)
	ZEND_ARG_OBJ_INFO(0, p_rd, libvlc_renderer_discoverer_t, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(libvlc_media_discoverer_new);
ZEND_FUNCTION(libvlc_media_discoverer_start);
ZEND_FUNCTION(libvlc_media_discoverer_stop);
ZEND_FUNCTION(libvlc_media_discoverer_media_list);
ZEND_FUNCTION(libvlc_media_discoverer_is_running);
ZEND_FUNCTION(libvlc_renderer_item_hold);
ZEND_FUNCTION(libvlc_renderer_item_release);
ZEND_FUNCTION(libvlc_renderer_item_name);
ZEND_FUNCTION(libvlc_renderer_item_type);
ZEND_FUNCTION(libvlc_renderer_item_icon_uri);
ZEND_FUNCTION(libvlc_renderer_item_flags);
ZEND_FUNCTION(libvlc_renderer_discoverer_new);
ZEND_FUNCTION(libvlc_renderer_discoverer_start);
ZEND_FUNCTION(libvlc_renderer_discoverer_stop);
ZEND_FUNCTION(libvlc_renderer_discoverer_event_manager);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(libvlc_media_discoverer_new, arginfo_libvlc_media_discoverer_new)
	ZEND_FE(libvlc_media_discoverer_start, arginfo_libvlc_media_discoverer_start)
	ZEND_FE(libvlc_media_discoverer_stop, arginfo_libvlc_media_discoverer_stop)
	ZEND_FE(libvlc_media_discoverer_media_list, arginfo_libvlc_media_discoverer_media_list)
	ZEND_FE(libvlc_media_discoverer_is_running, arginfo_libvlc_media_discoverer_is_running)
	ZEND_FE(libvlc_renderer_item_hold, arginfo_libvlc_renderer_item_hold)
	ZEND_FE(libvlc_renderer_item_release, arginfo_libvlc_renderer_item_release)
	ZEND_FE(libvlc_renderer_item_name, arginfo_libvlc_renderer_item_name)
	ZEND_FE(libvlc_renderer_item_type, arginfo_libvlc_renderer_item_type)
	ZEND_FE(libvlc_renderer_item_icon_uri, arginfo_libvlc_renderer_item_icon_uri)
	ZEND_FE(libvlc_renderer_item_flags, arginfo_libvlc_renderer_item_flags)
	ZEND_FE(libvlc_renderer_discoverer_new, arginfo_libvlc_renderer_discoverer_new)
	ZEND_FE(libvlc_renderer_discoverer_start, arginfo_libvlc_renderer_discoverer_start)
	ZEND_FE(libvlc_renderer_discoverer_stop, arginfo_libvlc_renderer_discoverer_stop)
	ZEND_FE(libvlc_renderer_discoverer_event_manager, arginfo_libvlc_renderer_discoverer_event_manager)
	ZEND_FE_END
};
