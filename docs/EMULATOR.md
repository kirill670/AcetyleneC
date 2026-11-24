# Running builds on an EKA emulator

The SDK does not ship an emulator. An EKA2 emulator is a separate download and stays outside this
repository; AcetyleneC only *connects* to it.

## Connecting one

**Build > Set Emulator...** picks the emulator executable and writes `acetylene.ini` next to
`AcetyleneC.exe`. The default argument template is `%sisx%`, so **F5** packages the project if
needed and starts the emulator with the package.

`acetylene.ini`:

```ini
; placeholders: %e32% %sisx% %project%
emulator=F:\emulators\eka2\eka2.exe
emu_args=%sisx%
emu_workdir=
pkg=
```

| key | meaning |
|---|---|
| `emulator` | absolute path to the emulator binary |
| `emu_args` | command line; `%e32%` = built image, `%sisx%` = package, `%project%` = project name |
| `emu_workdir` | working directory for the emulator (empty = inherit) |
| `pkg` | optional `.pkg` to use instead of the generated one (relative to the repo root) |

## What F5 does

1. Refuses to start if no emulator is configured and says so in the output pane.
2. Verifies the emulator binary exists.
3. Auto-packages (`acetylene-sis` -> `build/<project>.sisx`) when the argument template mentions
   `%sisx%` or `%sis%` and no package is present yet.
4. Substitutes the placeholders and starts the emulator detached.
5. Writes the exact command line into the output pane, so a failed launch is diagnosable.

## Typical setups

*Emulator that installs a SISX:*

```ini
emu_args=%sisx%
```

*Emulator that boots a ROM and then needs the image on a mounted drive:*

```ini
emu_args=-rom F:\emulators\eka2\rom.bin -app %e32%
```

*Emulator with its own console runner:*

```ini
emu_args=--run %e32% --headless
```

## What is not covered

The IDE cannot observe the emulator's screen or drive its menus. Verification of the running app
stays inside the emulator window. If an emulator exposes a scriptable interface, the right way to
use it is to wrap it in a small `.bat`/`.exe` and point `emulator` at that wrapper with the built
paths substituted through the placeholders.
