#!/usr/bin/env bash
set -euo pipefail

venv_bin="${GITHUB_WORKSPACE:?}/.venv/bin"
mkdir -p "$venv_bin"

cat > "$venv_bin/verify-g++" <<'EOF'
#!/usr/bin/env bash
exec g++ "$@"
EOF

cat > "$venv_bin/coverage-g++" <<'EOF'
#!/usr/bin/env bash
exec g++ "$@"
EOF

chmod +x "$venv_bin/verify-g++" "$venv_bin/coverage-g++"
