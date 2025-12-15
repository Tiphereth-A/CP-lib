# Contributing Guide

## Code Style

1. **Use existing utilities** from `include/util/*.hpp`
2. **Follow examples**: [qpow.hpp](https://github.com/Tiphereth-A/CP-lib/blob/master/include/math/qpow.hpp), [chrom_num.hpp](https://github.com/Tiphereth-A/CP-lib/blob/master/include/graph/chrom_num.hpp), [kmp.hpp](https://github.com/Tiphereth-A/CP-lib/blob/master/include/str/kmp.hpp)

### Language Requirements

| Language | Directories |
|----------|-------------|
| **English** | `*.md`, `include/*`, `doc_md/*`, `meta_test/*`, `test/*`, `tests/*` |
| **Simplified Chinese** | `*.tex`, `*.typ`, `cheatsheet/*`, `notebook/tex/*`, `notebook/typ/*`, `usage/*` |

## Directory Structure

| Directory | Purpose |
|-----------|---------|
| `include/` | C++ header files (algorithms & data structures) |
| `notebook/tex/` | LaTeX documentation (Chinese) |
| `notebook/typ/` | Typst documentation (Chinese) |
| `doc_md/` | Markdown documentation for competitive-verifier (English) |
| `usage/` | Usage examples |
| `test/` | Online judge verification tests |
| `cheatsheet/` | LaTeX cheatsheet sections |
| `template/` | PDF template files (LaTeX & Typst) |
| `config.yml` | Main configuration |
| `tcgen.yml` | Test matrix configuration |
| `libs/` | Python manager modules |
| `_gen/` | Generated content files |
| `_pdf_out/` | Compiled PDF output |

## Adding New Content

### New Implementation

```bash
python manager.py new
```

This creates:
- `include/<chapter>/<file>.hpp` - Code
- `notebook/tex/<chapter>/<file>.tex` - LaTeX documentation
- `notebook/typ/<chapter>/<file>.typ` - Typst documentation (empty, to be filled)
- `doc_md/<chapter>/<file>.md` - Verifier doc
- `usage/<chapter>/<file>.cpp` - Usage example

Then:
1. Implement your algorithm
2. Write documentation (images → `img/`, other files → `src/`)
3. Add tests in `test/` if applicable
4. Adjust ordering in `config.yml`

### New Cheatsheet

1. Write documentation in `cheatsheet/`
2. Add entry in `config.yml` under `cheatsheets:`

## Testing

```bash
python manager.py fmt           # Format code
python manager.py run-usage     # Run usage examples
python manager.py run           # Generate and compile notebook (LaTeX)
python manager.py run -t typ    # Generate and compile notebook (Typst)
pytest                          # Run Python tests
```

## Issues

Use GitHub Issues for bugs, documentation errors, feature requests, or questions.
