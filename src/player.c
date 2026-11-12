/*
 * The libvlc_media_player.h functions tools/generate.php leaves to hand.
 */
#include "runtime.h"
#include "../stubs/player_arginfo.h"

PHP_FUNCTION(libvlc_track_description_list_release)
{
	zval *zl;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zl, vlc_ce_libvlc_track_description_t)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_track_description_t, p_track_description, zl, 1);
	for (libvlc_track_description_t *node = p_track_description; node != NULL; node = node->p_next) {
		vlc_release(node, vlc_ce_libvlc_track_description_t);
	}
	libvlc_track_description_list_release(p_track_description);
}

PHP_FUNCTION(libvlc_audio_output_list_release)
{
	zval *zl;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zl, vlc_ce_libvlc_audio_output_t)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_audio_output_t, p_list, zl, 1);
	for (libvlc_audio_output_t *node = p_list; node != NULL; node = node->p_next) {
		vlc_release(node, vlc_ce_libvlc_audio_output_t);
	}
	libvlc_audio_output_list_release(p_list);
}

PHP_FUNCTION(libvlc_audio_output_device_list_release)
{
	zval *zl;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zl, vlc_ce_libvlc_audio_output_device_t)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_audio_output_device_t, p_list, zl, 1);
	for (libvlc_audio_output_device_t *node = p_list; node != NULL; node = node->p_next) {
		vlc_release(node, vlc_ce_libvlc_audio_output_device_t);
	}
	libvlc_audio_output_device_list_release(p_list);
}

PHP_FUNCTION(libvlc_audio_equalizer_release)
{
	zval *ze;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ze, vlc_ce_libvlc_equalizer_t)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_equalizer_t, p_equalizer, ze, 1);
	vlc_release(p_equalizer, vlc_ce_libvlc_equalizer_t);
	libvlc_audio_equalizer_release(p_equalizer);
}

PHP_FUNCTION(libvlc_video_get_size)
{
	zval *zmp, *zx, *zy;
	zend_long num;
	unsigned x = 0, y = 0;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(zmp, vlc_ce_libvlc_media_player_t)
		Z_PARAM_LONG(num)
		Z_PARAM_ZVAL(zx)
		Z_PARAM_ZVAL(zy)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_player_t, p_mi, zmp, 1);

	int result = libvlc_video_get_size(p_mi, (unsigned) num, &x, &y);
	ZEND_TRY_ASSIGN_REF_LONG(zx, x);
	ZEND_TRY_ASSIGN_REF_LONG(zy, y);
	RETURN_LONG(result);
}

PHP_FUNCTION(libvlc_video_get_cursor)
{
	zval *zmp, *zx, *zy;
	zend_long num;
	int x = 0, y = 0;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(zmp, vlc_ce_libvlc_media_player_t)
		Z_PARAM_LONG(num)
		Z_PARAM_ZVAL(zx)
		Z_PARAM_ZVAL(zy)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_player_t, p_mi, zmp, 1);

	int result = libvlc_video_get_cursor(p_mi, (unsigned) num, &x, &y);
	ZEND_TRY_ASSIGN_REF_LONG(zx, x);
	ZEND_TRY_ASSIGN_REF_LONG(zy, y);
	RETURN_LONG(result);
}

PHP_FUNCTION(libvlc_video_new_viewpoint)
{
	ZEND_PARSE_PARAMETERS_NONE();
	libvlc_video_viewpoint_t *vp = libvlc_video_new_viewpoint();
	if (vp == NULL) {
		RETURN_NULL();
	}
	vlc_viewpoint_to(vp, return_value);
	libvlc_free(vp);
}

static double vlc_prop_double(zend_object *obj, const char *name)
{
	return zval_get_double(zend_read_property(obj->ce, obj, name, strlen(name), true, NULL));
}

PHP_FUNCTION(libvlc_video_update_viewpoint)
{
	zval *zmp, *zvp;
	bool absolute;
	libvlc_video_viewpoint_t vp;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(zmp, vlc_ce_libvlc_media_player_t)
		Z_PARAM_OBJECT_OF_CLASS(zvp, vlc_ce_libvlc_video_viewpoint_t)
		Z_PARAM_BOOL(absolute)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_player_t, p_mi, zmp, 1);

	vp.f_yaw = (float) vlc_prop_double(Z_OBJ_P(zvp), "f_yaw");
	vp.f_pitch = (float) vlc_prop_double(Z_OBJ_P(zvp), "f_pitch");
	vp.f_roll = (float) vlc_prop_double(Z_OBJ_P(zvp), "f_roll");
	vp.f_field_of_view = (float) vlc_prop_double(Z_OBJ_P(zvp), "f_field_of_view");
	RETURN_LONG(libvlc_video_update_viewpoint(p_mi, &vp, absolute));
}

PHP_FUNCTION(libvlc_media_player_get_full_title_descriptions)
{
	zval *zmp, *ztitles, list;
	libvlc_title_description_t **titles = NULL;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zmp, vlc_ce_libvlc_media_player_t)
		Z_PARAM_ZVAL(ztitles)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_player_t, p_mi, zmp, 1);

	int count = libvlc_media_player_get_full_title_descriptions(p_mi, &titles);
	vlc_list_box(&list, (void **) titles, count > 0 ? (unsigned) count : 0, vlc_ce_libvlc_title_description_t);
	/* The elements stay libvlc's until libvlc_title_descriptions_release(); only the array goes now. */
	free(titles);
	ZEND_TRY_ASSIGN_REF_VALUE(ztitles, &list);
	RETURN_LONG(count);
}

PHP_FUNCTION(libvlc_title_descriptions_release)
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
	libvlc_title_description_t **titles = (libvlc_title_description_t **) vlc_list_ptrs(list, count, vlc_ce_libvlc_title_description_t, 1);
	if (titles == NULL) {
		RETURN_THROWS();
	}
	for (zend_long i = 0; i < count; i++) {
		vlc_release(titles[i], vlc_ce_libvlc_title_description_t);
	}
	libvlc_title_descriptions_release(titles, (unsigned) count);
}

PHP_FUNCTION(libvlc_media_player_get_full_chapter_descriptions)
{
	zval *zmp, *zchapters, list;
	zend_long title;
	libvlc_chapter_description_t **chapters = NULL;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(zmp, vlc_ce_libvlc_media_player_t)
		Z_PARAM_LONG(title)
		Z_PARAM_ZVAL(zchapters)
	ZEND_PARSE_PARAMETERS_END();
	VLC_ARG(libvlc_media_player_t, p_mi, zmp, 1);

	int count = libvlc_media_player_get_full_chapter_descriptions(p_mi, (int) title, &chapters);
	vlc_list_box(&list, (void **) chapters, count > 0 ? (unsigned) count : 0, vlc_ce_libvlc_chapter_description_t);
	free(chapters);
	ZEND_TRY_ASSIGN_REF_VALUE(zchapters, &list);
	RETURN_LONG(count);
}

PHP_FUNCTION(libvlc_chapter_descriptions_release)
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
	libvlc_chapter_description_t **chapters = (libvlc_chapter_description_t **) vlc_list_ptrs(list, count, vlc_ce_libvlc_chapter_description_t, 1);
	if (chapters == NULL) {
		RETURN_THROWS();
	}
	for (zend_long i = 0; i < count; i++) {
		vlc_release(chapters[i], vlc_ce_libvlc_chapter_description_t);
	}
	libvlc_chapter_descriptions_release(chapters, (unsigned) count);
}

void vlc_register_player(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
