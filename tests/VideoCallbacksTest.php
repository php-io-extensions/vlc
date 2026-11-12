<?php

declare(strict_types=1);

/** A temp 4:2:0 Y4M of $frames grey frames, $w × $h, 25 fps, deleted at shutdown. */
function y4m(int $w, int $h, int $frames): string
{
    $frame = "FRAME\n".str_repeat("\x80", $w * $h + 2 * intdiv($w, 2) * intdiv($h, 2));
    $base = tempnam(sys_get_temp_dir(), 'vlc');
    $file = $base.'.y4m';
    register_shutdown_function(fn () => @unlink($base));
    file_put_contents($file, "YUV4MPEG2 W{$w} H{$h} F25:1 Ip A1:1 C420jpeg\n".str_repeat($frame, $frames));
    register_shutdown_function(fn () => @unlink($file));

    return $file;
}

it('renders frames into memory PHP owns', function (): void {
    $ffi = FFI::cdef();
    $buf = $ffi->new('char[12288]', false);
    $address = $ffi->cast('uintptr_t', FFI::addr($buf))->cdata;
    $mp = libvlc_media_player_new_from_media(libvlc_media_new_path(instance(), y4m(64, 48, 4)));
    $displayed = [];
    libvlc_video_set_format($mp, 'RV32', 64, 48, 256);
    libvlc_video_set_callbacks(
        $mp,
        fn (): array => [$address],
        null,
        function (int $picture) use (&$displayed): void {
            $displayed[] = $picture;
        },
    );
    libvlc_media_player_play($mp);

    expect(waitFor(function () use ($mp) { return libvlc_media_player_get_state($mp) === libvlc_Ended; }, 5.0))->toBeTrue();
    waitFor(function () use (&$displayed) { return $displayed !== []; }, 1.0);
    expect($displayed)->not->toBeEmpty()
        ->and(FFI::string($buf, 12288))->not->toBe(str_repeat("\0", 12288));
    libvlc_media_player_release($mp);
    FFI::free($buf);
})->skip(! extension_loaded('ffi'), 'needs ext-ffi to own the pixel memory');

/* A lock that answers no planes gets the binding's scratch picture: every plane of it, sized from the format. */
it('renders a planar picture into the scratch picture when the lock answers no planes', function (): void {
    $mp = libvlc_media_player_new_from_media(libvlc_media_new_path(instance(), y4m(64, 48, 3)));
    libvlc_video_set_format_callbacks($mp, function (string &$chroma, int &$width, int &$height, array &$pitches, array &$lines): int {
        $chroma = 'I420';
        $pitches = [64, 32, 32];
        $lines = [48, 24, 24];

        return 1;
    }, null);
    $displayed = 0;
    libvlc_video_set_callbacks($mp, fn (): array => [], null, function () use (&$displayed): void {
        $displayed++;
    });
    libvlc_media_player_play($mp);

    expect(waitFor(fn () => libvlc_media_player_get_state($mp) === libvlc_Ended, 5.0))->toBeTrue()
        ->and($displayed)->toBeGreaterThan(0);
    libvlc_media_player_release($mp);
});

it('renders into a scratch picture with no format set at all', function (): void {
    $mp = libvlc_media_player_new_from_media(libvlc_media_new_path(instance(), y4m(64, 48, 3)));
    libvlc_video_set_callbacks($mp, fn (): array => [], null, null);
    libvlc_media_player_play($mp);

    expect(waitFor(fn () => libvlc_media_player_get_state($mp) === libvlc_Ended, 5.0))->toBeTrue();
    libvlc_media_player_release($mp);
});

it('lets PHP choose the picture format', function (): void {
    $mp = libvlc_media_player_new_from_media(libvlc_media_new_path(instance(), y4m(64, 48, 2)));
    $asked = null;
    libvlc_video_set_format_callbacks($mp, function (string &$chroma, int &$width, int &$height, array &$pitches, array &$lines) use (&$asked): int {
        $asked = [$width, $height];
        $chroma = 'RV32';
        $pitches = [256];
        $lines = [48];

        return 1;
    }, null);
    libvlc_video_set_callbacks($mp, fn (): array => [], null, null);
    libvlc_media_player_play($mp);

    expect(waitFor(function () use (&$asked) { return $asked !== null; }, 5.0))->toBeTrue()
        ->and($asked)->toBe([64, 48]);
    libvlc_media_player_stop($mp);
    libvlc_media_player_release($mp);
});
