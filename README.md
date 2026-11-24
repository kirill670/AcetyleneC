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
| E32 import table | emitted by `acetylene-e32fix` | Header CRC recovered (`crc32 ^ 0x7601236A`), Idata record layout recovered, and the tool appends a validated import section to the `elf2e32` output. `elf2e32 --dump=i` reads it and prints the DLL name, count and patched address. One Idata record per DLL is written and the format is validated against Symbian's own parser; the parser only prints the first record, so multi-DLL chaining could not be observed either way, and nothing was tested on a device. |
| DLL builds | works | `is_dll=1` in the `.acproj` switches the pipeline to the DLL flow: links without the EXE CRT, entry `E32Dll`, and `elf2e32 --targettype=DLL` also emits the `.def` and `.dso` import library. Verified: `EPOC Dll for ARMV5 CPU`. |
| SIS / SISX packaging | works via platform `makesis` | `Ctrl+P` (or Build > Package) generates a `.pkg` from the project and produces `build/<name>.sisx`; the result parses in Symbian `signsis` ("No primary signatures"), which confirms the container. | `acetylene-sis` validates the `.pkg`, invokes the target's `makesis.exe` (same as Carbide does) and produces a real SISX (verified: `7a 1a 20 10` header, 380-byte package from the test pkg). |
| Certificate generator | works | `acetylene-makekeys` generates RSA keys, self-signed X.509 v3 certs, PEM/PKCS#1 output. Verified independently with a Python DER/RSA verifier. |
| Signing with those certs | **not accepted by `signsis`** | The SDK's `signsis.exe` only parses its own PEM profile and rejects ours. Sign with keys produced by the bundled `makekeys.exe` for now. |
| Run on emulator | adapter to an external EKA emulator | F5 packages and launches the emulator you configured; the SDK never bundles it. Exact command line goes to the output pane. See `docs/EMULATOR.md`. |
| C++ | works (subset) | `acetylene-cxx`, MIT, our own front-end: classes, fields, methods, constructors, member access, out-of-line definitions, Itanium mangling (`_ZN7Counter3GetEv`). It transpiles to C and then goes through TCC. Rejects inheritance, virtuals, destructors, references and templates with an explicit error. The bundled GCCE `g++` is still available for full C++. |
| C headers/libs from all SDKs | yes | `sdk/targets/{s60v2,s60v30,s60v31,s60v32,s60v5}/{include,lib,tools}` — imported from the official archives. |
| IDE | works | Tree, tabs, C/C++ highlighting, editing with undo/redo, find bar (Ctrl+F, Enter = next) and go-to-line (Ctrl+G), multi-file project build where every `source=` entry is compiled and linked, error list with the exact command log, status bar. Verified interactively: typing, undo, save-to-disk, search match, C and C++ builds. |

## Running on an emulator

No emulator is shipped. **Build > Set Emulator...** points AcetyleneC at an EKA2 emulator you
downloaded yourself; **F5** then packages the project when needed and starts it with the built
paths substituted (`%e32%`, `%sisx%`, `%project%`). Settings live in `acetylene.ini` next to the
IDE, format and examples in `docs/EMULATOR.md`.

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
4. **F7** builds every `source=` in the project (C via TCC, C++ via `acetylene-cxx` then TCC), links with `acetylene-ld` and post-links with `elf2e32` into `build/<name>.e32`.
5. Shortcuts: `Ctrl+N` new project, `Ctrl+O` open, `Ctrl+S`/`Ctrl+Shift+S` save/save-as, `Ctrl+W`
   close tab, `Ctrl+Tab` / `Ctrl+Shift+Tab` switch tabs, `Ctrl+Z/Y` undo/redo, `Ctrl+F`/`Ctrl+G`
   find / goto, `Ctrl+P` package, `F7`/`Ctrl+F7` build/rebuild, `F9` sign, `F5` run, `` Ctrl+` ``
   toggle output.

Right-click works everywhere it should: the project tree (open, save, build, package, sign, run,
refresh), the tab strip (save, close, close others, save all), the editor (undo/redo/clipboard/find/
goto/save), the output pane (copy line, copy log, clear) and the find bar (cut/copy/paste/select all/
close). The find field itself is editable: arrows, Home/End, Backspace/Delete and `Ctrl+V`.

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

* E32 import tables are not emitted; `docs/E32-IMPORTS.md` records exactly what was tried and what
  the next attempt needs (reproduce the GCCE `-shared` link product for `elftran`, or recover the
  header CRC to splice an Idata table into the `elf2e32` output).
* `signsis` rejects our generated certificates; the SDK `makekeys` path works.
* C++ relies on the bundled GCCE compiler, not on an MIT-licensed frontend.
