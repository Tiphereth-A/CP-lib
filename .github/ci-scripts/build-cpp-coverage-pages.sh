#!/usr/bin/env bash
set -euo pipefail

out=".competitive-verifier/docs/static/coverage-cpp"
mkdir -p "$out"
uv run gcovr --gcov-suspicious-hits-threshold 0 --html-details "$out/summary.html"
