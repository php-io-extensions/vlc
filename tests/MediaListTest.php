<?php

declare(strict_types=1);

it('holds media in a lockable list', function (): void {
    $list = libvlc_media_list_new(instance());
    $a = libvlc_media_new_path(instance(), wav());
    $b = libvlc_media_new_path(instance(), wav());

    libvlc_media_list_lock($list);
    expect(libvlc_media_list_add_media($list, $a))->toBe(0)
        ->and(libvlc_media_list_add_media($list, $b))->toBe(0)
        ->and(libvlc_media_list_count($list))->toBe(2)
        ->and(libvlc_media_list_item_at_index($list, 1))->toBe($b)
        ->and(libvlc_media_list_index_of_item($list, $b))->toBe(1)
        ->and(libvlc_media_list_is_readonly($list))->toBe(0);
    libvlc_media_list_unlock($list);

    libvlc_media_list_release($list);
    libvlc_media_release($a);
    libvlc_media_release($b);
});

it('plays a list through a list player', function (): void {
    $list = libvlc_media_list_new(instance());
    foreach ([wav(1.0), wav(1.0)] as $path) {
        $m = libvlc_media_new_path(instance(), $path);
        libvlc_media_list_add_media($list, $m);
        libvlc_media_release($m);
    }
    $lp = libvlc_media_list_player_new(instance());
    libvlc_media_list_player_set_media_list($lp, $list);

    libvlc_media_list_player_play($lp);
    expect(waitFor(fn () => libvlc_media_list_player_get_state($lp) === libvlc_Playing))->toBeTrue()
        ->and(libvlc_media_list_player_get_media_player($lp))->toBeInstanceOf(libvlc_media_player_t::class);

    libvlc_media_list_player_stop($lp);
    libvlc_media_list_player_release($lp);
    libvlc_media_list_release($list);
});
