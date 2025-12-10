import re
import os
from libs.decorator import with_logger


class TextTypstBase:
    def __init__(self, s: str):
        self._str: str = s.removesuffix('\n')

    def get(self) -> str:
        return self._str

    def get_label_name(self) -> str:
        # Clean LaTeX commands and special characters for use in labels
        # Remove backslashes, quotes that are not valid in labels
        # Replace punctuation and special chars with hyphens for readability
        cleaned = self._str.replace('\\', '').replace('"', '').replace("'", '')
        return re.sub(r'[,.;@?!&$#/ ()*<>]', '-', cleaned.casefold())


class PathTypst(TextTypstBase):
    def __init__(self, path: str):
        super().__init__(path)
        # Typst uses forward slashes like LaTeX
        self._str = self._str.replace('\\', '/')


class NameTypst(TextTypstBase):
    def __init__(self, path: str):
        super().__init__(path)
        # Clean up LaTeX escape sequences for Typst
        # Remove LaTeX escape sequences like \"
        self._str = self._str.replace(r'\"', '')
        # Handle other common LaTeX escapes
        self._str = self._str.replace(r'\o', 'o')
        self._str = self._str.replace(r"\'", '')
        # Escape special Typst markdown characters in text
        # Using raw strings to avoid interpretation
        self._str = self._str.replace('*', r'\*')
        self._str = self._str.replace('_', r'\_')
        self._str = self._str.replace('`', r'\`')


# File extensions that Typst cannot include (LaTeX-specific files)
LATEX_ONLY_EXTENSIONS = ('.tex',)

@with_logger
def typst_include(path: PathTypst, **kwargs) -> list[str]:
    """Generate Typst include command."""
    # Note: If the file is a LaTeX file, we skip it since Typst can't include LaTeX
    # Users should provide .typ files for documentation
    if path.get().endswith(LATEX_ONLY_EXTENSIONS):
        return [f'// LaTeX doc file skipped: {path.get()}\n', '\n']
    
    # Check if the .typ file exists in the _gen directory
    # The path is relative to the working directory where typst will be run
    check_path = path.get()
    if not os.path.exists(check_path):
        return [f'// Documentation file not found (skipped): {path.get()}\n', '\n']
    
    return [f'#include "../{path.get()}"\n', '\n']


@with_logger
def typst_label(prefix: str, name: TextTypstBase, **kwargs) -> list[str]:
    """Generate Typst label command."""
    return [f' <{prefix}:{name.get_label_name()}>\n']


@with_logger
def typst_heading(name: NameTypst, level: int = 1, **kwargs) -> list[str]:
    """Generate Typst heading command."""
    heading_prefix = '=' * level
    return [f'{heading_prefix} {name.get()}'] + typst_label('sec' if level > 1 else 'ch', name) + ['\n']


@with_logger
def typst_chapter(name: NameTypst, **kwargs) -> list[str]:
    """Generate Typst chapter heading."""
    return typst_heading(name, level=1)


@with_logger
def typst_section(name: NameTypst, **kwargs) -> list[str]:
    """Generate Typst section heading."""
    return ['\n'] + typst_heading(name, level=2)


@with_logger
def typst_listing_code(path: PathTypst, file_type: str, **kwargs) -> list[str]:
    """Generate Typst code listing command."""
    # Use fixpath function to adjust path relative from _gen/ directory
    return [
        f'Path: `{path.get()}`\n\n',
        f'#raw(read(fixpath("{path.get()}")), lang: "{file_type}")\n',
        '\n'
    ]


@with_logger
def typst_listing_code_range(path: PathTypst, file_type: str, begin: int, end: int, **kwargs) -> list[str]:
    """Generate Typst code listing command with line range."""
    # Typst doesn't have built-in line range support, so we'll read and slice
    # Use fixpath function to adjust path relative from _gen/ directory
    return [
        f'Path: `{path.get()}`\n\n',
        f'#raw(read(fixpath("{path.get()}")).split("\n").slice({begin - 1}, {end}).join("\n"), lang: "{file_type}")\n',
        '\n'
    ]
