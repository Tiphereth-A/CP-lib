# CP-lib AI Coding Instructions

## Project Overview

**CP-lib** is a header-only C++20 competitive programming library with 450+ algorithm/data structure implementations. It's designed for competitive programming contests with automated verification against online judges (Aizu, Library Checker, Yukicoder, etc.) and generates printable PDF notebooks for offline reference.

- **Language**: C++20 with GNU extensions (GCC 13+ required)
- **Standard**: All code uses `-std=gnu++20 -O2` with strict warnings
- **Management**: Python 3.12+ CLI via `manager.py` for code generation, testing, and documentation

## Directory Structure

```
src/              # Algorithm implementations (bit, comb, ds, graph, tree, geo2d, str, etc.)
├─ */lib.hpp      # Each algorithm in its own lib.hpp
├─ index.yml      # Category definitions with Chinese descriptions
test/
├─ cpv/           # Competitive-verifier tests (auto-verified)
├─ cpv_meta/      # Test matrix templates (*.cppmeta files)
├─ cpv_local/     # Local/archived problem tests
libs/             # Python CLI implementation
├─ commands/      # CLI commands (new, doc, test, fmt, matrix, pack)
├─ classes/       # Content tree, test matrix parser
.verify-helper/   # Competitive-verifier configuration
```

## Code Conventions

### Namespace and Structure

All C++ code lives in `tifa_libs` namespace with category subnamespaces:

```cpp
namespace tifa_libs::ds {        // Data structures
namespace tifa_libs::str {       // String algorithms
namespace tifa_libs::graph {     // Graph algorithms
```

### Header Guards and Include Pattern

Every `lib.hpp` uses this pattern:

```cpp
#ifndef TIFALIBS_CATEGORY_NAME_LIB  // e.g., TIFALIBS_DS_TRIE01_LIB
#define TIFALIBS_CATEGORY_NAME_LIB

#include "../../util/alias/others/lib.hpp"  // Common aliases/types

namespace tifa_libs::category {
  // Implementation
}

#endif
```

### Essential Macros (from `src/util/util/lib.hpp`)

- `CEXP` → `constexpr`
- `CEXPE` → `constexpr explicit`
- `NE` → `noexcept`
- `CNE` → `const noexcept`
- `CR` → `const&`
- `TPN` → `typename`
- `flt_(T, i, l, r, ...)` → `for (T i = l, ie = r, ...; i < ie; ++i)` - loop macro
- `retif_(cond, if_true, ...)` → conditional return

### Type Aliases (from `src/util/alias/others/lib.hpp`)

- Integer: `i32`, `u32`, `i64`, `u64` (not `int`, `long long`)
- Containers: `vec<T>`, `vvec<T>` (2D), `vecp<U,T>` (vector of pairs)
- Use `__gnu_pbds` containers when available: `set`, `map`, `hset`, `hmap`, `pq`

## Test Matrix System

### `.cppmeta` Files

Template files with placeholders for generating multiple test variants:

```cpp
#define PROBLEM "https://judge-url/problem-id"

#include "../../../src/..."
// ---<GENTC>--- begin
// ---<GENTC>--- append category
// ---<GENTC>--- end
```

The `---<GENTC>---` markers are replaced by `tcgen.yml` configurations to generate `.test.cpp` files.

### `tcgen.yml` Configuration

Defines categories (e.g., `mints`, `mintd`, `hash`) with priorities and code templates. Used to generate test matrices where same algorithm is tested with different modular arithmetic implementations, hash functions, etc.

### Verification Metadata

Test files must start with `#define PROBLEM "URL"` for competitive-verifier:

```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_2_A"
```

## Python CLI Workflows

All commands via `python manager.py [command]`:

### Core Commands

- **`new`** - Create new algorithm section: prompts for fullname (e.g., `ds.trie`) and title
- **`doc`** - Generate LaTeX documentation to `.cp-lib/` for PDF compilation
- **`test`** - Run quick C++ compilation tests on all implementations
- **`fmt`** - Format code (calls `autopep8` for Python, clang-format for C++)
- **`meta`** - Generate `.test.cpp` files from `.cppmeta` templates using `tcgen.yml`
- **`pack`** - Extract `.hpp` files for release

### Installation & Setup

```bash
uv sync --frozen              # Install base dependencies
uv sync --frozen --group verify  # Add competitive-verifier tools
python manager.py --help      # See all commands
```

## Development Workflow

### Adding a New Algorithm

1. `python manager.py new` → Enter fullname (e.g., `ds.my_structure`) and title
2. Edit generated `src/[category]/[name]/lib.hpp`
3. Follow header guard pattern: `TIFALIBS_[CATEGORY]_[NAME]_LIB`
4. Use namespace `tifa_libs::[category]`
5. Create test in `test/cpv*/` with `#define PROBLEM "URL"`
6. Run `python manager.py test` for fast compilation check

### Testing Strategy

- **Fast test**: `python manager.py test` - compile all `src/` and `test/` files
- **Full verification**: GitHub Actions runs `competitive-verifier` on push
- **Manual verify**: `uv run oj-verify run` (requires `--group verify`)

### PDF Documentation

LaTeX notebook generated from code via:

```bash
python manager.py doc        # Generate .tex files
make download-fonts          # One-time font setup
latexmk -xelatex -shell-escape -file-line-error -8bit notebook.tex    # Compile (slow ~6 minutes)
```

Uses `minted` for syntax highlighting, requires `pygments` (`--group latex`).

## Integration Points

### competitive-verifier

- Config: `.verify-helper/`
- Runs verification workflow on included files: `src/`, `test/cpv/`, `test/cpv_local/`
- Generates documentation site pages at https://cplib.tifa-233.com/

### online-judge-verify-helper

- `oj-bundle` command for code expansion/bundling before OJ submission
- Auto-expands `#include` directives for submission

### TINplate

LaTeX template system for ICPC-style notebook generation. Class: `ICPCnotebook.cls`.

## Common Pitfalls

1. **Don't use standard types**: Use `i32`, `u32`, not `int`, `unsigned`
2. **Macro usage**: `flt_` is the standard loop pattern, not range-for when index needed
3. **Headers only**: No `.cpp` files in `src/`, everything is header-only
4. **PROBLEM define**: All test files MUST start with `#define PROBLEM "URL"`
5. **Namespace**: Never use `using namespace tifa_libs;` in headers, only in tests
6. **Test generation**: After modifying `.cppmeta`, run `python manager.py matrix` to regenerate
7. **Assert disabled**: `assert()` becomes no-op when `ONLINE_JUDGE` defined

## Build Configuration

From `Makefile`: GCC flags include `-Wall -Wextra -Wconversion -Wpedantic -Wparentheses -Wzero-as-null-pointer-constant -Wregister -Wvolatile -Wredundant-tags -Wmismatched-tags -Wstrict-null-sentinel -Woverloaded-virtual -Wenum-conversion -Wcomma-subscript -Wno-variadic-macros -Wno-extra-semi -Wno-useless-cast -fmax-errors=1`

Code must compile cleanly with these strict warnings.
