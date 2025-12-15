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
        doc_dir_tex = test_config.get_doc_dir(doc_type='tex')
        doc_dir_typ = test_config.get_doc_dir(doc_type='typ')
        assert doc_dir_tex == 'doc'
        assert doc_dir_typ == 'doc_typ'


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
                'typ': 'notebook/typ'
            },
            'cheatsheets': {'cs1': 'CS1'},
            'default_file_type': 'cs',
            'file_types': {'.cpp': 'cs', '.py': 'pycs'},
            'code_type_list': ['cs', 'pycs'],
            'doc_type_list': ['tex', 'typ'],
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
        assert full_config.get_doc_dir(doc_type='tex') == 'doc'

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
                'typ': 'notebook/typ'
            },
            'notebook_file_dir': 'template',
            'notebook_file': 'notebook',
            'cheatsheets': {},
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
                'typ': 'notebook/typ'
            },
            'notebook_file_dir': 'template',
            'notebook_file': 'notebook',
            'cheatsheets': {},
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


# =============================================================================
# ConfigBase Advanced Tests
# =============================================================================


class TestConfigBaseAdvanced:
    """Advanced tests for ConfigBase class."""

    def test_reload_permission_error(self, tmp_path: Path) -> None:
        """Test reload raises PermissionError for inaccessible file."""
        path = tmp_path / 'nonexistent.yml'
        with pytest.raises(PermissionError):
            ConfigBase(str(path))

    def test_output_write_permission_error(self, tmp_path: Path) -> None:
        """Test output raises PermissionError for inaccessible file."""
        import os
        path = tmp_path / 'config.yml'
        path.write_text(yaml.dump({'a': 1}), encoding='utf-8')
        config = ConfigBase(str(path), readonly=False)

        # Make file read-only
        os.chmod(str(path), 0o444)
        try:
            with pytest.raises(PermissionError):
                config.output()
        finally:
            # Restore permissions for cleanup
            os.chmod(str(path), 0o644)


# =============================================================================
# Config Additional Coverage Tests
# =============================================================================


class TestConfigAdditionalCoverage:
    """Additional tests to improve coverage."""

    @pytest.fixture
    def extended_config_data(self) -> dict[str, Any]:
        """Extended configuration data for additional coverage."""
        return {
            'notebook': {
                'chapters': {'ch1': 'Chapter 1', 'ch2': 'Chapter 2'},
                'sections': {
                    'ch1': [{'sec1': 'Section 1', 'code_ext': 'cpp', 'usage_ext': 'in'}],
                    'ch2': []
                }
            },
            'notebook_code_dir': 'src',
            'notebook_doc_dir': {'tex': 'doc', 'typ': 'notebook/typ'},
            'competitive_verifier_doc_dir': 'cvdoc',
            'cheatsheet_dir': 'cheatsheet',
            'usage_dir': 'usage',
            'notebook_file_dir': 'template',
            'notebook_file': 'notebook',
            'cheatsheets': {'cs1': 'Cheatsheet 1'},
            'default_file_type': 'cpp',
            'file_types': {'cpp': 'cpp', 'hpp': 'cpp', 'py': 'python'},
            'code_type_list': ['cpp', 'python'],
            'doc_type_list': ['tex', 'typ'],
            'run_usage_commands': {'cpp': 'g++ {src}'},
            'formatting_commands': {'cpp': 'clang-format {src}', 'tex': 'latexindent {src}'},
            'compile_pdf_commands': {'tex': 'latexmk {src}', 'typ': 'typst {src} {out}'}
        }

    @pytest.fixture
    def extended_config(self, tmp_path: Path, extended_config_data: dict[str, Any]) -> Config:
        """Create extended Config."""
        path = make_temp_yaml(tmp_path, extended_config_data)
        return Config(path)

    def test_get_cvdoc_dir(self, extended_config: Config) -> None:
        """Test getting competitive verifier doc directory."""
        assert extended_config.get_cvdoc_dir() == 'cvdoc'

    def test_get_sections_by_chapter_empty(self, extended_config: Config) -> None:
        """Test getting sections for chapter with no sections."""
        sections = extended_config.get_sections_by_chapter('ch2')
        assert sections == []

    def test_get_sections_by_chapter_nonexistent(self, extended_config: Config) -> None:
        """Test getting sections for nonexistent chapter."""
        sections = extended_config.get_sections_by_chapter('nonexistent')
        assert sections == []

    def test_set_sections_by_chapter_new(self, extended_config: Config) -> None:
        """Test setting sections for a new chapter."""
        section = Section('newchapter', 'n', 'N', 'cpp', 'in')
        extended_config.set_sections_by_chapter('newchapter', [section])
        # Should create the chapter if not exists (warns)

    def test_append_chapter_duplicate(self, extended_config: Config) -> None:
        """Test appending duplicate chapter does nothing."""
        original_keys = extended_config.get_chapter_key()
        extended_config.append_chapter('ch1')  # Already exists
        assert extended_config.get_chapter_key() == original_keys

    def test_append_section_duplicate(self, extended_config: Config) -> None:
        """Test appending duplicate section does nothing."""
        # Create a section with a name that matches an existing one
        section = Section('ch1', 'sec1', 'Section 1', 'cpp', 'in')
        extended_config.append_section(section)
        # Should warn and skip - no error raised

    def test_get_code_type_list(self, extended_config: Config) -> None:
        """Test getting code type list."""
        types = extended_config.get_code_type_list()
        assert 'cpp' in types
        assert 'python' in types

    def test_get_doc_type_list(self, extended_config: Config) -> None:
        """Test getting doc type list."""
        types = extended_config.get_doc_type_list()
        assert 'tex' in types
        assert 'typ' in types

    def test_get_formatting_command_doc_type(self, extended_config: Config) -> None:
        """Test getting formatting command for doc type."""
        cmd = extended_config.get_formatting_command('tex', 'file.tex')
        assert 'latexindent' in cmd[0]

    def test_get_run_usage_command_non_code_type(self, extended_config: Config) -> None:
        """Test getting run usage command for non-code type."""
        cmd = extended_config.get_run_usage_command('tex', 'file.tex')
        assert cmd == []

    def test_get_doc_dir_typst(self, extended_config: Config) -> None:
        """Test getting doc directory for typst."""
        doc_dir = extended_config.get_doc_dir(doc_type='typ')
        assert doc_dir == 'notebook/typ'


class TestConfigKeyErrorPaths:
    """Tests for Config KeyError handling paths."""

    @pytest.fixture
    def keyerror_config_data(self) -> dict[str, Any]:
        """Config data with missing command entries for KeyError testing."""
        return {
            'notebook': {
                'chapters': {'ch1': 'Chapter 1'},
                'sections': {'ch1': []}
            },
            'notebook_code_dir': 'src',
            'notebook_doc_dir': {'tex': 'doc', 'typ': 'notebook/typ'},
            'competitive_verifier_doc_dir': 'cvdoc',
            'cheatsheet_dir': 'cheatsheet',
            'usage_dir': 'usage',
            'notebook_file_dir': 'template',
            'notebook_file': 'notebook',
            'cheatsheets': {},
            'default_file_type': 'cpp',
            'file_types': {'cpp': 'cpp'},
            'code_type_list': ['cpp', 'python'],
            'doc_type_list': ['tex', 'typ'],
            'run_usage_commands': {},  # Empty - will cause KeyError
            'formatting_commands': {},  # Empty - will cause KeyError
            'compile_pdf_commands': {}  # Empty - will cause KeyError
        }

    @pytest.fixture
    def keyerror_config(self, tmp_path: Path, keyerror_config_data: dict[str, Any]) -> Config:
        """Create Config that will trigger KeyError paths."""
        path = make_temp_yaml(tmp_path, keyerror_config_data)
        return Config(path)

    def test_get_run_usage_command_keyerror(self, keyerror_config: Config) -> None:
        """Test get_run_usage_command when command not found (KeyError)."""
        # 'cpp' is a valid code type but has no run_usage_command defined
        cmd = keyerror_config.get_run_usage_command('cpp', 'test.cpp')
        assert cmd == []

    def test_get_formatting_command_keyerror(self, keyerror_config: Config) -> None:
        """Test get_formatting_command when command not found (KeyError)."""
        # 'cpp' is a valid code type but has no formatting_command defined
        cmd = keyerror_config.get_formatting_command('cpp', 'test.cpp')
        assert cmd == []

    def test_get_compile_pdf_command_keyerror(self, keyerror_config: Config) -> None:
        """Test get_compile_pdf_command when command not found (KeyError)."""
        # 'tex' is a valid doc type but has no compile_pdf_command defined
        cmd = keyerror_config.get_compile_pdf_command('tex')
        assert cmd == []


class TestConfigNotebookMethods:
    """Tests for Config notebook file/dir methods."""

    @pytest.fixture
    def notebook_config_data(self) -> dict[str, Any]:
        """Config data with notebook file settings."""
        return {
            'notebook': {'chapters': {}, 'sections': {}},
            'notebook_code_dir': 'src',
            'notebook_doc_dir': {'tex': 'doc', 'typ': 'notebook/typ'},
            'notebook_file_dir': 'template',
            'notebook_file': 'notebook',
            'cheatsheets': {},
            'default_file_type': 'cpp',
            'file_types': {},
            'code_type_list': [],
            'doc_type_list': [],
            'run_usage_commands': {},
            'formatting_commands': {},
            'compile_pdf_commands': {}
        }

    @pytest.fixture
    def notebook_config(self, tmp_path: Path, notebook_config_data: dict[str, Any]) -> Config:
        """Create Config with notebook settings."""
        path = make_temp_yaml(tmp_path, notebook_config_data)
        return Config(path)

    def test_get_notebook_file_dir(self, notebook_config: Config) -> None:
        """Test getting notebook file directory."""
        assert notebook_config.get_notebook_file_dir() == 'template'

    def test_get_notebook_file(self, notebook_config: Config) -> None:
        """Test getting notebook file name."""
        assert notebook_config.get_notebook_file() == 'notebook'
