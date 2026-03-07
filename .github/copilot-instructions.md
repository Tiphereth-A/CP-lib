# Project Guidelines

## Overview

CP-lib is a header-only C++20 competitive programming library with 450+ algorithm/data structure implementations. It includes Python tooling for verification, documentation generation, and test management.

## Code Style

### C++

- **Standard**: C++20 (`gnu++20`), compiled with `g++ -O2 -Wall -Wextra`
- **Compiler**: GCC >= 13
- **Formatting**: `.clang-format` (Google-based, column limit 0). Run: `python manager.py fmt -d src`
- **Namespace**: All code lives in `tifa_libs` (or sub-namespaces like `tifa_libs::math`)
- **Include guard**: `#pragma once`
- **Naming**: `snake_case` for classes, functions, files. Private helpers suffixed with `_` (e.g., `ins_()`)
- **Concepts**: Suffixed with `_c` (e.g., `int_c`, `mint_c`, `alist_c`)
- **Custom macros** (from `src/util/util/lib.hpp`): `CEXP` = `constexpr`, `CEXPE` = `constexpr explicit`, `CR` = `const&`, `TPN` = `typename`, `NE` = `noexcept`, `CNE` = `const noexcept`
- **Type aliases**: `i32`, `u32`, `i64`, `u64`, `f64`, `vec<T>`, `vvec<T>`, `ptt<T>`, etc.
- Use `constexpr` and `noexcept` pervasively. Use C++20 concepts (`requires` clauses) over SFINAE.

### Python

- **Version**: >= 3.11
- **Package manager**: `uv`
- **CLI framework**: Click
- **Style**: autopep8

## Architecture

```
src/           # C++ header-only library (each algorithm in its own dir with lib.hpp + doc.tex)
libs/          # Python tooling (CLI commands, config, content generation, utilities)
  cmd/         #   Click commands: doc, new, verify, fmt, meta, pack
  conf/        #   Config parsers (YAML)
  content/     #   LaTeX/documentation generation
  meta/        #   Test code generation from .cppmeta templates
  util/        #   Shared utilities
test/
  cplib/       # Python tests (pytest, markers: unit/integration/system)
  cpv/         # C++ verification tests (organized by online judge)
  cpv_local/   # Local C++ tests
  cpv_meta/    # .cppmeta template files for parameterized test generation
```

Source categories under `src/`: `util`, `io`, `fast`, `ds` (data structures), `math`, `nt` (number theory), `comb`, `lalg`, `conv`, `fps`, `graph`, `tree`, `geo2d`, `geo3d`, `str`, `bit`, `gen`, `rand`, `edh`, `game`, `opt`.

Each algorithm directory contains `lib.hpp` (implementation) and `doc.tex` (LaTeX documentation).

## Build and Test

```bash
# Install dependencies
uv sync --frozen

# Format code
python manager.py fmt -d src test/cpv

# Generate test code from .cppmeta templates
python manager.py meta

# Verify C++ implementations (compile + run embedded samples)
python manager.py verify

# Run Python tests
pytest test/cplib/ -v

# Compile all C++ files (sanity check)
make all

# Generate documentation
python manager.py doc -s src -t tex
```

## Conventions

- **C++ test files** must contain a `PROBLEM` marker comment (e.g., `// cplib.manager: PROBLEM https://...`) and embedded test samples in `/*sample ... ======== ... */` blocks.
- **New library sections**: Use `python manager.py new` to scaffold.
- **Parameterized tests**: Define variants in `tcgen.yml`, write `.cppmeta` templates in `test/cpv_meta/`, generate with `python manager.py meta`.
- When adding a new algorithm, create both `lib.hpp` and `doc.tex` in its directory.
- The manager.py `verify` command compiles test files with `g++ -std=gnu++20 -fmax-errors=1 -ftrapv` and runs embedded sample cases.
