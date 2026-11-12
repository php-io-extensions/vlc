<?php

declare(strict_types=1);

if (! extension_loaded('vlc')) {
    throw new RuntimeException('The vlc extension is not loaded; run ./install-macos.sh or ./install-debian-trixie.sh');
}

/* libvlc from VLC.app finds its plugins only through VLC_PLUGIN_PATH; the distro libvlc knows its own. */
if (getenv('VLC_PLUGIN_PATH') === false && is_dir('/Applications/VLC.app/Contents/MacOS/plugins')) {
    putenv('VLC_PLUGIN_PATH=/Applications/VLC.app/Contents/MacOS/plugins');
}

/** Instance arguments for every Mac test: no sound, no window. */
const VLC_TEST_ARGS = ['--aout=dummy', '--vout=dummy', '--no-video-title-show', '--quiet'];

/** One silent, windowless instance for the whole run. */
function instance(): libvlc_instance_t
{
    static $instance = null;

    return $instance ??= libvlc_new(count(VLC_TEST_ARGS), VLC_TEST_ARGS) ?? throw new RuntimeException('libvlc_new returned NULL: '.libvlc_errmsg());
}

/** A temp 44100 Hz stereo s16 sine WAV of $seconds, deleted at shutdown. */
function wav(float $seconds = 0.5): string
{
    $frames = (int) round(44100 * $seconds);
    $pcm = '';
    for ($i = 0; $i < $frames; $i++) {
        $s = (int) (sin(2 * M_PI * 440 * $i / 44100) * 8000);
        $pcm .= pack('v2', $s & 0xFFFF, $s & 0xFFFF);
    }
    $base = tempnam(sys_get_temp_dir(), 'vlc');
    $file = $base.'.wav';
    register_shutdown_function(fn () => @unlink($base));
    file_put_contents($file, 'RIFF'.pack('V', 36 + strlen($pcm)).'WAVEfmt '.pack('VvvVVvv', 16, 1, 2, 44100, 44100 * 4, 4, 16).'data'.pack('V', strlen($pcm)).$pcm);
    register_shutdown_function(fn () => @unlink($file));

    return $file;
}

/** Polls $done every 10 ms for up to $seconds; whether it came true. */
function waitFor(callable $done, float $seconds = 3.0): bool
{
    $deadline = microtime(true) + $seconds;
    while (! $done()) {
        if (microtime(true) > $deadline) {
            return false;
        }
        usleep(10_000);
    }

    return true;
}

/** macOS and Linux signal numbers a kept refusal's probe dies by. */
const PROBE_SIGBUS = PHP_OS_FAMILY === 'Darwin' ? 10 : 7;
const PROBE_SIGSEGV = 11;
const PROBE_SIGABRT = 6;

/** Skips a tests/Probes test unless the loaded ext-vlc is a probe build (--enable-vlc-probes). */
function requireProbeBuild(): void
{
    if (! defined('VLC_PROBES')) {
        test()->markTestSkipped('ext-vlc is not a probe build (configure --enable-vlc-probes): VLC_PROBES is undefined');
    }
}

/**
 * Runs $code in a child of this PHP with only ext-vlc loaded. $siteOff names the kept site
 * VLC_PROBE_OFF turns off, null keeps every site. $gmalloc runs the child under libgmalloc
 * (macOS) with Zend's allocator off, so an over-read faults at the guard page instead of reading
 * the next heap block.
 *
 * @return array{signal: ?int, stdout: string}
 */
function vlcProbe(string $code, ?string $siteOff, bool $gmalloc = false): array
{
    $script = "<?php\ndeclare(strict_types=1);\nconst VLC_TEST_ARGS = ".var_export(VLC_TEST_ARGS, true).";\ntry {\n".$code."\n} catch (Throwable \$t) {\n    echo 'REFUSED ', get_class(\$t), ': ', \$t->getMessage(), \"\\n\";\n}\necho \"SURVIVED\\n\";\n";
    $file = tempnam(sys_get_temp_dir(), 'vlc-probe');
    file_put_contents($file, $script);

    $env = getenv();
    unset($env['VLC_PROBE_OFF'], $env['DYLD_INSERT_LIBRARIES'], $env['USE_ZEND_ALLOC']);
    $env['XDEBUG_MODE'] = 'off';
    if ($siteOff !== null) {
        $env['VLC_PROBE_OFF'] = $siteOff;
    }
    if ($gmalloc && PHP_OS_FAMILY === 'Darwin') {
        $env['DYLD_INSERT_LIBRARIES'] = '/usr/lib/libgmalloc.dylib';
        $env['USE_ZEND_ALLOC'] = '0';
    }

    $command = [PHP_BINARY, '-n', '-d', 'memory_limit=128M', '-d', 'extension='.ini_get('extension_dir').'/vlc.so', $file];
    $process = proc_open($command, [0 => ['file', '/dev/null', 'r'], 1 => ['pipe', 'w'], 2 => ['file', '/dev/null', 'w']], $pipes, null, $env);
    $stdout = (string) stream_get_contents($pipes[1]);
    fclose($pipes[1]);
    do {
        $status = proc_get_status($process);
        if ($status['running']) {
            usleep(20_000);
        }
    } while ($status['running']);
    proc_close($process);
    @unlink($file);

    return ['signal' => $status['signaled'] ? $status['termsig'] : null, 'stdout' => $stdout];
}
