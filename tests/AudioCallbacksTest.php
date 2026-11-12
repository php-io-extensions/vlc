<?php

declare(strict_types=1);

it('hands decoded samples to PHP', function (): void {
    $mp = libvlc_media_player_new_from_media(libvlc_media_new_path(instance(), wav(0.5)));
    $frames = 0;
    $sizes = [];
    $drained = false;
    libvlc_audio_set_format($mp, 'S16N', 44100, 2);
    libvlc_audio_set_callbacks(
        $mp,
        function (string $samples, int $count, int $pts) use (&$frames, &$sizes): void {
            $frames += $count;
            $sizes[] = strlen($samples) === $count * 4;
        },
        null,
        null,
        null,
        function () use (&$drained): void {
            $drained = true;
        },
    );
    libvlc_media_player_play($mp);

    expect(waitFor(function () use ($mp) { return libvlc_media_player_get_state($mp) === libvlc_Ended; }, 5.0))->toBeTrue();
    waitFor(function () use (&$drained) { return $drained; }, 1.0);
    expect($frames)->toBeGreaterThanOrEqual(21000)->toBeLessThanOrEqual(23100)
        ->and(array_unique($sizes))->toBe([true]);
    libvlc_media_player_release($mp);
});

it('hands samples in libvlc\'s default format when none is set', function (): void {
    $mp = libvlc_media_player_new_from_media(libvlc_media_new_path(instance(), wav(0.5)));
    $frames = 0;
    $sized = true;
    libvlc_audio_set_callbacks($mp, function (string $samples, int $count) use (&$frames, &$sized): void {
        $frames += $count;
        $sized = $sized && strlen($samples) === $count * 4;   // S16N, 2 channels
    }, null, null, null, null);
    libvlc_media_player_play($mp);

    expect(waitFor(function () use ($mp) { return libvlc_media_player_get_state($mp) === libvlc_Ended; }, 5.0))->toBeTrue()
        ->and($frames)->toBeGreaterThan(0)
        ->and($sized)->toBeTrue();
    libvlc_media_player_release($mp);
});

it('lets PHP choose the format', function (): void {
    $mp = libvlc_media_player_new_from_media(libvlc_media_new_path(instance(), wav(0.5)));
    $asked = null;
    $frames = 0;
    libvlc_audio_set_format_callbacks($mp, function (string &$format, int &$rate, int &$channels) use (&$asked): int {
        $asked = [$format, $rate, $channels];
        $format = 'S16N';
        $rate = 48000;
        $channels = 1;

        return 0;
    }, null);
    libvlc_audio_set_callbacks($mp, function (string $samples, int $count) use (&$frames): void {
        $frames += strlen($samples) === $count * 2 ? $count : 0;
    }, null, null, null, null);
    libvlc_media_player_play($mp);

    expect(waitFor(function () use ($mp) { return libvlc_media_player_get_state($mp) === libvlc_Ended; }, 5.0))->toBeTrue()
        ->and($asked[1])->toBe(44100)
        ->and($asked[2])->toBe(2)
        ->and($frames)->toBeGreaterThanOrEqual(23000)->toBeLessThanOrEqual(25200);
    libvlc_media_player_release($mp);
});

it('stops in under a second while audio callables are set', function (): void {
    $mp = libvlc_media_player_new_from_media(libvlc_media_new_path(instance(), wav(3.0)));
    libvlc_audio_set_format($mp, 'S16N', 44100, 2);
    libvlc_audio_set_callbacks($mp, fn (string $s, int $c, int $p) => usleep(5000), null, null, null, null);
    libvlc_audio_set_volume_callback($mp, fn (float $v, bool $m) => null);
    libvlc_media_player_play($mp);
    waitFor(function () use ($mp) { return libvlc_media_player_get_state($mp) === libvlc_Playing; });
    usleep(200_000);

    $t = microtime(true);
    libvlc_media_player_stop($mp);
    expect(microtime(true) - $t)->toBeLessThan(1.0);
    libvlc_media_player_release($mp);
});
