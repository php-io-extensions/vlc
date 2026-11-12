<?php

declare(strict_types=1);

it('creates, retains and releases an instance', function (): void {
    $i = libvlc_new(count(VLC_TEST_ARGS), VLC_TEST_ARGS);

    expect($i)->toBeInstanceOf(libvlc_instance_t::class);

    libvlc_retain($i);
    libvlc_release($i);
    expect($i->pointer())->not->toBe(0);
    libvlc_release($i);
    expect($i->pointer())->toBe(0);
});

it('releases a handle with its last counted reference', function (): void {
    $media = libvlc_media_new_path(instance(), wav());
    $mp = libvlc_media_player_new_from_media($media);

    expect(libvlc_media_player_get_media($mp))->toBe($media);   // a new reference
    libvlc_media_release($media);
    expect($media->pointer())->not->toBe(0);

    libvlc_media_player_release($mp);
    expect($mp->pointer())->toBe(0);
    libvlc_media_release($media);
    expect($media->pointer())->toBe(0)
        ->and(fn () => libvlc_media_get_mrl($media))->toThrow(ValueError::class, 'libvlc_media_t has been released');
});

it('keeps the thread error message until cleared', function (): void {
    instance();
    libvlc_clearerr();
    expect(libvlc_errmsg())->toBeNull();

    expect(libvlc_printerr('no such media: %s at %d', 'x.wav', 7))->toBe('no such media: x.wav at 7')
        ->and(libvlc_errmsg())->toBe('no such media: x.wav at 7');

    libvlc_clearerr();
    expect(libvlc_errmsg())->toBeNull();
});

it('lists the audio filters as a live linked list', function (): void {
    $head = libvlc_audio_filter_list_get(instance());
    expect($head)->toBeInstanceOf(libvlc_module_description_t::class);

    $names = [];
    for ($node = $head; $node !== null; $node = $node->p_next) {
        $names[] = $node->psz_name;
    }
    expect($names)->not->toBeEmpty()
        ->and(array_filter($names, fn ($n) => ! is_string($n) || $n === ''))->toBe([]);

    $second = $head->p_next;
    libvlc_module_description_list_release($head);
    expect($head->pointer())->toBe(0)
        ->and($second?->pointer() ?? 0)->toBe(0);
});

it('reads the clock and names event types', function (): void {
    expect(libvlc_clock())->toBeGreaterThan(0)
        ->and(libvlc_event_type_name(libvlc_MediaPlayerPlaying))->toBe('MediaPlayerPlaying');
});

it('sets the user agent and app id without error', function (): void {
    libvlc_set_user_agent(instance(), 'vlc-tests 0.11', 'vlc-tests/0.11');
    libvlc_set_app_id(instance(), 'com.example.vlc-tests', '0.11', 'vlc');

    expect(true)->toBeTrue();
});
