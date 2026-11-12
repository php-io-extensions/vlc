<?php

declare(strict_types=1);

/** Media whose bytes PHP serves from $bytes through the four callables; $log records the calls. */
function servedMedia(string $bytes, array &$log, ?Closure $read = null): libvlc_media_t
{
    $offset = 0;

    return libvlc_media_new_callbacks(
        instance(),
        function (?int &$size) use ($bytes, &$log, &$offset): int {
            $log[] = 'open';
            $size = strlen($bytes);
            $offset = 0;

            return 0;
        },
        $read ?? function (int $len) use ($bytes, &$offset): string {
            $chunk = substr($bytes, $offset, $len);
            $offset += strlen($chunk);

            return $chunk;
        },
        function (int $to) use (&$offset, &$log): int {
            $log[] = 'seek';
            $offset = $to;

            return 0;
        },
        function () use (&$log): void {
            $log[] = 'close';
        },
    );
}

/* libvlc's preparser skips callback media (parsed status: skipped), so the bytes are read by playing. */
it('plays media whose bytes PHP serves', function (): void {
    $log = [];
    $media = servedMedia(file_get_contents(wav(1.0)), $log);
    $mp = libvlc_media_player_new_from_media($media);
    libvlc_media_player_play($mp);

    expect(waitFor(fn () => libvlc_media_player_get_state($mp) === libvlc_Playing))->toBeTrue()
        ->and(libvlc_media_tracks_get($media, $tracks))->toBe(1)
        ->and($tracks[0]->audio->i_rate)->toBe(44100)
        ->and(waitFor(fn () => libvlc_media_player_get_state($mp) === libvlc_Ended))->toBeTrue()
        ->and($log[0])->toBe('open')
        ->and($log)->toContain('close');
    libvlc_media_tracks_release($tracks, 1);
    libvlc_media_player_release($mp);
    libvlc_media_release($media);
});

/* libvlc 3.0 ends callback media in libvlc_Ended, not libvlc_Error, even when open fails. */
it('surfaces the exception and ends playback when the read callable throws', function (): void {
    $log = [];
    $media = servedMedia('', $log, function (int $len): string {
        throw new RuntimeException('read failed');
    });
    $mp = libvlc_media_player_new_from_media($media);
    libvlc_media_player_play($mp);

    expect(fn () => waitFor(fn () => false, 3.0))->toThrow(RuntimeException::class, 'read failed');
    expect(waitFor(fn () => libvlc_media_player_get_state($mp) === libvlc_Ended))->toBeTrue();
    libvlc_media_player_release($mp);
    libvlc_media_release($media);
});
