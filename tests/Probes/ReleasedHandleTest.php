<?php

declare(strict_types=1);

/*
 * A released handle holds NULL. libvlc dereferences every handle it is given, so passing the
 * NULL on would crash.
 */
it('keeps a released handle from reaching libvlc', function (): void {
    requireProbeBuild();
    $code = '$i = libvlc_new(count(VLC_TEST_ARGS), VLC_TEST_ARGS); libvlc_release($i); libvlc_retain($i);';

    $kept = vlcProbe($code, null);
    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toStartWith('REFUSED ValueError: libvlc_retain(): Argument #1 ($p_instance) libvlc_instance_t has been released');

    $off = vlcProbe($code, 'vlc-released-handle');
    expect($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
});
