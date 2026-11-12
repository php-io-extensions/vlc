<?php

declare(strict_types=1);

/** The installed libvlc headers, outside deprecated.h. */
function vlcHeaders(): array
{
    foreach (['/Applications/VLC.app/Contents/MacOS/include/vlc', '/usr/include/vlc'] as $dir) {
        if (is_file("$dir/vlc.h")) {
            return array_values(array_filter(glob("$dir/libvlc*.h"), fn (string $f): bool => basename($f) !== 'deprecated.h'));
        }
    }
    throw new RuntimeException('libvlc headers not found');
}

it('registers every libvlc enumerator and integer define', function (): void {
    $text = preg_replace('#/\*.*?\*/|//[^\n]*#s', '', implode("\n", array_map('file_get_contents', vlcHeaders())));
    preg_match_all('/enum\s*\w*\s*\{(.*?)\}/s', $text, $bodies);
    $names = ['LIBVLC_RENDERER_CAN_AUDIO', 'LIBVLC_RENDERER_CAN_VIDEO', 'LIBVLC_VERSION_MAJOR', 'LIBVLC_VERSION_MINOR',
        'LIBVLC_VERSION_REVISION', 'LIBVLC_VERSION_EXTRA', 'LIBVLC_VERSION_INT', 'libvlc_role_Last'];
    foreach ($bodies[1] as $body) {
        foreach (array_filter(array_map('trim', explode(',', $body))) as $enumerator) {
            $names[] = preg_replace('/\W.*$/s', '', $enumerator);
        }
    }

    expect(array_values(array_filter($names, fn (string $n): bool => ! defined($n))))->toBe([])
        ->and(count($names))->toBe(226);
});

it('gives the C values', function (): void {
    expect(libvlc_Playing)->toBe(3)
        ->and(libvlc_MediaPlayerEndReached)->toBe(265)
        ->and(libvlc_media_parse_local)->toBe(0)
        ->and(LIBVLC_VERSION_MAJOR)->toBe(3)
        ->and(LIBVLC_VERSION_REVISION)->toBe(24)
        ->and(libvlc_role_Last)->toBe(libvlc_role_Test);
});
