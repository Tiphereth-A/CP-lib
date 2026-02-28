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

## Installation

Requirements:

- **Compiler**: GCC 13.0 or higher (GNU Compiler Collection)
- **Python**: Python 3.12 or higher (for management scripts)
- **LaTeX**: Required only if you want to generate PDF documentation

The project uses Python for management scripts. Install dependencies using `uv`.

Optional dependency groups:

- **dev**: Development tools (e.g., `pycodestyle`)
- **latex**: LaTeX compiling dependencies (e.g., `pygments` for syntax highlighting)
- **verify**: Verification tools (e.g., `competitive-verifier`)

For LaTeX compiling:

- **Fonts**: Run `make download-fonts` to download required fonts (see `.github/workflows/verify.yml`)
- [inkscape](https://github.com/inkscape/inkscape) for SVG files support

```bash
# Clone the repository
git clone https://github.com/Tiphereth-A/CP-lib.git
cd CP-lib

# Install Python dependencies
uv sync --frozen

# Install verify group for using `oj-verify` and `oj-bundle` if needed
uv sync --frozen --group verify

# Verify installation
python3 manager.py --help
```

## Usage

If you only want to use the library or the PDF, just check out [Releases](https://github.com/Tiphereth-A/CP-lib/releases/latest).

The library is header-only, so you can simply include the headers you need:

```cpp
// your_code.cpp
#include "nt/gl/gcd/lib.hpp"
#include "ds/fenwick/d1/lib.hpp"

using namespace tifa_libs;

int main() {
    // Use algorithms and data structures
    // Example: GCD
    u64 a = 48, b = 18;
    u64 result = math::gcd(a, b);  // Returns 6
    
    // Example: Fenwick Tree
    ds::fenwick<u64> fw(10);
    fw.add(1, 5);
    fw.add(2, 3);
    u64 sum = fw.sum(1, 2);  // Returns 8
    
    return 0;
}
```

The `manager.py` script provides several commands for managing the repository, see `python manager.py --help` for details.

### Writing Tests

#### For Online Judge Problems

1. Create test file: `test/cpv/<oj>/<problem>.test.cpp`
2. Include the implementation
3. Solve the problem using the library, the test will be automatically verified

**Example:**

```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/..."
#include "../../../src/math/gl/gcd/lib.hpp"
// ... implementation
```

#### For Local Tests

Acturally, local tests is a **hack** of Online Judge Problems test. It uses a fixed OJ problem [A + B](https://judge.yosupo.jp/problem/aplusb), so the steps are basically like steps for OJ problems. But there are some more rules:

1. Create tests in `test/cpv_local/`

2. Follow the format of this example code

    <details>
    <summary>Example</summary>

    ```cpp
    #define UNITTEST
    #define PROBLEM "https://judge.yosupo.jp/problem/aplusb" // NOT change

    // ... your headers

    #include "../base.hpp" // MUST include this header

    void single_test();

    // ... implementation

    int main() {
        auto tcase = unittest::pre_test();

        // change code in each cases if you want
        switch (tcase) {
            case unittest::TC::example_00: single_test(); break;
            case unittest::TC::example_01: break;
            case unittest::TC::random_00: break;
            case unittest::TC::random_01: break;
            case unittest::TC::random_02: break;
            case unittest::TC::random_03: break;
            case unittest::TC::random_04: break;
            case unittest::TC::random_05: break;
            case unittest::TC::random_06: break;
            case unittest::TC::random_07: break;
            case unittest::TC::random_08: break;
            case unittest::TC::random_09: break;
            default: break;
        }

        unittest::post_test();
    }
    ```

    </details>

3. If you have some testdata files, then put data in `test/cpv_data/_data/` folder and follow the format of this example code

    <details>
    <summary>Example</summary>

    ```cpp
    #define UNITTEST
    #define PROBLEM "https://judge.yosupo.jp/problem/aplusb" // NOT change

    // ... your headers

    #include "../base.hpp" // MUST include this header

    using namespace tifa_libs;

    strn single_proceed(std::ifstream &fin); // use `fin` as `std::cin`, return output as `std::string`

    // ... implementation

    void test(strnv data) {
        auto [fn_in, fn_ans] = unittest::get_fname_in_ans("foo", "bar", data); // change param
        std::ifstream fin(fn_in), fans(fn_ans);

        u32 t = 1;
        u32 testcase = 0;
        // fin >> t; // if have multiple testcases in single file
        flt_ (u32, i, 0, t) {
            ++testcase;
            strn got = single_proceed(fin);
            strn want, _;
            // change following codes based on answer format
            while (std::getline(fans, _)) want += _ + '\n';
            while (isspace(got.back())) got.pop_back();
            while (isspace(want.back())) want.pop_back();
            check(got, want, check_param(testcase));
        }
    }

    int main() {
        auto tcase = unittest::pre_test();

        // change code in each cases if you want
        switch (tcase) {
            case unittest::TC::example_00: test("1"); break;
            case unittest::TC::example_01: test("2"); break;
            case unittest::TC::random_00: test("3"); break;
            case unittest::TC::random_01: break;
            case unittest::TC::random_02: break;
            case unittest::TC::random_03: break;
            case unittest::TC::random_04: break;
            case unittest::TC::random_05: break;
            case unittest::TC::random_06: break;
            case unittest::TC::random_07: break;
            case unittest::TC::random_08: break;
            case unittest::TC::random_09: break;
            default: break;
        }

        unittest::post_test();
    }
    ```

    </details>

## FAQs

**Q: How can I submit the code using headers of this repo to any OJ**  
A: Use [oj-bundle](https://github.com/online-judge-tools/verification-helper?tab=readme-ov-file#autoexpansion-of-includes) to auto-expansion your code, it has been included in `verify` group of [Python dependencies](#python-dependencies) already.

You can also find a `bundled` button at any code pages of [documentation site](https://cplib.tifa-233.com/#library-files), click the button then you will get the expanded code.

**Q: Test verification fails**  
A:

- Check online judge credentials (if required)
- Check if the problem still exists on the OJ
- Review test file syntax
- Check Time/memory limits (tests GitHub Action may takes ~3x more times than local)

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
