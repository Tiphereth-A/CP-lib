import os
import pytest
import yaml
from libs.content.section import Section, _EXT_TYPE, _TYPE_EXT, _TEMPLACES


def write_yaml(path, data):
    with open(path, 'w', encoding='utf8') as f:
        yaml.dump(data, f, sort_keys=False)


@pytest.mark.unit
class TestSectionConstants:
    def test_ext_type_mapping(self):
        assert _EXT_TYPE['.hpp'] == 'cpp'
        assert _EXT_TYPE['.py'] == 'py'
        assert _EXT_TYPE['.md'] == 'markdown'

    def test_type_ext_reverse(self):
        assert _TYPE_EXT['cpp'] == ['.hpp', '.cpp']

    def test_templates_exist(self):
        assert set(_TEMPLACES) == {'cpvdoc.md',
                                   'doc.tex', 'doc.typ', 'lib.hpp', 'usage.cpp'}


@pytest.mark.unit
class TestSection:
    def _make_section(self, tmp_path, name='gcd', title='GCD'):
        sect_dir = tmp_path / name
        sect_dir.mkdir()
        return Section(str(sect_dir), title)

    def test_repr(self, tmp_path):
        s = self._make_section(tmp_path)
        r = repr(s)
        assert r == f"Section(name=gcd, title=GCD, dir={str(tmp_path / 'gcd')})"

    def test_init_files_creates_expected_files(self, tmp_path):
        s = self._make_section(tmp_path)
        s.init_files()
        files = os.listdir(str(tmp_path / 'gcd'))
        assert set(files) == {'lib.hpp', 'cpvdoc.md',
                              'doc.tex', 'doc.typ', 'usage.cpp'}

    def test_init_files_lib_hpp_content(self, tmp_path):
        s = self._make_section(tmp_path)
        s.init_files()
        content = (tmp_path / 'gcd' / 'lib.hpp').read_text(encoding='utf8')
        assert content.split('\n', 1)[0] == '#pragma once'

    def test_expand_tex_no_doc_raises(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        os.makedirs('mylib')
        s = Section('mylib', 'MyLib')
        # No doc.tex in directory
        with pytest.raises(FileNotFoundError):
            s.expand_tex('temp')

    def test_expand_tex_basic(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        os.makedirs('lib')
        with open('lib/lib.hpp', 'w') as f:
            f.write('// code\n// line2\n// line3\n')
        with open('lib/doc.tex', 'w') as f:
            f.write('% {lib.hpp}\n')
        os.makedirs('temp')
        s = Section('lib', 'Lib')
        s.expand_tex('temp')
        assert os.path.exists('temp/lib/doc.tex')
        content = open('temp/lib/doc.tex').read()
        assert content == 'Path: \\verb|lib/lib.hpp|\n\n\\inputminted[firstline=1,lastline=3]{cpp}{lib/lib.hpp}\n\n\n'

    def test_expand_tex_with_start(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        os.makedirs('lib2')
        with open('lib2/lib.hpp', 'w') as f:
            f.writelines([f'line{i}\n' for i in range(5)])
        with open('lib2/doc.tex', 'w') as f:
            f.write('% {lib.hpp,start=2}\n')
        os.makedirs('temp')
        s = Section('lib2', 'Lib2')
        s.expand_tex('temp')
        out = open('temp/lib2/doc.tex').read()
        assert out == 'Path: \\verb|lib2/lib.hpp|\n\n\\inputminted[firstline=2,lastline=5]{cpp}{lib2/lib.hpp}\n\n\n'

    def test_expand_tex_with_start_and_stop(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        os.makedirs('lib3')
        with open('lib3/lib.hpp', 'w') as f:
            f.writelines([f'line{i}\n' for i in range(10)])
        with open('lib3/doc.tex', 'w') as f:
            f.write('% {lib.hpp,start=2,stop=5}\n')
        os.makedirs('temp')
        s = Section('lib3', 'Lib3')
        s.expand_tex('temp')
        out = open('temp/lib3/doc.tex').read()
        assert out == 'Path: \\verb|lib3/lib.hpp|\n\n\\inputminted[firstline=2,lastline=5]{cpp}{lib3/lib.hpp}\n\n\n'

    def test_expand_tex_negative_stop(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        os.makedirs('lib4')
        with open('lib4/lib.hpp', 'w') as f:
            f.writelines([f'line{i}\n' for i in range(10)])
        with open('lib4/doc.tex', 'w') as f:
            f.write('% {lib.hpp,start=1,stop=-2}\n')
        os.makedirs('temp')
        s = Section('lib4', 'Lib4')
        s.expand_tex('temp')
        out = open('temp/lib4/doc.tex').read()
        # stop=-2 => 10 + (-2) = 8
        assert out == 'Path: \\verb|lib4/lib.hpp|\n\n\\inputminted[firstline=1,lastline=8]{cpp}{lib4/lib.hpp}\n\n\n'

    def test_expand_typ_not_implemented(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        os.makedirs('mylib2')
        s = Section('mylib2', 'MyLib')
        with pytest.raises(AssertionError):
            s.expand_typ('temp')
