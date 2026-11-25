#!/bin/sh
set -e
. "$(dirname "$0")/env.sh"

OUT="$ACETYLENE_ROOT/plugins"

build_plugin() {
    name="$1"
    shift
    dir="$OUT/$name"
    echo "== plugin $name"
    "$CC" -O2 -s -shared -municode -o "$dir/$name.dll" "$dir/$name.c" "$@"
}

mkdir -p "$OUT/autocomplete" "$OUT/imageviewer" "$OUT/jsonlint" "$OUT/mcp"

build_plugin autocomplete
build_plugin imageviewer -lgdiplus
build_plugin jsonlint
build_plugin mcp -lws2_32

ls -l "$OUT"/*/*.dll
