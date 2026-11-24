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
if command -v zip >/dev/null 2>&1; then
    (cd "$STAGE" && zip -qr "$OUT/$ZIP" .)
elif command -v 7z >/dev/null 2>&1; then
    (cd "$STAGE" && 7z a -tzip -mx=6 "$OUT/$ZIP" . >/dev/null)
elif command -v powershell >/dev/null 2>&1; then
    powershell -NoProfile -Command "Compress-Archive -Path '$STAGE/*' -DestinationPath '$OUT/$ZIP' -CompressionLevel Optimal"
else
    echo "no zip tool found: install zip, 7z or run on a host with PowerShell" >&2
    exit 1
fi
(
    cd "$OUT"
    sha256sum "$ZIP" > SHA256SUMS.txt
)
ls -l "$OUT/$ZIP"
