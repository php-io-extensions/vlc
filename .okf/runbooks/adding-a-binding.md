---
type: Runbook
title: Adding a binding
description: Generated or hand-written; stub, gen_stub, the C file that includes the stub's arginfo and registers its functions, the test, the support list.
resource: tools/generate.php
tags: [vlc, contributing]
status: draft
generated: { by: claude-opus/5.5, at: 2026-11-11T00:00:00Z }
---

# Overview

1. A function whose parameters and result are all plain (handle, integer, float, bool, string, `void *`) comes from `php84 tools/generate.php <group>`. To change one, change the generator (`NULLABLE`, `FREES`, `REFCOUNTED`, `NEW_REF`) and rerun it; never edit `gen_*` files.
2. Any other shape is hand-written in the group's own stub and `.c`, and listed in the generator's `FREES` when a plain shape needs hand code (it frees handles or records a format).
3. Regenerate arginfo: `php84 /opt/homebrew/opt/php@8.4/lib/php/build/gen_stub.php stubs`. One `.c` includes one arginfo header and registers its `ext_functions` from MINIT (`src/vlc.c`), and is listed in `config.m4`.
4. Write the `PHP_FUNCTION` out; the guard matches each to its stub. A throw needs a site or a `helpers.marshal` function.
5. Test it in `tests/`, build, run the suite on NTS and ZTS, then `php84 scripts/support.php`.
