---
type: Runbook
title: Build, install, test
description: Mac NTS/ZTS against VLC.app, the Pi through Debian's libvlc-dev, and probe builds.
resource: install-macos.sh
tags: [vlc, build]
status: draft
generated: { by: claude-opus/5.5, at: 2026-11-11T00:00:00Z }
sources:
  - id: mac
    resource: install-macos.sh
    title: macOS installer
  - id: pi
    resource: install-debian-trixie.sh
    title: Debian trixie installer
---

# Mac

VLC.app 3.0 in `/Applications` ships `Contents/MacOS/include/vlc`, `lib/libvlc.dylib` (universal, install name `@rpath/libvlc.dylib`) and `plugins/`, no pkg-config file. `config.m4` finds the prefix by `include/vlc/vlc.h`; `PHP_ADD_LIBRARY_WITH_PATH` adds the rpath.

```bash
bash install-macos.sh           # php@8.4 and php@8.4-zts
php84 -d memory_limit=128M vendor/bin/pest
```

libvlc from VLC.app finds its plugins only through `VLC_PLUGIN_PATH`; `tests/Pest.php` sets it when unset.

# Probe build

```bash
VLC_CONFIGURE=--enable-vlc-probes bash install-macos.sh
php84 -d memory_limit=128M vendor/bin/pest    # tests/Probes run; VLC_PROBE_OFF=<site> turns one site off
bash install-macos.sh                          # back to a release build
```

# Pi

`fnk` is the maintainer's shell alias for the Pi: run `zsh -ic 'fnk "<cmd>"'`. Install `libvlc-dev vlc-plugin-base` there (sudo, the maintainer), copy the tree without `.git` and `vendor`, then `./install-debian-trixie.sh` and the suite. Sound is allowed on the Pi.

# Citations

[1] [mac](install-macos.sh)
[2] [pi](install-debian-trixie.sh)
