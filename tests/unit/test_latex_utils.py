"""Unit tests for latex_utils module.

This module tests the LaTeX utility classes and functions used
for generating LaTeX output in the notebook generation process.
"""

import pytest

from libs.latex_utils import (
    NameLaTeX,
    PathLaTeX,
    TextLaTeXBase,
    latex_chapter,
    latex_input,
    latex_label,
    latex_listing_code,
    latex_listing_code_range,
    latex_section,
)


pytestmark = pytest.mark.unit


# =============================================================================
# TextLaTeXBase Tests
# =============================================================================


class TestTextLaTeXBase:
    """Tests for TextLaTeXBase class."""

    def test_get_returns_original_text(self) -> None:
        """Test that get() returns the original text."""
        text = TextLaTeXBase('Hello_World\\')
        assert text.get() == 'Hello_World\\'

    def test_get_label_name(self) -> None:
        """Test label name generation."""
        text = TextLaTeXBase('Hello_World\\')
        label = text.get_label_name()
        assert isinstance(label, str)

    def test_get_label_name_with_spaces(self) -> None:
        """Test label name with spaces."""
        text = TextLaTeXBase('Hello World')
        label = text.get_label_name()
        assert isinstance(label, str)


# =============================================================================
# PathLaTeX Tests
# =============================================================================


class TestPathLaTeX:
    """Tests for PathLaTeX class."""

    def test_backslash_conversion(self) -> None:
        """Test conversion of backslashes to forward slashes."""
        path = PathLaTeX(r"a\\b\\c")
        assert '/' in path.get()

    def test_forward_slash_preserved(self) -> None:
        """Test that forward slashes are preserved."""
        path = PathLaTeX('x/y/z')
        result = path.get()
        assert '/' in result

    @pytest.mark.parametrize("input_path", [
        'simple/path',
        'path/with/many/parts',
        r'windows\\style\\path',
    ])
    def test_various_path_formats(self, input_path: str) -> None:
        """Test various path format inputs."""
        path = PathLaTeX(input_path)
        result = path.get()
        assert isinstance(result, str)


# =============================================================================
# NameLaTeX Tests
# =============================================================================


class TestNameLaTeX:
    """Tests for NameLaTeX class."""

    def test_underscore_replacement(self) -> None:
        """Test that underscores are replaced with spaces."""
        name = NameLaTeX('some_name')
        assert ' ' in name.get()

    def test_no_underscore(self) -> None:
        """Test name without underscores."""
        name = NameLaTeX('simple')
        assert name.get() == 'simple'


# =============================================================================
# LaTeX Wrapper Function Tests
# =============================================================================


class TestLaTeXWrappers:
    """Tests for LaTeX wrapper functions."""

    def test_latex_input(self) -> None:
        """Test latex_input returns a list."""
        path = PathLaTeX('x/y')
        result = latex_input(path)
        assert isinstance(result, list)

    def test_latex_label(self) -> None:
        """Test latex_label generates valid output."""
        name = NameLaTeX('Test')
        result = latex_label('pre', name)
        assert isinstance(result, list)

    def test_latex_chapter(self) -> None:
        """Test latex_chapter generates chapter markup."""
        name = NameLaTeX('Chap_Name')
        result = latex_chapter(name)
        assert any('\\chapter' in s for s in result if isinstance(s, str))

    def test_latex_section(self) -> None:
        """Test latex_section generates section markup."""
        name = NameLaTeX('Sec_Name')
        result = latex_section(name)
        assert any('section' in s for s in result if isinstance(s, str))


# =============================================================================
# LaTeX Code Listing Tests
# =============================================================================


class TestLaTeXCodeListing:
    """Tests for LaTeX code listing functions."""

    def test_listing_code_basic(self) -> None:
        """Test basic code listing generation."""
        path = PathLaTeX('a/b')
        result = latex_listing_code(path, 'cpp')
        assert any('inputminted' in s for s in result if isinstance(s, str))

    def test_listing_code_range(self) -> None:
        """Test code listing with line range."""
        path = PathLaTeX('a/b')
        result = latex_listing_code_range(path, 'py', 1, 3)
        assert any(
            'firstline' in s or 'lastline' in s
            for s in result if isinstance(s, str)
        )

    @pytest.mark.parametrize("language", ['cpp', 'python', 'java', 'text'])
    def test_listing_code_various_languages(self, language: str) -> None:
        """Test code listing with various programming languages."""
        path = PathLaTeX('test/file')
        result = latex_listing_code(path, language)
        assert isinstance(result, list)
        assert len(result) > 0
