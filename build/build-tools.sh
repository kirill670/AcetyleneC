#!/bin/sh
set -e
HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/.." && pwd)"
. "$HERE/env.sh"
OUT="$ROOT/build/bin"
mkdir -p "$OUT"
TAGHDR="$ROOT/build/ac_build.h"
{
    if [ -n "${AC_BUILD_TAG:-}" ]; then
        printf '#define AC_BUILD_TAG "%s"\n' "$AC_BUILD_TAG"
    fi
    if [ -n "${AC_BUILD_TITLE:-}" ]; then
        printf '#define AC_BUILD_TITLE "%s"\n' "$AC_BUILD_TITLE"
    fi
} > "$TAGHDR"

$CC -O2 -std=c99 -o "$OUT/acetylene-ld.exe" "$ROOT/src/ld/ld.c" "$ROOT/src/common/ac.c"
$CC -O2 -std=c99 -o "$OUT/acetylene-makekeys.exe" \
    "$ROOT/src/sign/makekeys.c" "$ROOT/src/sign/hash.c" "$ROOT/src/sign/rsa.c" \
    "$ROOT/src/sign/dsa.c" "$ROOT/src/sign/cert.c" "$ROOT/src/sign/cert_dsa.c" \
    "$ROOT/src/common/ac.c" -ladvapi32
$CC -O2 -std=c99 -o "$OUT/acetylene-e32fix.exe" "$ROOT/src/e32/e32fix.c" "$ROOT/src/common/ac.c"
$CC -O2 -std=c99 -o "$OUT/acetylene-cxx.exe" "$ROOT/src/cxx/cxx.c" "$ROOT/src/common/ac.c"
$CC -O2 -std=c99 -o "$OUT/acetylene-sis.exe" "$ROOT/src/sis/sis.c" "$ROOT/src/common/ac.c"
$CC -O2 -std=c99 -o "$OUT/acetylene-pe.exe" "$ROOT/src/pe/pe.c"
$CC -O2 -std=c99 -include "$TAGHDR" -o "$OUT/AcetyleneC.exe" \
    "$ROOT/src/ide/ui.c" "$ROOT/src/ide/editor.c" "$ROOT/src/ide/emu.c" "$ROOT/src/ide/plugin.c" "$ROOT/src/ide/pebuild.c" "$ROOT/src/common/ac.c" \
    -lgdi32 -lcomdlg32 -lole32 -lshell32 -lcomctl32 -mwindows
cp -f "$ROOT/build/tcc-cross-arm/tcc.exe" "$OUT/acetylene-cc.exe"
$CC -O2 -std=c99 -o "$OUT/acetylene-mcp-stdio.exe" "$ROOT/tools/mcp-stdio.c" -lws2_32
$CC -O2 -std=c99 -o "$OUT/plugin-host.exe" "$ROOT/tests/plugin-host.c"

echo "tools built into $OUT"
