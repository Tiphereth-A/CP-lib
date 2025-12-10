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
