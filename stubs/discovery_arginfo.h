/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 66e3aa3ef87f75459903f0078e45616451edced8 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_discoverer_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_mdis, libvlc_media_discoverer_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_discoverer_list_get, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_inst, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, i_cat, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, ppp_services, IS_ARRAY, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_media_discoverer_list_release, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, pp_services, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, i_count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_renderer_discoverer_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_rd, libvlc_renderer_discoverer_t, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_renderer_discoverer_list_get, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_inst, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(1, ppp_services, IS_ARRAY, 1)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_renderer_discoverer_list_release arginfo_libvlc_media_discoverer_list_release

ZEND_FUNCTION(libvlc_media_discoverer_release);
ZEND_FUNCTION(libvlc_media_discoverer_list_get);
ZEND_FUNCTION(libvlc_media_discoverer_list_release);
ZEND_FUNCTION(libvlc_renderer_discoverer_release);
ZEND_FUNCTION(libvlc_renderer_discoverer_list_get);
ZEND_FUNCTION(libvlc_renderer_discoverer_list_release);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(libvlc_media_discoverer_release, arginfo_libvlc_media_discoverer_release)
	ZEND_FE(libvlc_media_discoverer_list_get, arginfo_libvlc_media_discoverer_list_get)
	ZEND_FE(libvlc_media_discoverer_list_release, arginfo_libvlc_media_discoverer_list_release)
	ZEND_FE(libvlc_renderer_discoverer_release, arginfo_libvlc_renderer_discoverer_release)
	ZEND_FE(libvlc_renderer_discoverer_list_get, arginfo_libvlc_renderer_discoverer_list_get)
	ZEND_FE(libvlc_renderer_discoverer_list_release, arginfo_libvlc_renderer_discoverer_list_release)
	ZEND_FE_END
};
