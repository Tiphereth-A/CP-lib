import re
from libs.decorator import with_logger


class TextTypstBase:
    def __init__(self, s: str):
        self._str: str = s.removesuffix('\n')

    def get(self) -> str:
        return self._str

    def get_label_name(self) -> str:
        return re.sub(r'[,.;@?!&$#/ ()*]', '-', self._str.casefold().replace('\\', ''))


class PathTypst(TextTypstBase):
    def __init__(self, path: str):
        super().__init__(path)
        # Typst uses forward slashes like LaTeX
        self._str = self._str.replace('\\', '/')


class NameTypst(TextTypstBase):
    def __init__(self, path: str):
        super().__init__(path)
        # Keep underscores in Typst (no need to escape like LaTeX)
        pass


@with_logger
def typst_include(path: PathTypst, **kwargs) -> list[str]:
    """Generate Typst include command."""
    return [f'#include "{path.get()}"\n', '\n']


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
    return [
        f'Path: `{path.get()}`\n\n',
        f'#raw(read("{path.get()}"), lang: "{file_type}")\n',
        '\n'
    ]


@with_logger
def typst_listing_code_range(path: PathTypst, file_type: str, begin: int, end: int, **kwargs) -> list[str]:
    """Generate Typst code listing command with line range."""
    # Typst doesn't have built-in line range support, so we'll read and slice
    return [
        f'Path: `{path.get()}`\n\n',
        f'#raw(read("{path.get()}").split("\\n").slice({begin - 1}, {end}).join("\\n"), lang: "{file_type}")\n',
        '\n'
    ]
