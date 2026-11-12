<?php

declare(strict_types=1);

/** Notes when PHP frees the state a callable captured. */
final class Freed
{
    /** @var list<string> */
    public static array $gone = [];

    public function __construct(private string $name) {}

    public function __destruct()
    {
        self::$gone[] = $this->name;
    }
}

/** A callable whose captured Freed($name) only the binding holds once the caller lets go. */
function holding(string $name, mixed $return = null): Closure
{
    $freed = new Freed($name);

    return function (mixed ...$args) use ($freed, $return): mixed {
        return $return;
    };
}

function freed(string $name, float $seconds = 3.0): bool
{
    return waitFor(fn () => in_array($name, Freed::$gone, true), $seconds);
}

it('frees the callables of callback media once libvlc frees the media', function (): void {
    $media = libvlc_media_new_callbacks(instance(), holding('m-open', -1), holding('m-read', ''), holding('m-seek', -1), holding('m-close'));
    libvlc_media_release($media);

    expect(freed('m-open'))->toBeTrue()
        ->and(freed('m-read'))->toBeTrue()
        ->and(freed('m-seek'))->toBeTrue()
        ->and(freed('m-close'))->toBeTrue();
});

it('keeps callback media callables while a player still holds the media', function (): void {
    $media = libvlc_media_new_callbacks(instance(), holding('h-open', -1), holding('h-read', ''), null, null);
    $mp = libvlc_media_player_new_from_media($media);
    libvlc_media_release($media);

    expect(freed('h-open', 0.2))->toBeFalse();
    libvlc_media_player_release($mp);
    expect(freed('h-open'))->toBeTrue();
});

it('frees a played callback media after the player lets it go', function (): void {
    $bytes = file_get_contents(wav(0.3));
    $offset = 0;
    $marker = new Freed('p-read');
    $media = libvlc_media_new_callbacks(
        instance(),
        function (?int &$size) use ($bytes): int {
            $size = strlen($bytes);

            return 0;
        },
        function (int $len) use ($bytes, &$offset, $marker): string {
            $chunk = substr($bytes, $offset, $len);
            $offset += strlen($chunk);

            return $chunk;
        },
        null,
        null,
    );
    unset($marker);
    $mp = libvlc_media_player_new_from_media($media);
    libvlc_media_release($media);
    libvlc_media_player_play($mp);

    expect(waitFor(fn () => libvlc_media_player_get_state($mp) === libvlc_Ended, 5.0))->toBeTrue();
    libvlc_media_player_release($mp);
    expect(freed('p-read'))->toBeTrue();
});

it('detaches and frees event callables with the last release of their object', function (): void {
    $mp = libvlc_media_player_new(instance());
    libvlc_event_attach(libvlc_media_player_event_manager($mp), libvlc_MediaPlayerPlaying, holding('e-player'));
    $ml = libvlc_media_list_new(instance());
    libvlc_event_attach(libvlc_media_list_event_manager($ml), libvlc_MediaListItemAdded, holding('e-list'));
    $media = libvlc_media_new_path(instance(), wav(0.1));
    libvlc_event_attach(libvlc_media_event_manager($media), libvlc_MediaStateChanged, holding('e-media'));

    libvlc_media_player_release($mp);
    libvlc_media_list_release($ml);
    libvlc_media_release($media);

    expect(Freed::$gone)->toContain('e-player', 'e-list', 'e-media');
});

it('keeps event callables while the binding still holds a reference', function (): void {
    $mp = libvlc_media_player_new(instance());
    libvlc_media_player_retain($mp);
    libvlc_event_attach(libvlc_media_player_event_manager($mp), libvlc_MediaPlayerPlaying, holding('r-player'));

    libvlc_media_player_release($mp);
    expect(Freed::$gone)->not->toContain('r-player');
    libvlc_media_player_release($mp);
    expect(Freed::$gone)->toContain('r-player');
});

it('unsets and frees an instance\'s log, exit and dialog callables with its last release', function (): void {
    $vlc = libvlc_new(count(VLC_TEST_ARGS), VLC_TEST_ARGS);
    libvlc_log_set($vlc, holding('i-log'));
    libvlc_set_exit_handler($vlc, holding('i-exit'));
    $cbs = new libvlc_dialog_cbs();
    $cbs->pf_display_error = holding('i-dialog');
    libvlc_dialog_set_callbacks($vlc, $cbs);
    unset($cbs);
    libvlc_event_attach(libvlc_vlm_get_event_manager($vlc), libvlc_VlmMediaAdded, holding('i-vlm'));

    libvlc_release($vlc);

    expect(Freed::$gone)->toContain('i-log', 'i-exit', 'i-dialog', 'i-vlm');
});

it('frees VLM event callables when the VLM is released', function (): void {
    $vlc = libvlc_new(count(VLC_TEST_ARGS), VLC_TEST_ARGS);
    libvlc_event_attach(libvlc_vlm_get_event_manager($vlc), libvlc_VlmMediaAdded, holding('v-vlm'));
    libvlc_vlm_release($vlc);

    expect(Freed::$gone)->toContain('v-vlm');
    libvlc_release($vlc);
});

it('keeps a player\'s callables while a list player holds it', function (): void {
    $mlp = libvlc_media_list_player_new(instance());
    $mp = libvlc_media_player_new(instance());
    libvlc_media_list_player_set_media_player($mlp, $mp);
    libvlc_audio_set_callbacks($mp, holding('l-play'), null, null, null, null);
    libvlc_event_attach(libvlc_media_player_event_manager($mp), libvlc_MediaPlayerPlaying, holding('l-event'));
    libvlc_media_player_release($mp);

    expect(Freed::$gone)->not->toContain('l-play')
        ->and(Freed::$gone)->not->toContain('l-event');
    libvlc_media_list_player_release($mlp);
    expect(Freed::$gone)->toContain('l-play', 'l-event');
});

it('keeps the list player\'s own player callables until the list player goes', function (): void {
    $mlp = libvlc_media_list_player_new(instance());
    $mp = libvlc_media_list_player_get_media_player($mlp);
    libvlc_audio_set_callbacks($mp, holding('o-play'), null, null, null, null);
    libvlc_media_player_release($mp);

    expect(Freed::$gone)->not->toContain('o-play');
    libvlc_media_list_player_release($mlp);
    expect(Freed::$gone)->toContain('o-play');
});

it('frees a player\'s callables when a list player swaps it out', function (): void {
    $mlp = libvlc_media_list_player_new(instance());
    $mp = libvlc_media_player_new(instance());
    libvlc_media_list_player_set_media_player($mlp, $mp);
    libvlc_audio_set_callbacks($mp, holding('s-play'), null, null, null, null);
    libvlc_media_player_release($mp);
    $other = libvlc_media_player_new(instance());
    libvlc_media_list_player_set_media_player($mlp, $other);

    expect(Freed::$gone)->toContain('s-play');
    libvlc_media_player_release($other);
    libvlc_media_list_player_release($mlp);
});

it('frees renderer discoverer event callables with the discoverer', function (): void {
    libvlc_renderer_discoverer_list_get(instance(), $services);
    if ($services === []) {
        $this->markTestSkipped('no renderer discoverer module');
    }
    $rd = libvlc_renderer_discoverer_new(instance(), $services[0]->psz_name);
    libvlc_renderer_discoverer_list_release($services, count($services));
    libvlc_event_attach(libvlc_renderer_discoverer_event_manager($rd), libvlc_RendererDiscovererItemAdded, holding('d-event'));
    libvlc_renderer_discoverer_release($rd);

    expect(Freed::$gone)->toContain('d-event');
});
