"""Unit tests for cppmeta target content generation.

This module tests the target content generation from cppmeta files,
including include list handling and content assembly.
"""

from pathlib import Path
from typing import Any

import pytest

from libs.testcase_matrix import cppmeta_parser


pytestmark = pytest.mark.unit


# =============================================================================
# Fake Case Class for Testing
# =============================================================================


class FakeCase:
    """Fake case class for testing target content generation."""

    def get_label(self) -> str:
        return 'cat-mem'

    def get_include_list(self) -> list[str]:
        return [str(Path('inc') / 'file.h')]

    def get_content_after_include(self) -> str:
        return '// after\nline2\n'

    def get_content_main_begin(self) -> str:
        return 'first\n  second\n'


# =============================================================================
# Target Content Tests
# =============================================================================


class TestGetAllTargetContent:
    """Tests for _get_all_target_content method."""

    def test_various_content_types(
        self, tmp_path: Path, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """Test target content generation with various content types."""
        # Prepare a cppmeta parser with fake code lines
        lines = [
            '// header\n',
            '// ---<GENTC>--- begin\n',
            '// ---<GENTC>--- append A B\n',
            '// ---<GENTC>--- end\n',
            'int main() {\n',
            '// after main\n'
        ]

        parser = cppmeta_parser('f', str(tmp_path), lines)

        def fake_get_all_cases() -> tuple[int, int, int, list[FakeCase]]:
            """Return fake case data."""
            # block_begin = 1, block_end = 4, main_index = 4
            return 1, 4, 4, [FakeCase()]

        monkeypatch.setattr(parser, '_get_all_cases', fake_get_all_cases)

        results = parser._get_all_target_content()
        assert results

        target_path, code_lines = results[0]

        # Include line should be present
        assert any(
            '#include' in s for s in code_lines if isinstance(s, str)
        )

        # after_include block was added as lines
        assert any(
            'after' in s for s in code_lines if isinstance(s, str)
        )

        # main_begin lines should be indented
        assert any(
            isinstance(s, str) and s.startswith('  first')
            for s in code_lines
        )

        # Target path should include filename noext and label
        assert 'cat-mem' in target_path
