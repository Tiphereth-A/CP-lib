import os
import re

from libs.decorator import with_logger
from libs.content.latex_utils import PathLaTeX, latex_listing_code_range

_EXT_TYPE: dict[str, str] = {
    '.md': 'markdown',
    '.tex': 'tex',
    '.typ': 'typst',
    '.hpp': 'cpp',
    '.cpp': 'cpp',
    '.py': 'py'
}
_TYPE_EXT: dict[str, list[str]] = {}
for _ext, _type in _EXT_TYPE.items():
    _TYPE_EXT.setdefault(_type, []).append(_ext)


_TEMPLACES = {
    "cpvdoc.md": """---
title: {name}
documentation_of: ./{path}/lib.hpp
---
""",
    "doc.tex": """% {lib.hpp,start=3}
% {usage.cpp,start=2}
""",
    "doc.typ": """// {lib.hpp,start=3}
// {usage.cpp,start=2}
""",
    "lib.hpp": """#pragma once

namespace tifa_libs {
}  // namespace tifa_libs
""",
    "usage.cpp": """// competitive-verifier: DISPLAY never
// cplib.manager: PROBLEM https://example.com

#include "lib.hpp"

int main() {
}

/*
description
*/

/*sample
input
========
output
*/
"""
}


class Section:
    def __init__(self, dir: str, title: str):
        self._dir = dir
        self._name = os.path.basename(dir)
        self._title = title

    def __repr__(self) -> str:
        return f"Section(name={self._name}, title={self._title}, dir={self._dir})"

    def _get_src_list(self) -> set[str]:
        return set(os.listdir(self._dir))

    @with_logger
    def init_files(self, **kwargs):
        with open(os.path.join(self._dir, "cpvdoc.md"), 'w', encoding='utf8') as f:
            f.write(_TEMPLACES["cpvdoc.md"].format(
                name=self._name,
                path=self._dir.replace(os.sep, '/')
            ))
        for _type in ["lib.hpp", "doc.tex", "doc.typ", "usage.cpp"]:
            with open(os.path.join(self._dir, _type), 'w', encoding='utf8') as f:
                f.write(_TEMPLACES[_type])

    @with_logger
    def expand_tex(self, temp_path: str, **kwargs):
        src_list = self._get_src_list()
        custom_doc = "doc.tex" in src_list
        if custom_doc:
            src_list.remove("doc.tex")

        result_path = os.path.join(temp_path, self._dir, "doc.tex")
        os.makedirs(os.path.dirname(result_path), exist_ok=True)
        with open(result_path, 'w', encoding='utf8') as f_result:
            content: str = _TEMPLACES["doc.tex"] if not custom_doc else open(
                os.path.join(self._dir, "doc.tex"), 'r', encoding='utf8').read()
            for file in src_list:
                pattern = re.compile(
                    r'% \{' + re.escape(file) + r'(?:,start=(-?\d+))?(?:,stop=(-?\d+))?\}')
                total_lines: int = 0
                with open(os.path.join(self._dir, file), 'rb') as f:
                    total_lines = sum(1 for _ in f)

                while True:
                    match = pattern.search(content)
                    if not match:
                        break
                    start, stop = 1, total_lines
                    if match.group(1):
                        start = int(match.group(1))
                    if match.group(2):
                        stop = int(match.group(2))
                        if stop <= 0:
                            stop = total_lines + stop
                    content = content.replace(
                        match.group(0),
                        ''.join(latex_listing_code_range(
                            PathLaTeX(os.path.join(self._dir, file)),
                            _EXT_TYPE[os.path.splitext(file)[1]],
                            start,
                            stop)))
            f_result.write(content)

    @with_logger
    def expand_typ(self, temp_path: str, **kwargs):
        assert False, "Not implemented yet"
