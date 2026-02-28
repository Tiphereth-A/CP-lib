import os
import re

from libs.decorator import with_logger
from libs.latex_utils import PathLaTeX, latex_listing_code_range
from libs.templates import TEMPLATE_CPVDOC_MD, TEMPLATE_DOC_TEX, TEMPLATE_DOC_TYP, TEMPLATE_LIB_HPP, TEMPLATE_USAGE_CPP
from libs.utils import EXT_TYPE_MP, TEMP_PATH


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
            f.write(TEMPLATE_CPVDOC_MD.format(
                name=self._name,
                path=self._dir.replace(os.sep, '/')
            ))
        with open(os.path.join(self._dir, "lib.hpp"), 'w', encoding='utf8') as f:
            f.write(TEMPLATE_LIB_HPP.format(
                path_upper='_'.join(self._dir.split(os.sep)[1:]).upper(),
                category=self._dir.split(os.sep)[1]
            ))
        with open(os.path.join(self._dir, "doc.tex"), 'w', encoding='utf8') as f:
            f.write(TEMPLATE_DOC_TEX)
        with open(os.path.join(self._dir, "doc.typ"), 'w', encoding='utf8') as f:
            f.write(TEMPLATE_DOC_TYP)
        with open(os.path.join(self._dir, "usage.cpp"), 'w', encoding='utf8') as f:
            f.write(TEMPLATE_USAGE_CPP)

    @with_logger
    def expand_tex(self, **kwargs):
        src_list = self._get_src_list()
        doc_template_path = os.path.join(self._dir, "doc.tex")
        if "doc.tex" not in src_list:
            raise FileNotFoundError(f"{doc_template_path} not found")
        src_list.remove("doc.tex")

        result_path = os.path.join(TEMP_PATH, self._dir, "doc.tex")
        os.makedirs(os.path.dirname(result_path), exist_ok=True)
        with open(result_path, 'w', encoding='utf8') as f_result:
            content: str = ''
            with open(doc_template_path, 'r', encoding='utf8') as f:
                content = f.read()
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
                            EXT_TYPE_MP[os.path.splitext(file)[1]],
                            start,
                            stop)))
            f_result.write(content)

    @with_logger
    def expand_typ(self, **kwargs):
        assert False, "Not implemented yet"
