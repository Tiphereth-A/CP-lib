"""Unit tests for typst_utils module.

This module tests the Typst utility classes and functions used
for generating Typst output in the notebook generation process.
"""

import pytest
from pathlib import Path

from libs.typst_utils import (
    LATEX_ONLY_EXTENSIONS,
    NameTypst,
    PathTypst,
    TextTypstBase,
    typst_chapter,
    typst_heading,
    typst_include,
    typst_label,
    typst_listing_code,
    typst_listing_code_range,
    typst_section,
)


pytestmark = pytest.mark.unit


# =============================================================================
# TextTypstBase Tests
# =============================================================================


class TestTextTypstBase:
    """Tests for TextTypstBase class."""

    def test_initialization(self) -> None:
        """Test TextTypstBase initialization."""
        text = TextTypstBase('Hello_World\\')
        assert text.get() == 'Hello_World\\'

    def test_get_label_name_basic(self) -> None:
        """Test basic label name generation."""
        text = TextTypstBase('Test Label')
        label = text.get_label_name()
        assert isinstance(label, str)
        assert label == 'test-label'

    def test_get_label_name_with_special_chars(self) -> None:
        """Test label name generation with special characters."""
        text = TextTypstBase('A* Algorithm')
        label = text.get_label_name()
        assert '-' in label
        assert '*' not in label

    def test_get_label_name_with_latex_escape(self) -> None:
        """Test label name with LaTeX escape sequences."""
        text = TextTypstBase(r'M\"obius')
        label = text.get_label_name()
        # Should remove backslash and quotes
        assert '\\' not in label
        assert '"' not in label

    def test_empty_string(self) -> None:
        """Test handling of empty strings."""
        text = TextTypstBase('')
        assert text.get() == ''


# =============================================================================
# PathTypst Tests
# =============================================================================


class TestPathTypst:
    """Tests for PathTypst class."""

    def test_backslash_to_forward_slash(self) -> None:
        """Test conversion of backslashes to forward slashes."""
        path = PathTypst(r"a\\b\\c")
        assert '/' in path.get()
        assert '\\' not in path.get()

    def test_forward_slash_unchanged(self) -> None:
        """Test that forward slashes remain unchanged."""
        path = PathTypst('x/y/z')
        assert path.get() == 'x/y/z'

    def test_mixed_slashes(self) -> None:
        """Test mixed slash handling."""
        path = PathTypst(r'a/b\\c')
        result = path.get()
        assert '\\' not in result
        assert '/' in result

    @pytest.mark.parametrize("input_path,expected_contains", [
        ('simple/path', '/'),
        (r'windows\\path', '/'),
        ('single', 'single'),
    ])
    def test_various_path_formats(self, input_path: str, expected_contains: str) -> None:
        """Test various path format inputs."""
        path = PathTypst(input_path)
        assert expected_contains in path.get()


# =============================================================================
# NameTypst Tests
# =============================================================================


class TestNameTypst:
    """Tests for NameTypst class."""

    def test_escape_asterisk(self) -> None:
        """Test asterisk escaping."""
        name = NameTypst('A* Search')
        result = name.get()
        assert r'\*' in result

    def test_escape_underscore(self) -> None:
        """Test underscore escaping."""
        name = NameTypst('snake_case_name')
        result = name.get()
        assert r'\_' in result

    def test_escape_backtick(self) -> None:
        """Test backtick escaping."""
        name = NameTypst('code with `backtick`')
        result = name.get()
        assert r'\`' in result

    def test_latex_escape_removal(self) -> None:
        """Test removal of LaTeX escape sequences."""
        name = NameTypst(r'Test \"quoted\"')
        result = name.get()
        # Should not contain the backslash-quote sequence
        assert r'\"' not in result

    def test_multiple_special_chars(self) -> None:
        """Test handling multiple special characters."""
        name = NameTypst('A*_test_`code`')
        result = name.get()
        assert r'\*' in result
        assert r'\_' in result
        assert r'\`' in result

    def test_unicode_characters(self) -> None:
        """Test handling of unicode characters."""
        name = NameTypst('中文测试')
        result = name.get()
        # Should preserve unicode
        assert '中文测试' in result


# =============================================================================
# Typst Include Tests
# =============================================================================


class TestTypstInclude:
    """Tests for typst_include function."""

    def test_typ_file_include(self, tmp_path: Path) -> None:
        """Test include for .typ files."""
        typ_file = tmp_path / 'content.typ'
        typ_file.write_text('test content')
        path = PathTypst(str(typ_file))
        result = typst_include(path)

        assert isinstance(result, list)
        assert any('#include' in s for s in result if isinstance(s, str))

    def test_tex_file_skipped(self) -> None:
        """Test include for .tex files (should be skipped)."""
        path = PathTypst('content.tex')
        result = typst_include(path)

        assert isinstance(result, list)
        assert any('LaTeX doc file skipped' in s for s in result if isinstance(s, str))
        assert not any('#include' in s for s in result if isinstance(s, str))


# =============================================================================
# Typst Label and Heading Tests
# =============================================================================


class TestTypstLabelAndHeading:
    """Tests for typst_label and typst_heading functions."""

    def test_typst_label(self) -> None:
        """Test label generation."""
        name = NameTypst('Test Section')
        result = typst_label('sec', name)

        assert isinstance(result, list)
        assert any('<sec:' in s for s in result if isinstance(s, str))

    def test_typst_heading_level1(self) -> None:
        """Test level 1 heading generation."""
        name = NameTypst('Chapter Name')
        result = typst_heading(name, level=1)

        assert isinstance(result, list)
        assert any('=' in s for s in result if isinstance(s, str))
        assert any('<ch:' in s for s in result if isinstance(s, str))

    def test_typst_heading_level2(self) -> None:
        """Test level 2 heading generation."""
        name = NameTypst('Section Name')
        result = typst_heading(name, level=2)

        assert isinstance(result, list)
        # Level 2 uses ==
        assert any('==' in s for s in result if isinstance(s, str))

    def test_typst_chapter(self) -> None:
        """Test chapter generation."""
        name = NameTypst('Test Chapter')
        result = typst_chapter(name)

        assert isinstance(result, list)
        assert any('=' in s for s in result if isinstance(s, str))
        assert any('<ch:' in s for s in result if isinstance(s, str))

    def test_typst_section(self) -> None:
        """Test section generation."""
        name = NameTypst('Test Section')
        result = typst_section(name)

        assert isinstance(result, list)
        # Should have section marker
        assert any('==' in s for s in result if isinstance(s, str))
        assert any('<sec:' in s for s in result if isinstance(s, str))


# =============================================================================
# Typst Code Listing Tests
# =============================================================================


class TestTypstCodeListing:
    """Tests for Typst code listing functions."""

    def test_listing_code_basic(self) -> None:
        """Test basic code listing generation."""
        path = PathTypst('test.cpp')
        result = typst_listing_code(path, 'cpp')

        assert isinstance(result, list)
        assert any('#raw' in s for s in result if isinstance(s, str))
        assert any('lang:' in s for s in result if isinstance(s, str))
        assert any('Path:' in s for s in result if isinstance(s, str))

    def test_listing_code_with_relative_path(self) -> None:
        """Test code listing with relative path adjustment."""
        path = PathTypst('include/util/util.hpp')
        result = typst_listing_code(path, 'cpp')

        # Check that path uses fixpath function
        assert any('fixpath(' in s for s in result if isinstance(s, str))
        assert any('include/util/util.hpp' in s for s in result if isinstance(s, str))

    def test_listing_code_range(self) -> None:
        """Test code listing with line range."""
        path = PathTypst('test.py')
        result = typst_listing_code_range(path, 'python', 10, 20)

        assert isinstance(result, list)
        assert any('#raw' in s for s in result if isinstance(s, str))
        assert any('slice' in s for s in result if isinstance(s, str))
        # Check line numbers (0-indexed, so 10-1=9 and 20)
        assert any('9' in s for s in result if isinstance(s, str))
        assert any('20' in s for s in result if isinstance(s, str))

    def test_listing_code_range_path_adjustment(self) -> None:
        """Test code listing range with path adjustment."""
        path = PathTypst('include/math/gcd.hpp')
        result = typst_listing_code_range(path, 'cpp', 1, 10)

        # Should use fixpath function
        assert any('fixpath(' in s for s in result if isinstance(s, str))
        assert any('include/math/gcd.hpp' in s for s in result if isinstance(s, str))

    @pytest.mark.parametrize("language", ['cpp', 'python', 'java', 'text'])
    def test_listing_code_various_languages(self, language: str) -> None:
        """Test code listing with various programming languages."""
        path = PathTypst('test/file')
        result = typst_listing_code(path, language)
        assert isinstance(result, list)
        assert len(result) > 0


# =============================================================================
# Constants and Edge Cases Tests
# =============================================================================


class TestConstantsAndEdgeCases:
    """Tests for constants and edge cases."""

    def test_latex_only_extensions_constant(self) -> None:
        """Test LATEX_ONLY_EXTENSIONS constant."""
        assert isinstance(LATEX_ONLY_EXTENSIONS, tuple)
        assert '.tex' in LATEX_ONLY_EXTENSIONS

    def test_path_with_leading_dotdot(self) -> None:
        """Test path that already starts with ../"""
        path = PathTypst('../already/relative')
        result = typst_listing_code(path, 'cpp')

        # Should not double-add ../
        assert '../already/relative' in str(result)
        assert not any('../../already' in s for s in result if isinstance(s, str))

    def test_typst_include_file_not_found(self) -> None:
        """Test typst_include when file does not exist."""
        path = PathTypst('nonexistent/file.typ')
        result = typst_include(path)

        assert isinstance(result, list)
        assert any('not found' in s for s in result if isinstance(s, str))
