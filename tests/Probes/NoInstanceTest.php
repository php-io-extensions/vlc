<?php

declare(strict_types=1);

/*
 * libvlc creates its per-thread error key in the first libvlc_new(). Before that,
 * libvlc_clearerr() sets an uncreated key and libvlc aborts the process.
 */
it('keeps libvlc_clearerr before any libvlc_new from aborting the process', function (): void {
    requireProbeBuild();

    $kept = vlcProbe('libvlc_clearerr();', null);
    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toStartWith('REFUSED Error: libvlc_clearerr(): no libvlc_instance_t yet');

    $off = vlcProbe('libvlc_clearerr();', 'vlc-no-instance');
    expect($off['signal'])->toBe(PROBE_SIGABRT);
});

/* libvlc_printerr() frees the previous message in the same uncreated slot. */
it('keeps libvlc_printerr before any libvlc_new from aborting the process', function (): void {
    requireProbeBuild();

    $kept = vlcProbe('libvlc_printerr("x");', null);
    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toStartWith('REFUSED Error: libvlc_printerr(): no libvlc_instance_t yet');

    $off = vlcProbe('libvlc_printerr("x");', 'vlc-printerr-no-instance');
    expect($off['signal'])->toBe(PROBE_SIGABRT);
});
