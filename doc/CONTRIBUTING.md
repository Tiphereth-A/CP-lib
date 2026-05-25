## Code Style Guidelines

1. **Use existing utilities**: Before writing new code, check `src/util/**/lib.hpp` for existing macros, traits and types
2. **Follow examples**: Look at existing implementations like:
    - [src/math/qpow/basic/lib.hpp](https://github.com/Tiphereth-A/CP-lib/blob/master/src/math/qpow/basic/lib.hpp)
    - [src/graph/cnt/chrom_num/lib.hpp](https://github.com/Tiphereth-A/CP-lib/blob/master/src/graph/cnt/chrom_num/lib.hpp)
    - [src/str/kmp/lib.hpp](https://github.com/Tiphereth-A/CP-lib/blob/master/src/str/kmp/lib.hpp)
3. See [AGENTS.md](../AGENTS.md) for some detailed instructions.

## Repository Architecture

See [ARCHITECTURE.md](ARCHITECTURE.md) for the directory layout and key files.

## Adding New Contents

### New Implementation

1. **Use the management script**:

    ```bash
    uv run python manager.py new
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
