#!/usr/bin/env bash
set -euo pipefail

src_dir="${GCOV_INPUT_DIR:-.}"
dst_dir="${GCOV_OUTPUT_DIR:-_gcov}"
ignore_prev_result="${IGNORE_PREV_RESULT:-false}"

mkdir -p "$dst_dir"

if ! test -d "$src_dir"; then
  echo "::notice::GCOV_INPUT_DIR '$src_dir' does not exist; skip collecting"
  echo "::group::files"
  ls -l "$dst_dir"
  echo "::endgroup::"
  exit 0
fi

move_gcov_files() {
  while IFS= read -r -d '' f; do
    base="$(basename "$f")"
    dst="$dst_dir/$base"
    if [[ "$ignore_prev_result" == "true" && -e "$dst" ]]; then
      echo "::error::Refusing to overwrite existing '$dst' while ignore_prev_result enabled"
      exit 1
    fi
    mv -f "$f" "$dst"
  done
}

if [[ "$src_dir" == "." ]]; then
  find "$src_dir" -type f \( -name '*.gcno' -o -name '*.gcda' \) -not -path "./$dst_dir/*" -print0 |
    move_gcov_files
else
  find "$src_dir" -type f \( -name '*.gcno' -o -name '*.gcda' \) -print0 |
    move_gcov_files
fi

echo "::group::files"
ls -l "$dst_dir"
echo "::endgroup::"
