# The EPOC PE era: S60v2, S60v1, UIQ 2.x, S80

Symbian releases before EABI (S60 2nd Edition, Series 60 1.x, UIQ 2.1, S80 DP2) do not use the
`.e32` images that `elf2e32` produces. They run **ABI-less ARM images** that the old toolchain
created by translating a PE file, and their import libraries are ARM COFF objects, not ELF.

AcetyleneC handles that generation with `build/bin/acetylene-pe.exe`: one binary that reads our ELF
objects and the SDK's COFF libraries, links them, and writes the final image. No SDK executable is
involved — the format was reconstructed from the SDK headers (`f32image.h`) and from images
produced by the platform tools during development.

## Pipeline

```sh
build/bin/acetylene-cc.exe -I sdk/include -I sdk/include/tcc -c hello.c -o hello.o
build/bin/acetylene-cc.exe -I sdk/include -I sdk/include/tcc -c sdk/runtime/e32main_shim_legacy.c -o shim.o
build/bin/acetylene-pe.exe -o hello.app hello.o shim.o \
    -entry _E32Startup -uid1 0x100039CE -uid2 0xE0000001 -uid3 0 \
    -heap 0x1000 0x100000 -stack 0x2000 \
    -L sdk/targets/s60v2/lib -leexe -lecrt0 -lestlib -leuser
```

`hello.app` is the finished executable. `-v` prints every section that goes into text, data and bss.

The IDE runs the same command: `run_build_pipeline` asks `ide_target_is_legacy` whether the target
's `target.ini` says `format=pe`, and if so hands the project to `run_build_legacy`, which compiles
every `source=` entry, adds the legacy entry shim and calls `acetylene-pe` with the runtime libraries
listed in that `target.ini`. Setting `target=s60v2` (or `s60v1`, `s80`, `uiq21`) in a `.acproj` is all
a project needs.

The C entry point is plain `E32Main`; `sdk/runtime/e32main_shim_legacy.c` provides the ARM C++
mangling (`E32Main__Fv`) that `ecrt0.lib` calls. That is the legacy equivalent of the Itanium
(`_Z7E32Mainv`) shim used by the EABI path.

## Input formats

**ELF objects** come from our compiler: ARM, little-endian, `R_ARM_ABS32` and `R_ARM_PC24` only.

**COFF import libraries** (`.lib`) are `ar` archives of COFF objects with machine `0x0a00`. This
old dialect differs from Microsoft COFF in two ways that matter:

* relocation records are **14 bytes**: `VirtualAddress(4)`, `SymbolTableIndex(4)`, `Type(2)`,
  `Addend(4)`;
* relocation types are `2` (`ARM_32`, absolute) and `3` (`ARM_26`, PC-relative branch).

A library is a chain of three kinds of object:

| Object | Contents | Role |
|---|---|---|
| head | `.idata$2` (import descriptor template) | glue, not emitted |
| per-symbol stub | `.text` thunk (`ldr ip,[pc,#4]; ldr ip,[ip]; bx ip`), `.idata$4`/`.idata$5` holding `0x80000000 \| ordinal` | one imported function |
| tail | `.idata$7` = `NAME[uid3].DLL` | the DLL name for the whole library |

The linker recognises a stub by the combination of an `.idata$5` section and a public symbol defined
in `.text`. Head and tail objects have the same section names but no thunk, so they are skipped.
The DLL name comes from the tail, the ordinal from the stub's `.idata$5`.

## Output format

Header, 0x7C bytes, exactly as `f32image.h` describes it:

| Offset | Field |
|---|---|
| 0x00 | iUid1, iUid2, iUid3 |
| 0x0C | iCheck — the UID checksum, see below |
| 0x10 | `EPOC` |
| 0x14 | iCpu = 0x2000 (ARM) |
| 0x18 | iCheckSumCode — sum of all 32-bit words of the code section |
| 0x1C | iFormat (`KImageHdrFmt_J` is set in iFlags for compression support) |
| 0x20 | iVersion, 0x00C00001 = 1.0(192) |
| 0x24 | iTime, 64-bit |
| 0x2C | iFlags = 0x01000000 |
| 0x30 | iCodeSize, iDataSize, heap min/max, stack, bss |
| 0x48 | iEntryPoint (offset into code) |
| 0x4C | iCodeBase = 0x400000, iDataBase |
| 0x54 | iDllRefTableCount, export directory (0), |
| 0x60 | iTextSize, iCodeOffset = 0x7C, iDataOffset, iImportOffset, relocation offsets (0), priority |

Code section = text, then the **import address table**: one 32-bit slot per imported function filled
with its ordinal, plus one zero terminator. `iTextSize` is the text size, so the IAT starts exactly
there; `iCodeSize = iTextSize + 4 * (imports + 1)`. With no imports there is no IAT at all and
`iImportOffset` is 0.

Each import stub's thunk literal is rewritten to `0x400000 + text_size + 4 * slot`, so the generated
code starts `ldr ip,[pc,#4] / ldr ip,[ip] / bx ip / .word <IAT address>`.

The import section holds one record per DLL:

```
u32 size                       // bytes after this field
u32 offset_of_dll_name         // relative to the start of this section
u32 number_of_imports
u32 ordinals[number_of_imports]
char name[]                    // "ESTLIB[10003b0b].DLL"
```

The loader resolves the ordinals in order against consecutive IAT slots.

## UID checksum

`iCheck` is not a CRC of the header; it is a linear map of the three UIDs. It equals
`uidcrc.exe uid1 uid2 uid3` from the SDK for every value tested. The map treats each UID byte as
eight independent bits feeding two 16-bit accumulators, which are combined as `(hi << 16) | lo`.
`src/pe/pe.c` carries the 48 constants and `tests/run-tests.sh` checks the published vectors.

Unknown symbols that the runtime expects the linker to define (`__CTOR_LIST__`, `__CTOR_END__`,
`__DTOR_LIST__`, `__DTOR_END__`) are placed at the end of the data area, so the constructor walk is
empty rather than dangling.

## Targets

`tools/sdkimport.sh` imports five S60 targets plus UIQ 2.1, Series 60 1.x and S80. Each
`sdk/targets/<name>/target.ini` records the ABI: `format=eabi` for S60 3rd Edition and later (the
`elf2e32` pipeline), `format=pe` for the legacy generation (this linker).

| Target | Basis | Format |
|---|---|---|
| s60v1 | Series 60 SDK 1.2 (Symbian 6.1) | pe |
| s60v2 | S60 2nd Edition FP3 (Symbian 7.0s) | pe |
| s80 | S80 DP 2.0 | pe |
| uiq21 | UIQ 2.1 (Symbian 7.0) | pe |
| s60v30 | S60 3rd Edition (Symbian 9.1) | eabi |
| s60v31 | S60 3.1 (Symbian 9.2) | eabi |
| s60v32 | S60 3.2 (Symbian 9.3) | eabi |
| s60v5 | S60 5th Edition (Symbian 9.4) | eabi |

## What was verified, and what was not

Verified here:

* images built by this linker and by the SDK's own `arm-epoc-pe-ld` + `petran` from the **same
  object files** have the same entry point, the same import name (`ESTLIB[10003b0b].DLL`), the same
  ordinal, and the IAT in the same place relative to the text;
* header fields match the reference images produced by `petran` field by field, including the UID
  check and the code checksum;
* a hello-world for S60v2, S60v1, UIQ 2.1 and S80 links into a complete image.

Not verified: nothing has run on a device or an EKA emulator. The image carries no base relocation
table, exactly like the platform's GCC path for these SDKs, so it is bound to 0x400000; DLL export
tables are not implemented yet, so only executables are produced.
