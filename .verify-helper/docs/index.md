<h3 align="center">CP-lib</h3>
  <p align="center">
    My code library for competitive programming.
    <br/>
    powered by <a href="https://github.com/competitive-verifier/competitive-verifier">competitive-verifier/competitive-verifier</a> & <a href="https://github.com/Tiphereth-A/TINplate">Tiphereth-A/TINplate</a>.
    <br/>
    <br/>
    <a href="https://github.com/Tiphereth-A/CP-lib/issues">Report Bug</a>
    ·
    <a href="https://github.com/Tiphereth-A/CP-lib/issues">Request Feature</a>
    ·
    <a href="https://github.com/Tiphereth-A/CP-lib/releases/latest">Latest PDF & Code Release</a>
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

- **Language**: C++20 with GCC 13+ compiler support
- **Optimization**: Code compiled with `-O2` optimization flag
- **Verification**: Automated testing on multiple online judges (Aizu, Library Checker, Yukicoder, etc.)
- **Documentation**: Supports PDF documentation generating for offline usage

## Installation

### System Requirements

- **Compiler**: GCC 13.0 or higher (GNU Compiler Collection)
- **Python**: Python 3.12 or higher (for management scripts)
- **LaTeX**: Required only if you want to generate PDF documentation

### Dependencies

#### Python Dependencies

The project uses Python for management scripts. Install dependencies using `uv`:

```bash
uv sync --frozen
```

Core Python dependencies:

- `click` - Command-line interface framework
- `coloredlogs` - Colored logging output
- `multipledispatch` - Multiple dispatch support
- `pyyaml` - YAML configuration parsing

Optional dependency groups:

- **dev**: Development tools (e.g., `pycodestyle`)
- **latex**: LaTeX compiling dependencies (e.g., `pygments` for syntax highlighting)
- **verify**: Verification tools (e.g., `competitive-verifier`)

#### C++ Dependencies

The library is header-only and requires no external C++ dependencies beyond the standard library.

#### LaTeX Dependencies

- **Fonts**: Run `make download-fonts` to download required fonts (see `Makefile`)
- **Python Dependencies**: See `latex` group of [Python Dependencies](#python-dependencies)
- **Others**:
    - [inkscape](https://github.com/inkscape/inkscape) for SVG files support

### Installation Steps

#### Quick Installation (Using the Library Only)

If you only want to use the library in your projects:

**Download from Releases:**

1. Go to [Releases](https://github.com/Tiphereth-A/CP-lib/releases/latest)
2. Download `CP-lib.tar.gz`
3. Extract and copy the `include` directory to your project

**Linux/macOS:**

```bash
# Clone the repository
git clone https://github.com/Tiphereth-A/CP-lib.git
cd CP-lib

# Copy the include directory to your project
cp -r include /path/to/your/project/
```

**Windows (PowerShell):**

```powershell
# Clone the repository
git clone https://github.com/Tiphereth-A/CP-lib.git
cd CP-lib

# Copy the include directory to your project
Copy-Item -Recurse include C:\path\to\your\project\
```

#### Full Installation (For Development)

**Linux/macOS:**

```bash
# Clone the repository
git clone https://github.com/Tiphereth-A/CP-lib.git
cd CP-lib

# Install Python dependencies
python3 -m pip install --user uv
uv sync --frozen

# Install verify group for using `oj-verify` and `oj-bundle` if needed
uv sync --frozen --group verify

# Verify installation
python manager.py --help
```

**Windows:**

```powershell
# Clone the repository
git clone https://github.com/Tiphereth-A/CP-lib.git
cd CP-lib

# Install Python dependencies
python -m pip install --user uv
uv sync --frozen

# Install verify group for using `oj-verify` and `oj-bundle` if needed
uv sync --frozen --group verify

# Verify installation
python manager.py --help
```

## Usage

### Using the Library in Your Code

The library is header-only, so you can simply include the headers you need:

```cpp
#include "include/nt/gcd.hpp"
#include "include/ds/fenwick.hpp"

using namespace tifa_libs;

int main() {
    // Use algorithms and data structures
    // Example: GCD
    u64 a = 48, b = 18;
    u64 result = math::gcd(a, b);  // Returns 6
    
    // Example: Fenwick Tree
    ds::fenwick_tree<u64> fw(10);
    fw.add(1, 5);
    fw.add(2, 3);
    u64 sum = fw.sum(1, 2);  // Returns 8
    
    return 0;
}
```

Then compiling your code

```bash
g++ -std=gnu++20 -O2 -I./include your_code.cpp -o your_code
```

### Management Script Commands

The `manager.py` script provides several commands for managing the repository:

```bash
python manager.py [OPTIONS] COMMAND [ARGS]...
```

**Options:**
- `-l, --level [CRITICAL|ERROR|WARNING|INFO|DEBUG]`: Set log level (default: INFO)
- `--help`: Show help message

**Commands:**

1. **`new`** - Add a new implementation

    ```bash
    python manager.py new
    ```

    Prompts for:

    - Chapter name (e.g., `graph`, `math`, `ds`)
    - File name (without extension)
    - Section title (for notebook)
    - Code file extension (default: `hpp`)
    - Usage file extension (default: `cpp`)

2. **`fmt`** - Lint all code files

    ```bash
    python manager.py fmt -t cpp  # Format only C++ files
    ```

3. **`gentc`** - Generate test codes from test matrices

    ```bash
    python manager.py gentc
    python manager.py gentc -s meta_test -t test
    ```

4. **`run`** - Compile the complete notebook (PDF)

    ```bash
    python manager.py run
    ```

    Options:

    - `--no-fmt`: Skip linting before compilation
    - `--no-run-usage`: Skip running usage codes
    - `--no-gen`: Skip generating notebook & cheatsheet contents
    - `--no-clean`: Skip cleaning temporary files

5. **`run-usage`** - Compile and run usage examples

    ```bash
    python manager.py run-usage
    python manager.py run-usage -t cpp -l 8  # Use 8 threads
    ```

6. **`gen-nb`** - Generate notebook contents

    ```bash
    python manager.py gen-nb
    ```

7. **`gen-cs`** - Generate cheatsheet contents

    ```bash
    python manager.py gen-cs
    ```

8. **`clean`** - Clean up temporary files after PDF compiling

    ```bash
    python manager.py clean
    ```

### Configuration Files

The repository uses two main configuration files:

1. **`config.yml`**: Main configuration file containing:

    - Directory paths (code, documentation, usage, cheatsheet)
    - Chapter and section definitions
    - Code style settings
    - Compilation commands

2. **`tcgen.yml`**: Test matrices configuration:

    - Test matrix definitions
    - Code generation templates
    - Member configurations for different test scenarios

### Example Workflow

```bash
# 1. Add a new algorithm implementation
python manager.py new
# Follow prompts to create files

# 2. Write your implementation in include/your_chapter/your_file.hpp

# 3. Write documentation in doc_tex/your_chapter/your_file.tex

# 4. Write usage example in usage/your_chapter/your_file.cpp

# 5. Format your code
python manager.py fmt

# 6. Test your usage example
python manager.py run-usage

# 7. Generate and compile notebook
python manager.py run
```

## Features

### Algorithm Implementations

The library includes implementations across multiple categories:

#### Data Structures

In `include/ds/`.

- **Trees**: Segment trees, Link-Cut trees, K-D trees, ...
- **Heaps**: d-ary heaps, leftist trees, skew heaps, ...
- **Advanced**: Persistent segment trees, FHQ Treap, RBTrees, ...
- **Specialized**: Monotonic queues/stacks, 01-Trie, Dynamic bitset, ...

#### Graph Algorithms

In `include/graph/`.

- **Shortest Paths**: Dijkstra, Floyd-Warshall, Johnson, ...
- **Flow Networks**: Dinic, HLPP (Highest Label Preflow-Push), Min-cost flow, ...
- **Matching**: Hungarian algorithm, Hopcroft-Karp, (Weighted) blossom algorithm, ...
- **Connectivity**: SCC, BCC, TCC, ...
- **Trees**: LCA, Heavy-Light Decomposition, Dominator trees, ...
- **Special**: Steiner tree, Gomory-Hu tree, 2-SAT solver, ...

#### Mathematics

- **Number Theory** (`include/nt/`): Pollard-rho, Stern-Brocot tree, min-25 sieve, ...
- **Combinatorics** (`include/comb/`): (q-)Binomial coefficients, Stirling numbers, Bell numbers, ...
- **Convolutions** (`include/conv/`): NTT, Zeta-Mobius transform, Subset convolution, ...
- **Polynomials** (`include/poly/`): polynomial/sparse polynomial/set power series operations, ...
- **Linear Algebra** (`include/lalg/`): Gaussian elimination, Linear basis, (Sparse) matrix operations, ...
- **Miscellaneous** (`include/math/`): deBruijn, Newton interpolation, Young table, ...

#### String Algorithms

In `include/str/`.

- **Pattern Matching**: KMP, Z-algorithm, Aho-Corasick, ...
- **Suffix Structures**: Suffix array, suffix automaton, extended suffix automaton, ...
- **Hashing**: String rolling hash, 2D string rolling hashing, ...
- **Others**: Manacher, Lyndon factorization, Runs factorization, ...

#### Computational Geometry

- **2D Geometry** (`include/geo2d/`): Convex hull, Closest pair, Area unions, ...
- **3D Geometry** (`include/geo3d/`): 3D points, planes, convex hull, ...

#### Optimization

In `include/opt/`.

- **Dynamic Programming**: Knapsack variants, LIS, LCS, ...
- **Specialized**: DLX (Dancing Links), A* search, SMawk algorithm, ...

#### Miscellaneous

- **Encoding, Decoding, Hashing** (`include/edh/`): Base64, Huffman tree, Prufer code, Garsia-Wachs, ...
- **Enumeration** (`include/enum/`): Subset enumeration, Supset enumeration, Gosper, ...
- **I/O specialization** (`include/io/`): Fast integer/floating point I/O based on `mmap`, `__int128` I/O, tuple I/O, ...
- **Utilities** (`include/util/`): Traits, bitset getword, libstdc++ `std::unordered_*` hacker, ...

### Automated Verification

All implementations are automatically verified against problems from:

- **[Aizu Online Judge](https://judge.u-aizu.ac.jp/)** (AOJ)
- **[Library Checker](https://judge.yosupo.jp)**
- **[Yukicoder](https://yukicoder.me)**
- **Local tests**

Verification runs on every push and pull request via GitHub Actions.

### Printable Documentation

Generate a PDF notebook containing all implementations:

```bash
python manager.py run
```

The generated PDF (`notebook.pdf`) includes:

- All algorithm implementations with syntax highlighting
- Documentation (in Simplified Chinese)
- Usage examples
- Cheatsheets

### Test Matrix Support

Generate multiple test variants from a single template:

```bash
python manager.py gentc
```

This generates test files from `meta_test/*.cppmeta` templates, allowing testing with different:

- Hash functions
- Modular arithmetic implementations (Montgomery vs. Barrett)
- Convolution methods, e.g. 3 modular NTT or MTT (FFT optimized by [matthew99a](https://matthew99a.github.io/))
- Other parameterized variations

### Code Quality Tools

- **Automatic Linting**: Code formatting with clang-format
- **Static Analysis**: CodeQL and Flawfinder integration
- **Continuous Integration**: Automated testing on multiple platforms

## Contributing

We welcome contributions! Please read the following guidelines before submitting.

1. **Fork the repository** and clone your fork
2. **Read the contributing guidelines** in [CONTRIBUTING.md](https://github.com/Tiphereth-A/CP-lib/blob/master/CONTRIBUTING.md)
3. **Set up your development environment** (see Installation section)

## License

This project is licensed under the **GNU Affero General Public License v3.0 (AGPL-3.0)**.

See the [LICENSE](https://github.com/Tiphereth-A/CP-lib/blob/master/LICENSE) file for the full license text.

## Testing

### Running Tests

The repository includes several testing through multiple methods:

#### Test Matrix Generation

Generate and run parameterized tests:

```bash
# Generate test files from templates
python manager.py gentc

# Tests are generated in test/ directory
```

#### Online Judge Verification

Tests against real problems from online judges:

```bash
# Install verification dependencies
uv sync --frozen --group verify

# Run verification (requires online judge credentials)
competitive-verifier verify
```

Supported online judges:

- **Aizu Online Judge**: Problems in `test/aizu-*/`
- **Library Checker**: Problems in `test/library-checker-*/`
- **Yukicoder**: Problems in `test/yukicoder/`

#### Usage Example Tests

Compile and run all usage examples:

```bash
python manager.py run-usage
```

This compiles all files in `usage/` to ensure they work correctly.

### Continuous Integration

Tests run automatically on:

- Every push to `master`
- Every pull request
- Manual workflow dispatch

Check test status: [GitHub Actions](https://github.com/Tiphereth-A/CP-lib/actions)

### Writing Tests

#### For Online Judge Problems

1. Create test file: `test/<oj>/<problem>.test.cpp`
2. Include the implementation
3. Solve the problem using the library, the test will be automatically verified

**Example:**

```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/..."
#include "include/math/gcd.hpp"
// ... implementation
```

#### For Local Tests

Acturally, local tests is a **hack** of Online Judge Problems test. It uses a fixed OJ problem [A + B](https://judge.yosupo.jp/problem/aplusb), so the steps are basically like steps for OJ problems. But there are some more rules:

1. Create tests in `test/_local/`

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

3. If you have some testdata files, then put data in `data/` folder and follow the format of this example code

    <details>
    <summary>Example</summary>

    ```cpp
    #define UNITTEST
    #define PROBLEM "https://judge.yosupo.jp/problem/aplusb" // NOT change

    // ... your headers

    #include "../base.hpp" // MUST include this header

    using namespace tifa_libs;

    strn single_proceed(std::ifstream &); // use `fin` as `std::cin`, return output as `std::string`

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

### Test Coverage

The verification system tracks:

- ✅ Passed
- ❌ Failed
- ⚠️ No tests avalible

View verification status: [Documentation Site](https://cplib.tifa-233.com/#library-files)

## FAQs

### Usage Questions

**Q: How can I submit the code using headers of this repo to any OJ**  
A: Use [oj-bundle](https://github.com/online-judge-tools/verification-helper?tab=readme-ov-file#autoexpansion-of-includes) to auto-expansion your code, it has been included in `verify` group of [Python dependencies](#python-dependencies) already.

You can also find a `bundled` button at any code pages of [documentation site](https://cplib.tifa-233.com/#library-files), click the button then you will get the expanded code.

**Q: What namespace should I use?**  
A: All code is in the `tifa_libs` namespace. Use:

```cpp
using namespace tifa_libs;
```

**Q: How do I find the right algorithm for my problem?**  
A:

1. Check the [documentation site](https://cplib.tifa-233.com/#library-files)
2. Browse `include/` directory by category
3. Search the repository for keywords
4. Check usage examples in `usage/`

**Q: Can I modify the implementations?**  
A: Yes, but if you distribute modified versions, you must comply with AGPL-3.0 license requirements.

### Development Questions

**Q: How do I add a new algorithm?**  
A: Use `python manager.py new` to create the necessary files, then implement your algorithm.

**Q: How do I test my new implementation?**  
A:

1. Write a usage example in `usage/`
2. Run `python manager.py run-usage`
3. Add tests in `test/`
4. Run verification

**Q: How do I update the PDF notebook?**  
A: Run `python manager.py run` to regenerate and compile the notebook.

### Troubleshooting

**Q: Test verification fails**  
A:

- Check online judge credentials (if required)
- Check if the problem still exists on the OJ
- Review test file syntax
- Check Time/memory limits (tests GitHub Action may takes ~3x more times than local)

**Q: PDF generation is slow**  
A: This is normal for large documents. Use `--no-run-usage` to skip usage compilation:

```bash
python manager.py run --no-run-usage
```

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

Thank you to all contributors who have helped improve this library. See the [Contributors](https://github.com/Tiphereth-A/CP-lib/graphs/contributors) page.

### Inspiration

This library is inspired by and builds upon the work of the competitive programming community, including:

- Various algorithm textbooks and resources
- Open-source competitive programming libraries
- Community discussions and improvements

See [notebook.bib](https://github.com/Tiphereth-A/CP-lib/blob/master/notebook.bib) for details.

### Citation

If you use this library in academic work, please cite it using the provided [CITATION.bib](https://github.com/Tiphereth-A/CP-lib/blob/master/CITATION.bib) file.
