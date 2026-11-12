<?php

declare(strict_types=1);

require_once __DIR__ . '/../scripts/support.php';

it('counts the LIBVLC_API functions of each header, sorted, once each, past comments and macros', function (): void {
    $header = "/** LIBVLC_API void libvlc_commented(void); */\nLIBVLC_API libvlc_instance_t *\nlibvlc_new( int argc, const char *const *argv );\n"
        . "LIBVLC_API void libvlc_release( libvlc_instance_t *p_instance );\n"
        . "LIBVLC_API VLC_FORWARD_DECLARE_OBJECT(libvlc_media_list_t *) libvlc_media_subitems( libvlc_media_t *p_md );\n"
        . "#  define LIBVLC_API __attribute__((visibility(\"default\")))\n";

    expect(support_counted(['libvlc.h' => $header, 'empty.h' => "#define X 1\n"]))
        ->toBe(['libvlc.h' => ['libvlc_media_subitems', 'libvlc_new', 'libvlc_release']]);
});

it('reads the top-level functions of a stub, not class methods', function (): void {
    $stub = "<?php\nfunction libvlc_new(int \$argc, array \$argv): ?libvlc_instance_t {}\nfinal class libvlc_media_t { public function pointer(): int {} }\nfunction libvlc_release(libvlc_instance_t \$i): void {}\n";

    expect(support_functions($stub))->toBe(['libvlc_new', 'libvlc_release']);
});

it('renders one line per function, with the reason for an unbound one', function (): void {
    $md = support_render(['libvlc.h' => ['libvlc_new', 'libvlc_vprinterr']], ['libvlc_new' => true, 'libvlc_helper' => true],
        ['libvlc_vprinterr' => 'takes a va_list'], 'libvlc 3.0.24', '2026-11-11');

    expect($md)->toContain('- [x] `libvlc_new`')
        ->toContain('- [ ] `libvlc_vprinterr` — takes a va_list')
        ->toContain('## libvlc.h (1 / 2)')
        ->toContain('libvlc 3.0.24 — 1 / 2 members bound (50.0%) — 2026-11-11')
        ->toContain('- `libvlc_helper`');
});

it('computes the badge from the counts', function (): void {
    expect(support_badge('libvlc API', 277, 282))
        ->toBe('[![libvlc API](https://img.shields.io/badge/libvlc_API-98.2%25_%28277%2F282%29-blue?style=flat-square)](SUPPORT.md)');
});

it('binds every exported libvlc 3.0.24 function, and SUPPORT.md and the badge are current', function (): void {
    $root = dirname(__DIR__);
    exec(PHP_BINARY . ' ' . escapeshellarg("{$root}/scripts/support.php") . ' --check', $out, $code);

    expect($code)->toBe(0)
        ->and(file_get_contents("{$root}/SUPPORT.md"))->toContain('libvlc 3.0.24 — 277 / 282 members bound (98.2%)');
});
