#!/usr/bin/env bash
set -euo pipefail

echo "::group::free"
free
echo "::endgroup::"

echo "::group::swapon"
swapon
echo "::endgroup::"

echo "::group::df"
df -ha --o --total
echo "::endgroup::"

echo "::group::du"
du -ha | sort -hr
echo "::endgroup::"
