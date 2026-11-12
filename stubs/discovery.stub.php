<?php

/** @generate-class-entries */

/*
 * The libvlc_media_discoverer.h and libvlc_renderer_discoverer.h functions tools/generate.php
 * leaves to hand: the service arrays and the releases that free handles. Implementations:
 * src/discovery.c.
 */

/** The handle reads 0 from pointer() afterwards. */
function libvlc_media_discoverer_release(libvlc_media_discoverer_t $p_mdis): void {}

/** Fills $ppp_services with a list of libvlc_media_discoverer_description_t; returns the count. */
function libvlc_media_discoverer_list_get(libvlc_instance_t $p_inst, int $i_cat, ?array &$ppp_services): int {}

/** $pp_services is a list of libvlc_media_discoverer_description_t; $i_count may not exceed its length (ValueError). */
function libvlc_media_discoverer_list_release(array $pp_services, int $i_count): void {}

/** The handle reads 0 from pointer() afterwards. */
function libvlc_renderer_discoverer_release(libvlc_renderer_discoverer_t $p_rd): void {}

/** Fills $ppp_services with a list of libvlc_rd_description_t; returns the count. */
function libvlc_renderer_discoverer_list_get(libvlc_instance_t $p_inst, ?array &$ppp_services): int {}

/** $pp_services is a list of libvlc_rd_description_t; $i_count may not exceed its length (ValueError). */
function libvlc_renderer_discoverer_list_release(array $pp_services, int $i_count): void {}
