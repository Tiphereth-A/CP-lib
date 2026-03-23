<h3 align="center">CP-lib</h3>
  <p align="center">
    My code library for competitive programming.
    <br/>
    powered by <a href="https://github.com/competitive-verifier/competitive-verifier">competitive-verifier/competitive-verifier</a> & <a href="https://github.com/Tiphereth-A/TINplate">Tiphereth-A/TINplate</a>.
    <br/>
    <br/>
    <a href="https://cplib.tifa-233.com/#library-files">Documentation Site</a>
    ·
    <a href="https://github.com/Tiphereth-A/CP-lib/issues">Report Bug & Request Feature</a>
    ·
    <a href="https://github.com/Tiphereth-A/CP-lib/releases/latest">Latest Release</a>
    ·
    <a href="https://github.com/Tiphereth-A/CP-lib/blob/master/CITATION.bib">Citation File</a>
  </p>
</div>

![GitHub license](https://img.shields.io/github/license/Tiphereth-A/CP-lib)
![Standard](https://img.shields.io/static/v1?label=standard&message=C%2B%2B20+with+O2&color=green&logo=cplusplus)
![Requirements](https://img.shields.io/static/v1?label=requirments&message=GCC+>=13&color=blue&logo=cplusplus)
![Code Size](https://img.shields.io/github/languages/code-size/Tiphereth-A/CP-lib)

[![GitHub deployments](https://img.shields.io/github/deployments/Tiphereth-A/CP-lib/github-pages?label=pages+state&logo=github)](https://cplib.tifa-233.com/#library-files)
[![GitHub Workflow Status (with event) - verify](https://img.shields.io/github/actions/workflow/status/Tiphereth-A/CP-lib/verify.yml?label=verify&logo=github)](https://github.com/Tiphereth-A/CP-lib/actions)
[![GitHub Workflow Status (with event) - release](https://img.shields.io/github/actions/workflow/status/Tiphereth-A/CP-lib/release.yml?label=release&logo=github)](https://github.com/Tiphereth-A/CP-lib/actions)
[![GitHub Workflow Status (with event) - codeql](https://img.shields.io/github/actions/workflow/status/Tiphereth-A/CP-lib/codeql.yml?label=codeql&logo=github)](https://github.com/Tiphereth-A/CP-lib/actions)
[![GitHub Workflow Status (with event) - flawfinder](https://img.shields.io/github/actions/workflow/status/Tiphereth-A/CP-lib/flawfinder.yml?label=flawfinder&logo=github)](https://github.com/Tiphereth-A/CP-lib/actions)
[![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/Tiphereth-A/CP-lib)

**CP-lib** is a header-only C++ code library designed for competitive programming with 450+ implementations of algorithms and data structures commonly used in competitive programming contests.

The repository solves several key problems for competitive programmers:

- **Code Reusability**: Provides well-tested, ready-to-use implementations of common algorithms and data structures
- **Reliability**: All implementations are automatically verified against problems from supported online judges (OJ) to ensure correctness
- **Documentation**: Generates printable PDF documents (notebooks) for offline reference during competitions
- **Maintainability**: Includes automated testing, linting, and verification workflows to keep the codebase reliable

### Key Characteristics

- **Verification**: Automated testing on multiple online judges (Aizu, Library Checker, Yukicoder, etc.)
- **Documentation**: Supports PDF documentation generating for offline usage
- **Test matrix**: Generate multiple test variants from template.

## Usage

Requirements:

- **Compiler**: GCC 13.0 or higher (GNU Compiler Collection)
- **Python**: Python 3.12 or higher (for management scripts)
- **LaTeX**: Required only if you want to generate PDF documentation

The project uses Python for management scripts. Install dependencies using `uv`.

Optional dependency groups:

- **dev**: Development tools (e.g., `pycodestyle`)
- **latex**: LaTeX compiling dependencies (e.g., `pygments` for syntax highlighting)
- **verify**: Verification tools (`competitive-verifier`)
- **bundle**: Bundle codes by `oj-bundle` for submitting to OJs (`online-judge-verify-helper`)

For LaTeX compiling:

- **Fonts**: Run `make download-fonts` to download required fonts (see `.github/workflows/verify.yml`)
- [inkscape](https://github.com/inkscape/inkscape) for SVG files support

```bash
# Clone the repository
git clone -c core.symlinks=true git@github.com:Tiphereth-A/CP-lib.git
cd CP-lib

# Install Python dependencies
uv sync --frozen

# Install verify group for using `oj-verify` if needed
uv sync --frozen --group verify

# Install bundle group for using `oj-bundle` if needed
# Warning: NEVER use `oj-verify` from `online-judge-verify-helper`
uv sync --frozen --group bundle

# Verify installation
python3 manager.py --help
```

The `manager.py` script provides several commands for managing the repository, see `python manager.py --help` for details.

## FAQs

**Q: How can I submit the code using headers of this repo to any OJ**  
A: Use [oj-bundle](https://github.com/online-judge-tools/verification-helper?tab=readme-ov-file#autoexpansion-of-includes) to auto-expansion your code, it has been included in `verify` group of [Python dependencies](#python-dependencies) already.

You can also find a `bundled` button at any code pages of [documentation site](https://cplib.tifa-233.com/#library-files), click the button then you will get the expanded code.

**Q: PDF generation is slow**  
A: This is normal for large LaTeX documents, the expected time used in PDF generation is about 6 minutes in GitHub Action.

## Acknowledgments

### Core Tools and Libraries

- **[competitive-verifier](https://github.com/competitive-verifier/competitive-verifier)**: Automated verification system for competitive programming code
- **[TINplate](https://github.com/Tiphereth-A/TINplate)**: LaTeX template system for generating printable notebooks
- **[online-judge-verify-helper](https://github.com/online-judge-tools/verification-helper)**: Helper tools for OJ verification

### Online Judges

This library is verified against problems from:

- **Aizu Online Judge** (AOJ)
- **Library Checker** (judge.yosupo.jp)
- **Yukicoder**

### Contributors

Thank you to all contributors who have helped improve this library! See the [Contributors](https://github.com/Tiphereth-A/CP-lib/graphs/contributors) page.

### Inspiration

This library is inspired by and builds upon the work of the competitive programming community, including:

- Various algorithm textbooks and resources
- Open-source competitive programming libraries
- Community discussions and improvements

See [notebook.bib](https://github.com/Tiphereth-A/CP-lib/blob/master/notebook.bib) for details.

### Citation

If you use this library in academic work, please cite it using the provided [CITATION.bib](https://github.com/Tiphereth-A/CP-lib/blob/master/CITATION.bib) file.
