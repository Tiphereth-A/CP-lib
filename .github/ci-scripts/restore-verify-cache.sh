#!/usr/bin/env bash
set -euo pipefail

cache_branch="${CACHE_BRANCH:-verify-cache}"
cache_path="${CACHE_PATH:?CACHE_PATH is required}"
workspace="${GITHUB_WORKSPACE:-.}"
archive_path="$workspace/$(basename "$cache_path")"

if git fetch --depth=1 origin "$cache_branch"; then
  if git cat-file -e "origin/$cache_branch:$cache_path" 2>/dev/null; then
    git show "origin/$cache_branch:$cache_path" > "$archive_path"
    tar -xzf "$archive_path" -C "$workspace"
    rm -f "$archive_path"

    echo "cache-hit=true" >> "$GITHUB_OUTPUT"
  else
    echo "cache-hit=false" >> "$GITHUB_OUTPUT"
  fi
else
  echo "cache-hit=false" >> "$GITHUB_OUTPUT"
fi
