---
okf_version: "0.2"
---

# ext-vlc

1:1 PHP bindings of libvlc 3.0: 277 of the 282 functions of the 3.0.24 headers outside deprecated.h, against the installed library (VLC.app on macOS, libvlc-dev on Debian). Version 0.11.0. Linux and macOS.

# API

* [Bindings](api/bindings.md) — Functions, handles, list elements, value classes and constants by header; which are generated and which hand-written.

# Architecture

* [Handles and callbacks](architecture/handles-and-callbacks.md) — Identity table, reference counting, list elements, the callback queue, kept refusals.

# Runbooks

* [Build, install, test](runbooks/build.md) — Mac NTS/ZTS against VLC.app, the Pi, probe builds.
* [Adding a binding](runbooks/adding-a-binding.md) — Generated or hand-written, stub, gen_stub, registration, the test, the support list.
