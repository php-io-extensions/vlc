<?php

declare(strict_types=1);

it('delivers libvlc log messages with their context', function (): void {
    $vlc = libvlc_new(count(VLC_TEST_ARGS), VLC_TEST_ARGS);
    $messages = [];
    libvlc_log_set($vlc, function (int $level, libvlc_log_t $ctx, string $message) use (&$messages): void {
        libvlc_log_get_context($ctx, $module, $file, $line);
        libvlc_log_get_object($ctx, $name, $header, $id);
        $messages[] = [$level, $message, $module, $name, $id];
    });

    $mp = libvlc_media_player_new_from_media(libvlc_media_new_path($vlc, '/nonexistent/file.wav'));
    libvlc_media_player_play($mp);
    waitFor(function () use (&$messages, $mp) { return $messages !== [] && libvlc_media_player_get_state($mp) >= libvlc_Ended; });
    libvlc_media_player_stop($mp);
    libvlc_log_unset($vlc);

    expect($messages)->not->toBeEmpty();
    [$level, $message, $module, $name, $id] = $messages[0];
    expect($level)->toBeIn([LIBVLC_DEBUG, LIBVLC_NOTICE, LIBVLC_WARNING, LIBVLC_ERROR])
        ->and($message)->toBeString()
        ->and($module)->toBeString()
        ->and($name)->toBeString()
        ->and($id)->toBeInt();
    libvlc_media_player_release($mp);
    libvlc_release($vlc);
});

it('sets an exit handler', function (): void {
    $vlc = libvlc_new(count(VLC_TEST_ARGS), VLC_TEST_ARGS);
    libvlc_set_exit_handler($vlc, fn () => null);
    libvlc_release($vlc);

    expect(true)->toBeTrue();
});
