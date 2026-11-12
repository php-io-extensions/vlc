<?php

/** @generate-class-entries */

/*
 * The bound libvlc functions. The implementation is the PHP_FUNCTION of the same name in
 * src/libvlc.c. A handle that was released is refused (ValueError): libvlc would dereference it.
 */

/* libvlc.h */

/**
 * The calling thread's last libvlc error message, null when there is none. Before the process's
 * first libvlc_new() libvlc has no error state, and the result is unspecified.
 */
function libvlc_errmsg(): ?string {}

/** Error before the process's first libvlc_new(): libvlc would abort the process. */
function libvlc_clearerr(): void {}

/**
 * Sets the calling thread's error message and returns it. $fmt and $args are formatted by PHP's
 * sprintf (same conversions as C printf for %s, %d, %u, %x, %f, %c, %%), then handed to libvlc
 * as one string.
 */
function libvlc_printerr(string $fmt, mixed ...$args): string {}

/** $argv is a list of strings; $argc may not exceed its length (ValueError). */
function libvlc_new(int $argc, array $argv): ?libvlc_instance_t {}

function libvlc_release(libvlc_instance_t $p_instance): void {}

function libvlc_retain(libvlc_instance_t $p_instance): void {}

function libvlc_add_intf(libvlc_instance_t $p_instance, ?string $name): int {}

function libvlc_set_user_agent(libvlc_instance_t $p_instance, string $name, string $http): void {}

function libvlc_set_app_id(libvlc_instance_t $p_instance, string $id, string $version, string $icon): void {}

/** Frees memory libvlc allocated, by address. */
function libvlc_free(int $ptr): void {}

function libvlc_event_type_name(int $event_type): ?string {}

/** Releases the whole list; every element handle reads 0 from pointer() afterwards. */
function libvlc_module_description_list_release(libvlc_module_description_t $p_list): void {}

function libvlc_audio_filter_list_get(libvlc_instance_t $p_instance): ?libvlc_module_description_t {}

function libvlc_video_filter_list_get(libvlc_instance_t $p_instance): ?libvlc_module_description_t {}

function libvlc_clock(): int {}

/* libvlc_media.h */

function libvlc_media_new_location(libvlc_instance_t $p_instance, string $psz_mrl): ?libvlc_media_t {}

function libvlc_media_new_path(libvlc_instance_t $p_instance, string $path): ?libvlc_media_t {}

function libvlc_media_new_fd(libvlc_instance_t $p_instance, int $fd): ?libvlc_media_t {}

function libvlc_media_new_as_node(libvlc_instance_t $p_instance, string $psz_name): ?libvlc_media_t {}

function libvlc_media_add_option(libvlc_media_t $p_md, string $psz_options): void {}

function libvlc_media_add_option_flag(libvlc_media_t $p_md, string $psz_options, int $i_flags): void {}

function libvlc_media_retain(libvlc_media_t $p_md): void {}

function libvlc_media_release(libvlc_media_t $p_md): void {}

function libvlc_media_get_mrl(libvlc_media_t $p_md): ?string {}

function libvlc_media_duplicate(libvlc_media_t $p_md): ?libvlc_media_t {}

function libvlc_media_get_meta(libvlc_media_t $p_md, int $e_meta): ?string {}

function libvlc_media_set_meta(libvlc_media_t $p_md, int $e_meta, ?string $psz_value): void {}

function libvlc_media_save_meta(libvlc_media_t $p_md): int {}

function libvlc_media_get_state(libvlc_media_t $p_md): int {}

/** Fills $p_stats; returns libvlc's int result (non-zero on success). */
function libvlc_media_get_stats(libvlc_media_t $p_md, libvlc_media_stats_t $p_stats): int {}

/** A new reference to the media's sub-items list. */
function libvlc_media_subitems(libvlc_media_t $p_md): ?libvlc_media_list_t {}

function libvlc_media_event_manager(libvlc_media_t $p_md): libvlc_event_manager_t {}

function libvlc_media_get_duration(libvlc_media_t $p_md): int {}

function libvlc_media_parse_with_options(libvlc_media_t $p_md, int $parse_flag, int $timeout): int {}

function libvlc_media_parse_stop(libvlc_media_t $p_md): void {}

function libvlc_media_get_parsed_status(libvlc_media_t $p_md): int {}

/** void *: an address. */
function libvlc_media_set_user_data(libvlc_media_t $p_md, int $p_new_user_data): void {}

function libvlc_media_get_user_data(libvlc_media_t $p_md): int {}

/** Fills $tracks with a list of libvlc_media_track_t; returns the count. libvlc owns them until libvlc_media_tracks_release(). */
function libvlc_media_tracks_get(libvlc_media_t $p_md, ?array &$tracks): int {}

function libvlc_media_get_codec_description(int $i_type, int $i_codec): ?string {}

/** $p_tracks is a list of libvlc_media_track_t; $i_count may not exceed its length (ValueError). Every released handle reads 0 from pointer() afterwards. */
function libvlc_media_tracks_release(array $p_tracks, int $i_count): void {}

function libvlc_media_get_type(libvlc_media_t $p_md): int {}

function libvlc_media_slaves_add(libvlc_media_t $p_md, int $i_type, int $i_priority, string $psz_uri): int {}

function libvlc_media_slaves_clear(libvlc_media_t $p_md): void {}

/** Fills $ppp_slaves with a list of libvlc_media_slave_t; returns the count. */
function libvlc_media_slaves_get(libvlc_media_t $p_md, ?array &$ppp_slaves): int {}

/** $pp_slaves is a list of libvlc_media_slave_t; $i_count may not exceed its length (ValueError). */
function libvlc_media_slaves_release(array $pp_slaves, int $i_count): void {}
