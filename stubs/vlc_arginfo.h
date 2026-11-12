/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 0b444ddcb1500fb2e9e74771878a2b9b94c21e62 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libvlc_get_version, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_libvlc_get_compiler arginfo_libvlc_get_version

#define arginfo_libvlc_get_changeset arginfo_libvlc_get_version

ZEND_FUNCTION(libvlc_get_version);
ZEND_FUNCTION(libvlc_get_compiler);
ZEND_FUNCTION(libvlc_get_changeset);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(libvlc_get_version, arginfo_libvlc_get_version)
	ZEND_FE(libvlc_get_compiler, arginfo_libvlc_get_compiler)
	ZEND_FE(libvlc_get_changeset, arginfo_libvlc_get_changeset)
	ZEND_FE_END
};
