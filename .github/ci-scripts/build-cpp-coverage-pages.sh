#!/usr/bin/env bash
set -euo pipefail

out=".competitive-verifier/docs/static/coverage-cpp"
mkdir -p "$out"
uv run gcovr --merge-mode-functions merge-use-line-max --gcov-suspicious-hits-threshold 0 --html-details "$out/summary.html"
