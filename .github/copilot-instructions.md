# CP-lib Project Guidelines

CP-lib is a header-only C++ library for competitive programming with 450+ implementations of algorithms and data structures. All code is automatically verified against multiple online judges (OJ) to ensure correctness.

## Code Style

- **Language Standard**: C++20 with GCC 13.0 or higher
- **Compilation**: Single-pass compilation to executable (header-only design)
- **Key Headers**:
  - Located in `src/` organized by category: `util/`, `bit/`, `gen/`, `io/`, `ds/`, `opt/`, `graph/`, `tree/`, `poly/`, `math/`, etc.
  - Each file is a self-contained header with no external includes beyond STL
- **Code Organization**: Use descriptive namespaces and clear variable names
- **Documentation**: Code comments should reference algorithms/concepts; detailed docs are in `doc/`

Exemplar files: `src/util/`, `src/ds/` (standard data structures)

## Architecture

The library uses **dual verification**:
1. **Python Unit Tests** (`test/cplib/`): pytest-based tests for manager script logic
2. **OJ Verification** (`test/cpv/`): Automated submission to Aizu, Library Checker, Yukicoder, etc. via `competitive-verifier`

**Test Matrix**: Configuration in `tcgen.yml` generates multiple test variants from templates for comprehensive coverage.

**Documentation Pipeline**: LaTeX source in `notebook.tex` generates printable PDF notebooks for offline competition reference.

## Build and Test

```bash
# Install dependencies
uv sync --frozen
uv sync --frozen --group verify    # For OJ verification
uv sync --frozen --group latex     # For PDF generation

# Code management via manager.py
python manager.py fmt -d src -d test     # Format all code
python manager.py test                   # Run Python unit tests
python manager.py verify                 # Verify against online judges
python manager.py doc                    # Generate PDF notebook
python manager.py pack <file>            # Bundle code for OJ submission

# View all commands
python manager.py --help
```

## Conventions

### Testing Strategy
- **Unit Tests**: Python tests in `test/cplib/` use pytest with markers (`@pytest.mark.unit`, `@pytest.mark.integration`)
- **OJ Verification**: Critical paths verified against real contest problems; see `test/cpv/` for verification configs
- **Test Running**: Always run `python manager.py test` before committing changes

### Formatting
- Use `python manager.py fmt` regularly; it applies `autopep8` conventions
- All Python code must pass `pycodestyle` checks
- Pre-commit: Run `python manager.py fmt -d src -d test` to validate

### Header-Only Design
- All implementations live in headers (`.hpp`), no `.cpp` files in library
- Avoid global state; prefer template parameters and function parameters
- Each header should compile independently without external includes beyond STL

### Common Development Tasks
- **Adding New Algorithm**: Create file in appropriate `src/<category>/` folder
- **Fixing Bug**: Update `.hpp`, run unit tests, verify against OJs if applicable
- **Updating Documentation**: Modify LaTeX in `notebook.tex` or category docs in `doc/`
