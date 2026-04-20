#!/usr/bin/env bash
set -euo pipefail

cache_branch="${CACHE_BRANCH:-verify-cache}"

tar -czf merged-result.tar.gz -C ".artifacts/merged" merged-result.json
tar -czf _gcov.tar.gz _gcov

(
  git switch --orphan "$cache_branch"
  git add merged-result.tar.gz
  git add _gcov.tar.gz

  git config user.name "github-actions[bot]"
  git config user.email "41898282+github-actions[bot]@users.noreply.github.com"
  git commit -m "cache: ${GITHUB_SHA}"

  git push -f origin "$cache_branch"
)
