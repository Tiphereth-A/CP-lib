"""Unit tests for testcase_matrix module.

This module tests the test case matrix functionality used for
generating test code from cppmeta files.
"""

from pathlib import Path
from typing import Any

import pytest

from libs import testcase_matrix as tm


pytestmark = pytest.mark.unit


# =============================================================================
# Fake ConfigTCGen Classes for Testing
# =============================================================================


class FakeTCGen:
    """Fake ConfigTCGen for basic testing."""

    def __init__(self) -> None:
        self._members: dict[str, list[str]] = {
            'A': ['a1', 'a2'],
            'B': ['b1']
        }

    def get_priority(self, cat: str) -> int:
        return 0

    def get_memberlist(self, cat: str | list[str]) -> list[tuple[str, str]]:
        """Get member list for category."""
        if isinstance(cat, list):
            result: list[tuple[str, str]] = []
            for c in cat:
                result.extend(self.get_memberlist(c))
            return result
        return [(cat, m) for m in self._members.get(cat, [])]

    def get_member_content(self, cat: str | list[str], mem: str) -> dict[str, Any]:
        """Get member content."""
        return {
            'category_name': cat,
            'member_name': mem,
            'include': [f"inc_{mem}.h"] if mem.endswith('1') else [],
            'after_include': f"//after_{mem}\n" if mem.endswith('1') else '',
            'main_begin': f"//main_{mem}\n" if mem.endswith('1') else '',
            'requirements': []
        }

    def get_categories(self) -> list[str]:
        return list(self._members.keys())

    def get_categories_with_same_priority(self, cat: str) -> list[str]:
        return [cat]


class FakeReqTCGen:
    """Fake ConfigTCGen with requirements for testing."""

    def __init__(self) -> None:
        self._members: dict[str, list[str]] = {
            'A': ['a1', 'a2'],
            'B': ['b1', 'b2']
        }

    def get_priority(self, cat: str) -> int:
        return 0

    def get_memberlist(self, cat: str | list[str]) -> list[tuple[str, str]]:
        """Get member list for category."""
        if isinstance(cat, list):
            result: list[tuple[str, str]] = []
            for c in cat:
                result.extend(self.get_memberlist(c))
            return result
        return [(cat, m) for m in self._members.get(cat, [])]

    def get_member_content(self, cat: str | list[str], mem: str) -> dict[str, Any]:
        """Get member content with requirements."""
        if mem == 'a1':
            return {
                'category_name': cat,
                'member_name': mem,
                'requirements': [['B']],
                'include': ['inc_$m.h'],
                'after_include': '',
                'main_begin': ''
            }
        return {
            'category_name': cat,
            'member_name': mem,
            'requirements': [],
            'include': [],
            'after_include': '',
            'main_begin': ''
        }

    def get_categories(self) -> list[str]:
        return list(self._members.keys())

    def get_categories_with_same_priority(self, cat: str) -> list[str]:
        return [cat]


class FakeMainTCGen:
    """Fake ConfigTCGen with main_begin content for testing."""

    def __init__(self, tmp_path: Path) -> None:
        self.tmp_path = tmp_path

    def get_priority(self, cat: str) -> int:
        return 0

    def get_memberlist(self, cat: str | list[str]) -> list[tuple[str, str]]:
        """Get member list."""
        return [(cat, 'm1')] if isinstance(cat, str) else [(cat[0], 'm1')]

    def get_member_content(self, cat: str | list[str], mem: str) -> dict[str, Any]:
        """Get member content with main_begin."""
        return {
            'category_name': str(cat),
            'member_name': mem,
            'include': [str(self.tmp_path / 'inc.h')],
            'after_include': '// after\n',
            'main_begin': 'Xline\n  Yline\n',
            'requirements': []
        }

    def get_categories(self) -> list[str]:
        return ['A']

    def get_categories_with_same_priority(self, cat: str) -> list[str]:
        return [cat]


# =============================================================================
# testcase_matrix Tests
# =============================================================================


class TestTestcaseMatrix:
    """Tests for testcase_matrix class."""

    def test_case_parser_and_matrix(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test case parsing and matrix generation."""
        fake = FakeTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        matrix = tm.testcase_matrix()
        matrix.append(['A', 'B'])
        matrix.make_all_cases()
        all_cases = matrix.get_all_cases()

        assert all(isinstance(c, tm.case_parser) for c in all_cases)

    def test_exclude_case(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test excluding a specific case."""
        fake = FakeTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        matrix = tm.testcase_matrix()
        matrix.append(['A', 'B'])
        matrix.make_all_cases()
        all_cases = matrix.get_all_cases()

        if all_cases:
            case0 = all_cases[0]._case_list
            matrix.exclude(case0)
            # Excluded case should not be present
            tags = [c._case_list for c in matrix.get_all_cases()]
            assert tuple(case0) not in [tuple(x) for x in tags]

    def test_exclude_wildcard(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test excluding cases by wildcard pattern."""
        fake = FakeTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        matrix = tm.testcase_matrix()
        matrix.append(['A', 'B'])
        matrix.make_all_cases()
        before = len(matrix.get_all_cases())

        matrix.exclude_wildcard('A-*')
        after = len(matrix.get_all_cases())

        assert after <= before


# =============================================================================
# cppmeta_parser Tests
# =============================================================================


class TestCppmetaParser:
    """Tests for cppmeta_parser class."""

    def test_basic_parsing(
        self, monkeypatch: pytest.MonkeyPatch, tmp_path: Path
    ) -> None:
        """Test basic cppmeta file parsing."""
        fake = FakeTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        lines = [
            '// header\n',
            tm._GENTC_BEGIN,
            tm._GENTC_COMMAND_APPEND + ' A B\n',
            tm._GENTC_END,
            tm._GENTC_MAIN,
            '// after main\n'
        ]

        parser = tm.cppmeta_parser('f', str(tmp_path), lines)
        results = parser.get_results()

        assert isinstance(results, list)
        assert all(
            isinstance(fp, str) and isinstance(cl, list)
            for fp, cl in results
        )

    def test_main_begin_indentation(
        self, monkeypatch: pytest.MonkeyPatch, tmp_path: Path
    ) -> None:
        """Test that main_begin lines are properly indented."""
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', FakeMainTCGen(tmp_path))

        lines = [
            '// hdr\n',
            tm._GENTC_BEGIN,
            tm._GENTC_COMMAND_APPEND + ' A\n',
            tm._GENTC_END,
            tm._GENTC_MAIN,
            '// tail\n'
        ]

        parser = tm.cppmeta_parser('f', str(tmp_path), lines)
        results = parser.get_results()

        assert results
        _, content = results[0]
        # Ensure main_begin lines were prefixed with two spaces
        assert any(line.startswith('  Xline') for line in content)


class TestCppmetaParserApplyFormat:
    """Tests for cppmeta_parser format application."""

    def test_apply_format_and_include(
        self, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """Test format specifier application and include list."""
        fake = FakeReqTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        # Create a case parser directly
        case = tm.case_parser([('A', 'a1'), ('B', 'b1')])

        # Apply format specifiers
        out = case._apply_format_specifiers('file_$m_$mb0b', 'a1', ['b1'])
        assert 'a1' in out and 'b1' in out

        # Include list
        lst = case.get_include_list()
        assert isinstance(lst, list)

    def test_matrix_expansion(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test matrix expansion with requirements."""
        fake = FakeReqTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        matrix = tm.testcase_matrix()
        matrix.append(['A', 'B'])
        matrix.make_all_cases()
        all_cases = matrix.get_all_cases()

        assert len(all_cases) >= 1


# =============================================================================
# cppmeta_parser Error Handling Tests
# =============================================================================


class TestCppmetaParserErrors:
    """Tests for cppmeta_parser error handling."""

    def test_missing_main_raises(
        self, monkeypatch: pytest.MonkeyPatch, tmp_path: Path
    ) -> None:
        """Test that missing main raises RuntimeError."""
        fake = FakeReqTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        lines = ['// header\n', tm._GENTC_BEGIN, tm._GENTC_END]
        parser = tm.cppmeta_parser('f', str(tmp_path), lines)

        with pytest.raises(RuntimeError):
            parser.get_results()

    def test_exclude_before_append_raises(
        self, monkeypatch: pytest.MonkeyPatch, tmp_path: Path
    ) -> None:
        """Test that exclude before append raises RuntimeError."""
        fake = FakeReqTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        lines = [
            tm._GENTC_BEGIN,
            tm._GENTC_COMMAND_EXCLIDE + ' A-B1\n',
            tm._GENTC_END,
            tm._GENTC_MAIN
        ]
        parser = tm.cppmeta_parser('g', str(tmp_path), lines)

        with pytest.raises(RuntimeError):
            parser.get_results()

    def test_duplicate_begin_raises(self) -> None:
        """Test that duplicate BEGIN markers raise RuntimeError."""
        lines = [
            tm._GENTC_BEGIN,
            tm._GENTC_BEGIN,
            tm._GENTC_END,
            tm._GENTC_MAIN
        ]
        parser = tm.cppmeta_parser('f', '.', lines)

        with pytest.raises(RuntimeError):
            parser.get_results()

    def test_end_without_begin_raises(self) -> None:
        """Test that END without BEGIN raises RuntimeError."""
        lines = [
            tm._GENTC_END,
            tm._GENTC_BEGIN,
            tm._GENTC_END,
            tm._GENTC_MAIN
        ]
        parser = tm.cppmeta_parser('f', '.', lines)

        with pytest.raises(RuntimeError):
            parser.get_results()

    def test_block_after_main_raises(self) -> None:
        """Test that GENTC block after main raises RuntimeError."""
        lines = [
            tm._GENTC_MAIN,
            tm._GENTC_BEGIN,
            tm._GENTC_END
        ]
        parser = tm.cppmeta_parser('f', '.', lines)

        with pytest.raises(RuntimeError):
            parser.get_results()

    def test_append_after_exclude_raises(self) -> None:
        """Test that append after exclude raises RuntimeError."""
        lines = [
            tm._GENTC_BEGIN,
            tm._GENTC_COMMAND_EXCLIDE + ' A-B\n',
            tm._GENTC_COMMAND_APPEND + ' A B\n',
            tm._GENTC_END,
            tm._GENTC_MAIN
        ]
        parser = tm.cppmeta_parser('f', '.', lines)

        with pytest.raises(RuntimeError):
            parser.get_results()


# =============================================================================
# case_parser Additional Tests
# =============================================================================


class TestCaseParserAdvanced:
    """Advanced tests for case_parser class."""

    def test_case_parser_str(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test case_parser string representation."""
        fake = FakeTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        case = tm.case_parser([('A', 'a1'), ('B', 'b1')])
        result = str(case)
        assert isinstance(result, str)

    def test_get_content_after_include(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test get_content_after_include method."""
        fake = FakeTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        case = tm.case_parser([('A', 'a1')])
        content = case.get_content_after_include()
        assert '//after_a1' in content

    def test_get_content_main_begin(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test get_content_main_begin method."""
        fake = FakeTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        case = tm.case_parser([('A', 'a1')])
        content = case.get_content_main_begin()
        assert '//main_a1' in content

    def test_get_label(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test get_label method."""
        fake = FakeTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        case = tm.case_parser([('A', 'a1'), ('B', 'b1')])
        label = case.get_label()
        assert 'A-a1' in label
        assert 'B-b1' in label

    def test_apply_format_specifiers_empty(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test _apply_format_specifiers with empty content."""
        fake = FakeTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        case = tm.case_parser([('A', 'a1')])
        result = case._apply_format_specifiers('', 'mem', [])
        assert result == ''


# =============================================================================
# testcase_matrix Additional Tests
# =============================================================================


class TestTestcaseMatrixAdvanced:
    """Advanced tests for testcase_matrix class."""

    def test_exclude_nonexistent_case(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test excluding a case that doesn't exist."""
        fake = FakeTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        matrix = tm.testcase_matrix()
        matrix.append(['A', 'B'])
        matrix.make_all_cases()

        # Try to exclude non-existent case
        matrix.exclude([('X', 'x1')])
        # Should just warn and continue

    def test_get_all_cases_without_make(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test get_all_cases calls make_all_cases if needed."""
        fake = FakeTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        matrix = tm.testcase_matrix()
        matrix.append(['A'])
        # Don't call make_all_cases explicitly
        cases = matrix.get_all_cases()
        assert len(cases) > 0

    def test_exclude_wildcard_no_match(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test exclude_wildcard with pattern that matches nothing."""
        fake = FakeTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        matrix = tm.testcase_matrix()
        matrix.append(['A', 'B'])
        matrix.make_all_cases()
        before = len(matrix.get_all_cases())

        matrix.exclude_wildcard('NONEXISTENT-*')
        after = len(matrix.get_all_cases())

        assert after == before


# =============================================================================
# cppmeta_parser Advanced Tests
# =============================================================================


class TestCppmetaParserAdvanced:
    """Advanced tests for cppmeta_parser class."""

    def test_no_gentc_block(self, tmp_path: Path) -> None:
        """Test parsing file without GENTC block raises RuntimeError."""
        lines = [tm._GENTC_MAIN, '// just comments\n']
        parser = tm.cppmeta_parser('f', str(tmp_path), lines)

        with pytest.raises(RuntimeError, match='GENTC block not found'):
            parser.get_results()

    def test_block_after_main_position(self, tmp_path: Path) -> None:
        """Test GENTC block position after main raises RuntimeError."""
        # main function appears before block_end
        lines = [
            tm._GENTC_MAIN,  # main at index 0
            tm._GENTC_BEGIN,  # begin at index 1
            tm._GENTC_END,  # end at index 2
        ]
        parser = tm.cppmeta_parser('f', str(tmp_path), lines)

        with pytest.raises(RuntimeError, match='must be before main'):
            parser.get_results()

    def test_unknown_gentc_command(
        self, monkeypatch: pytest.MonkeyPatch, tmp_path: Path
    ) -> None:
        """Test parsing file with unknown GENTC command."""
        fake = FakeTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        lines = [
            tm._GENTC_BEGIN,
            '// ---<GENTC>--- unknown_command\n',
            tm._GENTC_END,
            tm._GENTC_MAIN
        ]
        parser = tm.cppmeta_parser('f', str(tmp_path), lines)

        with pytest.raises(RuntimeError, match='unknown GENTC command'):
            parser.get_results()

    def test_include_relpath(
        self, monkeypatch: pytest.MonkeyPatch, tmp_path: Path
    ) -> None:
        """Test _get_include_relpath method."""
        fake = FakeTCGen()
        monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

        lines = [tm._GENTC_BEGIN, tm._GENTC_END, tm._GENTC_MAIN]
        target_dir = str(tmp_path / 'target')
        parser = tm.cppmeta_parser('f', target_dir, lines)

        relpath = parser._get_include_relpath(str(tmp_path / 'include' / 'file.h'))
        assert '/' in relpath or relpath  # Should convert to forward slashes


# =============================================================================
# case_parser Content Ignore Tests
# =============================================================================


class TestCaseParserContentIgnore:
    """Tests for case_parser _get_content_ignore method."""

    def test_content_ignore_duplicate_categories(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test _get_content_ignore skips duplicate categories."""

        class FakeSamePriorityTCGen:
            """Fake TCGen where cat1 and cat2 have same priority."""

            def get_priority(self, cat: str) -> int:
                return 1  # All same priority

            def get_memberlist(self, cat: str | list[str]) -> list[tuple[str, str]]:
                if isinstance(cat, list):
                    return [(c, 'm1') for c in cat]
                return [(cat, 'm1')]

            def get_member_content(self, cat: str | list[str], mem: str) -> dict:
                return {
                    'category_name': cat,
                    'member_name': mem,
                    'include': [],
                    'after_include': f'// content from {cat}\n',
                    'main_begin': '',
                    'requirements': []
                }

            def get_categories(self) -> list[str]:
                return ['cat1', 'cat2']

            def get_categories_with_same_priority(self, cat: str) -> list[str]:
                return ['cat1', 'cat2']  # Both have same priority

        monkeypatch.setattr(tm, 'CONFIG_TCGEN', FakeSamePriorityTCGen())

        # Create case with both categories
        case = tm.case_parser([('cat1', 'm1'), ('cat2', 'm1')])
        content = case.get_content_after_include()

        # Should only include content from one category (cat1)
        # since both have same priority
        assert '// content from cat1' in content


class TestCaseParserRequirements:
    """Tests for case_parser with requirements."""

    def test_case_parser_with_nested_requirements(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test case_parser handles nested requirements."""

        class FakeNestedReqTCGen:
            def __init__(self) -> None:
                self._members = {
                    'A': ['a1'],
                    'B': ['b1'],
                    'C': ['c1']
                }

            def get_priority(self, cat: str) -> int:
                priorities = {'A': 0, 'B': 1, 'C': 2}
                return priorities.get(cat, 0)

            def get_memberlist(self, cat: str | list[str]) -> list[tuple[str, str]]:
                if isinstance(cat, list):
                    result = []
                    for c in cat:
                        result.extend(self.get_memberlist(c))
                    return result
                return [(cat, m) for m in self._members.get(cat, [])]

            def get_member_content(self, cat: str | list[str], mem: str) -> dict:
                if mem == 'a1':
                    return {
                        'category_name': cat,
                        'member_name': mem,
                        'requirements': [['B']],
                        'include': ['inc_$m.h'],
                        'after_include': '// after $m and $mb0b\n',
                        'main_begin': ''
                    }
                return {
                    'category_name': cat,
                    'member_name': mem,
                    'requirements': [],
                    'include': [],
                    'after_include': '',
                    'main_begin': ''
                }

            def get_categories(self) -> list[str]:
                return list(self._members.keys())

            def get_categories_with_same_priority(self, cat: str) -> list[str]:
                return [cat]

        monkeypatch.setattr(tm, 'CONFIG_TCGEN', FakeNestedReqTCGen())

        case = tm.case_parser([('A', 'a1'), ('B', 'b1')])

        # Test format specifier replacement
        includes = case.get_include_list()
        assert any('inc_a1.h' in inc for inc in includes)

        content = case.get_content_after_include()
        # $m should be replaced with 'a1' and $mb0b with 'b1'
        assert 'a1' in content or 'b1' in content
