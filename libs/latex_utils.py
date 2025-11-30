import re
from libs.decorator import withlog


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


@withlog
def xelatex(file: str, **kwargs) -> list:
    return ['xelatex', "-synctex=1", "-interaction=nonstopmode", "-file-line-error", file + '.tex']


@withlog
def bibtex(file: str, **kwargs) -> list:
    return ['bibtex', file]


@withlog
def latexmk(file: str, **kwargs) -> list:
    return ['latexmk', '-cd', '-xelatex', '-file-line-error', '-halt-on-error', '-interaction=nonstopmode', '-shell-escape', '-synctex=1', '-outdir=_pdf_out', '-time', file + '.tex']


LATEX_COMPILE_COMMAND_GROUP: list = [latexmk]
# LATEX_COMPILE_COMMAND_GROUP: list = [xelatex, bibtex, xelatex, xelatex]


def _latex_command(command: str, *args) -> str:
    """Generate a LaTeX command string."""
    return rf"\{command}{{" + '}{'.join(args) + '}\n'


def _latex_command_with_option(command: str, option: str, *args) -> str:
    """Generate a LaTeX command string with options."""
    return rf"\{command}[{option}]{{" + '}{'.join(args) + '}\n'


@withlog
def latex_input(path: PathLaTeX, **kwargs) -> list[str]:
    """Generate LaTeX input command."""
    return [_latex_command('input', path.get()), '\n']


@withlog
def latex_label(prefix: str, name: TextLaTeXBase, **kwargs) -> list[str]:
    """Generate LaTeX label command."""
    return [_latex_command('label', f"{prefix}:{name.get_label_name()}")]


@withlog
def latex_chapter(name: NameLaTeX, **kwargs) -> list[str]:
    """Generate LaTeX chapter command."""
    return [_latex_command('chapter', name.get())] + latex_label('ch', name) + ['\n']


@withlog
def latex_section(name: NameLaTeX, **kwargs) -> list[str]:
    """Generate LaTeX section command."""
    return ['\n', _latex_command('section', name.get())] + latex_label('sec', name)


@withlog
def latex_listing_code(path: PathLaTeX, code_style: str, **kwargs) -> list[str]:
    """Generate LaTeX code listing command."""
    return [
        rf'Path: \verb|{path.get()}|',
        '\n\n',
        _latex_command('inputminted', code_style, path.get()),
        '\n'
    ]


@withlog
def latex_listing_code_range(path: PathLaTeX, code_style: str, begin: int, end: int, **kwargs) -> list[str]:
    """Generate LaTeX code listing command with line range."""
    return [
        rf'Path: \verb|{path.get()}|',
        '\n\n',
        _latex_command_with_option(
            'inputminted',
            rf'firstline={begin},lastline={end}',
            code_style,
            path.get()
        ),
        '\n'
    ]
