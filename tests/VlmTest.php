<?php

declare(strict_types=1);

it('adds, shows, changes and deletes a broadcast', function (): void {
    $vlc = libvlc_new(count(VLC_TEST_ARGS), VLC_TEST_ARGS);
    $input = 'file://'.wav();

    expect(libvlc_vlm_add_broadcast($vlc, 'b', $input, '#dummy', 1, ['sout-keep'], 0, 0))->toBe(0)
        ->and(libvlc_vlm_show_media($vlc, 'b'))->toContain('"b"')
        ->and(libvlc_vlm_change_media($vlc, 'b', $input, '#dummy', 0, [], 1, 1))->toBe(0)
        ->and(libvlc_vlm_add_vod($vlc, 'v', $input, 0, [], 0, null))->toBe(0)
        ->and(libvlc_vlm_del_media($vlc, 'v'))->toBe(0)
        ->and(libvlc_vlm_del_media($vlc, 'b'))->toBe(0);

    libvlc_vlm_release($vlc);
    libvlc_release($vlc);
});

/* libvlc dereferences the name: null crashed libvlc_vlm_add_broadcast (SIGSEGV). */
it('takes a VLM media name as a string, never null', function (): void {
    expect(fn () => libvlc_vlm_add_broadcast(instance(), null, 'file:///x', '', 0, [], 1, 0))->toThrow(TypeError::class)
        ->and(fn () => libvlc_vlm_add_vod(instance(), null, 'file:///x', 0, [], 1, null))->toThrow(TypeError::class)
        ->and(fn () => libvlc_vlm_change_media(instance(), null, 'file:///x', '', 0, [], 1, 0))->toThrow(TypeError::class);
});
