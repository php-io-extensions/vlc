# vlc

[![CI](https://img.shields.io/github/actions/workflow/status/php-io-extensions/vlc/ci.yml?style=flat-square&label=CI)](https://github.com/php-io-extensions/vlc/actions/workflows/ci.yml)
[![libvlc API](https://img.shields.io/badge/libvlc_API-98.2%25_%28277%2F282%29-blue?style=flat-square)](SUPPORT.md)

1:1 PHP bindings of libvlc 3.0: the instance and its log, media, the media player, the equalizer, media lists and the list player, the media library, media and renderer discoverers, VLM, dialogs, events, and the media, audio and video callbacks. Version 0.11.0. Linux and macOS.

Function and constant names are the C names. A handle is one PHP object per native pointer. Dropping the last PHP reference does not release the native object.

## Requirements

- libvlc 3.0 (built and tested against 3.0.24)
- PHP 8.4, NTS or ZTS
- macOS: VLC.app 3.0 in `/Applications` (`brew install --cask vlc`). It ships the headers and the library; set `VLC_PLUGIN_PATH=/Applications/VLC.app/Contents/MacOS/plugins` for the processes that use the extension, or `libvlc_new` finds no plugins and returns `null`.
- Debian trixie and Raspberry Pi OS: `apt install libvlc-dev vlc-plugin-base`

VLC.app ships no pkg-config file; `config.m4` finds `include/vlc/vlc.h` in VLC.app and the usual prefixes, or under `--with-vlc=DIR`.

## Install

Through PIE:

```bash
pie install php-io-extensions/vlc
```

From a checkout:

```bash
./install-macos.sh              # Homebrew php@8.4 and php@8.4-zts
./install-debian-trixie.sh      # Debian trixie / Raspberry Pi OS
```

The macOS installer ad-hoc signs the `.so` and writes `30-vlc.ini`, unless an ini in that PHP's scan directory already loads `vlc`. Pass other PHP binaries as arguments to install those instead.

### macOS: `VLC_PLUGIN_PATH`

VLC.app's libvlc finds its plugins only through `VLC_PLUGIN_PATH`. Without it, `libvlc_new()` returns `null`. Set it in the environment of every process that uses the extension, or with `putenv()` before the first `libvlc_new()`:

```bash
export VLC_PLUGIN_PATH=/Applications/VLC.app/Contents/MacOS/plugins
```

The extension sets no default. Debian's libvlc knows its own plugin directory and needs nothing.

## Names

Bindings are the C API with these translations:

- `libvlc_instance_t *`, `libvlc_media_t *`, `libvlc_media_player_t *` and the other opaque types are handles of those class names; `NULL` is `null`.
- A list libvlc returns (`libvlc_audio_output_list_get`, `libvlc_media_tracks_get`, ...) is handles whose properties are the C fields, read live; libvlc owns them until you pass the list back to its `*_release`. A linked list's `p_next` is the next handle.
- `libvlc_event_t`, `libvlc_media_stats_t`, `libvlc_video_viewpoint_t` and `libvlc_dialog_cbs` are value objects; `libvlc_event_t::$u` is the union member for the event type.
- Out-parameters are by-reference: `libvlc_video_get_size($mp, 0, $width, $height)`.
- `argc` / `argv` and every other pointer + count are a PHP list and its count, in C order: `libvlc_new(count($args), $args)`.
- `void *`, `FILE *`, drawables (`libvlc_media_player_set_nsobject`, `_set_xwindow`) and video planes are `int` addresses.
- Every function libvlc lets you pass a callback takes PHP callables instead of the C function pointer and its `void *` data.

## Callbacks

libvlc calls back on its own threads. PHP never runs there: the call is handed to the PHP thread that set it, at its next VM interrupt point (a loop iteration, `usleep()`, a function call).

| Callback | Called as | libvlc waits |
|---|---|---|
| `libvlc_event_attach` | `fn(libvlc_event_t $event)` | until the data is copied (≤ 1 s); the callable runs after, so it may stop the player |
| `libvlc_log_set` | `fn(int $level, libvlc_log_t $ctx, string $message)` | ≤ 1 s; `$ctx` is valid during the call |
| `libvlc_set_exit_handler` | `fn()` | as events |
| `libvlc_media_new_callbacks` | open `fn(?int &$size): int`, read `fn(int $len): string\|int`, seek `fn(int $offset): int`, close `fn()` | ≤ 5 s each (close: never) |
| `libvlc_audio_set_callbacks` | play `fn(string $samples, int $count, int $pts)`, pause/resume/flush `fn(int $pts)`, drain `fn()` | never |
| `libvlc_audio_set_volume_callback` | `fn(float $volume, bool $mute)` | never |
| `libvlc_audio_set_format_callbacks` | setup `fn(string &$format, int &$rate, int &$channels): int`, cleanup `fn()` | setup ≤ 5 s |
| `libvlc_video_set_callbacks` | lock `fn(): array` (plane addresses), unlock `fn(int $picture, array $planes)`, display `fn(int $picture)` | lock ≤ 100 ms |
| `libvlc_video_set_format_callbacks` | setup `fn(string &$chroma, int &$width, int &$height, array &$pitches, array &$lines): int`, cleanup `fn()` | setup ≤ 5 s |
| `libvlc_dialog_set_callbacks` | one Closure per `libvlc_dialog_cbs` field, with the C parameters after `p_data` | never |

Audio and video data waiting for the PHP thread is capped at 1024 calls; past that, new data is dropped. A call the PHP thread does not reach in time gets libvlc's no-op: media callbacks report an error, the audio setup refuses, the video lock renders into a scratch picture the extension owns. An exception thrown by a callable surfaces at the PHP thread's next interrupt point. When the request ends, every callable is dropped and libvlc gets the no-ops.

### Lifetime

The extension frees a callable when libvlc can no longer call it:

- Media from `libvlc_media_new_callbacks`: when libvlc frees the media (`libvlc_MediaFreed`), wherever its last reference goes. A player holding the media keeps its callables.
- Event callables: on `libvlc_event_detach`, or detached with the extension's last release of their object. A VLM's go with `libvlc_vlm_release`.
- An instance's log, exit handler and dialog callables: replaced, unset, or unset with the instance's last release.
- A player's audio and video callables: when libvlc destroys the player. A list player holding the player counts as a reference.

An object the script never releases keeps its callables, as libvlc keeps the object.

## Refusals

The extension refuses a call only where libvlc would crash the process:

| Site | Call | Error |
|---|---|---|
| `vlc-no-instance` | `libvlc_clearerr()` before the process's first `libvlc_new()` | `Error` |
| `vlc-released-handle` | a handle whose last counted reference was released, or a list element after its list's `*_release` | `ValueError` |
| `vlc-list-count` | a count past its list | `ValueError` |
| `vlc-printerr-no-instance` | `libvlc_printerr()` before the process's first `libvlc_new()` | `Error` |
| `vlc-discoverer-not-running` | `libvlc_media_discoverer_stop()` on a discoverer that is not running | `ValueError` |

The reference-counted classes (instance, media, media player, media list, list player, media library, renderer item) count the references the extension handed out: creation, `*_retain` / `_hold`, and the getters libvlc documents as returning a new reference. A handle the extension never counted (`fromPointer`, an event's pointer) counts as one.

## Example

```php
putenv('VLC_PLUGIN_PATH=/Applications/VLC.app/Contents/MacOS/plugins'); // macOS

$vlc = libvlc_new(1, ['--quiet']);
$media = libvlc_media_new_path($vlc, '/path/to/song.mp3');
$mp = libvlc_media_player_new_from_media($media);
libvlc_media_release($media);   // the player holds its own reference

$ended = false;
libvlc_event_attach(libvlc_media_player_event_manager($mp), libvlc_MediaPlayerEndReached,
    function (libvlc_event_t $e) use (&$ended): void { $ended = true; });

libvlc_media_player_play($mp);
while (! $ended) {
    usleep(10_000);
}
libvlc_media_player_release($mp);
libvlc_release($vlc);
```

## Coverage

[`SUPPORT.md`](SUPPORT.md) lists every function of the libvlc 3.0.24 headers (deprecated.h excepted), bound or not, and why not. Regenerate it with `php84 scripts/support.php`.

## Tests

```bash
composer install
php84 -d memory_limit=128M vendor/bin/pest
```

Mac tests run silent and windowless (`--aout=dummy --vout=dummy`). `tests/Probes` runs only against a probe build (`VLC_CONFIGURE=--enable-vlc-probes ./install-macos.sh`).

## License

MIT. libvlc itself is LGPL-2.1-or-later and is not part of this package.
