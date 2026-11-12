<?php

declare(strict_types=1);

/** A player on a fresh WAV of $seconds, its event manager, and the media. */
function playerOn(float $seconds): array
{
    $media = libvlc_media_new_path(instance(), wav($seconds));
    $mp = libvlc_media_player_new_from_media($media);

    return [$mp, libvlc_media_player_event_manager($mp), $media];
}

it('delivers player events from libvlc threads to PHP', function (): void {
    [$mp, $em] = playerOn(0.5);
    $seen = [];
    $record = function (libvlc_event_t $e) use (&$seen): void {
        $seen[] = $e;
    };

    expect(libvlc_event_attach($em, libvlc_MediaPlayerPlaying, $record))->toBe(0)
        ->and(libvlc_event_attach($em, libvlc_MediaPlayerEndReached, $record))->toBe(0);
    libvlc_media_player_play($mp);

    expect(waitFor(function () use (&$seen) { return count($seen) >= 2; }))->toBeTrue();
    $types = array_map(fn (libvlc_event_t $e) => $e->type, $seen);
    expect($types)->toContain(libvlc_MediaPlayerPlaying)
        ->and($types)->toContain(libvlc_MediaPlayerEndReached)
        ->and($seen[0]->p_obj)->toBe($mp->pointer());

    libvlc_event_detach($em, libvlc_MediaPlayerPlaying, $record);
    libvlc_event_detach($em, libvlc_MediaPlayerEndReached, $record);
    libvlc_media_player_release($mp);
});

it('fills the union member of the event type', function (): void {
    [$mp, $em] = playerOn(0.5);
    $lengths = [];
    $es = null;
    libvlc_event_attach($em, libvlc_MediaPlayerLengthChanged, function (libvlc_event_t $e) use (&$lengths): void {
        $lengths[] = $e->u->new_length;
    });
    libvlc_event_attach($em, libvlc_MediaPlayerESAdded, function (libvlc_event_t $e) use (&$es): void {
        $es = $e->u;
    });
    libvlc_media_player_play($mp);

    expect(waitFor(function () use (&$lengths, &$es) { return $lengths !== [] && $es !== null; }))->toBeTrue()
        ->and($lengths[0])->toBe(500)
        ->and($es->i_type)->toBe(libvlc_track_audio)
        ->and($es->i_id)->toBe(0);
    libvlc_media_player_stop($mp);
    libvlc_media_player_release($mp);
});

it('stops calling a detached callable', function (): void {
    [$mp, $em] = playerOn(0.5);
    $calls = 0;
    $count = function () use (&$calls): void {
        $calls++;
    };
    libvlc_event_attach($em, libvlc_MediaPlayerTimeChanged, $count);
    libvlc_event_detach($em, libvlc_MediaPlayerTimeChanged, $count);
    libvlc_media_player_play($mp);
    waitFor(fn () => libvlc_media_player_get_state($mp) === libvlc_Ended);

    expect($calls)->toBe(0);
    libvlc_media_player_release($mp);
});

it('surfaces an exception thrown by an event callable', function (): void {
    [$mp, $em] = playerOn(0.5);
    libvlc_event_attach($em, libvlc_MediaPlayerPlaying, function (): void {
        throw new RuntimeException('from the event');
    });
    libvlc_media_player_play($mp);

    expect(fn () => waitFor(fn () => false, 3.0))->toThrow(RuntimeException::class, 'from the event');
    libvlc_media_player_stop($mp);
    libvlc_media_player_release($mp);
});

it('returns from stop called inside an event callable', function (): void {
    [$mp, $em] = playerOn(0.5);
    $stopped = null;
    libvlc_event_attach($em, libvlc_MediaPlayerPlaying, function () use ($mp, &$stopped): void {
        $t = microtime(true);
        libvlc_media_player_stop($mp);
        $stopped = microtime(true) - $t;
    });
    libvlc_media_player_play($mp);

    expect(waitFor(function () use (&$stopped) { return $stopped !== null; }, 5.0))->toBeTrue()
        ->and($stopped)->toBeLessThan(2.0);
    libvlc_media_player_release($mp);
});

it('ends a request with a playing player and attached callables', function (): void {
    $run = vlcProbe(<<<'PHP'
        $vlc = libvlc_new(count(VLC_TEST_ARGS), VLC_TEST_ARGS);
        $m = libvlc_media_new_location($vlc, 'vlc://nop');
        $mp = libvlc_media_player_new_from_media($m);
        libvlc_event_attach(libvlc_media_player_event_manager($mp), libvlc_MediaPlayerTimeChanged, fn () => null);
        libvlc_media_player_play($mp);
        usleep(100000);
        PHP, null);

    expect($run['signal'])->toBeNull()
        ->and($run['stdout'])->toBe("SURVIVED\n");
});
