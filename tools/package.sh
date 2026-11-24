#!/bin/sh
set -e
HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/.." && pwd)"
TAG="${AC_BUILD_TAG:-dev}"
OUT="${1:-$ROOT/build/dist}"
STAGE="$ROOT/build/stage"

mkdir -p "$OUT"
rm -rf "$STAGE"
mkdir -p "$STAGE/build/bin" "$STAGE/plugins" "$STAGE/docs"

for exe in "$ROOT"/build/bin/*.exe; do
    case "$(basename "$exe")" in
        plugin-host.exe) continue ;;
    esac
    cp -f "$exe" "$STAGE/build/bin/"
done

for p in autocomplete imageviewer jsonlint mcp; do
    mkdir -p "$STAGE/plugins/$p"
    cp -f "$ROOT/plugins/$p/plugin.json" "$ROOT/plugins/$p/$p.dll" "$STAGE/plugins/$p/"
done

cp -f "$ROOT/LICENSE" "$ROOT/README.md" "$ROOT/THIRD_PARTY.md" "$STAGE/"
cp -f "$ROOT"/docs/*.md "$STAGE/docs/"
cp -r "$ROOT/examples" "$STAGE/examples"
cp -r "$ROOT/sdk" "$STAGE/sdk"

ZIP="AcetyleneC-$TAG-win32.zip"
rm -f "$OUT/$ZIP"
(
    cd "$STAGE"
    zip -qr "$OUT/$ZIP" .
)
(
    cd "$OUT"
    sha256sum "$ZIP" > SHA256SUMS.txt
)
ls -l "$OUT/$ZIP"
