# GitHub Copilot Instructions for CP-lib

## Repository Overview

CP-lib is a **header-only C++ code library** for competitive programming with 450+ implementations of algorithms and data structures. The library is automatically verified against problems from online judges (OJ) such as Aizu, Library Checker, and Yukicoder.

## Language and Standards

### C++ Requirements
- **Standard**: C++20
- **Compiler**: GCC 13.0 or higher (required)
- **Optimization**: Code should be compiled with `-O2` optimization flag
- **Style Guide**: Based on Google C++ Style Guide (see `.clang-format`)
- **Header-only**: All implementations are header-only libraries in `include/` directory

### Code Style Conventions
- Follow `.clang-format` configuration (Google style with customizations)
- No column limit (`ColumnLimit: 0`)
- Use `AllowShortIfStatementsOnASingleLine: AllIfsAndElse`
- Use 2 spaces for indentation (per Google style)
- Include guards or `#pragma once` for header files
- Prefer template metaprogramming and compile-time optimizations where applicable

### Competitive Programming Constraints
- Prioritize **runtime performance** over readability when necessary
- Keep implementations **self-contained** (minimal external dependencies)
- Avoid dynamic memory allocation when possible for performance
- Use standard library features extensively (STL containers, algorithms)
- Code must be **copy-pasteable** for competitive programming contests

## Project Structure

```
CP-lib/
├── include/           # Main library headers (all implementations go here)
│   ├── bit/          # Bit manipulation algorithms
│   ├── comb/         # Combinatorics
│   ├── conv/         # Convolution operations
│   ├── ds/           # Data structures
│   ├── edh/          # Edit distance / hashing
│   ├── fast/         # Fast I/O and optimizations
│   ├── game/         # Game theory algorithms
│   ├── geo2d/        # 2D geometry
│   ├── geo3d/        # 3D geometry
│   ├── graph/        # Graph algorithms
│   ├── io/           # Input/output utilities
│   ├── lalg/         # Linear algebra
│   ├── math/         # Mathematical algorithms
│   ├── nt/           # Number theory
│   ├── opt/          # Optimization algorithms
│   ├── poly/         # Polynomial operations
│   ├── rand/         # Random utilities
│   ├── str/          # String algorithms
│   ├── tree/         # Tree algorithms
│   └── util/         # General utilities
├── test/             # Test files for online judge verification
│   ├── aizu/         # Aizu online judge tests
│   ├── library-checker-*/ # Library Checker tests
│   └── ...
├── libs/             # Python utility libraries
│   ├── classes/      # Core classes (Config, Section, etc.)
│   ├── commands/     # CLI command implementations
│   ├── latex_utils.py    # LaTeX utilities
│   ├── typst_utils.py    # Typst utilities
│   ├── testcase_matrix.py # Test case generation
│   └── utils.py      # General utilities
├── tests/            # Python tests (97%+ coverage)
│   ├── unit/         # Unit tests
│   ├── integration/  # Integration tests
│   └── system/       # System tests
├── doc_md/           # Markdown documentation
├── notebook/         # Algorithm documentation
│   ├── tex/          # LaTeX documentation source
│   └── typ/          # Typst documentation source
├── template/         # PDF generation templates
│   ├── ICPCnotebook.cls  # LaTeX template class
│   ├── notebook.typ      # Typst template
│   └── common.typ        # Shared Typst definitions
└── manager.py        # Python management script (CLI entry point)
```

## Building and Testing

### C++ Code
```bash
# Compile individual test files
g++ -std=gnu++20 -O2 -Wall -Wextra -Wconversion -Wpedantic test/example.cpp

# Build all test objects
make all

# Clean build artifacts
make clean
```

### Python Scripts
```bash
# Install Python dependencies
uv sync --frozen

# Install with development dependencies
uv sync --frozen --group dev

# Install with LaTeX support
uv sync --frozen --group latex

# Run Python tests
uv run pytest --cov=libs --cov-report=term-missing -v

# Run specific test categories
uv run pytest -m unit           # Unit tests only
uv run pytest -m integration    # Integration tests only
uv run pytest -m system         # System tests only

# Python code style check
uv run pycodestyle libs/ tests/

# CLI usage
uv run python manager.py --help
uv run python manager.py gen-nb --help
uv run python manager.py gen-cs --help
uv run python manager.py gentc --help
```

### Verification System
```bash
# The project uses competitive-verifier for automated testing
# Tests are run automatically via GitHub Actions on push/PR
# See .github/workflows/verify.yml for CI configuration
```

## Python Code Standards

- **Version**: Python 3.11+ required
- **Package Manager**: Use `uv` for dependency management
- **Style**: Follow PEP 8 (enforced by pycodestyle)
- **Testing**: Use pytest with coverage reporting
- **Test Markers**: `@pytest.mark.unit`, `@pytest.mark.integration`, `@pytest.mark.system`
- **Key Dependencies**:
  - `click` - CLI framework
  - `coloredlogs` - Colored logging
  - `multipledispatch` - Multiple dispatch support
  - `pyyaml` - YAML configuration
- **Dev Dependencies**:
  - `pytest` + `pytest-cov` - Testing and coverage
  - `pycodestyle` - Style checking
- **Optional Dependencies**:
  - `pygments` - LaTeX syntax highlighting (latex group)
  - `competitive-verifier` - Verification system (verify group)

## Documentation

### C++ Documentation
- Use Doxygen-style comments for public APIs
- Document time complexity (e.g., `O(n log n)`)
- Document space complexity when relevant
- Include example usage in comments
- Document mathematical formulas using LaTeX notation

### Markdown Documentation
- Place documentation in `doc_md/` directory
- Use proper markdown formatting
- Include code examples with proper syntax highlighting

### LaTeX Documentation
- LaTeX sources in `notebook/tex/` directory
- Use `pygments` for code syntax highlighting
- Requires LaTeX distribution with appropriate fonts
- Generate with: `uv run python manager.py gen-nb -t tex`
- Compile PDF: `uv run python manager.py run -t tex`

### Typst Documentation
- Typst sources in `notebook/typ/` directory
- Modern alternative to LaTeX with simpler syntax and faster compilation (10-20x)
- Shares common definitions in `template/common.typ`
- Generate with: `uv run python manager.py gen-nb -t typ && uv run python manager.py gen-cs -t typ`
- Compile PDF: `uv run python manager.py run -t typ`

## Security and Code Quality

### Security Scanning
- CodeQL analysis runs on all changes (see `.github/workflows/codeql.yml`)
- Flawfinder static analysis for C/C++ code
- Address all critical and high-severity findings

### Code Review Guidelines
- Test all changes against relevant online judge problems
- Ensure backward compatibility with existing code
- Verify compilation with GCC 13+ and C++20 standard
- Check for correctness using competitive-verifier
- Performance regressions are critical issues

## Common Tasks

### Adding a New Algorithm
1. Create a new header file in the appropriate `include/` subdirectory
2. Implement the algorithm as a header-only library
3. Add comprehensive comments including complexity analysis
4. Create test files in `test/` that verify correctness against OJ problems
5. Update documentation in `doc_md/` if adding a major feature
6. Ensure code follows `.clang-format` style

### Modifying Existing Code
1. Check if there are existing tests in `test/` for the code
2. Make minimal changes to preserve existing functionality
3. Verify changes don't break existing tests
4. Update documentation if interface changes
5. Run verification tests locally if possible

### Adding Python Utilities
1. Place new utilities in `libs/` directory
2. Add tests in `tests/` using pytest
3. Follow PEP 8 style guidelines
4. Update `pyproject.toml` if adding new dependencies
5. Ensure compatibility with Python 3.11+

## GitHub Actions Workflows

- **verify.yml**: Runs competitive-verifier on all test files
- **python-tests.yml**: Runs pytest on Python code with multiple Python versions
- **codeql.yml**: Security scanning with CodeQL
- **flawfinder.yml**: Static analysis for C/C++ code
- **release.yml**: Automated release process
- **summary.yml**: Generates summary information

## Important Notes

- **DO NOT** break existing APIs without careful consideration
- **DO NOT** add external C++ dependencies (keep header-only)
- **DO NOT** modify test files in ways that change their verification purpose
- **DO NOT** commit build artifacts (*.o, executables) - use `.gitignore`
- **ALWAYS** test changes with GCC 13+ compiler
- **ALWAYS** consider competitive programming use cases (time limits, memory limits)
- **ALWAYS** maintain O(1) or O(log n) operations where expected by users
- **PREFER** compile-time computation over runtime when possible
- **PREFER** standard library features over custom implementations

## Contact and Resources

- **Issues**: Report bugs and request features via GitHub Issues
- **Documentation Site**: https://cplib.tifa-233.com/
- **Citation**: See CITATION.bib for academic citation information
