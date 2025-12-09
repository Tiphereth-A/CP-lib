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

- **Language**: C++20 with GCC 13+ compiler support
- **Optimization**: Code compiled with `-O2` optimization flag
- **Verification**: Automated testing on multiple online judges (Aizu, Library Checker, Yukicoder, etc.)
- **Documentation**: Supports PDF documentation generating for offline usage

## Installation

### System Requirements

- **Compiler**: GCC 13.0 or higher (GNU Compiler Collection)
- **Python**: Python 3.12 or higher (for management scripts)
- **PDF Generation**: LaTeX or Typst (required only if you want to generate PDF documentation)

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

#### PDF Generation Dependencies

Choose **one** of the following:

**Option 1: LaTeX (Traditional)**
- **Fonts**: Run `make download-fonts` to download required fonts (see `Makefile`)
- **Python Dependencies**: See `latex` group of [Python Dependencies](#python-dependencies)
- **Others**:
    - [inkscape](https://github.com/inkscape/inkscape) for SVG files support

**Option 2: Typst (Modern, Faster)**
- **Typst**: Install from [typst.io](https://github.com/typst/typst/releases) or via package manager
- No additional dependencies required
- Significantly faster compilation compared to LaTeX

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
python3 manager.py --help
```

**Windows:**

```powershell
# Clone the repository
git clone 'https://github.com/Tiphereth-A/CP-lib.git'
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
// your_code.cpp
#include "include/nt/gcd.hpp"
#include "include/ds/fenwick.hpp"

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

Then compiling your code

```bash
g++ -std=gnu++20 -O2 -I./include your_code.cpp -o your_code
```

### Management Script Commands

> For detailed documentation on the Python Manager System, including architecture, command internals, and extension guide, see [MANAGER_SYSTEM.md](https://github.com/Tiphereth-A/CP-lib/blob/master/doc/MANAGER_SYSTEM.md).

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
    # Using LaTeX (default)
    python manager.py run
    
    # Using Typst (faster)
    python manager.py run -t typ
    ```

    Options:

    - `-t, --code-type`: Document type (`tex` for LaTeX, `typ` for Typst, default: `tex`)
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
    # For LaTeX
    python manager.py gen-nb
    
    # For Typst
    python manager.py gen-nb -t typ
    ```

7. **`gen-cs`** - Generate cheatsheet contents

    ```bash
    # For LaTeX
    python manager.py gen-cs
    
    # For Typst
    python manager.py gen-cs -t typ
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

- **Trees**: [Segment tree](https://cplib.tifa-233.com/include/ds/segtree.hpp), [Link-Cut tree](https://cplib.tifa-233.com/include/ds/link_cut_tree.hpp), [K-D tree](https://cplib.tifa-233.com/include/ds/kdtree.hpp), ...
- **Heaps**: [d-ary heap](https://cplib.tifa-233.com/include/ds/d_ary_heap.hpp), [leftist tree](https://cplib.tifa-233.com/include/ds/leftist_tree.hpp), [skew heap](https://cplib.tifa-233.com/include/ds/skew_heap.hpp), ...
- **Advanced**: [Persistent segment tree](https://cplib.tifa-233.com/include/ds/persistent_segtree.hpp), [FHQ Treap](https://cplib.tifa-233.com/include/ds/fhq_treap.hpp), [RBTree](https://cplib.tifa-233.com/include/ds/rbtree.hpp), ...
- **Specialized**: [Monotonic queue](https://cplib.tifa-233.com/include/ds/mono_queue.hpp)/[stack](https://cplib.tifa-233.com/include/ds/mono_stack.hpp), [01-Trie](https://cplib.tifa-233.com/include/ds/trie01.hpp), [Dynamic bitset](https://cplib.tifa-233.com/include/ds/dbitset.hpp), ...

#### Graph Algorithms

In `include/graph/` and `include/tree/`.

- **Shortest Paths**: [Dijkstra](https://cplib.tifa-233.com/include/graph/dijkstra.hpp), [Floyd-Warshall](https://cplib.tifa-233.com/include/graph/floyd.hpp), [Johnson](https://cplib.tifa-233.com/include/graph/johnson.hpp), ...
- **Flow Networks**: [Dinic](https://cplib.tifa-233.com/include/graph/dinic.hpp), [HLPP (Highest Label Preflow-Push)](https://cplib.tifa-233.com/include/graph/hlpp.hpp), [Min-cost flow](https://cplib.tifa-233.com/include/graph/ssp.hpp), ...
- **Matching**: [Hungarian algorithm](https://cplib.tifa-233.com/include/graph/hungarian.hpp), [Hopcroft-Karp](https://cplib.tifa-233.com/include/graph/hopkap.hpp), ([Weighted](https://cplib.tifa-233.com/include/graph/blossomw.hpp)) [blossom algorithm](https://cplib.tifa-233.com/include/graph/blossom.hpp), ...
- **Connectivity**: [Tarjan SCC](https://cplib.tifa-233.com/include/graph/tarjan.hpp), [BCC](https://cplib.tifa-233.com/include/graph/v_bcc.hpp), [Edge BCC](https://cplib.tifa-233.com/include/graph/e_bcc.hpp), [Edge TCC](https://cplib.tifa-233.com/include/graph/e_tcc.hpp), ...
- **Trees**: [LCA](https://cplib.tifa-233.com/include/tree/lca_hld.hpp), [Heavy-Light Decomposition](https://cplib.tifa-233.com/include/tree/hld.hpp), [Dominator tree](https://cplib.tifa-233.com/include/graph/domtree.hpp), ...
- **Special**: [Steiner tree](https://cplib.tifa-233.com/include/graph/steiner_tree.hpp), [Gomory-Hu tree](https://cplib.tifa-233.com/include/graph/gomory_hu.hpp), [2-SAT solver](https://cplib.tifa-233.com/include/graph/sat2.hpp), ...

#### Mathematics

- **Number Theory** (`include/nt/`): [Pollard-rho](https://cplib.tifa-233.com/include/nt/pfactors.hpp), [Stern-Brocot tree](https://cplib.tifa-233.com/include/nt/sbt.hpp), [min-25 sieve](https://cplib.tifa-233.com/include/nt/min25_sieve.hpp), ...
- **Combinatorics** (`include/comb/`): ([q-](https://cplib.tifa-233.com/include/comb/qbinom.hpp))[Binomial coefficients](https://cplib.tifa-233.com/include/comb/binom.hpp), [Bernoulli number](https://cplib.tifa-233.com/include/comb/gen_bernoulli.hpp), [Bell number](https://cplib.tifa-233.com/include/comb/gen_bell.hpp), ...
- **Convolutions** (`include/conv/`): [NTT](https://cplib.tifa-233.com/include/conv/ntt.hpp), [Walsh-Hadamard transform](https://cplib.tifa-233.com/include/conv/wht.hpp), [Subset convolution](https://cplib.tifa-233.com/include/conv/conv_subset.hpp), ...
- **Polynomials** (`include/poly/`): [polynomial](https://cplib.tifa-233.com/include/poly/poly.hpp)/[sparse polynomial](https://cplib.tifa-233.com/include/poly/polysp.hpp)/[set power series operations](https://cplib.tifa-233.com/include/poly/comp_fpssps.hpp), ...
- **Linear Algebra** (`include/lalg/`): [Gaussian elimination](https://cplib.tifa-233.com/include/lalg/ge_mat.hpp), [Linear basis](https://cplib.tifa-233.com/include/lalg/basis_z2.hpp), ([Sparse](https://cplib.tifa-233.com/include/lalg/matsp.hpp)) [matrix](https://cplib.tifa-233.com/include/lalg/mat.hpp) operations, ...
- **Miscellaneous** (`include/math/`): [deBruijn](https://cplib.tifa-233.com/include/math/debruijn.hpp), [Newton interpolation](https://cplib.tifa-233.com/include/math/interp_newton_n2.hpp), [Young table](https://cplib.tifa-233.com/include/math/youngt.hpp), ...

#### String Algorithms

In `include/str/`.

- **Pattern Matching**: [KMP](https://cplib.tifa-233.com/include/str/kmp.hpp), [Z-algorithm](https://cplib.tifa-233.com/include/str/z_func.hpp), [Aho-Corasick](https://cplib.tifa-233.com/include/str/aho_corasick.hpp), ...
- **Suffix Structures**: [Suffix array](https://cplib.tifa-233.com/include/str/suffix_array.hpp), [suffix automaton](https://cplib.tifa-233.com/include/str/suffix_automaton.hpp), [extended suffix automaton](https://cplib.tifa-233.com/include/str/ex_suffix_automaton.hpp), ...
- **Hashing**: [String rolling hash](https://cplib.tifa-233.com/include/str/hash_substr.hpp), [2D string rolling hashing](https://cplib.tifa-233.com/include/str/hash_substr_2d.hpp), ...
- **Others**: [Manacher](https://cplib.tifa-233.com/include/str/manacher.hpp), [Lyndon factorization](https://cplib.tifa-233.com/include/str/lyndon.hpp), [Runs enumeration](https://cplib.tifa-233.com/include/str/run_hash.hpp), ...

#### Computational Geometry

- **2D Geometry** (`include/geo2d/`): ([Dynamic](https://cplib.tifa-233.com/include/geo2d/dcvh.hpp)) [convex hull](https://cplib.tifa-233.com/include/geo2d/cvh.hpp), [Closest pair](https://cplib.tifa-233.com/include/geo2d/min_dis_ps.hpp), ([Circle](https://cplib.tifa-233.com/include/geo2d/aunion_cs.hpp)/[Polygon](https://cplib.tifa-233.com/include/geo2d/aunion_pos.hpp)) area unions, ...
- **3D Geometry** (`include/geo3d/`): [3D point](https://cplib.tifa-233.com/include/geo3d/point3d.hpp), [Plane](https://cplib.tifa-233.com/include/geo3d/planev.hpp), [Convex hull](https://cplib.tifa-233.com/include/geo3d/cvh3d.hpp), ...

#### Optimization

In `include/opt/`.

- **Dynamic Programming**: Knapsack variants ([01](https://cplib.tifa-233.com/include/opt/knapsack_01.hpp)/[mixed](https://cplib.tifa-233.com/include/opt/knapsack_mixed.hpp)/[mixed huge](https://cplib.tifa-233.com/include/opt/knapsack_mixed_huge.hpp)), [LIS](https://cplib.tifa-233.com/include/opt/lis.hpp), [Cyclic LCS](https://cplib.tifa-233.com/include/opt/lcs_circ.hpp), ...
- **Specialized**: [DLX (Dancing Links)](https://cplib.tifa-233.com/include/opt/dlx.hpp), [A* search](https://cplib.tifa-233.com/include/opt/astar.hpp), [SMawk algorithm](https://cplib.tifa-233.com/include/opt/smawk.hpp), ...

#### Miscellaneous

- **Encoding, Decoding, Hashing** (`include/edh/`): [Base64](https://cplib.tifa-233.com/include/edh/base64.hpp), [Huffman tree](https://cplib.tifa-233.com/include/edh/huffman_tree.hpp), [Prufer code](https://cplib.tifa-233.com/include/edh/prufer.hpp), [Garsia-Wachs](https://cplib.tifa-233.com/include/edh/garsia_wachs.hpp), ...
- **Enumeration** (`include/enum/`): [Subset enumeration](https://cplib.tifa-233.com/include/enum/enum_subset.hpp), [Supset enumeration](https://cplib.tifa-233.com/include/enum/enum_supset.hpp), [Gosper](https://cplib.tifa-233.com/include/enum/gosper.hpp), ...
- **I/O specialization** (`include/io/`): [Fast integer/floating point I/O based on `mmap`](https://cplib.tifa-233.com/include/io/fastin.hpp), [`__int128` I/O](https://cplib.tifa-233.com/include/io/ios128.hpp), [tuple I/O](https://cplib.tifa-233.com/include/io/ios_tuple.hpp), ...
- **Utilities** (`include/util/`): [n-dim vector](https://cplib.tifa-233.com/include/util/ndvec.hpp), [bitset getword](https://cplib.tifa-233.com/include/util/bitset_getdata.hpp), [libstdc++ `std::unordered_*` hacker](https://cplib.tifa-233.com/include/util/unordered_stl_hacker.hpp), ...

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
# Using LaTeX (traditional, slower)
python manager.py run

# Using Typst (modern, faster)
python manager.py run -t typ
```

The generated PDF (`notebook.pdf` in `_pdf_out/`) includes:

- All algorithm implementations with syntax highlighting
- Documentation (in Simplified Chinese)
- Usage examples
- Cheatsheets

**Note**: Typst compilation is significantly faster than LaTeX (typically 10-20x speedup) and requires fewer dependencies.

### Test Matrix Support

Generate multiple test variants from a single template:

```bash
python manager.py gentc
```

This generates test files from `meta_test/*.cppmeta` templates, allowing testing with different:

- Hash functions
- Modular arithmetic implementations (Montgomery vs. Barrett)
- Convolution methods, e.g. 3-modular NTT or MTT (optimized FFT, by [matthew99a](https://matthew99a.github.io/))
- Other parameterized variations

### Code Quality Tools

- **Automatic Linting**: Code formatting with clang-format
- **Static Analysis**: CodeQL and Flawfinder integration
- **Continuous Integration**: Automated testing on multiple platforms

## Contributing

We welcome contributions! Please read the following guidelines before submitting.

1. **Fork the repository** and clone your fork
2. **Read the contributing guidelines** in [CONTRIBUTING.md](https://github.com/Tiphereth-A/CP-lib/blob/master/doc/CONTRIBUTING.md)
3. **Set up your development environment** (see [Installation](#installation) section)

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

- **Aizu Online Judge**: Problems in `test/aizu/` and `test/aizu-*/`
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
A: This is normal for large LaTeX documents, the expected time used in PDF generation is about 6 minutes in GitHub Action. You can use `--no-run-usage` to skip usage compilation:

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

Thank you to all contributors who have helped improve this library! See the [Contributors](https://github.com/Tiphereth-A/CP-lib/graphs/contributors) page.

### Inspiration

This library is inspired by and builds upon the work of the competitive programming community, including:

- Various algorithm textbooks and resources
- Open-source competitive programming libraries
- Community discussions and improvements

See [notebook.bib](https://github.com/Tiphereth-A/CP-lib/blob/master/notebook.bib) for details.

### Citation

If you use this library in academic work, please cite it using the provided [CITATION.bib](https://github.com/Tiphereth-A/CP-lib/blob/master/CITATION.bib) file.
