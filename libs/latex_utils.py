import re
from libs.decorator import with_logger


class TextLaTeXBase:
    def __init__(self, s: str):
        self._str: str = s.removesuffix('\n')

    def get(self) -> str:
        return self._str

    def get_label_name(self) -> str:
        return re.sub(r'[,.;@?!&$#/ ()*]', '-', self._str.casefold().replace('\\', ''))


class PathLaTeX(TextLaTeXBase):
    def __init__(self, path: str):
        super().__init__(path)
        self._str = self._str.replace('\\', '/')


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
    return [_latex_command('input', _latex_command('fixpath', path.get()).rstrip()), '\n']


@with_logger
def latex_label(prefix: str, name: TextLaTeXBase, **kwargs) -> list[str]:
    """Generate LaTeX label command."""
    return [_latex_command('label', f"{prefix}:{name.get_label_name()}")]


@with_logger
def latex_chapter(name: NameLaTeX, **kwargs) -> list[str]:
    """Generate LaTeX chapter command."""
    return [_latex_command('chapter', name.get())] + latex_label('ch', name) + ['\n']


@with_logger
def latex_section(name: NameLaTeX, **kwargs) -> list[str]:
    """Generate LaTeX section command."""
    return ['\n', _latex_command('section', name.get())] + latex_label('sec', name)


@with_logger
def latex_listing_code(path: PathLaTeX, file_type: str, **kwargs) -> list[str]:
    """Generate LaTeX code listing command."""
    return [
        rf'Path: \verb|{path.get()}|',
        '\n\n',
        _latex_command(
            'inputminted',
            file_type,
            _latex_command('fixpath', path.get()).rstrip()
        ),
        '\n'
    ]


@with_logger
def latex_listing_code_range(path: PathLaTeX, file_type: str, begin: int, end: int, **kwargs) -> list[str]:
    """Generate LaTeX code listing command with line range."""
    return [
        rf'Path: \verb|{path.get()}|',
        '\n\n',
        _latex_command_with_option(
            'inputminted',
            rf'firstline={begin},lastline={end}',
            file_type,
            _latex_command('fixpath', path.get()).rstrip()
        ),
        '\n'
    ]
