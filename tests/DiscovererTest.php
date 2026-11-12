<?php

declare(strict_types=1);

it('lists media discovery services as releasable handles', function (): void {
    $count = libvlc_media_discoverer_list_get(instance(), libvlc_media_discoverer_localdirs, $services);

    expect($count)->toBeGreaterThanOrEqual(1)
        ->and($services)->toHaveCount($count)
        ->and($services[0])->toBeInstanceOf(libvlc_media_discoverer_description_t::class)
        ->and($services[0]->psz_name)->toBeString()->not->toBe('')
        ->and($services[0]->i_cat)->toBe(libvlc_media_discoverer_localdirs);

    $first = $services[0];
    libvlc_media_discoverer_list_release($services, $count);
    expect($first->pointer())->toBe(0);
});

it('starts, stops and releases a media discoverer', function (): void {
    libvlc_media_discoverer_list_get(instance(), libvlc_media_discoverer_localdirs, $services);
    $name = $services[0]->psz_name;
    libvlc_media_discoverer_list_release($services, count($services));

    $md = libvlc_media_discoverer_new(instance(), $name);
    expect($md)->toBeInstanceOf(libvlc_media_discoverer_t::class)
        ->and(libvlc_media_discoverer_start($md))->toBe(0)
        ->and(libvlc_media_discoverer_is_running($md))->toBe(1)
        ->and(libvlc_media_discoverer_media_list($md))->toBeInstanceOf(libvlc_media_list_t::class);

    libvlc_media_discoverer_stop($md);
    libvlc_media_discoverer_release($md);
    expect($md->pointer())->toBe(0);
});

it('lists renderer discovery services', function (): void {
    $count = libvlc_renderer_discoverer_list_get(instance(), $services);

    expect($services)->toHaveCount($count);
    if ($count > 0) {
        expect($services[0])->toBeInstanceOf(libvlc_rd_description_t::class);
        $rd = libvlc_renderer_discoverer_new(instance(), $services[0]->psz_name);
        libvlc_renderer_discoverer_list_release($services, $count);
        expect(libvlc_renderer_discoverer_event_manager($rd))->toBeInstanceOf(libvlc_event_manager_t::class);
        libvlc_renderer_discoverer_release($rd);
        expect($rd->pointer())->toBe(0);
    }
});
