<?php

declare(strict_types=1);

it('refuses libvlc_clearerr before any libvlc_new in the process', function (): void {
    $run = vlcProbe('libvlc_clearerr();', null);

    expect($run['signal'])->toBeNull()
        ->and($run['stdout'])->toStartWith('REFUSED Error: libvlc_clearerr(): no libvlc_instance_t yet');
});
