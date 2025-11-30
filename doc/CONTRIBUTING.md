## Code Style Guidelines

1. **Use existing utilities**: Before writing new code, check `include/util/*.hpp` for existing macros, traits and types
2. **Follow examples**: Look at existing implementations like:

    - [include/math/qpow.hpp](https://github.com/Tiphereth-A/CP-lib/blob/master/include/math/qpow.hpp)
    - [include/graph/chrom_num.hpp](https://github.com/Tiphereth-A/CP-lib/blob/master/include/graph/chrom_num.hpp)
    - [include/str/kmp.hpp](https://github.com/Tiphereth-A/CP-lib/blob/master/include/str/kmp.hpp)

3. **Language requirements**:

    You should only use Simplified Chinese or English in this repository.

    - **English** for: `*.md`, `include/*`, `doc_md/*`, `meta_test/*`, `test/*`, `tests/*`
    - **Simplified Chinese** for: `*.tex`, `cheatsheet/*`, `doc_tex/*`, `usage/*`

    If you have any trouble with this, please feel free to ask owner for help! ;)

## Directories and files

This section describes the purpose of each directory and important files in the repository.

### Core Directories

- **`include/`** - Main C++ header files containing all algorithm and data structure implementations. Organized by category (e.g., `graph/`, `math/`, `ds/`, `str/`). All code should be in English.

- **`doc_tex/`** - LaTeX documentation files for the PDF notebook. Organized by chapter matching `include/` structure. Documentation should be written in Simplified Chinese. These files are included in the generated PDF notebook.

- **`doc_md/`** - Markdown documentation files for competitive-verifier. Organized by chapter matching `include/` structure. Used by the verification system to generate documentation on the website. Should be written in English.

- **`usage/`** - Usage example files demonstrating how to use each implementation. Organized by chapter matching `include/` structure. Comments should be in Simplified Chinese. These examples are compiled and run during testing.

- **`test/`** - Test files for verification against online judges (Aizu, Library Checker, Yukicoder) and local tests. Organized by online judge or test type. Should be written in English.

- **`cheatsheet/`** - LaTeX files for cheatsheet sections in the PDF notebook. Contains quick reference materials. Should be written in Simplified Chinese.

### Configuration and Management

- **`config.yml`** - Main configuration file defining directory paths, chapter/section structure, code styles, and compilation commands.

- **`tcgen.yml`** - Test matrix configuration file for generating parameterized test variants from templates.

- **`libs/`** - Python library modules used by `manager.py` for managing the repository, generating content, and processing files.

- **`manager.py`** - Main management script providing commands for creating new implementations, formatting code, generating notebooks, and running tests.

### Generated and Build Directories

- **`_gen/`** - Generated files from `python manager.py gen-cs` and `python manager.py gen-nb`. Contains generated LaTeX content files (`contents_cheatsheet.tex`, `contents_notebook.tex`).

- **`_pdf_out/`** - Output directory for PDF files built by `python manager.py run`. Contains the compiled notebook PDF.

- **`_minted-notebook/`** - Temporary directory for LaTeX minted package output (syntax highlighting) during PDF compilation.

- **`build/`** - CMake build artifacts and compiled object files.

- **`downloads/`** - Temporary directory for downloaded font files (created by `make download-fonts`).

- **`fonts/`** - Directory containing extracted font files for LaTeX compilation (created by `make download-fonts`).

- **`svg-inkscape/`** - Processed SVG files converted to PDF format for inclusion in LaTeX documents.

### Testing and Data

- **`test/`** - Test files for verification against online judges (Aizu, Library Checker, Yukicoder) and local tests. Organized by online judge or test type. Should be written in English.

- **`tests/`** - Python test suite for the manager system using pytest. Should be written in English.

- **`meta_test/`** - Test matrix template files (`.cppmeta`). These templates are used to generate multiple test variants with different parameters (e.g., hash functions, modular arithmetic implementations). Should be written in English.

- **`data/`** - Test data files organized by online judge or problem source. Contains input/output files (`.in`, `.out`, `.ans`) for local testing.

- **`benchmark/`** - Benchmark files for performance testing.

### Documentation Resources

- **`img/`** - Image files (SVG, PNG) used in documentation. Referenced from `doc_tex/` and `cheatsheet/` files.

- **`src/`** - Miscellaneous source files referenced in documentation (e.g., example code snippets, reference materials).  Referenced from `notebook.tex`, `doc_tex/` and `cheatsheet/` files.

### LaTeX Configuration

- **`notebook.tex`** - Main LaTeX file for the notebook PDF.

- **`ICPCnotebook.cls`** - LaTeX class file defining the notebook style.

- **`notebook.bib`** - Bibliography file for citations in the notebook.

### Other Directories

- **`.github/`** - GitHub Actions workflows and configuration files for CI/CD.

- **`.verify-helper/`** - Configuration files for competitive-verifier.

- **`local/`** - Local files for personal use (typically not tracked in git).

## Adding New Contents

### New Implementation

1. **Use the management script**:

    ```bash
    python manager.py new
    ```

2. **Fill in the required information**:

    - Chapter name (e.g., `graph`, `math`, `ds`)
    - File name (without extension)
    - Section title (for notebook)
    - File extensions

3. **The script will create**:

    - Code file: `include/<chapter>/<file>.hpp`
    - Documentation: `doc_tex/<chapter>/<file>.tex`
    - Competitive verifier doc: `doc_md/<chapter>/<file>.md`
    - Usage example: `usage/<chapter>/<file>.cpp`

4. **Implement your algorithm** in the generated files

5. **Write documentations** if necessary. Images put in `img/` folder, other files put in `src/` folder.

6. **Add tests** in `test/` directory (if applicable)

7. **Adjust ordering in `config.yml`**

### New Cheatsheet

1. **Write documentations** in `cheatsheet/` folder. Images put in `img/` folder, other files put in `src/` folder.
2. **Add info in `config.yml`** (in `cheatsheets:`)

### Testing Your Changes

```bash
# Format your code
python manager.py fmt

# Run usage examples
python manager.py run-usage

# Generate and compile notebook
python manager.py run

# Run Python tests for manager system
pytest                    # Run all tests
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
