# Manager System

CLI framework built with [Click](https://click.palletsprojects.com/) for managing CP-lib.

## Architecture

```
libs/
├── cli.py                # CLI entry point
├── consts.py             # Global constants
├── decorator.py          # @with_logger, @with_timer
├── latex_utils.py        # LaTeX generation
├── typst_utils.py        # Typst generation
├── testcase_matrix.py    # Test matrix parsing
├── utils.py              # Utility functions
├── classes/
│   ├── config.py         # Main configuration
│   ├── config_tcgen.py   # Test generation config
│   ├── decorator_result_handler.py
│   └── section.py        # Section representation
└── commands/
    ├── clean.py          # Clean temp files
    ├── compile_pdf.py    # Compile PDF
    ├── fmt.py            # Format code
    ├── gen_cs.py         # Generate cheatsheet
    ├── gen_nb.py         # Generate notebook
    ├── gentc.py          # Generate test codes
    ├── new.py            # Create new section
    └── run_usage.py      # Run usage examples
```

## Commands

| Command | Description |
|---------|-------------|
| `clean` | Remove temporary files from `_pdf_out/` |
| `gen-nb [-t typ]` | Generate notebook contents (LaTeX/Typst) |
| `gen-cs [-t typ]` | Generate cheatsheet contents |
| `run-usage [-t cpp] [-l 8]` | Run usage examples in parallel |
| `run [-t typ] [--no-fmt] [--no-run-usage] [--no-gen] [--no-clean]` | Full compile workflow |
| `fmt [-t cpp]` | Format code files |
| `new` | Create new implementation (interactive) |
| `gentc [-s meta_test] [-t test]` | Generate test codes from `.cppmeta` |

### Compile Workflow (`run`)

1. Format code (`fmt`)
2. Run usage examples (`run-usage`)
3. Generate contents (`gen-nb`, `gen-cs`)
4. Compile PDF (LaTeX or Typst)
5. Clean temp files (`clean`)

## Core Components

### Decorators

```python
@with_logger
@with_timer
def my_command(**kwargs):
    logger = kwargs.get('logger')
    logger.info('Working...')
```

- `@with_logger` - Injects logger, logs entry/exit
- `@with_timer` - Measures execution time

### Configuration

- `Config` (`config.yml`) - Directories, chapters, sections, commands
- `ConfigTCGen` (`tcgen.yml`) - Test matrix generation

### Utilities

| Module | Purpose |
|--------|---------|
| `latex_utils.py` | LaTeX: `\chapter`, `\section`, `\inputminted` |
| `typst_utils.py` | Typst: headings, `#include`, code blocks |
| `utils.py` | File operations, scanning, deduplication |
| `testcase_matrix.py` | Parse `.cppmeta` files |

## Extension

### Adding a Command

1. Create `libs/commands/my_command.py`:

```python
from libs.decorator import with_logger

@with_logger
def my_command_logic(param, **kwargs):
    logger = kwargs.get('logger')
    logger.info(f"Processing {param}")

def register_my_command(cli):
    @cli.command('my-command')
    @click.option('--param', required=True)
    def _my_command(param):
        """My command description"""
        my_command_logic(param)
```

2. Register in `libs/cli.py`:

```python
from libs.commands.my_command import register_my_command
register_my_command(cli)
```

### Adding Configuration

1. Add to `config.yml`
2. Add getter in `libs/classes/config.py`
3. Use via `from libs.consts import CONFIG`

## Testing

See [tests/README.md](../tests/README.md) for test suite documentation.

```bash
pytest                    # All tests
pytest -m unit            # Unit tests only
pytest --cov=libs         # With coverage
```

## Guidelines

- **Style**: PEP 8, type hints
- **Logging**: DEBUG/INFO/WARNING/ERROR/CRITICAL
- **Testing**: Test edge cases, use fixtures
- **Performance**: Cache config, use threading for parallel ops

