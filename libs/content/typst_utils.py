import re

from libs.decorator import with_logger


class TextTypstBase:
    def __init__(self, s: str):
        self._str: str = s.removesuffix('\n')

    def __repr__(self) -> str:
        return f"{self.__class__.__name__}({self._str})"

    def get(self) -> str:
        return self._str

    def get_label_name(self) -> str:
        return re.sub(r'[,.;@?!&$#\\/ ()*<|>]', '-', self._str.casefold())


class PathTypst(TextTypstBase):
    def __init__(self, path: str):
        super().__init__(path)
        self._str = self._str.replace('\\', '/')


class NameTypst(TextTypstBase):
    def __init__(self, path: str):
        super().__init__(path)
        self._str = self._str.replace('_', ' ')


@with_logger
def typst_include(path: PathTypst, **kwargs) -> list[str]:
    return [f'#include "{path.get()}"\n', '\n']


@with_logger
def typst_label(prefix: str, name: TextTypstBase, **kwargs) -> list[str]:
    return [f'<{prefix}-{name.get_label_name()}>']


@with_logger
def typst_heading(name: NameTypst, path: PathTypst, level: int, **kwargs) -> list[str]:
    if level < 0 or level > 3:
        raise ValueError(f"Invalid heading level: {level}")
    MARKS = ['=', '==', '===', '====']
    LAB = ['ch', 'sec', 'ssec', 'sssec']
    return [f'{MARKS[level]} {name.get()} '] + typst_label(LAB[level], path) + ['\n', '\n']


@with_logger
def typst_listing_code_range(path: PathTypst, file_type: str, start: int, stop: int, **kwargs) -> list[str]:
    return [
        f'Path: `{path.get()}`',
        '\n\n',
        f'#raw(\n'
        f'  read("{path.get()}").split("\\n").slice({start - 1}, {stop}).join("\\n"),\n'
        f'  lang: "{file_type}",\n'
        f'  block: true,\n'
        f')\n',
        '\n'
    ]
