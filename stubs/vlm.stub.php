<?php

/** @generate-class-entries */

/*
 * The libvlc_vlm.h functions tools/generate.php leaves to hand: the option string lists.
 * Implementations: src/vlm.c. $ppsz_options is a list of strings; $i_options may not exceed its
 * length (ValueError). $psz_name is not nullable: libvlc dereferences it.
 */

function libvlc_vlm_add_broadcast(libvlc_instance_t $p_instance, string $psz_name, ?string $psz_input, ?string $psz_output, int $i_options, array $ppsz_options, int $b_enabled, int $b_loop): int {}

function libvlc_vlm_add_vod(libvlc_instance_t $p_instance, string $psz_name, ?string $psz_input, int $i_options, array $ppsz_options, int $b_enabled, ?string $psz_mux): int {}

function libvlc_vlm_change_media(libvlc_instance_t $p_instance, string $psz_name, ?string $psz_input, ?string $psz_output, int $i_options, array $ppsz_options, int $b_enabled, int $b_loop): int {}
