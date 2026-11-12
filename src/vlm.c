/*
 * The libvlc_vlm.h functions tools/generate.php leaves to hand: the option string lists.
 */
#include "runtime.h"
#include "../stubs/vlm_arginfo.h"

#define VLM_STR(s) ((s) != NULL ? ZSTR_VAL(s) : NULL)

PHP_FUNCTION(libvlc_vlm_add_broadcast)
{
	zval *zi;
	zend_string *name, *input, *output;
	zend_long n, enabled, loop;
	HashTable *options;

	ZEND_PARSE_PARAMETERS_START(8, 8)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
		Z_PARAM_STR(name)
		Z_PARAM_STR_OR_NULL(input)
		Z_PARAM_STR_OR_NULL(output)
		Z_PARAM_LONG(n)
		Z_PARAM_ARRAY_HT(options)
		Z_PARAM_LONG(enabled)
		Z_PARAM_LONG(loop)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_instance, zi, 1);
	if (!vlc_list_count(n, zend_hash_num_elements(options), 5, 6)) {
		RETURN_THROWS();
	}
	const char **c_options = vlc_strings_from(options, n, 6);
	if (c_options == NULL) {
		RETURN_THROWS();
	}
	RETVAL_LONG(libvlc_vlm_add_broadcast(p_instance, VLM_STR(name), VLM_STR(input), VLM_STR(output), (int) n, c_options, (int) enabled, (int) loop));
	efree(c_options);
}

PHP_FUNCTION(libvlc_vlm_add_vod)
{
	zval *zi;
	zend_string *name, *input, *mux;
	zend_long n, enabled;
	HashTable *options;

	ZEND_PARSE_PARAMETERS_START(7, 7)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
		Z_PARAM_STR(name)
		Z_PARAM_STR_OR_NULL(input)
		Z_PARAM_LONG(n)
		Z_PARAM_ARRAY_HT(options)
		Z_PARAM_LONG(enabled)
		Z_PARAM_STR_OR_NULL(mux)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_instance, zi, 1);
	if (!vlc_list_count(n, zend_hash_num_elements(options), 4, 5)) {
		RETURN_THROWS();
	}
	const char **c_options = vlc_strings_from(options, n, 5);
	if (c_options == NULL) {
		RETURN_THROWS();
	}
	RETVAL_LONG(libvlc_vlm_add_vod(p_instance, VLM_STR(name), VLM_STR(input), (int) n, c_options, (int) enabled, VLM_STR(mux)));
	efree(c_options);
}

PHP_FUNCTION(libvlc_vlm_change_media)
{
	zval *zi;
	zend_string *name, *input, *output;
	zend_long n, enabled, loop;
	HashTable *options;

	ZEND_PARSE_PARAMETERS_START(8, 8)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
		Z_PARAM_STR(name)
		Z_PARAM_STR_OR_NULL(input)
		Z_PARAM_STR_OR_NULL(output)
		Z_PARAM_LONG(n)
		Z_PARAM_ARRAY_HT(options)
		Z_PARAM_LONG(enabled)
		Z_PARAM_LONG(loop)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_instance, zi, 1);
	if (!vlc_list_count(n, zend_hash_num_elements(options), 5, 6)) {
		RETURN_THROWS();
	}
	const char **c_options = vlc_strings_from(options, n, 6);
	if (c_options == NULL) {
		RETURN_THROWS();
	}
	RETVAL_LONG(libvlc_vlm_change_media(p_instance, VLM_STR(name), VLM_STR(input), VLM_STR(output), (int) n, c_options, (int) enabled, (int) loop));
	efree(c_options);
}

void vlc_register_vlm(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
