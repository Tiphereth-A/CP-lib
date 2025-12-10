"""Unit tests for typst_utils module."""

import pytest
from libs.typst_utils import (
    TextTypstBase, PathTypst, NameTypst, LATEX_ONLY_EXTENSIONS,
    typst_include, typst_label, typst_heading, typst_chapter, 
    typst_section, typst_listing_code, typst_listing_code_range
)

pytestmark = pytest.mark.unit


class TestTextTypstBase:
    """Tests for TextTypstBase class."""

    def test_initialization(self):
        """Test TextTypstBase initialization."""
        t = TextTypstBase('Hello_World\\')
        assert t.get() == 'Hello_World\\'

    def test_get_label_name(self):
        """Test label name generation."""
        t = TextTypstBase('Test Label')
        lbl = t.get_label_name()
        assert isinstance(lbl, str)
        assert lbl == 'test-label'

    def test_get_label_name_with_special_chars(self):
        """Test label name generation with special characters."""
        t = TextTypstBase('A* Algorithm')
        lbl = t.get_label_name()
        assert '-' in lbl
        assert '*' not in lbl

    def test_get_label_name_with_latex_escape(self):
        """Test label name with LaTeX escape sequences."""
        t = TextTypstBase(r'M\"obius')
        lbl = t.get_label_name()
        # Should remove backslash and quotes
        assert '\\' not in lbl
        assert '"' not in lbl


class TestPathTypst:
    """Tests for PathTypst class."""

    def test_backslash_to_forward_slash(self):
        """Test conversion of backslashes to forward slashes."""
        p = PathTypst(r"a\\b\\c")
        assert '/' in p.get()
        assert '\\' not in p.get()

    def test_forward_slash_unchanged(self):
        """Test that forward slashes remain unchanged."""
        p = PathTypst('x/y/z')
        assert p.get() == 'x/y/z'

    def test_mixed_slashes(self):
        """Test mixed slash handling."""
        p = PathTypst(r'a/b\\c')
        result = p.get()
        assert '\\' not in result
        assert '/' in result


class TestNameTypst:
    """Tests for NameTypst class."""

    def test_escape_asterisk(self):
        """Test asterisk escaping."""
        n = NameTypst('A* Search')
        result = n.get()
        assert r'\*' in result

    def test_escape_underscore(self):
        """Test underscore escaping."""
        n = NameTypst('snake_case_name')
        result = n.get()
        assert r'\_' in result

    def test_escape_backtick(self):
        """Test backtick escaping."""
        n = NameTypst('code with `backtick`')
        result = n.get()
        assert r'\`' in result

    def test_latex_escape_removal(self):
        """Test removal of LaTeX escape sequences."""
        n = NameTypst(r'Test \"quoted\"')
        result = n.get()
        # Should not contain the backslash-quote sequence
        assert r'\"' not in result

    def test_multiple_special_chars(self):
        """Test handling multiple special characters."""
        n = NameTypst('A*_test_`code`')
        result = n.get()
        assert r'\*' in result
        assert r'\_' in result
        assert r'\`' in result


class TestTypstFunctions:
    """Tests for Typst utility functions."""

    def test_typst_include_typ_file(self, tmp_path):
        """Test include for .typ files."""
        # Create a temporary .typ file so it exists
        typ_file = tmp_path / 'content.typ'
        typ_file.write_text('test content')
        p = PathTypst(str(typ_file))
        result = typst_include(p)
        assert isinstance(result, list)
        assert any('#include' in s for s in result if isinstance(s, str))

    def test_typst_include_tex_file(self):
        """Test include for .tex files (should be skipped)."""
        p = PathTypst('content.tex')
        result = typst_include(p)
        assert isinstance(result, list)
        assert any('LaTeX doc file skipped' in s for s in result if isinstance(s, str))
        assert not any('#include' in s for s in result if isinstance(s, str))

    def test_typst_label(self):
        """Test label generation."""
        name = NameTypst('Test Section')
        result = typst_label('sec', name)
        assert isinstance(result, list)
        assert any('<sec:' in s for s in result if isinstance(s, str))

    def test_typst_heading(self):
        """Test heading generation."""
        name = NameTypst('Chapter Name')
        result = typst_heading(name, level=1)
        assert isinstance(result, list)
        assert any('=' in s for s in result if isinstance(s, str))
        assert any('<ch:' in s for s in result if isinstance(s, str))

    def test_typst_heading_level2(self):
        """Test level 2 heading generation."""
        name = NameTypst('Section Name')
        result = typst_heading(name, level=2)
        assert isinstance(result, list)
        # Level 2 uses ==
        assert any('==' in s for s in result if isinstance(s, str))

    def test_typst_chapter(self):
        """Test chapter generation."""
        name = NameTypst('Test Chapter')
        result = typst_chapter(name)
        assert isinstance(result, list)
        assert any('=' in s for s in result if isinstance(s, str))
        assert any('<ch:' in s for s in result if isinstance(s, str))

    def test_typst_section(self):
        """Test section generation."""
        name = NameTypst('Test Section')
        result = typst_section(name)
        assert isinstance(result, list)
        # Should have newline at start and section marker
        assert any('==' in s for s in result if isinstance(s, str))
        assert any('<sec:' in s for s in result if isinstance(s, str))

    def test_typst_listing_code(self):
        """Test code listing generation."""
        p = PathTypst('test.cpp')
        result = typst_listing_code(p, 'cpp')
        assert isinstance(result, list)
        assert any('#raw' in s for s in result if isinstance(s, str))
        assert any('lang:' in s for s in result if isinstance(s, str))
        assert any('Path:' in s for s in result if isinstance(s, str))

    def test_typst_listing_code_with_relative_path(self):
        """Test code listing with relative path adjustment."""
        p = PathTypst('include/util/util.hpp')
        result = typst_listing_code(p, 'cpp')
        # Check that path uses fixpath function
        assert any('fixpath(' in s for s in result if isinstance(s, str))
        assert any('include/util/util.hpp' in s for s in result if isinstance(s, str))

    def test_typst_listing_code_range(self):
        """Test code listing with line range."""
        p = PathTypst('test.py')
        result = typst_listing_code_range(p, 'python', 10, 20)
        assert isinstance(result, list)
        assert any('#raw' in s for s in result if isinstance(s, str))
        assert any('slice' in s for s in result if isinstance(s, str))
        # Check line numbers (0-indexed, so 10-1=9 and 20)
        assert any('9' in s for s in result if isinstance(s, str))
        assert any('20' in s for s in result if isinstance(s, str))

    def test_typst_listing_code_range_path_adjustment(self):
        """Test code listing range with path adjustment."""
        p = PathTypst('include/math/gcd.hpp')
        result = typst_listing_code_range(p, 'cpp', 1, 10)
        # Should use fixpath function
        assert any('fixpath(' in s for s in result if isinstance(s, str))
        assert any('include/math/gcd.hpp' in s for s in result if isinstance(s, str))


class TestConstantsAndEdgeCases:
    """Tests for constants and edge cases."""

    def test_latex_only_extensions_constant(self):
        """Test LATEX_ONLY_EXTENSIONS constant."""
        assert isinstance(LATEX_ONLY_EXTENSIONS, tuple)
        assert '.tex' in LATEX_ONLY_EXTENSIONS

    def test_empty_string_handling(self):
        """Test handling of empty strings."""
        t = TextTypstBase('')
        assert t.get() == ''

    def test_special_unicode_characters(self):
        """Test handling of unicode characters."""
        n = NameTypst('中文测试')
        result = n.get()
        # Should preserve unicode
        assert '中文测试' in result

    def test_path_with_leading_dotdot(self):
        """Test path that already starts with ../"""
        p = PathTypst('../already/relative')
        result = typst_listing_code(p, 'cpp')
        # Should not double-add ../
        assert '../already/relative' in str(result)
        assert not any('../../already' in s for s in result if isinstance(s, str))
