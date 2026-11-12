# Log

## 2026-11-12

* **No callback record leaks.** Callback media records were never freed; event records leaked when their object went without a detach; an instance's log, exit and dialog records leaked with it; a player's records were freed while a list player still held it. Each record now goes when libvlc is done with it: see [Record lifetimes](architecture/handles-and-callbacks.md). `leaks --atExit`: 698 leaks before, 0 after. Mac 92 passed on NTS and ZTS, Pi 91 passed; the Pi tone replayed (`MediaPlayerEndReached` after 3.11 s).

## 2026-11-11

* **Green: Mac NTS and ZTS, Pi ZTS.** Mac 80 passed, 3 probes skipped; probe build 78 / 78 before the support tests landed. Pi (Debian 13.7, PHP 8.4.27 ZTS, libvlc-dev 3.0.24 rpt3): 79 passed; the FFI video test skips (no ext-ffi there). Pi smoke: a 3 s tone played through `alsa_output.platform-107c701400.hdmi.hdmi-stereo` and `MediaPlayerEndReached` arrived after 3.11 s.

* **ext-vlc 0.11.0: 277 / 282.** Guarded build against libvlc 3.0.24: VLC.app on macOS (headers and universal dylibs, no pkg-config file), `libvlc-dev` on Debian. Not bound: `libvlc_vprinterr` and four functions the 3.0.24 library does not export. deprecated.h is out of scope.
* **Generator.** `tools/generate.php` writes the 190 plain-shaped functions of five header groups; the rest are hand-written. ext-guard learned two libvlc shapes for it: `VLC_FORWARD_DECLARE_OBJECT(T *)` as a return type, and `libvlc_dialog_cbs` as a callback struct (with a typemap entry).
* **Callbacks.** miniaudio's queue, three ways: waited (results libvlc needs), deferred (events, exit handler: a synchronous serve deadlocked stop() inside an event callable), posted (void calls; real-time audio never waits on PHP).
* **Refusals kept, each probe-proven:** `vlc-no-instance` (SIGABRT), `vlc-released-handle` (SIGSEGV), `vlc-list-count` (SIGSEGV under libgmalloc). Dropped: `vlc-foreign-list` (a release takes a fresh malloc'd array, so a hand-built list is the same input).
* **libvlc facts.** A media's event manager is at the media's address. VLC.app's libvlc finds no plugins without `VLC_PLUGIN_PATH`. `TimeChanged` never fires with `--aout=dummy`. The preparser skips callback media (status skipped). Callback media ends in `libvlc_Ended` even when open fails. `FL32` is not a libvlc audio fourcc (`f32l` is). The first equalizer band is 31.25 Hz.
