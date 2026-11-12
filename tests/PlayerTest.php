<?php

declare(strict_types=1);

it('plays, pauses, changes rate and stops a WAV', function (): void {
    $media = libvlc_media_new_path(instance(), wav(2.0));
    $mp = libvlc_media_player_new_from_media($media);

    expect(libvlc_media_player_get_media($mp))->toBe($media)
        ->and(libvlc_media_player_play($mp))->toBe(0)
        ->and(waitFor(fn () => libvlc_media_player_get_state($mp) === libvlc_Playing))->toBeTrue()
        ->and(waitFor(fn () => libvlc_media_player_get_length($mp) > 0))->toBeTrue()
        ->and(libvlc_media_player_get_length($mp))->toBeGreaterThanOrEqual(1950)->toBeLessThanOrEqual(2050)
        ->and(libvlc_media_player_is_playing($mp))->toBe(1)
        ->and(libvlc_media_player_set_rate($mp, 2.0))->toBe(0)
        ->and(libvlc_media_player_get_rate($mp))->toBe(2.0);

    libvlc_media_player_set_pause($mp, 1);
    expect(waitFor(fn () => libvlc_media_player_get_state($mp) === libvlc_Paused))->toBeTrue();

    libvlc_media_player_stop($mp);
    expect(libvlc_media_player_get_state($mp))->toBe(libvlc_Stopped);

    libvlc_media_player_release($mp);
    libvlc_media_release($media);
});

it('passes drawables through as addresses', function (): void {
    $mp = libvlc_media_player_new(instance());

    libvlc_media_player_set_nsobject($mp, 0);
    libvlc_media_player_set_xwindow($mp, 42);
    expect(libvlc_media_player_get_nsobject($mp))->toBe(0)
        ->and(libvlc_media_player_get_xwindow($mp))->toBe(42)
        ->and(libvlc_media_player_event_manager($mp))->toBeInstanceOf(libvlc_event_manager_t::class);
    libvlc_media_player_release($mp);
});

it('reports no video size or cursor without video', function (): void {
    $mp = libvlc_media_player_new(instance());

    expect(libvlc_video_get_size($mp, 0, $px, $py))->toBe(-1)
        ->and(libvlc_video_get_cursor($mp, 0, $cx, $cy))->toBe(-1);
    libvlc_media_player_release($mp);
});

it('hands out a zero viewpoint and takes one back', function (): void {
    $mp = libvlc_media_player_new(instance());
    $vp = libvlc_video_new_viewpoint();

    expect($vp)->toBeInstanceOf(libvlc_video_viewpoint_t::class)
        ->and($vp->f_field_of_view)->toBe(0.0);
    $vp->f_field_of_view = 80.0;
    expect(libvlc_video_update_viewpoint($mp, $vp, true))->toBe(0);
    libvlc_media_player_release($mp);
});

it('lists outputs, devices, tracks, titles and chapters as releasable handles', function (): void {
    $media = libvlc_media_new_path(instance(), wav(1.0));
    $mp = libvlc_media_player_new_from_media($media);
    libvlc_media_player_play($mp);
    waitFor(fn () => libvlc_media_player_get_state($mp) === libvlc_Playing);

    $outputs = libvlc_audio_output_list_get(instance());
    expect($outputs)->toBeInstanceOf(libvlc_audio_output_t::class)
        ->and($outputs->psz_name)->toBeString();
    libvlc_audio_output_list_release($outputs);
    expect($outputs->pointer())->toBe(0);

    $devices = libvlc_audio_output_device_enum($mp);
    if ($devices !== null) {
        libvlc_audio_output_device_list_release($devices);
        expect($devices->pointer())->toBe(0);
    }

    $tracks = libvlc_audio_get_track_description($mp);
    expect($tracks)->toBeInstanceOf(libvlc_track_description_t::class)
        ->and($tracks->psz_name)->toBeString();
    libvlc_track_description_list_release($tracks);
    expect($tracks->pointer())->toBe(0);

    $count = libvlc_media_player_get_full_title_descriptions($mp, $titles);
    expect(count($titles))->toBe(max($count, 0));
    if ($count > 0) {
        libvlc_title_descriptions_release($titles, $count);
    }
    $count = libvlc_media_player_get_full_chapter_descriptions($mp, -1, $chapters);
    expect(count($chapters))->toBe(max($count, 0));
    if ($count > 0) {
        libvlc_chapter_descriptions_release($chapters, $count);
    }

    libvlc_media_player_stop($mp);
    libvlc_media_player_release($mp);
    libvlc_media_release($media);
});
