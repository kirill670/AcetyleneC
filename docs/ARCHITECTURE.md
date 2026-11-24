# Architecture

```
 source.c ──acetylene-cc (TCC, ARM EABI v4)──▶ .o  (ELF32, REL, literal pools, .rel.text)
                                                  │
                                       acetylene-ld│  resolves against sdk/targets/<t>/lib/*.lib
                                                  ▼
                                             app.elf (ET_EXEC, .text/.rodata/.data/.bss,
                                                      .ARM.exidx, .directive, import markers,
                                                      .rel.text for runtime-visible addresses)
                                                  │
                                      elf2e32 (SDK)│  header, code section, reloc tables, CRC
                                                  ▼
                                             app.e32
                                                  │
                                      makesis (SDK)│  .pkg script
                                                  ▼
                                            app.sisx
```

## Why TCC

TCC's ARM backend already emits real ARM code with EABI relocation types, literal pools and
PC-relative branches. Building it with `CROSS_TARGET=arm` produces a 32-bit Windows executable that
cross-compiles to ARM. Two local changes were needed: the EABI version flag (v4 to match the S60
libraries) and soft-float ABI selection (`TCC_ARM_EABI` without `TCC_ARM_VFP` for the default build,
`TCC_ARM_VFP` for devices with VFP).

## Import stubs

Each `*.lib` in an S60 SDK is an ar archive of tiny ELF objects:

```
StubCode:  e51ff004        ldr r12, [pc, #-4]
           00000000        .word <patched at load time>
.relStubCode: R_ARM_ABS32  against theImportedSymbol
.directive:  #<SYMEDIT> IMPORT #<DLL>ESTLIB{000a0000}[10003b0b].DLL#<\DLL>d2
```

`acetylene-ld` links the real function symbol to `StubCode`, defines the `#<DLL>...` marker at the
literal address and keeps the `.directive` text. That is the shape `elf2e32` expects from the 2005
GCCE flow. What is still missing is the import table in the produced E32; see README.

## IDE

`src/ide/editor.c` holds the document model (gap-free byte buffer, line index, incremental undo
records, block-comment state cache, tokenizer for highlighting). `src/ide/ui.c` is the Win32 GDI
shell: custom drawn menu bar, popup menus, toolbar, project tree, tab strip, editor, output pane,
status bar, double-buffered painting, splitter dragging, and the build driver that spawns
`acetylene-cc`, `acetylene-ld` and `elf2e32` with captured stdout parsed into the error list.
