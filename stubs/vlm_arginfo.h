/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: f2d81c293523d9a3335664b252635aa4f0d4b5ca */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_vlm_add_broadcast, 0, 8, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, psz_input, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, psz_output, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, i_options, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ppsz_options, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, b_enabled, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b_loop, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_vlm_add_vod, 0, 7, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_instance, libvlc_instance_t, 0)
	ZEND_ARG_TYPE_INFO(0, psz_name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, psz_input, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, i_options, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ppsz_options, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, b_enabled, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, psz_mux, IS_STRING, 1)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_vlm_change_media arginfo_libvlc_vlm_add_broadcast

ZEND_FUNCTION(libvlc_vlm_add_broadcast);
ZEND_FUNCTION(libvlc_vlm_add_vod);
ZEND_FUNCTION(libvlc_vlm_change_media);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(libvlc_vlm_add_broadcast, arginfo_libvlc_vlm_add_broadcast)
	ZEND_FE(libvlc_vlm_add_vod, arginfo_libvlc_vlm_add_vod)
	ZEND_FE(libvlc_vlm_change_media, arginfo_libvlc_vlm_change_media)
	ZEND_FE_END
};
