"""Unit tests for Section class.

This module tests the Section class used to represent code sections
in the notebook, including parsing, file path generation, and file I/O.
"""

import os
from pathlib import Path

import pytest

from libs.classes.section import Section


pytestmark = pytest.mark.unit


# =============================================================================
# Section Parsing Tests
# =============================================================================


class TestSectionParsing:
    """Tests for Section parsing from dictionary."""

    def test_parse_from_dict_valid(self, caplog: pytest.LogCaptureFixture) -> None:
        """Test parsing a valid dictionary into a Section."""
        section = Section('ch1')
        data = {'file1': 'Title 1', 'code_ext': 'cpp', 'usage_ext': 'in'}

        caplog.set_level('DEBUG')
        result = section.parse_from_dict(data.copy())

        assert result is section
        assert section.name == 'file1'
        assert section.title == 'Title 1'
        assert section.code_ext == 'cpp'
        assert section.usage_ext == 'in'

    def test_parse_from_dict_missing_title_warns(
        self, caplog: pytest.LogCaptureFixture
    ) -> None:
        """Test that missing title generates a warning."""
        section = Section('ch2')
        data = {'file2': '', 'code_ext': 'py', 'usage_ext': 'out'}

        caplog.set_level('WARNING')
        result = section.parse_from_dict(data.copy())

        assert result.title == 'file2'
        assert any(
            "title name not found" in r.message
            for r in caplog.records
            if r.levelname == 'WARNING'
        )

    def test_parse_from_dict_invalid_raises(
        self, caplog: pytest.LogCaptureFixture
    ) -> None:
        """Test that invalid dictionary raises KeyError."""
        section = Section('ch3')
        data = {'a': 'A', 'b': 'B', 'code_ext': 'c', 'usage_ext': 'u'}

        caplog.set_level('ERROR')
        with pytest.raises(KeyError):
            section.parse_from_dict(data.copy())

        assert any(
            'Invalid section config' in r.message
            for r in caplog.records
            if r.levelname == 'ERROR'
        )


# =============================================================================
# Section Dictionary and Filenames Tests
# =============================================================================


class TestSectionFilenames:
    """Tests for Section filename generation."""

    @pytest.fixture
    def section(self) -> Section:
        """Create a test Section instance."""
        return Section('ch', 'name1', 'Title', 'cpp', 'in')

    @pytest.fixture
    def directory_structure(self, tmp_path: Path) -> dict[str, Path]:
        """Create test directory structure."""
        return {
            'code': tmp_path / 'code',
            'doc': tmp_path / 'doc',
            'cvdoc': tmp_path / 'cvdoc',
            'usage': tmp_path / 'usage'
        }

    def test_get_dict(self, section: Section) -> None:
        """Test getting dictionary representation."""
        result = section.get_dict()
        assert result['name1'] == 'Title' or result.get('name1') == 'Title'

    def test_get_filenames_creates_directories(
        self, section: Section, directory_structure: dict[str, Path]
    ) -> None:
        """Test that get_filenames creates necessary directories."""
        code_p, doc_p, cv_p, usage_p = section.get_filenames(
            str(directory_structure['code']),
            str(directory_structure['doc']),
            str(directory_structure['cvdoc']),
            str(directory_structure['usage'])
        )

        # Directories should be created
        assert os.path.isdir(os.path.join(str(directory_structure['code']), 'ch'))

    def test_get_filenames_returns_correct_paths(
        self, section: Section, directory_structure: dict[str, Path]
    ) -> None:
        """Test that get_filenames returns correct file paths."""
        code_p, doc_p, cv_p, usage_p = section.get_filenames(
            str(directory_structure['code']),
            str(directory_structure['doc']),
            str(directory_structure['cvdoc']),
            str(directory_structure['usage'])
        )

        assert code_p.endswith('name1.cpp')
        assert doc_p.endswith('name1.tex')
        assert usage_p.endswith('name1.in')


# =============================================================================
# Section File I/O Tests
# =============================================================================


class TestSectionFileIO:
    """Tests for Section file I/O operations."""

    @pytest.fixture
    def section(self) -> Section:
        """Create a test Section instance."""
        return Section('ch', 'name1', 'Title', 'cpp', 'in')

    @pytest.fixture
    def directory_structure(self, tmp_path: Path) -> dict[str, Path]:
        """Create test directory structure."""
        return {
            'code': tmp_path / 'code',
            'doc': tmp_path / 'doc',
            'cvdoc': tmp_path / 'cvdoc',
            'usage': tmp_path / 'usage'
        }

    def test_open_creates_files(
        self, section: Section, directory_structure: dict[str, Path]
    ) -> None:
        """Test that open creates files and returns file objects."""
        f_code, f_doc, f_cvdoc, f_usage = section.open(
            str(directory_structure['code']),
            str(directory_structure['doc']),
            str(directory_structure['cvdoc']),
            str(directory_structure['usage']),
            'w',
            encoding='utf-8'
        )

        try:
            f_code.write('x')
        finally:
            f_code.close()
            f_doc.close()
            f_cvdoc.close()
            f_usage.close()

        # Get the file paths
        code_p, doc_p, cv_p, usage_p = section.get_filenames(
            str(directory_structure['code']),
            str(directory_structure['doc']),
            str(directory_structure['cvdoc']),
            str(directory_structure['usage'])
        )

        # Ensure files exist
        assert Path(code_p).exists()
        assert Path(doc_p).exists()
        assert Path(cv_p).exists()
        assert Path(usage_p).exists()
