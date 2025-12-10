"""Unit tests for Config class and ConfigBase."""

from libs.classes.section import Section
from libs.classes.config_base import ConfigBase
from libs.classes.config import Config
import yaml
import pytest

pytestmark = pytest.mark.unit


class TestConfig:
    """Tests for Config class."""

    def test_config_initialization(self, sample_config_file):
        """Test Config initialization with valid file."""
        config = Config(str(sample_config_file))
        assert config is not None

    def test_get_code_dir(self, test_config):
        """Test getting code directory."""
        code_dir = test_config.get_code_dir()
        assert code_dir == 'src'

    def test_get_doc_dir(self, test_config):
        """Test getting doc directory."""
        doc_dir = test_config.get_doc_dir()
        assert doc_dir == 'doc'

    def test_get_chapter_key(self, test_config):
        """Test getting chapter keys."""
        chapters = test_config.get_chapter_key()
        assert 'ch1' in chapters

    def test_get_sections_by_chapter(self, test_config):
        """Test getting sections by chapter."""
        sections = test_config.get_sections_by_chapter('ch1')
        assert len(sections) > 0

    def test_get_file_type(self, test_config):
        """Test getting file type for extension."""
        style = test_config.get_file_type('.cpp')
        assert style is not None

    def test_get_ext_names_by_file_type(self, test_config):
        """Test getting extension names by file type."""
        ext_names = test_config.get_ext_names_by_file_type('cpp')
        assert 'cpp' in ext_names

    def test_get_formatting_command(self, test_config, temp_dir):
        """Test getting formatting command."""
        test_file = temp_dir / 'test.cpp'
        test_file.write_text('test')

        cmd = test_config.get_formatting_command('cpp', str(test_file))
        assert isinstance(cmd, list)
        assert 'clang-format' in cmd[0] or 'clang-format' in str(cmd)
        assert str(test_file) in cmd or '{src}' in str(cmd)

    def test_get_run_usage_command(self, test_config, temp_dir):
        """Test getting run usage command."""
        test_file = temp_dir / 'test.cpp'
        test_file.write_text('test')

        cmd = test_config.get_run_usage_command('cpp', str(test_file))
        assert isinstance(cmd, list)
        assert 'g++' in cmd[0] or 'g++' in str(cmd)


def make_temp_yaml(tmp_path, data: dict):
    p = tmp_path / 'cfg.yml'
    p.write_text(yaml.dump(data), encoding='utf8')
    return str(p)


def test_configbase_reload_and_items(tmp_path):
    data = {'a': {'b': 1}, 'x': 2}
    p = make_temp_yaml(tmp_path, data)
    cb = ConfigBase(p)
    assert isinstance(str(cb), str)
    assert cb.items('a', 'b') == 1


def test_configbase_output_readonly(tmp_path):
    data = {'k': 1}
    p = make_temp_yaml(tmp_path, data)
    cb = ConfigBase(p, readonly=True)
    try:
        cb.output()
        assert False, 'should have raised AssertionError for readonly'
    except AssertionError:
        pass


def test_config_methods(tmp_path):
    data = {
        'notebook': {
            'chapters': {'c1': 'C1'},
            'sections': {'c1': [{'s1': 'S1', 'code_ext': 'cpp', 'usage_ext': 'in'}]}
        },
        'notebook_code_dir': 'code',
        'notebook_doc_dir': {
            'tex': 'doc',
            'typst': 'doc_typ'
        },
        'cheatsheets': {'cs1': 'CS1'},
        'export_usage_code_in_notebook': True,
        'default_file_type': 'cs',
        'file_types': {'.cpp': 'cs', '.py': 'pycs'},
        'code_type_list': ['cs', 'pycs'],
        'doc_type_list': [],
        'run_usage_commands': {'cs': 'run {src}'},
        'formatting_commands': {'cs': 'fmt {src}'}
    }
    p = make_temp_yaml(tmp_path, data)
    cfg = Config(p)
    assert cfg.get_code_dir() == 'code'
    assert cfg.get_doc_dir() == 'doc'
    assert cfg.get_chapter_key() == ['c1']
    assert cfg.get_chapter_title('c1') == 'C1'
    assert cfg.get_chapter_title('notfound') == 'notfound'

    secs = cfg.get_sections_by_chapter('c1')
    assert len(secs) == 1

    # append new chapter
    cfg.append_chapter('newch')
    assert 'newch' in cfg.get_chapter_key()

    # append section
    s = Section('newch', 'n', 'N', 'cpp', 'in')
    cfg.append_section(s)
    assert any(sec.name == 'n' for sec in cfg.get_sections_by_chapter('newch'))

    assert cfg.get_cheatsheets() == ['cs1']
    assert cfg.get_cheatsheet_name('cs1') == 'CS1'
    assert cfg.get_cheatsheet_name('missing') == 'missing'

    assert cfg.export_usage_code_in_notebook() is True
    assert cfg.get_default_file_type() == 'cs'
    assert cfg.get_file_type('.cpp') == 'cs'
    assert cfg.get_file_type('.unknown') == 'cs'
    assert 'cs' in cfg.get_all_file_types()
    assert '.cpp' in cfg.get_all_code_ext_names()
    assert cfg.get_ext_names_by_file_type('cs')

    assert cfg.get_run_usage_command('cs', 'f') == ['run', 'f']
    assert cfg.get_run_usage_command('missing', 'f') == []
    assert cfg.get_formatting_command('cs', 'f') == ['fmt', 'f']
    assert cfg.get_formatting_command('missing', 'f') == []


def test_compile_pdf_commands(tmp_path):
    """Test compile PDF command methods for LaTeX and Typst."""
    data = {
        'notebook': {
            'chapters': {},
            'sections': {}
        },
        'notebook_code_dir': 'code',
        'notebook_doc_dir': {
            'tex': 'doc',
            'typst': 'doc_typ'
        },
        'notebook_file_dir': 'template',
        'notebook_file': 'notebook',
        'cheatsheets': {},
        'export_usage_code_in_notebook': True,
        'default_file_type': 'cpp',
        'file_types': {'.tex': 'tex', '.typ': 'typ'},
        'code_type_list': ['cpp'],
        'doc_type_list': ['tex', 'typ'],
        'run_usage_commands': {},
        'formatting_commands': {},
        'compile_pdf_commands': {
            'tex': 'latexmk -xelatex {src}',
            'typ': 'typst compile {src} {out}'
        }
    }
    p = make_temp_yaml(tmp_path, data)
    cfg = Config(p)
    
    # Test _get_compile_pdf_commands_raw
    raw_commands = cfg._get_compile_pdf_commands_raw()
    assert 'tex' in raw_commands
    assert 'typ' in raw_commands
    assert 'latexmk' in raw_commands['tex']
    assert 'typst' in raw_commands['typ']
    
    # Test get_compile_pdf_command for LaTeX (no {out} placeholder)
    tex_cmd = cfg.get_compile_pdf_command('tex')
    assert isinstance(tex_cmd, list)
    assert 'latexmk' in tex_cmd[0]
    assert any('template/notebook.tex' in arg for arg in tex_cmd)
    
    # Test get_compile_pdf_command for Typst (with {out} placeholder)
    typ_cmd = cfg.get_compile_pdf_command('typ')
    assert isinstance(typ_cmd, list)
    assert 'typst' in typ_cmd[0]
    assert 'compile' in typ_cmd[1]
    assert any('template/notebook.typ' in arg for arg in typ_cmd)
    assert any('_pdf_out/notebook.pdf' in arg for arg in typ_cmd)
    
    # Test non-existent doc type
    missing_cmd = cfg.get_compile_pdf_command('missing')
    assert missing_cmd == []
    
    # Test non-doc type (e.g., 'cpp' which is code type)
    non_doc_cmd = cfg.get_compile_pdf_command('cpp')
    assert non_doc_cmd == []


def test_compile_pdf_command_placeholder_handling(tmp_path):
    """Test that {src} and {out} placeholders are handled correctly."""
    data = {
        'notebook': {'chapters': {}, 'sections': {}},
        'notebook_code_dir': 'code',
        'notebook_doc_dir': {
            'tex': 'doc',
            'typst': 'doc_typ'
        },
        'notebook_file_dir': 'template',
        'notebook_file': 'notebook',
        'cheatsheets': {},
        'export_usage_code_in_notebook': True,
        'default_file_type': 'cpp',
        'file_types': {},
        'code_type_list': ['cpp'],
        'doc_type_list': ['typ'],
        'run_usage_commands': {},
        'formatting_commands': {},
        'compile_pdf_commands': {
            'typ': 'typst compile --root . {src} {out}'
        }
    }
    p = make_temp_yaml(tmp_path, data)
    cfg = Config(p)
    
    # Test command with both {src} and {out}
    cmd = cfg.get_compile_pdf_command('typ')
    assert isinstance(cmd, list)
    assert 'typst' in cmd
    assert 'compile' in cmd
    assert '--root' in cmd
    assert '.' in cmd
    # Both placeholders should be replaced
    assert not any('{src}' in arg for arg in cmd)
    assert not any('{out}' in arg for arg in cmd)
    # Should contain actual paths
    assert any('notebook.typ' in arg for arg in cmd)
    assert any('.pdf' in arg for arg in cmd)
