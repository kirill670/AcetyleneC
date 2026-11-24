# E32 import table — state of the investigation

This is the one functional gap in the toolchain: images built by AcetyleneC have a correct header,
code section, entry point and relocation tables, but `Dll ref table count: 0`. Calls into OS DLLs
are not bound on device.

Everything learned while attacking it is recorded here so the next attempt starts from facts.

## What the 2005–2007 parser in the SDKs needs

`elf2e32` (both V0.16 and V2.0) reads `.dynsym` and `.hash` (strings in the binary confirm it), and
it validates the E32 header CRC on its own output. For ELF inputs it reports these distinct errors:

* `ELF file %s is not BPABI conformant` — e_flags must be EABI v4 (`0x04000000` up), not v5.
* `ELF File %s contains no static symbols` — `.symtab` must be present with global symbols.
* `ELF File %s has no exception descriptor` — `.ARM.exidx` with `PT_ARM_EXIDX`.
* `Undefined Symbol %s found in ELF File %s` — a `#<DLL>...` marker symbol present but undefined.
* `ELF File %s has corrupt entry point` / `Entry point and Text segment base both 0` — needs real
  `PT_LOAD` segments and `e_entry` inside `.text`.

All of those are now satisfied by `acetylene-ld`. What is *not* satisfied is whatever turns
markers into imports.

## Stub layout (verified byte-for-byte)

Each import library (`estlib.lib`, `euser.lib`, ...) is an `ar` archive whose members are ELF ARM
relocatables:

```
StubCode:      e51ff004        ldr r12, [pc, #-4]
               00000000        .word <patched by the loader>
.relStubCode:  R_ARM_ABS32 at offset 4, against symbol `theImportedSymbol` (value 4)
.directive:    #<SYMEDIT>\nIMPORT #<DLL>ESTLIB{000a0000}[10003b0b].DLL#<\DLL>d2\n
.comment:      \tAndy's magic stub generator vsn 0.2
```

The marker symbol `#<DLL>NAME{uid}[uid3].DLL#<\DLL>ordinal` is undefined in the stub. Symbols in
these archives default to EABI v2 while the CRT objects are v4, which is why a plain
`arm-none-symbianelf-ld` run on them fails with `EABI version 2 vs target 4`.

## Attempts made and their exact results

| Input shape | elf2e32 result |
|---|---|
| our ET_EXEC ELF, markers **undefined** | `E1035 Undefined Symbol #<DLL>...`, no image |
| our ET_EXEC ELF, markers defined as SHN_ABS at the literal address | image built, **0 imports** |
| same, markers defined with `.text` section index | image built, **0 imports** |
| plus `.rel.text` R_ARM_ABS32 at the literals against the markers | image built, **0 imports** |
| ET_DYN with `.dynsym` containing marker names (UNDEF) + `.hash` + `.rel.dyn` at the literals + `DT_ARM_SYMTABSZ` + `DT_SONAME` | image built, **0 imports** |
| ET_DYN with `.dynsym` containing the real names (printf, exit, `_ZN12CTrapCleanup3NewEv`) + `.rel.dyn` | image built, **0 imports** |
| official `arm-none-symbianelf-ld -shared -Ttext 0x8000 -Tdata 0x400000 --target1-abs --default-symver` over `.lib` stubs | links, but elf2e32 reports the markers undefined |
| same over `.dso` files | ld: `hidden symbol exit isn't defined` (the .dso export visibility is hidden) |
| `elftran` (both 02.01 build 549 and 596) on any of our ELFs | segfault, or `Unrecognized Dyn Array tag` for the `-shared` output |

## Notes for the next attempt

1. The recipe Carbide uses for GCCE is documented in `Epoc32/tools/ide_cw.pm`:

```
arm-none-symbianelf-ld -L<libsupc++ dir> -L<libgcc dir> \
  --target1-abs --no-undefined -nostdlib -Ttext 0x8000 -Tdata 0x400000 \
  -shared --default-symver -soname <name>{000a0000}[<uid3>].exe \
  --entry _E32Startup -u _E32Startup <FIRST_LIB> -o out.elf <objs> <libs> -lsupc++ -lgcc
```

   `_E32Startup` lives in `eexe.lib(UC_EXE_.o)`; the runtime group is
   `ecrt0.lib estlib.dso euser.dso drtaeabi.dso usrt2_2.lib libsupc++.a libgcc.a`.

2. `elftran` is the tool from the stub era and understands `.directive` natively. Feeding it a
   *genuine* GCCE link product is the shortest path to a working import table. Its crash is most
   likely a layout assumption we have not reproduced (mapping symbols `$a`/`$d`, `.emb_text`, or a
   section-order rule).

3. Writing our own E32 writer needs the header CRC, which is a CRC-32 over part of the 0x9c-byte
   header. The standard reflected table (poly 0xEDB88320) is present in `elf2e32.exe` at file
   offset 0xb86c0, but none of the tested combinations matched the stored value:

   * ranges `0..0x9c`, `0x18..0x9c`, `0x1c..0x9c`, `0x18..0x98`, whole file, and "skip the crc
     field" concatenations;
   * init 0 / 0xffffffff, xor 0 / 0xffffffff, the CRC field zeroed, the CRC field filled with
     0xff, and MSB-first variants with polys 0x04C11DB7 / 0x1EDC6F41.

   Two reference images (`s1.e32` from heap 0x10000 and `s2.e32` from heap 0x22222) were used as
   oracle pairs. If the CRC is recovered, an Idata table can be spliced into the image produced by
   `elf2e32` and validated with `elf2e32 --e32input --dump` before ever touching a device.

4. `elf2e32 --e32input --dump` is a reliable oracle: it prints import tables, relocation counts and
   the header CRC, and it rejects invalid images. Use it instead of guessing.
