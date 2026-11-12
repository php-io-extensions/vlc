/*
 * vlc: 1:1 bindings of libvlc 3.0. Handles and constants keep their C names; dropping the last
 * PHP reference does not release the native object.
 */
#include "queue.h"
#include "ext/standard/info.h"
#include "../stubs/vlc_arginfo.h"

PHP_FUNCTION(libvlc_get_version)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_STRING(libvlc_get_version());
}

PHP_FUNCTION(libvlc_get_compiler)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_STRING(libvlc_get_compiler());
}

PHP_FUNCTION(libvlc_get_changeset)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_STRING(libvlc_get_changeset());
}

ZEND_DECLARE_MODULE_GLOBALS(vlc)

static PHP_GINIT_FUNCTION(vlc)
{
#if defined(COMPILE_DL_VLC) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	zend_hash_init(&vlc_globals->boxes, 32, NULL, NULL, 1);
	zend_hash_init(&vlc_globals->refs, 32, NULL, NULL, 1);
	zend_hash_init(&vlc_globals->held, 8, NULL, NULL, 1);
}

static PHP_GSHUTDOWN_FUNCTION(vlc)
{
	zend_hash_destroy(&vlc_globals->boxes);
	zend_hash_destroy(&vlc_globals->refs);
	zend_hash_destroy(&vlc_globals->held);
}

PHP_MINIT_FUNCTION(vlc)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
	vlc_register_types();
	vlc_register_constants(module_number);
	vlc_register_libvlc();
	vlc_register_gen_player();
	vlc_register_player();
	vlc_register_gen_lists();
	vlc_register_gen_discovery();
	vlc_register_discovery();
	vlc_register_gen_vlm();
	vlc_register_vlm();
	vlc_register_gen_dialog();
	vlc_register_callbacks();
	vlc_queue_minit();
#ifdef VLC_PROBES
	REGISTER_BOOL_CONSTANT("VLC_PROBES", true, CONST_PERSISTENT);
#endif
	return SUCCESS;
}

PHP_RINIT_FUNCTION(vlc)
{
#if defined(COMPILE_DL_VLC) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	vlc_queue_rinit();
	return SUCCESS;
}

/* Every callable the request handed libvlc gives its no-op from now on; libvlc keeps the records. */
PHP_RSHUTDOWN_FUNCTION(vlc)
{
	vlc_queue_rshutdown();
	return SUCCESS;
}

PHP_MINFO_FUNCTION(vlc)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "vlc support", "enabled");
	php_info_print_table_row(2, "Version", PHP_VLC_VERSION);
	php_info_print_table_row(2, "libvlc version", libvlc_get_version());
	php_info_print_table_end();
}

zend_module_entry vlc_module_entry = {
	STANDARD_MODULE_HEADER,
	"vlc",
	NULL,
	PHP_MINIT(vlc),
	NULL,
	PHP_RINIT(vlc),
	PHP_RSHUTDOWN(vlc),
	PHP_MINFO(vlc),
	PHP_VLC_VERSION,
	PHP_MODULE_GLOBALS(vlc),
	PHP_GINIT(vlc),
	PHP_GSHUTDOWN(vlc),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_VLC
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(vlc)
#endif
