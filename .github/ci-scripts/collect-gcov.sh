#!/usr/bin/env bash
set -euo pipefail

mkdir -p _gcov
while IFS= read -r -d '' f; do
  base="$(basename "$f")"
  dst="_gcov/$base"
  if [[ ${IGNORE_PREV_RESULT:-} && -e "$dst" ]]; then
    echo "::error::Refusing to overwrite existing '$dst' while ignore_prev_result enabled"
    exit 1
  fi
  mv -f "$f" "$dst"
done < <(find . -type f \( -name '*.gcno' -o -name '*.gcda' \) -not -path './_gcov/*' -print0)

echo "::group::files"
ls -l _gcov
echo "::endgroup::"
