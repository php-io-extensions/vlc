<?php

declare(strict_types=1);

/*
 * A C count given as its own parameter: libvlc reads that many elements of the array built from
 * the list, so a count past the list reads past the array.
 */
it('keeps a count past its list from reaching libvlc', function (): void {
    requireProbeBuild();
    $code = 'libvlc_new(100000, ["--quiet"]);';

    $kept = vlcProbe($code, null);
    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toStartWith('REFUSED ValueError: libvlc_new(): Argument #1 ($argc) must be between 0 and the length of argument #2 ($argv)');

    $off = vlcProbe($code, 'vlc-list-count', gmalloc: true);
    expect($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
});
