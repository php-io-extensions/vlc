<?php

declare(strict_types=1);

it('lists presets and bands', function (): void {
    expect(libvlc_audio_equalizer_get_preset_count())->toBe(18)
        ->and(libvlc_audio_equalizer_get_band_count())->toBe(10)
        ->and(libvlc_audio_equalizer_get_preset_name(0))->toBe('Flat')
        ->and(libvlc_audio_equalizer_get_band_frequency(0))->toBe(31.25);
});

it('makes, edits, applies and releases an equalizer', function (): void {
    $eq = libvlc_audio_equalizer_new_from_preset(0);
    $mp = libvlc_media_player_new(instance());

    expect(libvlc_audio_equalizer_get_amp_at_index($eq, 0))->toBeFloat()
        ->and(libvlc_audio_equalizer_set_preamp($eq, 5.0))->toBe(0)
        ->and(libvlc_audio_equalizer_get_preamp($eq))->toBe(5.0)
        ->and(libvlc_audio_equalizer_set_amp_at_index($eq, -3.0, 1))->toBe(0)
        ->and(libvlc_media_player_set_equalizer($mp, $eq))->toBe(0)
        ->and(libvlc_media_player_set_equalizer($mp, null))->toBe(0);

    libvlc_audio_equalizer_release($eq);
    expect($eq->pointer())->toBe(0);
    libvlc_media_player_release($mp);
});
