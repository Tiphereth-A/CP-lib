## First thing before contributing

Read `include/util/*.hpp`, use macros/traits/types/... from these header files wherever possible.

Here are some examples:

- [include/math/qpow.hpp](include/math/qpow.hpp)
- [include/graph/chrom_num.hpp](include/graph/chrom_num.hpp)
- [include/str/kmp.hpp](include/str/kmp.hpp)

## Language requirements

You should only use Simplified Chinese or English in this repository.

You should use Simplified Chinese in:

- `*.tex`
- `cheatsheet/*`
- `doc_tex/*`
- `usage/*`

You should use English in:

- `*.md`
- `include/*`
- `doc_md/*`
- `meta_test/*`
- `test/*`

If you have any trouble with this, please feel free to ask owner for help! ;)

## Build steps

You can use `manager.py` to create new files, lint files, generate necessary files to compile PDF and so on.

```
Usage: manager.py [OPTIONS] COMMAND [ARGS]...

Options:
  -l, --level [CRITICAL|ERROR|WARNING|INFO|DEBUG]
                                  log level
  --help                          Show this message and exit.

Commands:
  clean      Clean up nonessential files during PDF building
  fmt        Lint all codes
  gen-cs     Generate cheatsheet contents
  gen-nb     Generate notebook contents
  gentc      Generate test codes from test matrices
  new        Add new note
  run        Compile notebook
  run-usage  Run usage codes
```

If you want to add a new implementation, it is recommended to run `python manager.py new` and fill the required information, which will generate needed files automatically.

After you finished your changes, you can run `python manager.py run` to generate the printable document. This will lint all supported codes, compile codes in `usage/*`, link all TeX files for building PDF, and clean nonessential files after building. You can disable any procedure by options listed in help messages.

## Directories

Some folders have been given specific functions to make manage script works happy:

- Results of `python manager.py gen-cs` and `python manager.py gen-nb` are located in `_gen`,
- PDF file built by `python manager.py run` is located in `_pdf_out`.
