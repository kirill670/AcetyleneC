#!/bin/sh
set -e
HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/.." && pwd)"
. "$HERE/env.sh"
SRC="$ROOT/vendor/tinycc"
OUT="$ROOT/build/tcc-cross-arm"
mkdir -p "$OUT"
cd "$SRC"
if [ ! -f config.mak ]; then
  ./configure --cc="$CC" --ar=ar --cpu=i386 --targetos=WIN32 --disable-static
fi
cat > config-extra.mak <<'EOM'
DEF-arm = -DTCC_TARGET_ARM -DTCC_ARM_EABI -DTCC_ARM_VFP
EOM
"$MAKE" -j8 CROSS_TARGET=arm arm-tcc.exe
cp -f arm-tcc.exe "$OUT/tcc.exe"
ls -l "$OUT/tcc.exe"
