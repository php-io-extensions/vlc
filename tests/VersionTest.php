<?php

declare(strict_types=1);

it('reports libvlc 3.0.24', function (): void {
    expect(libvlc_get_version())->toStartWith('3.0.24')
        ->and(phpversion('vlc'))->toBe('0.11.0');
});
