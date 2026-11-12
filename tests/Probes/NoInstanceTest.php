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
