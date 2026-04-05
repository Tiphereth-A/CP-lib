## Code Style Guidelines

1. **Use existing utilities**: Before writing new code, check `src/util/**/lib.hpp` for existing macros, traits and types
2. **Follow examples**: Look at existing implementations like:

    - [src/math/qpow/basic/lib.hpp](https://github.com/Tiphereth-A/CP-lib/blob/master/src/math/qpow/basic/lib.hpp)
    - [src/graph/cnt/chrom_num/lib.hpp](https://github.com/Tiphereth-A/CP-lib/blob/master/src/graph/cnt/chrom_num/lib.hpp)
    - [src/str/kmp/lib.hpp](https://github.com/Tiphereth-A/CP-lib/blob/master/src/str/kmp/lib.hpp)

## Directories and files

This section describes the purpose of each directory and important files in the repository.

### Core Directories

- **`src/`** - Main C++ header files and documentation organized by category (e.g., `graph/`, `math/`, `ds/`, `str/`). Each implementation is in its own subdirectory containing:
  - `lib.hpp` - C++ implementation (in English)
  - `doc.tex` - LaTeX documentation for PDF notebook (in Simplified Chinese)
  - `cpvdoc.md` - Markdown documentation for competitive-verifier (in English)
  - `usage.cpp` - Usage examples (comments in Simplified Chinese)
  - Image files (`.svg`, `.png`) - Documentation resources used directly in this directory
  - `index.yml` - In category directories, defines chapter structure and section names

- **`src/sheet/`** - Cheatsheet content for the PDF notebook. Contains quick reference materials (in Simplified Chinese).

- **`src/_titlepage/`** and **`src/_colophon/`** - Special sections for notebook title page and colophon.

- **`test/`** - Test files for verification. Contains subdirectories:
  - `cpv/` - Competitive-verifier tests organized by online judge (Aizu, Library Checker, Yukicoder)
  - `cpv_local/` - Local tests with custom implementations and test data
  - `cpv_local/_data/` - Test data files organized by OJ (`.in`, `.out`, `.ans`)
  - `cpv_meta/` - Test matrix template files (`.cppmeta`) for generating parameterized test variants
  - `cplib/` - Additional test utilities

### Configuration and Management

- **`tcgen.yml`** - Test matrix configuration file for generating parameterized test variants from templates.

- **`libs/`** - Python library modules used by `manager.py` for managing the repository, generating content, and processing files. Contains:
  - `cli.py` - Command-line interface
  - `commands/` - Command implementations
  - `classes/` - Data classes and models
  - `configs.py`, `utils.py`, `templates.py`, etc.

- **`manager.py`** - Main management script providing commands for creating new implementations, formatting code, generating notebooks, and running tests.

- **`pyproject.toml`** - Python project configuration and dependency management.

- **`uv.lock`** - Lock file for uv package manager.

### Generated and Build Directories

- **`.cp-lib/`** - Generated/processed files directory.

- **`_minted-notebook/`** - Temporary directory for LaTeX minted package output (syntax highlighting) during PDF compilation.

- **`svg-inkscape/`** - SVG files converted to PDF format for inclusion in LaTeX documents.

### LaTeX Configuration

- **`notebook.tex`** - Main LaTeX file for the notebook PDF.

- **`ICPCnotebook.cls`** - LaTeX class file defining the notebook style.

- **`notebook.bib`** - Bibliography file for citations in the notebook.

### Development Configuration

- **`.github/`** - GitHub Actions workflows and configuration files for CI/CD.

- **`.competitive-verifier/`** - Configuration files for competitive-verifier.
  - `config.toml` - Verifier configuration
  - `docs/` - Additional documentation

- **`.vscode/`** - VS Code workspace settings.

- **`.latexindent.yaml`** - Configuration for LaTeX indentation and formatting.

- **`.clang-format`** - Clang format configuration for C++ code style.

- **`.clangd`** - Clangd configuration for C++ language server.

- **`.prettierrc`** - Prettier configuration for code formatting.

- **`.gitignore`**, **`.gitattributes`** - Git configuration files.

### Other Directories and Files

- **`local/`** - Local files for personal use (typically not tracked in git).

## Adding New Contents

### New Implementation

1. **Use the management script**:

    ```bash
    python manager.py new
    ```

2. **Fill in the required information**:

    - Section name (such as `graph.sp.dijkstra`)
    - Section title (for notebook)

3. **The script will create a subdirectory** `src/<section>/` containing:

    - `lib.hpp` - C++ implementation (write in English)
    - `doc.tex` - LaTeX documentation for PDF notebook (write in Simplified Chinese)
    - `cpvdoc.md` - Competitive-verifier markdown documentation (write in English)
    - `usage.cpp` - Usage examples (comments in Simplified Chinese)

    You can delete any of them safely if not needed.

4. **Implement your algorithm** in the generated `lib.hpp` file

5. **Write documentation** in `doc.tex` and `cpvdoc.md`. If you need images or other resources, place them directly in the same directory.

6. **Add tests** in `test/cpv/`, `test/cpv_local/`, or `test/cpv_meta/` as appropriate

7. **Adjust ordering** by editing `src/<chapter>/index.yml` or `src/index.yml`

### Testing Your Changes

```bash
# Format your code
python manager.py fmt

# Run usage examples
python manager.py test

# Generate notebook
python manager.py doc

# Run verification tests (requires competitive-verifier)
# See .github/workflows for CI test commands
```

### Submitting Changes

1. **Create a branch** for your changes
2. **Make your changes** following the code style
3. **Test thoroughly** using the management script
4. **Submit a pull request** with a clear description

### Reporting Issues

Use GitHub Issues to report:

- Bugs in implementations
- Documentation errors
- Feature requests
- Questions about usage
