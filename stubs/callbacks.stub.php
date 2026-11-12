<?php

/** @generate-class-entries */

/*
 * The libvlc functions that take callbacks. Each takes PHP callables; libvlc's void * user data
 * is the binding's. libvlc calls back on its own threads: the call waits for this PHP thread to
 * reach its next VM interrupt point (any loop iteration, usleep(), a function call), and gets its
 * no-op result if that takes longer than its deadline. Implementations: src/callbacks.c.
 */

/**
 * $f_callback is called as fn(libvlc_event_t $event): void, within 1 s or not at all. Returns 0,
 * or ENOMEM.
 */
function libvlc_event_attach(libvlc_event_manager_t $p_event_manager, int $i_event_type, callable $f_callback): int {}

/** Detaches the record attached with this same callable. */
function libvlc_event_detach(libvlc_event_manager_t $p_event_manager, int $i_event_type, callable $f_callback): void {}

/**
 * $cb is called as fn(int $level, libvlc_log_t $ctx, string $message): void, within 1 s or not at
 * all; $ctx is valid only during the call. Replaces the instance's previous log callable.
 */
function libvlc_log_set(libvlc_instance_t $p_instance, callable $cb): void {}

function libvlc_log_unset(libvlc_instance_t $p_instance): void {}

/** FILE *: an address. */
function libvlc_log_set_file(libvlc_instance_t $p_instance, int $stream): void {}

function libvlc_log_get_object(libvlc_log_t $ctx, ?string &$name, ?string &$header, ?int &$id): void {}

function libvlc_log_get_context(libvlc_log_t $ctx, ?string &$module, ?string &$file, ?int &$line): void {}

/**
 * Media whose bytes PHP serves; each callable gets 5 s:
 * $open_cb fn(?int &$size): int (0, or non-zero for an error; set $size to the length or leave it),
 * $read_cb fn(int $len): string|int (at most $len bytes, '' at the end, or -1 for an error),
 * $seek_cb fn(int $offset): int (0 or -1), $close_cb fn(): void. A callable that throws, or does
 * not answer in time, is an error for libvlc.
 */
function libvlc_media_new_callbacks(libvlc_instance_t $instance, callable $open_cb, callable $read_cb, ?callable $seek_cb, ?callable $close_cb): ?libvlc_media_t {}

/**
 * Decoded audio to PHP instead of an output. Called without libvlc waiting for them:
 * $play fn(string $samples, int $count, int $pts) with $count frames of the set format,
 * $pause / $resume / $flush fn(int $pts), $drain fn().
 */
function libvlc_audio_set_callbacks(libvlc_media_player_t $mp, callable $play, ?callable $pause, ?callable $resume, ?callable $flush, ?callable $drain): void {}

/** $set_volume fn(float $volume, bool $mute), called without libvlc waiting for it. */
function libvlc_audio_set_volume_callback(libvlc_media_player_t $mp, ?callable $set_volume): void {}

/**
 * $setup fn(string &$format, int &$rate, int &$channels): int (0 to accept), within 5 s, else the
 * audio is refused; $cleanup fn(), called without libvlc waiting for it.
 */
function libvlc_audio_set_format_callbacks(libvlc_media_player_t $mp, callable $setup, ?callable $cleanup): void {}

/** The format $play's samples come in; $format is a four-character code ("S16N", "FL32"). */
function libvlc_audio_set_format(libvlc_media_player_t $mp, string $format, int $rate, int $channels): void {}

/**
 * Decoded video into memory PHP owns. $lock fn(): array (a list of plane addresses), within
 * 100 ms, else libvlc renders into a scratch buffer the binding owns; $unlock fn(int $picture,
 * array $planes) and $display fn(int $picture) are called without libvlc waiting for them.
 */
function libvlc_video_set_callbacks(libvlc_media_player_t $mp, callable $lock, ?callable $unlock, ?callable $display): void {}

/**
 * $setup fn(string &$chroma, int &$width, int &$height, array &$pitches, array &$lines): int (the
 * number of picture buffers, 0 to refuse), within 5 s; $pitches and $lines are lists of at most 5
 * ints. $cleanup fn(), called without libvlc waiting for it.
 */
function libvlc_video_set_format_callbacks(libvlc_media_player_t $mp, callable $setup, ?callable $cleanup): void {}

/** The picture format $lock's planes are rendered in. */
function libvlc_video_set_format(libvlc_media_player_t $mp, string $chroma, int $width, int $height, int $pitch): void {}

/**
 * Each non-null callable of $p_cbs is called without libvlc waiting for it, with the C
 * parameters after p_data; a libvlc_dialog_id stays valid until it is answered or dismissed.
 * null removes them.
 */
function libvlc_dialog_set_callbacks(libvlc_instance_t $p_instance, ?libvlc_dialog_cbs $p_cbs): void {}

/** $cb is called as fn(): void when the instance is asked to exit, within 1 s or not at all; null removes it. */
function libvlc_set_exit_handler(libvlc_instance_t $p_instance, ?callable $cb): void {}
