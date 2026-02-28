import os
import re
from libs.decorator import with_logger


class TextLaTeXBase:
    def __init__(self, s: str):
        self._str: str = s.removesuffix('\n')

    def __repr__(self) -> str:
        return f"{self.__class__.__name__}({self._str})"

    def get(self) -> str:
        return self._str

    def get_label_name(self) -> str:
        return re.sub(r'[,.;@?!&$#/ ()*<|>]', '-', self._str.casefold().replace(os.sep, ''))


class PathLaTeX(TextLaTeXBase):
    def __init__(self, path: str):
        super().__init__(path)
        self._str = self._str.replace(os.sep, '/')


class NameLaTeX(TextLaTeXBase):
    def __init__(self, path: str):
        super().__init__(path)
        self._str = self._str.replace(r'_', r' ')


def _latex_command(command: str, *args) -> str:
    """Generate a LaTeX command string."""
    return rf"\{command}{{" + '}{'.join(args) + '}\n'


def _latex_command_with_option(command: str, option: str, *args) -> str:
    """Generate a LaTeX command string with options."""
    return rf"\{command}[{option}]{{" + '}{'.join(args) + '}\n'


@with_logger
def latex_input(path: PathLaTeX, **kwargs) -> list[str]:
    """Generate LaTeX input command."""
    return [_latex_command('input', path.get()), '\n']


@with_logger
def latex_label(prefix: str, name: TextLaTeXBase, **kwargs) -> list[str]:
    """Generate LaTeX label command."""
    return [_latex_command('label', f"{prefix}:{name.get_label_name()}")]


@with_logger
def latex_section(name: NameLaTeX, path: PathLaTeX, level: int, **kwargs) -> list[str]:
    """Generate LaTeX section command."""
    if level < 0 or level > 3:
        raise ValueError(f"Invalid section level: {level}")
    CMD: list[str] = ['chapter', 'section', 'subsection', 'subsubsection']
    LAB: list[str] = ['ch', 'sec', 'ssec', 'sssec']
    return [_latex_command(CMD[level], name.get())] + latex_label(LAB[level], path) + ['\n']


@with_logger
def latex_listing_code(path: PathLaTeX, file_type: str, **kwargs) -> list[str]:
    """Generate LaTeX code listing command."""
    return [
        rf'Path: \verb|{path.get()}|',
        '\n\n',
        _latex_command(
            'inputminted',
            file_type,
            path.get()
        ),
        '\n'
    ]


@with_logger
def latex_listing_code_range(path: PathLaTeX, file_type: str, start: int, stop: int, **kwargs) -> list[str]:
    """Generate LaTeX code listing command with line range."""
    return [
        rf'Path: \verb|{path.get()}|',
        '\n\n',
        _latex_command_with_option(
            'inputminted',
            rf'firstline={start},lastline={stop}',
            file_type,
            path.get()
        ),
        '\n'
    ]
