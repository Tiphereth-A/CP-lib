import os
import pytest
from libs.content.latex_utils import (
    TextLaTeXBase, PathLaTeX, NameLaTeX,
    latex_input, latex_label, latex_section, latex_listing_code,
    latex_listing_code_range
)


@pytest.mark.unit
class TestTextLaTeXBase:
    def test_get_strips_newline(self):
        obj = TextLaTeXBase("hello\n")
        assert obj.get() == "hello"

    def test_get_no_newline(self):
        obj = TextLaTeXBase("hello")
        assert obj.get() == "hello"

    def test_repr(self):
        obj = TextLaTeXBase("test")
        assert repr(obj) == "TextLaTeXBase(test)"

    def test_get_label_name_replaces_specials(self):
        obj = TextLaTeXBase("Hello World, (foo)")
        label = obj.get_label_name()
        assert label == 'hello-world---foo-'

    def test_get_label_name_casefold(self):
        obj = TextLaTeXBase("UPPER")
        assert obj.get_label_name() == "upper"

    def test_get_label_name_sep(self):
        s = f"path{os.sep}file"
        obj = TextLaTeXBase(s)
        label = obj.get_label_name()
        assert label == 'path-file'


@pytest.mark.unit
class TestPathLaTeX:
    def test_backslash_converted(self):
        obj = PathLaTeX("src\\foo\\bar.hpp")
        assert obj.get() == "src/foo/bar.hpp"

    def test_no_op_on_forward_slash(self):
        obj = PathLaTeX("src/foo/bar.hpp")
        assert obj.get() == "src/foo/bar.hpp"


@pytest.mark.unit
class TestNameLaTeX:
    def test_underscore_replaced_with_space(self):
        obj = NameLaTeX("hello_world_test")
        assert obj.get() == "hello world test"

    def test_no_underscore_unchanged(self):
        obj = NameLaTeX("hello")
        assert obj.get() == "hello"


@pytest.mark.unit
class TestLatexInput:
    def test_returns_list(self):
        result = latex_input(PathLaTeX("src/foo.tex"))
        assert isinstance(result, list)
        assert len(result) == 2
        assert result[0] == '\\input{src/foo.tex}\n'

    def test_newline_element(self):
        result = latex_input(PathLaTeX("x.tex"))
        assert result[1] == '\n'


@pytest.mark.unit
class TestLatexLabel:
    def test_label_format(self):
        result = latex_label('sec', NameLaTeX('hello world'))
        assert result == ['\\label{sec:hello-world}\n']


@pytest.mark.unit
class TestLatexSection:
    def test_level_0(self):
        result = latex_section(NameLaTeX('Chapter One'),
                               PathLaTeX('ch/one'), 0)
        assert result == [
            '\\chapter{Chapter One}\n', '\\label{ch:ch-one}\n', '\n']

    def test_level_1(self):
        result = latex_section(NameLaTeX('A Section'), PathLaTeX('s/one'), 1)
        assert result == ['\\section{A Section}\n',
                          '\\label{sec:s-one}\n', '\n']

    def test_level_2(self):
        result = latex_section(NameLaTeX('Sub'), PathLaTeX('s/s'), 2)
        assert result == ['\\subsection{Sub}\n', '\\label{ssec:s-s}\n', '\n']

    def test_level_3(self):
        result = latex_section(NameLaTeX('SubSub'), PathLaTeX('s/s/s'), 3)
        assert result == [
            '\\subsubsection{SubSub}\n', '\\label{sssec:s-s-s}\n', '\n']

    def test_invalid_level_raises(self):
        with pytest.raises(ValueError):
            latex_section(NameLaTeX('X'), PathLaTeX('x'), -1)

    def test_invalid_level_too_high(self):
        with pytest.raises(ValueError):
            latex_section(NameLaTeX('X'), PathLaTeX('x'), 4)


@pytest.mark.unit
class TestLatexListingCode:
    def test_returns_list_with_path_and_inputminted(self):
        result = latex_listing_code(PathLaTeX("src/foo.hpp"), "cpp")
        assert result == [r'Path: \verb|src/foo.hpp|',
                          '\n\n', '\\inputminted{cpp}{src/foo.hpp}\n', '\n']

    def test_file_type_in_output(self):
        result = latex_listing_code(PathLaTeX("x.py"), "py")
        assert result == [r'Path: \verb|x.py|',
                          '\n\n', '\\inputminted{py}{x.py}\n', '\n']


@pytest.mark.unit
class TestLatexListingCodeRange:
    def test_returns_list(self):
        result = latex_listing_code_range(PathLaTeX("src/x.hpp"), "cpp", 1, 10)
        assert result == [r'Path: \verb|src/x.hpp|', '\n\n',
                          '\\inputminted[firstline=1,lastline=10]{cpp}{src/x.hpp}\n', '\n']

    def test_contains_firstline_lastline(self):
        result = latex_listing_code_range(PathLaTeX("src/x.hpp"), "cpp", 5, 20)
        assert result == [r'Path: \verb|src/x.hpp|', '\n\n',
                          '\\inputminted[firstline=5,lastline=20]{cpp}{src/x.hpp}\n', '\n']
