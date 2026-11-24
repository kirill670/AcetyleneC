# AcetyleneC — unofficial Symbian S60 SDK

An unofficial, self-hosted SDK and IDE for Symbian S60 devices, from **S60v2 (2nd Edition)** up to
**S60v5 (5th Edition)**. Everything is 32-bit Win32, built from source in this repo.

The IDE is called **AcetyleneC** and is a Win32/GDI editor in the spirit of Carbide.c++ / Visual
Studio: project tree, tabbed editor with C/C++ syntax highlighting, build pipeline and error list.

## What actually works

| Piece | State | Notes |
|---|---|---|
| `vendor/tinycc` built as ARM cross compiler (`build/bin/acetylene-cc.exe`) | works | Emits ARM ELF32 objects, EABI v4, soft-float ABI, Symbian-compatible `e_flags`. |
| `acetylene-ld` — ARM ELF linker | works | Resolves against the SDK's own `.lib` import libraries, applies ARM relocations, keeps `.directive` sections and `#<DLL>` import markers, emits `.rel.text`. |
| E32 image | works via `elf2e32` | The official Symbian post-linker is bundled per target and driven by the IDE. Header, code section, relocation and CRC are produced by Symbian's own tool. |
| E32 **import table** | **not generated** | This is the honest gap: the 2005/2007 `elf2e32` versions in the SDKs only build imports from the V2 "directive" flow of the original GCCE linker. Our linker reproduces the stub code and directives, but the produced E32 ends up with `Dll ref table count: 0`. Calls into OS DLLs will not bind on device yet. Static code, data and entry point are correct. |
| SIS / SISX packaging | works via platform `makesis` | `acetylene-sis` validates the `.pkg`, invokes the target's `makesis.exe` (same as Carbide does) and produces a real SISX (verified: `7a 1a 20 10` header, 380-byte package from the test pkg). |
| Certificate generator | works | `acetylene-makekeys` generates RSA keys, self-signed X.509 v3 certs, PEM/PKCS#1 output. Verified independently with a Python DER/RSA verifier. |
| Signing with those certs | **not accepted by `signsis`** | The SDK's `signsis.exe` only parses its own PEM profile and rejects ours. Sign with keys produced by the bundled `makekeys.exe` for now. |
| C++ | via bundled GCCE g++ | `sdk/gcce/bin/arm-none-symbianelf-g++.exe` (the official Symbian toolchain that ships in the SDK distribution, GPL). The originally planned MIT C++ frontend was **not** delivered — a half-working transpiler was removed rather than shipped as a stub. |
| C headers/libs from all SDKs | yes | `sdk/targets/{s60v2,s60v30,s60v31,s60v32,s60v5}/{include,lib,tools}` — imported from the official archives. |
| IDE | works | Tree, tabs, highlighting, editing with undo/redo, find/goto, build to `.e32`, error list, output log. |

## Layout

```
build/bin            built 32-bit tools (AcetyleneC.exe, acetylene-cc/ld/sis/makekeys)
src/ld               acetylene-ld (ARM ELF linker for Symbian)
src/sign             SHA-1/256, bignum, RSA, DER, X.509, makekeys
src/sis              .pkg parser + packaging driver
src/ide              AcetyleneC (Win32 GDI)
src/common           shared utilities
sdk/targets/<t>      headers, import libs and tools per S60 target
sdk/gcce             official Symbian GCCE toolchain (C++ compiler, ld, readelf)
sdk/include          C bindings for Symbian OS (mangled symbol declarations)
tools/sdkimport.sh   rebuilds sdk/targets from the official SDK archives
vendor               tinycc (LGPL-2.1), unshield (MIT), zlib
```

## Building the toolchain

Requirements: 32-bit MinGW-w64 (`i686-w64-mingw32-gcc`) and CMake. Both are fetched into `.cache`
by the bootstrap scripts; nothing is installed system-wide.

```sh
sh build/build-tcc.sh          # TCC as a Windows-hosted ARM cross compiler
sh build/build-tools.sh        # linker, makekeys, sis, IDE
```

## Using the IDE

1. `build/bin/AcetyleneC.exe`
2. **File > New Project** — pick a folder; a `main.c` stub is created.
3. Edit `target=s60v5` (or `s60v2`, `s60v30`, `s60v31`, `s60v32`) in the `.acproj`.
4. **F7** builds: TCC → `acetylene-ld` → `elf2e32`, producing `build/<name>.e32`.
5. `Ctrl+F` find, `Ctrl+G` goto line, `Ctrl+S` save, `Ctrl+Z/Y` undo/redo, `Ctrl+W` close tab.

C sources include `sdk/include` (AcetyleneC C bindings) and `sdk/include/tcc` (freestanding libc
prototypes). Symbian's own headers are C++-only and are **not** usable from C; the C bindings declare
the mangled Symbian entry points explicitly, e.g.:

```c
#include <acetylene/e32c.h>
GLDEF_C TInt E32Main(void) { return KErrNone; }
```

## Licensing

Our code is MIT (see `LICENSE`). Vendored components keep their own licenses: TCC (LGPL-2.1),
unshield (MIT), zlib (zlib). The imported SDK headers, libraries and tools remain under Nokia's
SDK EULA and Symbian/GPL terms respectively — see `THIRD_PARTY.md`. Do not redistribute binaries
built from them without checking those terms.

## Known gaps, stated plainly

* E32 import tables are not emitted (see above). Fixing this needs either the original GCCE
  `-shared` link flow reproduced exactly, or a from-scratch E32 writer with a verified Idata layout.
* `signsis` rejects our generated certificates; the SDK `makekeys` path works.
* C++ relies on the bundled GCCE compiler, not on an MIT-licensed frontend.
* The IDE builds one active source file per project; multi-file projects need a workspace build step.
