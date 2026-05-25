# Project Instructions

## Dev Environment Tips
- Ensure `core.symlinks=true` is enabled when cloning this repo (README is a symlink).
- Use GCC 13+ and Python 3.12+; LaTeX is only required for PDF generation, and `inkscape` is needed for SVG support.
- Install Python deps with `uv sync --frozen`; add groups as needed: `--group dev`, `--group verify`, `--group latex`, `--group bundle`.
- Initialize pre-commit after cloning: `uv run pre-commit install`.
- For PDF builds, download fonts with `make download-fonts`.
- Prefer `uv run python manager.py ...` so optional deps are available.

## Common Commands
- `uv run python manager.py --help` to list available repo commands.
- `uv run python manager.py new` to scaffold a new implementation under `src/`.
- `uv run python manager.py fmt` to format code (also used by pre-commit).
- `uv run python manager.py doc` to generate TeX for the notebook.

## Testing Instructions
- Run unit tests with `uv run pytest test/cplib/`.
- Run usage examples with `uv run python manager.py verify`.
- competitive-verifier verification will be running automatically in GitHub Action, so never running this in local.

## PR Instructions
- PR titles must follow the Conventional Commits specification.
- Allowed types: dev, feat, fix, docs, style, refactor, perf, test, build, ci, chore, revert.
- Always run unit tests and usage examples before commiting.

## Notes
- For code submission bundling, use `oj-bundle` from the `bundle` group; do not use `oj-verify` from `online-judge-verify-helper`.
- If the `runs:` section for certain GitHub Actions steps is too long, write the content as bash script in `.github/ci-scripts`.
