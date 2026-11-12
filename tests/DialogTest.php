<?php

declare(strict_types=1);

it('sets and clears the dialog callables', function (): void {
    $vlc = libvlc_new(count(VLC_TEST_ARGS), VLC_TEST_ARGS);
    $cbs = new libvlc_dialog_cbs();
    $cbs->pf_display_error = fn (string $title, string $text) => null;

    libvlc_dialog_set_callbacks($vlc, $cbs);
    libvlc_dialog_set_callbacks($vlc, null);
    libvlc_release($vlc);

    expect($cbs->pf_display_login)->toBeNull();
});
