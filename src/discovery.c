/*
 * The media and renderer discoverer functions tools/generate.php leaves to hand.
 */
#include "runtime.h"
#include "../stubs/discovery_arginfo.h"

PHP_FUNCTION(libvlc_media_discoverer_release)
{
	zval *zd;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zd, vlc_ce_libvlc_media_discoverer_t)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_discoverer_t, p_mdis, zd, 1);
	vlc_release(p_mdis, vlc_ce_libvlc_media_discoverer_t);
	libvlc_media_discoverer_release(p_mdis);
}

PHP_FUNCTION(libvlc_media_discoverer_list_get)
{
	zval *zi, *zservices, list;
	zend_long cat;
	libvlc_media_discoverer_description_t **services = NULL;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
		Z_PARAM_LONG(cat)
		Z_PARAM_ZVAL(zservices)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_inst, zi, 1);

	size_t count = libvlc_media_discoverer_list_get(p_inst, (libvlc_media_discoverer_category_t) cat, &services);
	vlc_list_box(&list, (void **) services, (unsigned) count, vlc_ce_libvlc_media_discoverer_description_t);
	/* The elements stay libvlc's until libvlc_media_discoverer_list_release(); only the array goes now. */
	free(services);
	ZEND_TRY_ASSIGN_REF_VALUE(zservices, &list);
	RETURN_LONG((zend_long) count);
}

PHP_FUNCTION(libvlc_media_discoverer_list_release)
{
	HashTable *list;
	zend_long count;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ARRAY_HT(list)
		Z_PARAM_LONG(count)
	ZEND_PARSE_PARAMETERS_END();
	if (!vlc_list_count(count, zend_hash_num_elements(list), 2, 1)) {
		RETURN_THROWS();
	}
	libvlc_media_discoverer_description_t **services = (libvlc_media_discoverer_description_t **) vlc_list_ptrs(list, count, vlc_ce_libvlc_media_discoverer_description_t, 1);
	if (services == NULL) {
		RETURN_THROWS();
	}
	for (zend_long i = 0; i < count; i++) {
		vlc_release(services[i], vlc_ce_libvlc_media_discoverer_description_t);
	}
	libvlc_media_discoverer_list_release(services, (size_t) count);
}

PHP_FUNCTION(libvlc_renderer_discoverer_release)
{
	zval *zd;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zd, vlc_ce_libvlc_renderer_discoverer_t)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_renderer_discoverer_t, p_rd, zd, 1);
	vlc_events_gone(p_rd);
	vlc_release(p_rd, vlc_ce_libvlc_renderer_discoverer_t);
	libvlc_renderer_discoverer_release(p_rd);
}

PHP_FUNCTION(libvlc_renderer_discoverer_list_get)
{
	zval *zi, *zservices, list;
	libvlc_rd_description_t **services = NULL;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zi, vlc_ce_libvlc_instance_t)
		Z_PARAM_ZVAL(zservices)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_instance_t, p_inst, zi, 1);

	size_t count = libvlc_renderer_discoverer_list_get(p_inst, &services);
	vlc_list_box(&list, (void **) services, (unsigned) count, vlc_ce_libvlc_rd_description_t);
	free(services);
	ZEND_TRY_ASSIGN_REF_VALUE(zservices, &list);
	RETURN_LONG((zend_long) count);
}

PHP_FUNCTION(libvlc_renderer_discoverer_list_release)
{
	HashTable *list;
	zend_long count;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ARRAY_HT(list)
		Z_PARAM_LONG(count)
	ZEND_PARSE_PARAMETERS_END();
	if (!vlc_list_count(count, zend_hash_num_elements(list), 2, 1)) {
		RETURN_THROWS();
	}
	libvlc_rd_description_t **services = (libvlc_rd_description_t **) vlc_list_ptrs(list, count, vlc_ce_libvlc_rd_description_t, 1);
	if (services == NULL) {
		RETURN_THROWS();
	}
	for (zend_long i = 0; i < count; i++) {
		vlc_release(services[i], vlc_ce_libvlc_rd_description_t);
	}
	libvlc_renderer_discoverer_list_release(services, (size_t) count);
}

void vlc_register_discovery(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
