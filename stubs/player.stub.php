<?php

/** @generate-class-entries */

/*
 * The libvlc_media_player.h functions tools/generate.php leaves to hand: out-pointers, list
 * arrays, the viewpoint struct, and the releases that free handles. Implementations: src/player.c.
 */

/** Releases the whole list; every element handle reads 0 from pointer() afterwards. */
function libvlc_track_description_list_release(libvlc_track_description_t $p_track_description): void {}

/** Releases the whole list; every element handle reads 0 from pointer() afterwards. */
function libvlc_audio_output_list_release(libvlc_audio_output_t $p_list): void {}

/** Releases the whole list; every element handle reads 0 from pointer() afterwards. */
function libvlc_audio_output_device_list_release(libvlc_audio_output_device_t $p_list): void {}

/** The handle reads 0 from pointer() afterwards. */
function libvlc_audio_equalizer_release(libvlc_equalizer_t $p_equalizer): void {}

function libvlc_video_get_size(libvlc_media_player_t $p_mi, int $num, ?int &$px, ?int &$py): int {}

function libvlc_video_get_cursor(libvlc_media_player_t $p_mi, int $num, ?int &$px, ?int &$py): int {}

/** A new viewpoint, as a value copy (libvlc's allocation is freed at once); null when libvlc is out of memory. */
function libvlc_video_new_viewpoint(): ?libvlc_video_viewpoint_t {}

function libvlc_video_update_viewpoint(libvlc_media_player_t $p_mi, libvlc_video_viewpoint_t $p_viewpoint, bool $b_absolute): int {}

/** Fills $titles with a list of libvlc_title_description_t; returns the count, -1 on error. */
function libvlc_media_player_get_full_title_descriptions(libvlc_media_player_t $p_mi, ?array &$titles): int {}

/** $p_titles is a list of libvlc_title_description_t; $i_count may not exceed its length (ValueError). */
function libvlc_title_descriptions_release(array $p_titles, int $i_count): void {}

/** Fills $pp_chapters with a list of libvlc_chapter_description_t; returns the count, -1 on error. */
function libvlc_media_player_get_full_chapter_descriptions(libvlc_media_player_t $p_mi, int $i_chapters_of_title, ?array &$pp_chapters): int {}

/** $p_chapters is a list of libvlc_chapter_description_t; $i_count may not exceed its length (ValueError). */
function libvlc_chapter_descriptions_release(array $p_chapters, int $i_count): void {}
