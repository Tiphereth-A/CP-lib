# Repository Architecture

This document describes the directory layout and key files in the repository.

## Core Directories

- `src/` - Main C++ header files and documentation organized by category (for example `graph/`, `math/`, `ds/`, `str/`). Each implementation is in its own subdirectory containing:
  - `lib.hpp` - C++ implementation (write in English)
  - `doc.tex` - LaTeX documentation for PDF notebook (write in Simplified Chinese)
  - `cpvdoc.md` - Competitive-verifier markdown documentation (write in English)
  - `usage.cpp` - Usage examples (comments in Simplified Chinese)
  - Other files (`.svg`, `.png`, ...) - Documentation resources used directly in this directory
  - `index.yml` - In category directories, defines chapter structure and section names

  Any files of `lib.hpp`, `doc.tex`, `cpvdoc.md`, `usage.cpp` are not necessary.
- `src/sheet/` - Cheatsheet content for the PDF notebook. Contains quick reference materials (in Simplified Chinese).
- `src/_titlepage/` and `src/_colophon/` - Special sections for notebook title page and colophon.
- `doc/` - Repository documentation.
- `test/` - Test files for verification. Contains subdirectories:
  - `bench/` - Benchmark codes
  - `cpv/` - Competitive-verifier tests organized by online judge (Aizu, Library Checker, Yukicoder)
  - `cpv_local/` - Local tests with custom implementations and test data
  - `cpv_local/_data/` - Test data files organized by OJ (`.in`, `.out`, `.ans`)
  - `cpv_meta/` - Test matrix template files (`.cppmeta`) for generating parameterized test variants
  - `cplib/` - Unit tests for manager script

## Configuration and Management

- `src/index.yml` - Top-level chapter ordering for the notebook.
- `test/cpv_meta/config.yml` - Test matrix configuration file for generating parameterized test variants from templates.
- `libs/` - Python library modules used by `manager.py` for managing the repository, generating content, and processing files. Contains:
  - `cmd/` - Command implementations
  - `conf/` - Config classes and models
  - `content/` - Content tree and section generation utilities
  - `decorator/` - Logging/timing decorators
  - `meta/` - Metadata parsers and test matrix helpers
  - `util/` - Shared utilities
- `manager.py` - Main management script providing commands for creating new implementations, formatting code, generating notebooks, and running tests.
- `cpv_patch.py` - Helper script for patching competitive-verifier metadata.
- `scripts/` - One-off utility scripts for pre-commit hooks (for example `replace_chinese_punct.py`).
- `pyproject.toml` - Python project configuration and dependency management.
- `Makefile` - Build helpers (for example compiling sources for CodeQL and downloading LaTeX fonts).

## Repository Metadata

- `README.md` - Project overview, requirements, and usage. Note: this is a symlink, the actual file is in `.competitive-verifier/docs/index.md`.
- `LICENSE` - Licensing terms.
- `CITATION.bib` - Citation metadata for academic use.

## LaTeX Configuration

- `notebook.tex` - Main LaTeX file for the notebook PDF.
- `ICPCnotebook.cls` - LaTeX class file defining the notebook style.
- `notebook.bib` - Bibliography file for citations in the notebook.

## Development Configuration

- `.github/` - GitHub Actions workflows and configuration files for CI/CD.
- `.competitive-verifier/` - Configuration files for competitive-verifier.
  - `config.toml` - Verifier configuration
  - `docs/` - Additional documentation
- `.latexindent.yaml` - Configuration for LaTeX indentation and formatting.
- `.clang-format` - Clang format configuration for C++ code style.
- `.clang-tidy` - Clang-tidy configuration.
- `.clangd` - Clangd configuration for C++ language server.
- `.pre-commit-config.yaml` - Pre-commit hooks configuration.
- `.gitignore`, `.gitattributes` - Git configuration files.
