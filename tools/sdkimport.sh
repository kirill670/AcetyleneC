#!/bin/sh
set +e
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
IS="$ROOT/.cache/extract/is"
OUT="$ROOT/sdk/targets"
mkdir -p "$OUT"

first_dir() {
    for c in "$@"; do
        if [ -d "$c" ]; then
            echo "$c"
            return 0
        fi
    done
    return 1
}

import_target() {
    name="$1"
    src="$2"
    dest="$OUT/$name"
    echo "== $name"
    rm -rf "$dest"
    mkdir -p "$dest/include" "$dest/lib" "$dest/tools"

    inc="$(first_dir "$src/CPP_API/epoc32/include" "$src/Epoc32/include" "$src/epoc32/include")" || inc=""
    if [ -n "$inc" ]; then
        cp -rf "$inc/." "$dest/include/" 2>/dev/null || true
    fi

    rel="$(first_dir "$src/CPP_API/epoc32/release" "$src/Epoc32/release" "$src/epoc32/release")" || rel=""
    if [ -n "$rel" ]; then
        for sub in armv5/lib armv5/udeb armv5/urel armi/urel armi/lib; do
            if [ -d "$rel/$sub" ]; then
                cp -rf "$rel/$sub/." "$dest/lib/" 2>/dev/null || true
            fi
        done
    fi

    tls="$(first_dir "$src/CPP_Toolchain/epoc32/tools" "$src/Epoc32/tools" "$src/epoc32/tools" "$src/CPP_SymbianToolchain/tools")" || tls=""
    if [ -n "$tls" ]; then
        cp -rf "$tls/." "$dest/tools/" 2>/dev/null || true
        rm -rf "$dest/tools/perllib" "$dest/tools/distrib" 2>/dev/null || true
    fi

    cat > "$dest/target.ini" <<EOF
[target]
name=$name
source=$src

[paths]
include=include
lib=lib
tools=tools

[abi]
machine=arm
eabi=4
float=softfp

[link]
crt=ecrt0.lib
runtime=eexe.lib estlib.lib euser.lib drtaeabi.lib usrt2_2.lib

[tools]
elf2e32=tools/elf2e32.exe
elftran=tools/elftran.exe
makesis=tools/makesis.exe
signsis=tools/signsis.exe
makekeys=tools/makekeys.exe
bmconv=tools/bmconv.exe
mifconv=tools/mifconv.exe
uidcrc=tools/uidcrc.exe
EOF
    printf "   include=%s lib=%s tools=%s\n" \
        "$(find "$dest/include" -type f 2>/dev/null | wc -l)" \
        "$(find "$dest/lib" -type f 2>/dev/null | wc -l)" \
        "$(find "$dest/tools" -type f 2>/dev/null | wc -l)"
}

import_target s60v2  "$IS/s60_2nd_sdk_fp3/tree"
import_target s60v30 "$IS/S60_3rd_SDK_v1.0/tree"
import_target s60v31 "$IS/s60v3.1_SDK/Symbian SDK S60v3.1 S9.2 v1.0.1/tree/SelfRegFiles2/tree"
import_target s60v32 "$IS/S60_SDK_3.2_v1.1.1_en/S60_SDK_3.2_v1.1.1_en/tree/SelfRegFiles2/tree"
import_target s60v5  "$IS/S60_5th_SDK_ASP_v1.0.1/S60_5th_SDK_ASP_v1.0.1/tree/SelfRegFiles1/tree"

du -sh "$OUT"/* 2>/dev/null
echo "SDK import complete"
