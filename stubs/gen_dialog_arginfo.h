/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: a28b13cfac8cda9971c6e142e9c47c30709404b9 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_dialog_set_context, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, p_id, libvlc_dialog_id, 0)
	ZEND_ARG_TYPE_INFO(0, p_context, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_dialog_get_context, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_id, libvlc_dialog_id, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_dialog_post_login, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_id, libvlc_dialog_id, 0)
	ZEND_ARG_TYPE_INFO(0, psz_username, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, psz_password, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, b_store, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_dialog_post_action, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, p_id, libvlc_dialog_id, 0)
	ZEND_ARG_TYPE_INFO(0, i_action, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_dialog_dismiss arginfo_libvlc_dialog_get_context

ZEND_FUNCTION(libvlc_dialog_set_context);
ZEND_FUNCTION(libvlc_dialog_get_context);
ZEND_FUNCTION(libvlc_dialog_post_login);
ZEND_FUNCTION(libvlc_dialog_post_action);
ZEND_FUNCTION(libvlc_dialog_dismiss);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(libvlc_dialog_set_context, arginfo_libvlc_dialog_set_context)
	ZEND_FE(libvlc_dialog_get_context, arginfo_libvlc_dialog_get_context)
	ZEND_FE(libvlc_dialog_post_login, arginfo_libvlc_dialog_post_login)
	ZEND_FE(libvlc_dialog_post_action, arginfo_libvlc_dialog_post_action)
	ZEND_FE(libvlc_dialog_dismiss, arginfo_libvlc_dialog_dismiss)
	ZEND_FE_END
};
