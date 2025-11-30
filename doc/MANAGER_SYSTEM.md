# Python Manager System Documentation

The Python Manager System is a modular command-line interface (CLI) framework built with [Click](https://click.palletsprojects.com/) that provides comprehensive management capabilities for the CP-lib project. It handles tasks such as:

- Code formatting and linting
- LaTeX notebook generation and compilation
- Test code generation from templates
- Usage example compilation and execution
- File cleanup and maintenance

### Key Features

- **Modular Architecture**: Each command is isolated in its own module
- **Unified Logging**: Colored, structured logging using `coloredlogs`
- **Configuration-Driven**: YAML-based configuration system
- **Extensible**: Easy to add new commands and functionality

## Architecture

### Directory Structure

```
libs/
├── __init__.py
├── cli.py                    # Main CLI entry point and command registration
├── consts.py                 # Global constants and configuration instances
├── decorator.py              # Decorators (e.g., @withlog)
├── latex_utils.py            # LaTeX generation utilities
├── testcase_matrix.py        # Test matrix parsing and generation
├── utils.py                  # General utility functions
├── classes/                  # Class definitions
│   ├── __init__.py
│   ├── config.py             # Main configuration class
│   ├── config_tcgen.py       # Test case generation config
│   └── section.py            # Section representation
└── commands/                 # Command modules
    ├── __init__.py
    ├── clean.py              # Clean temporary files
    ├── compile.py            # Compile LaTeX notebook
    ├── fmt.py                # Format/lint code files
    ├── gen_cs.py             # Generate cheatsheet contents
    ├── gen_nb.py             # Generate notebook contents
    ├── gentc.py              # Generate test codes
    ├── new.py                # Create new note/section
    └── run_usage.py          # Run usage examples
```

### Entry Point

The system entry point is `manager.py`, which is a thin wrapper that imports and invokes the CLI from `libs.cli`:

```python
#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""Main entry point for the CLI manager."""

from libs.cli import cli

if __name__ == '__main__':
    cli()
```

### CLI Initialization

The CLI is initialized in `libs/cli.py` with:

1. **Click Group**: Main command group with logging level option
2. **Colored Logging**: Configured with custom styles and formats
3. **Command Registration**: All commands are registered at module load time

```python
@click.group()
@click.option('-l', '--level', type=click.Choice([...]), default='INFO')
def cli(level: str):
    coloredlogs.install(level=level, ...)
```

## Command System

### Command Module Structure

Each command module follows a consistent pattern:

1. **Core Function**: The main logic function decorated with `@withlog`
2. **Registration Function**: A function that registers the command with the CLI
3. **Helper Functions**: Private functions for internal use

**Example**: Clean Command

```python
"""Clean command for removing nonessential files."""

import logging
import os

from libs.consts import CLEAN_EXT_NAME
from libs.decorator import withlog
from libs.utils import get_full_filenames


@withlog
def clean(logger: logging.Logger):
    """Clean up nonessential files during PDF building."""
    for full_filename in get_full_filenames(['_pdf_out'], CLEAN_EXT_NAME):
        os.remove(full_filename)
        logger.info(f"{full_filename} removed successfully")


def register_clean_command(cli):
    """Register the clean command with the CLI."""
    @cli.command('clean')
    def _clean():
        """Clean up nonessential files during PDF building"""
        clean()
```

### Available Commands

#### `clean` - Clean Temporary Files

**Purpose**: Remove nonessential files generated during PDF compilation.

**Location**: `libs/commands/clean.py`

**Usage**:

```bash
python manager.py clean
```

**Functionality**:

- Scans `_pdf_out/` directory
- Removes files with extensions in `CLEAN_EXT_NAME` (`.aux`, `.log`, `.toc`, etc.)
- Logs each removed file

#### `gen-nb` - Generate Notebook Contents

**Purpose**: Generate LaTeX content file for the main notebook from code, documentation, and usage files.

**Location**: `libs/commands/gen_nb.py`

**Usage**:

```bash
python manager.py gen-nb
```

**Functionality**:

- Scans chapters from `config.yml`
- For each chapter:
  - Loads sections from config
  - Discovers sections from filesystem (code, doc, usage files)
  - Merges and deduplicates sections
  - Generates LaTeX sections with:
    - Documentation input
    - Code listings (with special handling for `.hpp` header guards)
    - Usage examples (if enabled and non-empty)
- Writes to `_gen/contents_notebook.tex`

**Key Functions**:

- `load_from()`: Load and parse filenames from a directory
- `generate_notebook_contents()`: Main generation logic
- `_write_chapter()`: Write chapter and its sections
- `_generate_sections_from_files()`: Auto-discover sections from filesystem
- `_write_section()`: Write individual section with code and docs

#### `gen-cs` - Generate Cheatsheet Contents

**Purpose**: Generate LaTeX content file for the cheatsheet from configured cheatsheet files.

**Location**: `libs/commands/gen_cs.py`

**Usage**:

```bash
python manager.py gen-cs
```

**Functionality**:

- Reads cheatsheet names from `config.yml`
- Scans `cheatsheet/` directory for `.tex` files
- Merges configured and existing files
- Generates LaTeX chapter and sections
- Writes to `_gen/contents_cheatsheet.tex`

#### `run-usage` - Run Usage Examples

**Purpose**: Compile and execute all usage example files in parallel.

**Location**: `libs/commands/run_usage.py`

**Usage**:

```bash
python manager.py run-usage
python manager.py run-usage -t cpp -l 8
```

**Options**:

- `-t, --code-type`: Code type (default: `cpp`)
- `-l, --thlimit`: Thread limit (default: `8`)

**Functionality**:
- Scans `usage/` directory for files with specified extensions
- Filters out empty files
- Distributes files across multiple threads
- Compiles and runs each file using commands from config
- Logs progress per thread

#### `run` - Compile Notebook

**Purpose**: Complete workflow to compile the LaTeX notebook into PDF.

**Location**: `libs/commands/compile.py`

**Usage**:

```bash
python manager.py run
python manager.py run --no-fmt --no-run-usage
```

**Options**:

- `--no-fmt`: Skip code formatting
- `--no-run-usage`: Skip running usage examples
- `--no-gen`: Skip generating contents
- `--no-clean`: Skip cleaning temporary files

**Workflow**:

1. Format code (if not `--no-fmt`)
2. Run usage examples (if not `--no-run-usage`)
3. Generate notebook and cheatsheet contents (if not `--no-gen`)
4. Compile LaTeX using commands from `LATEX_COMPILE_COMMAND_GROUP`
5. Clean temporary files (if not `--no-clean`)

**Dependencies**: Calls other commands (`fmt`, `run-usage`, `gen-nb`, `gen-cs`, `clean`)

#### `fmt` - Format Code

**Purpose**: Format/lint all code files of a specified type.

**Location**: `libs/commands/fmt.py`

**Usage**:

```bash
python manager.py fmt
python manager.py fmt -t cpp
```

**Options**:

- `-t, --code-type`: Code type (default: `cpp`)

**Functionality**:

- Scans multiple directories (code, doc, cheatsheet, usage)
- Finds files with extensions matching the code type
- Runs formatting command from config for each file
- Uses `subprocess` to execute formatting tools (e.g., `clang-format`)

#### `new` - Create New Note

**Purpose**: Create a new algorithm implementation with all required files.

**Location**: `libs/commands/new.py`

**Usage**:

```bash
python manager.py new
```

**Prompts**:

- Chapter name (e.g., `graph`, `math`, `ds`)
- File name (without extension)
- Section title (for notebook)
- Code file extension (default: `hpp`)
- Usage file extension (default: `cpp`)

**Functionality**:

- Creates `Section` object
- Creates all required files:
  - Code file: `include/{chapter}/{file}.{code_ext}`
  - Doc file: `doc_tex/{chapter}/{file}.tex`
  - CVDoc file: `doc_md/{chapter}/{file}.md`
  - Usage file: `usage/{chapter}/{file}.{usage_ext}`
- Updates `config.yml` with new section
- Generates initial CVDoc content with metadata

#### `gentc` - Generate Test Codes

**Purpose**: Generate test code files from `.cppmeta` template files.

**Location**: `libs/commands/gentc.py`

**Usage**:

```bash
python manager.py gentc
python manager.py gentc -s meta_test -t test
```

**Options**:

- `-s, --source-dir`: Source directory (default: `meta_test`)
- `-t, --target-dir`: Target directory (default: `test`)

**Functionality**:

- Scans source directory for `.cppmeta` files
- Removes previously generated files (marked with `#define AUTO_GENERATED`)
- Parses each `.cppmeta` file using `cppmeta_parser`
- Generates multiple test variants based on test matrix
- Writes generated files to target directory

## Core Components

### Logging System

The system uses a custom `@withlog` decorator that:

1. Creates a logger named after the function
2. Injects the logger as a `logger` keyword argument
3. Logs function entry/exit with debug level
4. Logs return values (if any)

**Usage**:

```python
@withlog
def my_function(arg1, arg2, **kwargs):
    logger = kwargs.get('logger')
    logger.info("Processing...")
    return result
```

**Colored Output**: Configured in `cli.py` with custom styles for different log levels.

### Configuration System

#### Main Configuration (`libs/classes/config.py`)

The `Config` class loads settings from `config.yml` and provides methods to:

- Get directory paths (code, doc, usage, cheatsheet, etc.)
- Get chapter and section definitions
- Get code style settings
- Get compilation and formatting commands
- Manage sections (append, get by chapter, etc.)

**Key Methods**:

- `get_code_dir()`: Returns code directory path
- `get_chapter_key()`: Returns list of chapter keys
- `get_sections_by_chapter(chapter)`: Returns sections for a chapter
- `get_code_style(ext)`: Returns LaTeX code style for extension
- `get_formatting_command(code_type, filepath)`: Returns formatting command
- `get_run_usage_command(code_type, filepath)`: Returns compilation command

#### Test Case Generation Config (`libs/classes/config_tcgen.py`)

The `ConfigTCGen` class loads settings from `tcgen.yml` for test matrix generation.

### Constants (`libs/consts.py`)

Global constants and singleton instances:

- `CONFIG`: Main configuration instance
- `CONFIG_TCGEN`: Test case generation config instance
- `CONTENTS_DIR`: Directory for generated content files
- `CONTENTS_NB`: Path to notebook contents file
- `CONTENTS_CS`: Path to cheatsheet contents file
- `CLEAN_EXT_NAME`: List of file extensions to clean

### Section Class (`libs/classes/section.py`)

Represents a notebook section with:

- Chapter name
- File name (base name without extension)
- Section title
- Code file extension
- Usage file extension

**Methods**:

- `get_filenames(code_dir, doc_dir, cvdoc_dir, usage_dir)`: Returns full paths
- `open(...)`: Opens all section files with specified mode

### LaTeX Utilities (`libs/latex_utils.py`)

Provides functions to generate LaTeX commands:

- `latex_chapter(name)`: Generate `\chapter{...}`
- `latex_section(name)`: Generate `\section{...}`
- `latex_input(path)`: Generate `\input{...}`
- `latex_listing_code(path, style)`: Generate `\inputminted{...}`
- `latex_listing_code_range(path, style, begin, end)`: Generate with line range

**Classes**:

- `PathLaTeX`: Normalizes paths for LaTeX (converts `\` to `/`)
- `NameLaTeX`: Formats names for LaTeX (replaces `_` with spaces)

**Compilation Commands**:

- `LATEX_COMPILE_COMMAND_GROUP`: List of compilation procedures
- Currently uses `latexmk` for single-pass compilation

## Utilities and Helpers

### File Operations (`libs/utils.py`)

#### `get_full_filenames(dirs, valid_extname)`

Recursively finds all files with valid extensions in given directories.

**Parameters**:

- `dirs`: List of directory paths
- `valid_extname`: List of valid extensions (e.g., `['cpp', 'hpp']`)

**Returns**: List of full file paths

#### `scandir_file_merge(valid_ext_name, *paths)`

Scans directories and returns unique filenames with valid extensions.

**Parameters**:

- `valid_ext_name`: Iterable of valid extensions
- `*paths`: Variable number of directory paths

**Returns**: List of filenames (not full paths)

#### `scandir_dir_merge(*paths)`

Scans directories and returns unique directory names.

**Returns**: List of directory names

#### `file_preprocess(files_in_config, files_exist, logger)`

Merges configured files with existing files, removing duplicates and warning about missing files.

**Parameters**:

- `files_in_config`: List of filenames from config
- `files_exist`: List of existing filenames
- `logger`: Logger instance

**Returns**: Merged and deduplicated list

#### `parse_filename(filename)`

Parses filename into base name and extension.

**Returns**: Tuple of `(name_without_ext, extension)`

#### `unique(seq, hash_func)`

Removes duplicates from sequence while preserving order.

**Parameters**:

- `seq`: Input sequence
- `hash_func`: Function to generate hash key (default: identity)

**Returns**: List with duplicates removed

### Test Case Matrix (`libs/testcase_matrix.py`)

Provides `cppmeta_parser` for parsing `.cppmeta` files and generating test variants based on test matrices defined in `tcgen.yml`.

## Extension Guide

### Adding a New Command

1. **Create Command Module**: Create `libs/commands/my_command.py`

    ```python
    """My custom command."""

    import logging
    import click

    from libs.decorator import withlog


    @withlog
    def my_command_logic(param1: str, param2: int, **kwargs):
        """Main command logic."""
        logger = kwargs.get('logger')
        logger.info(f"Processing {param1} with {param2}")
        # Your logic here


    def register_my_command(cli):
        """Register the command with the CLI."""
        @cli.command('my-command')
        @click.option('--param1', type=str, required=True)
        @click.option('--param2', type=int, default=10)
        def _my_command(param1: str, param2: int):
            """Description of my command"""
            my_command_logic(param1, param2)
    ```

2. **Register in CLI**: Add to `libs/cli.py`

    ```python
    from libs.commands.my_command import register_my_command

    # In the registration section:
    register_my_command(cli)
    ```

3. **Test**: Run your command

    ```bash
    python manager.py my-command --param1 value --param2 20
    ```

### Adding Configuration Options

1. **Update `config.yml`**: Add your configuration keys
2. **Extend `Config` class**: Add getter methods in `libs/classes/config.py`

```python
def get_my_setting(self) -> str:
    """Get my custom setting."""
    return self._config['my_section']['my_setting']
```

3. **Use in Commands**: Import `CONFIG` from `libs.consts`

```python
from libs.consts import CONFIG

value = CONFIG.get_my_setting()
```

### Adding Utility Functions

1. **Add to `libs/utils.py`**: For general-purpose utilities
2. **Create new module**: For domain-specific utilities (e.g., `latex_utils.py`)

## Development Guidelines

### Code Style

- Follow PEP 8 style guide
- Use type hints for function parameters and return types
- Use descriptive variable and function names
- Keep functions focused and single-purpose

### Logging

- Use appropriate log levels:
  - `DEBUG`: Detailed information for debugging
  - `INFO`: General informational messages
  - `WARNING`: Warning messages (non-critical issues)
  - `ERROR`: Error messages (operation failures)
  - `CRITICAL`: Critical errors (system failures)

### Error Handling

- Use specific exceptions (e.g., `FileNotFoundError`, `KeyError`)
- Log errors with context before raising
- Provide helpful error messages to users

### Testing

- Test commands individually
- Use `--level DEBUG` for detailed logging during development
- Verify file operations with test directories
- Test error cases (missing files, invalid config, etc.)

### Documentation

- Document all public functions and classes
- Include usage examples in docstrings
- Update this document when adding new features

### Performance

- Use efficient file scanning (avoid redundant directory walks)
- Cache configuration values when possible
- Use threading for parallel operations (e.g., `run-usage`)
- Consider memory usage for large file operations

## Future Enhancements

Potential improvements to the manager system:

1. **Plugin System**: Allow external plugins to register commands
2. **Configuration Validation**: Validate config files on startup
3. **Dry-Run Mode**: Preview operations without executing
4. **Progress Bars**: Add progress indicators for long operations
5. **Parallel Generation**: Parallelize notebook generation
6. **Caching**: Cache file scans and configuration parsing
7. **Unit Tests**: Add comprehensive test suite
8. **Type Checking**: Add `mypy` type checking

## References

- [Click Documentation](https://click.palletsprojects.com/)
- [Coloredlogs Documentation](https://coloredlogs.readthedocs.io/)
- [Python Logging](https://docs.python.org/3/library/logging.html)
- [YAML Specification](https://yaml.org/spec/)

