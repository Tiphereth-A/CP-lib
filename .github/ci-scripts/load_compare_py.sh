#!/usr/bin/env bash
set -euo pipefail

output_path=.cp-lib/compare
tmp_path=.cp-lib/tmp

rm -rf "$tmp_path"
mkdir -p "$tmp_path"
git clone --depth=1 --branch=main https://github.com/google/benchmark.git "$tmp_path/benchmark"
mv "$tmp_path/benchmark/tools" "$output_path"
rm -rf "$tmp_path"
uv pip install -r "$output_path/requirements.txt"
