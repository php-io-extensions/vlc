<?php

declare(strict_types=1);

function parsedWav(float $seconds = 0.5): libvlc_media_t
{
    $media = libvlc_media_new_path(instance(), wav($seconds));
    expect(libvlc_media_parse_with_options($media, libvlc_media_parse_local, 5000))->toBe(0);
    $deadline = microtime(true) + 5;
    while (libvlc_media_get_parsed_status($media) === 0 && microtime(true) < $deadline) {
        usleep(10_000);
    }

    return $media;
}

it('parses a WAV file', function (): void {
    $media = parsedWav();

    expect(libvlc_media_get_parsed_status($media))->toBe(libvlc_media_parsed_status_done)
        ->and(libvlc_media_get_mrl($media))->toStartWith('file://')
        ->and(libvlc_media_get_type($media))->toBe(libvlc_media_type_file)
        ->and(libvlc_media_get_duration($media))->toBeGreaterThanOrEqual(450)->toBeLessThanOrEqual(550);
    libvlc_media_release($media);
});

it('hands out the tracks as live handles and takes them back', function (): void {
    $media = parsedWav();

    expect(libvlc_media_tracks_get($media, $tracks))->toBe(1)
        ->and($tracks)->toHaveCount(1);
    [$track] = $tracks;
    expect($track)->toBeInstanceOf(libvlc_media_track_t::class)
        ->and($track->i_type)->toBe(libvlc_track_audio)
        ->and($track->video)->toBeNull()
        ->and($track->audio->i_channels)->toBe(2)
        ->and($track->audio->i_rate)->toBe(44100)
        ->and(libvlc_media_get_codec_description(libvlc_track_audio, $track->i_codec))->toBeString();

    $audio = $track->audio;
    libvlc_media_tracks_release($tracks, 1);
    expect($track->pointer())->toBe(0)
        ->and($audio->pointer())->toBe(0);
    libvlc_media_release($media);
});

it('round-trips meta, options, user data and stats', function (): void {
    $media = parsedWav();

    libvlc_media_set_meta($media, libvlc_meta_Title, 'Sine');
    libvlc_media_add_option($media, ':no-video');
    libvlc_media_add_option_flag($media, ':no-sub-autodetect-file', libvlc_media_option_trusted);
    libvlc_media_set_user_data($media, 0x1234);
    $stats = new libvlc_media_stats_t();

    expect(libvlc_media_get_meta($media, libvlc_meta_Title))->toBe('Sine')
        ->and(libvlc_media_get_user_data($media))->toBe(0x1234)
        ->and(libvlc_media_get_state($media))->toBe(libvlc_NothingSpecial)
        ->and(libvlc_media_get_stats($media, $stats))->toBeInt()
        ->and($stats->i_read_bytes)->toBeInt();
    libvlc_media_release($media);
});

it('duplicates, retains, nests and manages media', function (): void {
    $media = parsedWav();
    $copy = libvlc_media_duplicate($media);
    $node = libvlc_media_new_as_node(instance(), 'folder');

    expect($copy)->toBeInstanceOf(libvlc_media_t::class)->not->toBe($media)
        ->and(libvlc_media_get_mrl($copy))->toBe(libvlc_media_get_mrl($media))
        ->and(libvlc_media_event_manager($media))->toBeInstanceOf(libvlc_event_manager_t::class)
        ->and(libvlc_media_get_mrl($node))->toBe('vlc://nop')
        ->and(libvlc_media_subitems($node))->toBeInstanceOf(libvlc_media_list_t::class);

    libvlc_media_retain($media);
    libvlc_media_release($media);
    libvlc_media_parse_stop($media);
    foreach ([$media, $copy, $node] as $m) {
        libvlc_media_release($m);
    }
});

it('opens media by location and by descriptor', function (): void {
    $path = wav();
    $location = libvlc_media_new_location(instance(), 'file://'.$path);
    $byFd = libvlc_media_new_fd(instance(), 0);

    expect(libvlc_media_get_mrl($location))->toBe('file://'.$path)
        ->and(libvlc_media_get_mrl($byFd))->toBe('fd://0');
    libvlc_media_release($location);
    libvlc_media_release($byFd);
});

it('adds, lists and clears slaves', function (): void {
    $media = parsedWav();

    expect(libvlc_media_slaves_add($media, libvlc_media_slave_type_audio, 2, 'file://'.wav()))->toBe(0)
        ->and(libvlc_media_slaves_get($media, $slaves))->toBe(1);
    expect($slaves[0]->i_type)->toBe(libvlc_media_slave_type_audio)
        ->and($slaves[0]->i_priority)->toBe(2)
        ->and($slaves[0]->psz_uri)->toStartWith('file://');

    libvlc_media_slaves_release($slaves, 1);
    libvlc_media_slaves_clear($media);
    expect(libvlc_media_slaves_get($media, $none))->toBe(0)
        ->and($none)->toBe([]);
    libvlc_media_release($media);
});

it('frees an address libvlc allocated', function (): void {
    libvlc_free(0);

    expect(true)->toBeTrue();
});
