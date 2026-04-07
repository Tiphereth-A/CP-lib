#!/usr/bin/env bash
set -euo pipefail

git log --all --reverse --format="%H" > current-hashes.txt
prev_hash="<not-found>"
if [[ -f commit-hashes.txt ]]; then
  matched_hash="$(awk 'NR==FNR { seen[$0] = 1; next } !seen[$0] { exit } { last = $0 } END { print last }' commit-hashes.txt current-hashes.txt)"
  if [[ -n "$matched_hash" ]]; then
    prev_hash="$matched_hash"
  fi
fi
echo "value=$prev_hash" >> "$GITHUB_OUTPUT"