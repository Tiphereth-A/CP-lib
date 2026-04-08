#!/usr/bin/env bash
set -euo pipefail

echo "::group::Downloading fonts"
make download-fonts
echo "::endgroup::"
echo "::group::Downloaded fonts list"
ls -l .cp-lib/fonts
echo "::endgroup::"