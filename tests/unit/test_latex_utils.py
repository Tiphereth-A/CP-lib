from libs.latex_utils import TextLaTeXBase, PathLaTeX, NameLaTeX
from libs.latex_utils import xelatex, bibtex, latexmk
from libs.latex_utils import latex_input, latex_label, latex_chapter, latex_section, latex_listing_code, latex_listing_code_range


def test_text_latex_base_and_label():
    t = TextLaTeXBase('Hello_World\\')
    assert t.get() == 'Hello_World\\'
    lbl = t.get_label_name()
    assert isinstance(lbl, str)


def test_path_and_name_latex():
    p = PathLaTeX(r"a\\b\\c")
    assert '/' in p.get()
    n = NameLaTeX('some_name')
    assert ' ' in n.get()  # underscores replaced with space


def test_commands_return_list():
    assert isinstance(xelatex('f'), list)
    assert isinstance(bibtex('f'), list)
    assert isinstance(latexmk('f'), list)


def test_latex_wrappers():
    p = PathLaTeX('x/y')
    name = NameLaTeX('Chap_Name')
    assert latex_input(p)  # returns list
    assert latex_label('pre', name)
    ch = latex_chapter(name)
    assert any('\\chapter' in s for s in ch if isinstance(s, str))
    sec = latex_section(name)
    assert any('section' in s for s in sec if isinstance(s, str))


def test_listing_code_variants():
    p = PathLaTeX('a/b')
    res = latex_listing_code(p, 'cpp')
    assert any('inputminted' in s for s in res if isinstance(s, str))
    res2 = latex_listing_code_range(p, 'py', 1, 3)
    assert any(
        'firstline' in s or 'lastline' in s for s in res2 if isinstance(s, str))
