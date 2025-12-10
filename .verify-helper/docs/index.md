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

![License](https://img.shields.io/github/license/Tiphereth-A/CP-lib)
![Standard](https://img.shields.io/static/v1?label=standard&message=C%2B%2B20+with+O2&color=green&logo=cplusplus)
![Requirements](https://img.shields.io/static/v1?label=requirments&message=GCC+>=13&color=blue&logo=cplusplus)
![Code Size](https://img.shields.io/github/languages/code-size/Tiphereth-A/CP-lib)

[![GitHub deployments](https://img.shields.io/github/deployments/Tiphereth-A/CP-lib/github-pages?label=pages+state&logo=github)](https://cplib.tifa-233.com/#library-files)
[![GitHub Workflow Status (with event) - verify](https://img.shields.io/github/actions/workflow/status/Tiphereth-A/CP-lib/verify.yml?label=verify&logo=github)](https://github.com/Tiphereth-A/CP-lib/actions)
[![GitHub Workflow Status (with event) - release](https://img.shields.io/github/actions/workflow/status/Tiphereth-A/CP-lib/release.yml?label=release&logo=github)](https://github.com/Tiphereth-A/CP-lib/actions)
[![GitHub Workflow Status (with event) - codeql](https://img.shields.io/github/actions/workflow/status/Tiphereth-A/CP-lib/codeql.yml?label=codeql&logo=github)](https://github.com/Tiphereth-A/CP-lib/actions)
[![GitHub Workflow Status (with event) - flawfinder](https://img.shields.io/github/actions/workflow/status/Tiphereth-A/CP-lib/flawfinder.yml?label=flawfinder&logo=github)](https://github.com/Tiphereth-A/CP-lib/actions)
[![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/Tiphereth-A/CP-lib)

## Quick Start

```cpp
#include "include/nt/gcd.hpp"
#include "include/ds/fenwick.hpp"

using namespace tifa_libs;

int main() {
    u64 result = math::gcd(48, 18);  // GCD
    ds::fenwick<u64> fw(10);         // Fenwick Tree
    fw.add(1, 5);
    return 0;
}
```

```bash
g++ -std=gnu++20 -O2 -I./include your_code.cpp -o your_code
```

## Installation

| Requirement | Version |
|-------------|---------|
| GCC | ≥13.0 |
| Python | ≥3.12 (for scripts) |
| PDF Gen | LaTeX or Typst (optional) |

```bash
git clone https://github.com/Tiphereth-A/CP-lib.git && cd CP-lib
uv sync --frozen                    # Python dependencies
uv sync --frozen --group verify     # For OJ verification
```

## Algorithm Categories

| Category | Directory | Examples |
|----------|-----------|----------|
| **Data Structures** | `ds/` | Segment tree, Link-Cut tree, Treap, Trie |
| **Graph** | `graph/`, `tree/` | Dijkstra, Dinic, Tarjan SCC, LCA, HLD |
| **Number Theory** | `nt/` | Pollard-rho, min-25 sieve, Stern-Brocot |
| **Combinatorics** | `comb/` | Binomial, Bernoulli, Bell numbers |
| **Convolution** | `conv/` | NTT, Walsh-Hadamard, Subset conv |
| **Polynomial** | `poly/` | Poly operations, Set power series |
| **Linear Algebra** | `lalg/` | Gaussian elimination, Linear basis |
| **String** | `str/` | KMP, Z-func, Suffix array/automaton, AC automaton |
| **Geometry** | `geo2d/`, `geo3d/` | Convex hull, Closest pair, Area union |
| **Optimization** | `opt/` | Knapsack, LIS, DLX, A* search |

Browse all implementations: [Documentation Site](https://cplib.tifa-233.com/#library-files)

## Manager Commands

```bash
python manager.py new          # Create new implementation
python manager.py fmt          # Lint code files
python manager.py run          # Generate PDF notebook (LaTeX)
python manager.py run -t typ   # Generate PDF notebook (Typst, faster)
python manager.py run-usage    # Test usage examples
python manager.py gentc        # Generate test codes from matrices
python manager.py clean        # Clean temp files
```

See [MANAGER_SYSTEM.md](https://github.com/Tiphereth-A/CP-lib/blob/master/doc/MANAGER_SYSTEM.md) for details.

## Testing & Verification

All implementations verified against:
- [Library Checker](https://judge.yosupo.jp)
- [Aizu Online Judge](https://judge.u-aizu.ac.jp/)
- [Yukicoder](https://yukicoder.me)

```bash
# Run OJ verification
uv sync --frozen --group verify
competitive-verifier verify
```

## Submit to OJ

Use [oj-bundle](https://github.com/online-judge-tools/verification-helper) to expand includes:

```bash
oj-bundle your_code.cpp > bundled.cpp
```

Or use the "bundled" button on the [documentation site](https://cplib.tifa-233.com/#library-files).

## Contributing

See [CONTRIBUTING.md](https://github.com/Tiphereth-A/CP-lib/blob/master/doc/CONTRIBUTING.md).

## Acknowledgments

- [competitive-verifier](https://github.com/competitive-verifier/competitive-verifier)
- [TINplate](https://github.com/Tiphereth-A/TINplate)
- [online-judge-verify-helper](https://github.com/online-judge-tools/verification-helper)
