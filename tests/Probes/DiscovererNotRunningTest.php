<?php

declare(strict_types=1);

/*
 * libvlc_media_discoverer_stop() stops the services discovery the discoverer holds without checking
 * that it holds one: before a successful start, or after a stop, it dereferences NULL.
 */
it('keeps libvlc_media_discoverer_stop off a discoverer that is not running', function (): void {
    requireProbeBuild();
    $code = '$i = libvlc_new(count(VLC_TEST_ARGS), VLC_TEST_ARGS); $d = libvlc_media_discoverer_new($i, "upnp"); libvlc_media_discoverer_stop($d);';

    $kept = vlcProbe($code, null);
    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toStartWith('REFUSED ValueError: libvlc_media_discoverer_stop(): Argument #1 ($p_mdis) is not running');

    $off = vlcProbe($code, 'vlc-discoverer-not-running');
    expect($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
});
