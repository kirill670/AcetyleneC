#!/bin/sh
set -e

TAG="${1:?usage: publish-release.sh <tag> <title> <notes-file> <dist-dir>}"
TITLE="${2:?title}"
NOTES="${3:?notes file}"
DIST="${4:?dist dir}"

: "${GH_TOKEN:?GH_TOKEN is required}"
: "${GITHUB_REPOSITORY:?GITHUB_REPOSITORY is required}"

API="https://api.github.com/repos/$GITHUB_REPOSITORY"
UPLOADS="https://uploads.github.com/repos/$GITHUB_REPOSITORY"
TMP="${RUNNER_TEMP:-/tmp}"

python - "$TAG" "$TITLE" "$NOTES" "$TMP/release-payload.json" <<'PY'
import json
import sys

tag, title, notes_path, out_path = sys.argv[1:5]
with open(notes_path, encoding="utf-8") as f:
    body = f.read()
with open(out_path, "w", encoding="utf-8") as f:
    json.dump(
        {
            "tag_name": tag,
            "name": title,
            "body": body,
            "draft": False,
            "prerelease": False,
            "make_latest": "true",
        },
        f,
        ensure_ascii=False,
    )
PY

RESPONSE="$TMP/release-response.json"
CODE=$(curl -sS -o "$RESPONSE" -w '%{http_code}' -X POST \
    -H "Authorization: Bearer $GH_TOKEN" \
    -H "Accept: application/vnd.github+json" \
    -H "Content-Type: application/json" \
    --data-binary @"$TMP/release-payload.json" \
    "$API/releases")
echo "release create: http $CODE"
if [ "$CODE" != "201" ]; then
    cat "$RESPONSE"
    exit 1
fi

RELEASE_ID=$(python - "$RESPONSE" <<'PY'
import json
import sys

with open(sys.argv[1], encoding="utf-8") as f:
    data = json.load(f)
print(data.get("id", ""))
PY
)
if [ -z "$RELEASE_ID" ]; then
    echo "release response has no id"
    cat "$RESPONSE"
    exit 1
fi
echo "release id: $RELEASE_ID"

for file in "$DIST"/*; do
    [ -f "$file" ] || continue
    name=$(basename "$file")
    size=$(wc -c < "$file" | tr -d ' ')
    echo "uploading $name ($size bytes)"
    CODE=$(curl -sS -o "$TMP/upload-response.json" -w '%{http_code}' -X POST \
        -H "Authorization: Bearer $GH_TOKEN" \
        -H "Content-Type: application/octet-stream" \
        --data-binary @"$file" \
        "$UPLOADS/releases/$RELEASE_ID/assets?name=$name")
    echo "  http $CODE"
    if [ "$CODE" != "201" ]; then
        cat "$TMP/upload-response.json"
        exit 1
    fi
done

echo "released $TAG"
