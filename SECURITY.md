# Security Policy

## Supported versions

ext-vlc is pre-1.0. No 0.x release receives security fixes or advisories; fixes land in the next
release line. Security support starts with 1.0.

| Version | Security fixes |
|---------|----------------|
| < 1.0   | No             |

## Reporting a vulnerability

Please don't open a public issue for a security problem.

Report it privately through GitHub: the **Report a vulnerability** button on the
[php-io-extensions/vlc](https://github.com/php-io-extensions/vlc) repository's **Security** tab.
If that isn't available, email **info@projectsaturnstudios.com**.

Include what you found, the affected version, your platform, PHP build (NTS or ZTS) and the
libvlc version (`php --ri vlc` shows it), and steps to reproduce. Reports are read and weighed for
the release line in development; before 1.0 there is no response-time commitment.

A defect in libvlc or one of its plugins belongs with the VideoLAN project. Report it here as
well when ext-vlc should guard against it.

## Security model

ext-vlc hands libvlc the locations, files, descriptors and options the PHP code gives it. libvlc
then opens files, network streams and devices, and loads its plugins, with the PHP process's
rights; ext-vlc does not restrict what libvlc may open.

- **Inputs.** A count past its list is refused before libvlc reads the list. `libvlc_clearerr()`
  before the first `libvlc_new()` is refused (libvlc would abort).
- **Addresses.** `fromPointer()`, `void *` user data, `FILE *` streams, drawables, video planes
  and `libvlc_free()` take addresses as ints and trust them: an address from another extension is
  passed through as given.
- **Handles.** A handle whose last counted reference was released, a list element after its
  list's `*_release`, and a released equalizer or discoverer throw `ValueError` instead of
  reaching libvlc with a freed pointer.
- **Callbacks.** PHP callables never run on libvlc's threads: each call is handed to the PHP
  thread that set it, within a deadline, and libvlc gets its no-op otherwise. At request end every
  callable is dropped; libvlc keeps calling the extension's records, which answer with the no-op.

A report is in scope when ext-vlc itself reads or writes memory it should not, leaks, or crashes:
a list copied past its length, a handle used after libvlc freed it, PHP entered from a libvlc
thread.
