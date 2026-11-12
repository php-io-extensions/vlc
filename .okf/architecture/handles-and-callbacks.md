---
type: Module
title: Handles and callbacks
description: One PHP object per (libvlc pointer, class); reference counting for the seven counted classes; list elements libvlc owns; the callback queue; the three kept refusals.
resource: src/runtime.c
tags: [vlc, handles, callbacks, threads]
status: draft
generated: { by: claude-opus/5.5, at: 2026-11-11T00:00:00Z }
sources:
  - id: runtime
    resource: src/runtime.c
    title: Identity table, reference counts, marshal helpers
  - id: queue
    resource: src/queue.c
    title: The callback queue
  - id: callbacks
    resource: src/callbacks.c
    title: Trampolines and the callback-taking functions
---

# Identity

`VLC_G(boxes)` maps (native address, class) to the live PHP object: one object per pair per thread. Address alone is not an identity: libvlc 3.0 embeds a media's event manager at the media's own address.

# Reference counting

Instance, media, media player, media list, list player, media library and renderer item are reference-counted in libvlc. `VLC_G(refs)` counts the references the binding handed out: creation, `*_retain` / `_hold` (`vlc_ref_add`), and the getters libvlc documents as returning a new reference (`vlc_box_new`; the generator's `NEW_REF` list). The class's own `*_release` runs `vlc_ref_releasing` before libvlc's release and drops one after it (`vlc_ref_drop`); the drop that reaches zero releases the handle. A pointer never counted (`fromPointer`, an event's pointer) counts as one, also when it is then retained. Equalizer and discoverers have one owner: their release releases the handle.

# List elements

libvlc owns them until the list's `*_release`. A linked list's release walks `p_next` and releases every node's handle. An array getter fills a PHP list and frees only libvlc's array; its `*_release` takes the list back and passes libvlc a fresh `malloc`'d array of the handles' pointers, which libvlc frees with `free()` after freeing the elements.

# The callback queue

libvlc calls back on its own threads; PHP never runs there (`src/queue.c`, ported from miniaudio). Three ways:

* **Waited** (`vlc_queue_call`): media open/read/seek, audio setup, video lock/format, log. The libvlc thread posts, raises the owner's `vm_interrupt`, waits up to its deadline (lock 100 ms; setup, format, media 5 s; log 1 s), then gets the no-op. A call fired on the owner thread itself is served at once.
* **Deferred** (`vlc_defer`): events and the exit handler. The serve copies the data into zvals; the libvlc thread is let go; the callable runs afterwards. A synchronous serve deadlocked `libvlc_media_player_stop` called inside an event callable: the emitting thread waited on the callable that joined it.
* **Posted** (`vlc_queue_post`): audio play/pause/resume/flush/drain/volume/cleanup, video unlock/display/cleanup, media close, dialogs. Arguments are copied into a malloc'd request; libvlc never waits.

Request end (`vlc_queue_rshutdown`) gives every record its no-op, drops queued and posted calls, waits for libvlc threads inside a call, frees the callables. libvlc keeps the records' native parts until their object goes, as below.

# Record lifetimes

A record (`vlc_cb`) is freed when libvlc can no longer call it. libvlc 3.0 announces only one death, `libvlc_MediaFreed`; the rest follow the binding's counts:

* **Callback media** (`libvlc_media_new_callbacks`): a native `libvlc_MediaFreed` listener marks the record dead (`vlc_cb_dead`, any thread). The owner thread takes dead records at its next interrupt, serves the calls libvlc posted for them (a close comes before the free), then frees them. A record whose request already ended is freed at once.
* **Event callables**: an event manager's handle carries its object (`vlc_box_em`). Before the binding's last release of that object, `vlc_ref_releasing` detaches and frees them (`libvlc_event_detach` takes the manager's lock, which libvlc holds while calling listeners). The VLM's go before `libvlc_vlm_release`; a renderer discoverer's before its release. A manager from `fromPointer` has no object: its records go on detach or with the process.
* **Instance**: before its last release, the log, exit handler and dialog callbacks are unset in libvlc (each unset returns once no call is running), then freed. libvlc may keep the instance alive for objects made from it; their callables on the instance stop here.
* **Players**: `libvlc_media_list_player_set_media_player` and `_get_media_player` count the list player's hold on its player (`VLC_G(held)`), dropped when the list player goes or swaps it. A player's count thus reaches zero only when libvlc destroys it; `vlc_owner_dead` then frees its audio and video records.
* A record whose object the script never releases lives as long as that object, as in C.

`tests/LifetimeTest.php` checks each rule through a `__destruct` on state the callables capture. `leaks --atExit` on a 200-iteration create/release script: 0 leaks (698 before this).

# Kept refusals

* `vlc-no-instance` — `libvlc_clearerr()` before the first `libvlc_new()`: libvlc aborts (SIGABRT). `libvlc_errmsg()` there reads a foreign thread slot but does not crash, so it passes through.
* `vlc-released-handle` — in `vlc_handle_arg`: a NULL handle reaching libvlc segfaults.
* `vlc-list-count` — in `vlc_list_count`: a count past its list reads past the array (segfaults under libgmalloc).

# Citations

[1] [runtime](src/runtime.c)
[2] [queue](src/queue.c)
[3] [callbacks](src/callbacks.c)
