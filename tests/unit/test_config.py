"""Unit tests for Config class and ConfigBase."""

from libs.classes.section import Section
from libs.classes.config_base import ConfigBase
from libs.classes.config import Config
import os
import yaml
import pytest
from pathlib import Path

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

    def test_get_code_style(self, test_config):
        """Test getting code style for extension."""
        style = test_config.get_code_style('.cpp')
        assert style is not None

    def test_get_ext_names_by_code_style(self, test_config):
        """Test getting extension names by code style."""
        ext_names = test_config.get_ext_names_by_code_style('cpp')
        assert 'cpp' in ext_names

    def test_get_formatting_command(self, test_config, temp_dir):
        """Test getting formatting command."""
        test_file = temp_dir / 'test.cpp'
        test_file.write_text('test')

        cmd = test_config.get_formatting_command('cpp', str(test_file))
        assert isinstance(cmd, list)
        assert 'clang-format' in cmd[0] or 'clang-format' in str(cmd)
        assert str(test_file) in cmd or '{filepath}' in str(cmd)

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
        'notebook_doc_dir': 'doc',
        'cheatsheets': {'cs1': 'CS1'},
        'export_usage_code_in_notebook': True,
        'default_code_style': 'cs',
        'code_styles': {'.cpp': 'cs', '.py': 'pycs'},
        'run_usage_commands': {'cs': ['run', '${filename}']},
        'formatting_commands': {'cs': ['fmt', '${filename}']}
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
    assert cfg.get_default_code_style() == 'cs'
    assert cfg.get_code_style('.cpp') == 'cs'
    assert cfg.get_code_style('.unknown') == 'cs'
    assert 'cs' in cfg.get_all_code_styles()
    assert '.cpp' in cfg.get_all_code_ext_names()
    assert cfg.get_ext_names_by_code_style('cs')

    assert cfg.get_run_usage_command('cs', 'f') == ['run', 'f']
    assert cfg.get_run_usage_command('missing', 'f') == []
    assert cfg.get_formatting_command('cs', 'f') == ['fmt', 'f']
    assert cfg.get_formatting_command('missing', 'f') == []
