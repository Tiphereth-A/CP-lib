"""Unit tests for Config class and ConfigBase.

This module contains comprehensive tests for configuration handling,
including initialization, data access, and command generation.
"""

from pathlib import Path
from typing import Any

import pytest
import yaml

from libs.classes.config import Config
from libs.classes.config_base import ConfigBase
from libs.classes.section import Section


pytestmark = pytest.mark.unit


# =============================================================================
# Helper Functions
# =============================================================================


def make_temp_yaml(tmp_path: Path, data: dict[str, Any]) -> str:
    """Create a temporary YAML file with given data.

    Args:
        tmp_path: Temporary directory path.
        data: Dictionary to serialize to YAML.

    Returns:
        Path to the created YAML file as string.
    """
    path = tmp_path / 'cfg.yml'
    path.write_text(yaml.dump(data), encoding='utf-8')
    return str(path)


# =============================================================================
# ConfigBase Tests
# =============================================================================


class TestConfigBase:
    """Tests for ConfigBase class."""

    def test_initialization_and_str(self, tmp_path: Path) -> None:
        """Test ConfigBase initialization returns valid string representation."""
        data = {'a': {'b': 1}, 'x': 2}
        path = make_temp_yaml(tmp_path, data)
        config = ConfigBase(path)
        assert isinstance(str(config), str)

    def test_items_nested_access(self, tmp_path: Path) -> None:
        """Test accessing nested configuration items."""
        data = {'a': {'b': 1}, 'x': 2}
        path = make_temp_yaml(tmp_path, data)
        config = ConfigBase(path)
        assert config.items('a', 'b') == 1

    def test_output_readonly_raises(self, tmp_path: Path) -> None:
        """Test that output raises AssertionError for readonly config."""
        data = {'k': 1}
        path = make_temp_yaml(tmp_path, data)
        config = ConfigBase(path, readonly=True)

        with pytest.raises(AssertionError):
            config.output()


# =============================================================================
# Config Initialization Tests
# =============================================================================


class TestConfigInitialization:
    """Tests for Config class initialization."""

    def test_config_initialization_valid_file(self, sample_config_file: Path) -> None:
        """Test Config initialization with valid file."""
        config = Config(str(sample_config_file))
        assert config is not None


# =============================================================================
# Config Directory Methods Tests
# =============================================================================


class TestConfigDirectoryMethods:
    """Tests for Config directory-related methods."""

    def test_get_code_dir(self, test_config: Config) -> None:
        """Test getting code directory."""
        code_dir = test_config.get_code_dir()
        assert code_dir == 'src'

    def test_get_doc_dir(self, test_config: Config) -> None:
        """Test getting doc directory."""
        doc_dir = test_config.get_doc_dir()
        assert doc_dir == 'doc'


# =============================================================================
# Config Chapter and Section Tests
# =============================================================================


class TestConfigChapterSection:
    """Tests for Config chapter and section methods."""

    def test_get_chapter_key(self, test_config: Config) -> None:
        """Test getting chapter keys."""
        chapters = test_config.get_chapter_key()
        assert 'ch1' in chapters

    def test_get_sections_by_chapter(self, test_config: Config) -> None:
        """Test getting sections by chapter."""
        sections = test_config.get_sections_by_chapter('ch1')
        assert len(sections) > 0


# =============================================================================
# Config File Type Tests
# =============================================================================


class TestConfigFileTypes:
    """Tests for Config file type methods."""

    def test_get_file_type(self, test_config: Config) -> None:
        """Test getting file type for extension."""
        style = test_config.get_file_type('.cpp')
        assert style is not None

    def test_get_ext_names_by_file_type(self, test_config: Config) -> None:
        """Test getting extension names by file type."""
        ext_names = test_config.get_ext_names_by_file_type('cpp')
        assert 'cpp' in ext_names


# =============================================================================
# Config Command Methods Tests
# =============================================================================


class TestConfigCommands:
    """Tests for Config command generation methods."""

    def test_get_formatting_command(self, test_config: Config, temp_dir: Path) -> None:
        """Test getting formatting command."""
        test_file = temp_dir / 'test.cpp'
        test_file.write_text('test')

        cmd = test_config.get_formatting_command('cpp', str(test_file))
        assert isinstance(cmd, list)
        assert 'clang-format' in cmd[0] or 'clang-format' in str(cmd)
        assert str(test_file) in cmd or '{src}' in str(cmd)

    def test_get_run_usage_command(self, test_config: Config, temp_dir: Path) -> None:
        """Test getting run usage command."""
        test_file = temp_dir / 'test.cpp'
        test_file.write_text('test')

        cmd = test_config.get_run_usage_command('cpp', str(test_file))
        assert isinstance(cmd, list)
        assert 'g++' in cmd[0] or 'g++' in str(cmd)


# =============================================================================
# Config Comprehensive Tests
# =============================================================================


class TestConfigComprehensive:
    """Comprehensive tests for Config with full data."""

    @pytest.fixture
    def full_config_data(self) -> dict[str, Any]:
        """Provide full configuration data for comprehensive testing."""
        return {
            'notebook': {
                'chapters': {'c1': 'C1'},
                'sections': {'c1': [{'s1': 'S1', 'code_ext': 'cpp', 'usage_ext': 'in'}]}
            },
            'notebook_code_dir': 'code',
            'notebook_doc_dir': {
                'tex': 'doc',
                'typ': 'doc_typ'
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

    @pytest.fixture
    def full_config(self, tmp_path: Path, full_config_data: dict[str, Any]) -> Config:
        """Create Config with full data."""
        path = make_temp_yaml(tmp_path, full_config_data)
        return Config(path)

    def test_basic_directory_methods(self, full_config: Config) -> None:
        """Test basic directory retrieval methods."""
        assert full_config.get_code_dir() == 'code'
        assert full_config.get_doc_dir() == 'doc'

    def test_chapter_methods(self, full_config: Config) -> None:
        """Test chapter retrieval methods."""
        assert full_config.get_chapter_key() == ['c1']
        assert full_config.get_chapter_title('c1') == 'C1'
        assert full_config.get_chapter_title('notfound') == 'notfound'

    def test_sections_retrieval(self, full_config: Config) -> None:
        """Test section retrieval."""
        sections = full_config.get_sections_by_chapter('c1')
        assert len(sections) == 1

    def test_append_chapter(self, full_config: Config) -> None:
        """Test appending a new chapter."""
        full_config.append_chapter('newch')
        assert 'newch' in full_config.get_chapter_key()

    def test_append_section(self, full_config: Config) -> None:
        """Test appending a new section."""
        # First append the chapter
        full_config.append_chapter('newch')
        section = Section('newch', 'n', 'N', 'cpp', 'in')
        full_config.append_section(section)

        sections = full_config.get_sections_by_chapter('newch')
        assert any(sec.name == 'n' for sec in sections)

    def test_cheatsheet_methods(self, full_config: Config) -> None:
        """Test cheatsheet-related methods."""
        assert full_config.get_cheatsheets() == ['cs1']
        assert full_config.get_cheatsheet_name('cs1') == 'CS1'
        assert full_config.get_cheatsheet_name('missing') == 'missing'

    def test_file_type_methods(self, full_config: Config) -> None:
        """Test file type methods."""
        assert full_config.export_usage_code_in_notebook() is True
        assert full_config.get_default_file_type() == 'cs'
        assert full_config.get_file_type('.cpp') == 'cs'
        assert full_config.get_file_type('.unknown') == 'cs'
        assert 'cs' in full_config.get_all_file_types()
        assert '.cpp' in full_config.get_all_code_ext_names()

    def test_command_methods(self, full_config: Config) -> None:
        """Test command generation methods."""
        assert full_config.get_run_usage_command('cs', 'f') == ['run', 'f']
        assert full_config.get_run_usage_command('missing', 'f') == []
        assert full_config.get_formatting_command('cs', 'f') == ['fmt', 'f']
        assert full_config.get_formatting_command('missing', 'f') == []


# =============================================================================
# Config PDF Compilation Tests
# =============================================================================


class TestConfigPdfCompilation:
    """Tests for PDF compilation command methods."""

    @pytest.fixture
    def pdf_config_data(self) -> dict[str, Any]:
        """Provide configuration data with PDF compilation commands."""
        return {
            'notebook': {
                'chapters': {},
                'sections': {}
            },
            'notebook_code_dir': 'code',
            'notebook_doc_dir': {
                'tex': 'doc',
                'typ': 'doc_typ'
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

    @pytest.fixture
    def pdf_config(self, tmp_path: Path, pdf_config_data: dict[str, Any]) -> Config:
        """Create Config with PDF compilation commands."""
        path = make_temp_yaml(tmp_path, pdf_config_data)
        return Config(path)

    def test_get_compile_pdf_commands_raw(self, pdf_config: Config) -> None:
        """Test retrieval of raw PDF compilation commands."""
        raw_commands = pdf_config._get_compile_pdf_commands_raw()
        assert 'tex' in raw_commands
        assert 'typ' in raw_commands
        assert 'latexmk' in raw_commands['tex']
        assert 'typst' in raw_commands['typ']

    def test_get_compile_pdf_command_latex(self, pdf_config: Config) -> None:
        """Test PDF compilation command for LaTeX (no {out} placeholder)."""
        tex_cmd = pdf_config.get_compile_pdf_command('tex')
        assert isinstance(tex_cmd, list)
        assert 'latexmk' in tex_cmd[0]
        # Check for path with either forward or back slashes (cross-platform)
        assert any('notebook.tex' in arg and 'template' in arg for arg in tex_cmd)

    def test_get_compile_pdf_command_typst(self, pdf_config: Config) -> None:
        """Test PDF compilation command for Typst (with {out} placeholder)."""
        typ_cmd = pdf_config.get_compile_pdf_command('typ')
        assert isinstance(typ_cmd, list)
        assert 'typst' in typ_cmd[0]
        assert 'compile' in typ_cmd[1]
        # Check for path with either forward or back slashes (cross-platform)
        assert any('notebook.typ' in arg and 'template' in arg for arg in typ_cmd)
        assert any('notebook.pdf' in arg and '_pdf_out' in arg for arg in typ_cmd)

    def test_get_compile_pdf_command_nonexistent(self, pdf_config: Config) -> None:
        """Test PDF compilation command for non-existent doc type."""
        missing_cmd = pdf_config.get_compile_pdf_command('missing')
        assert missing_cmd == []

    def test_get_compile_pdf_command_non_doc_type(self, pdf_config: Config) -> None:
        """Test PDF compilation command for non-doc type (e.g., 'cpp')."""
        non_doc_cmd = pdf_config.get_compile_pdf_command('cpp')
        assert non_doc_cmd == []


class TestConfigPdfPlaceholderHandling:
    """Tests for PDF compilation placeholder handling."""

    @pytest.fixture
    def placeholder_config(self, tmp_path: Path) -> Config:
        """Create Config for testing placeholder handling."""
        data = {
            'notebook': {'chapters': {}, 'sections': {}},
            'notebook_code_dir': 'code',
            'notebook_doc_dir': {
                'tex': 'doc',
                'typ': 'doc_typ'
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
        path = make_temp_yaml(tmp_path, data)
        return Config(path)

    def test_placeholder_replacement(self, placeholder_config: Config) -> None:
        """Test that {src} and {out} placeholders are properly replaced."""
        cmd = placeholder_config.get_compile_pdf_command('typ')

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
