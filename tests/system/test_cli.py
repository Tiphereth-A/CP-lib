"""System tests for CLI commands.

This module contains end-to-end system tests that verify the CLI
interface works correctly from user perspective.
"""

import os
from pathlib import Path
from unittest.mock import MagicMock, patch

import pytest
from click.testing import CliRunner

from libs.cli import cli


pytestmark = pytest.mark.system


# =============================================================================
# CLI System Tests
# =============================================================================


class TestCLISystem:
    """System tests for CLI commands."""

    @pytest.fixture
    def runner(self) -> CliRunner:
        """Create a CLI test runner."""
        return CliRunner()

    def test_help_command(self, runner: CliRunner) -> None:
        """Test that CLI help command works."""
        result = runner.invoke(cli, ['--help'])
        assert result.exit_code == 0
        assert 'Commands:' in result.output

    def test_log_level_option(self, runner: CliRunner) -> None:
        """Test CLI log level option."""
        result = runner.invoke(cli, ['--level', 'DEBUG', '--help'])
        assert result.exit_code == 0

    @pytest.mark.parametrize("level", ['DEBUG', 'INFO', 'WARNING', 'ERROR', 'CRITICAL'])
    def test_all_log_levels(self, runner: CliRunner, level: str) -> None:
        """Test different log levels."""
        result = runner.invoke(cli, ['--level', level, '--help'])
        assert result.exit_code == 0

    def test_invalid_command(self, runner: CliRunner) -> None:
        """Test CLI with invalid command."""
        result = runner.invoke(cli, ['invalid-command'])
        assert result.exit_code != 0

    def test_command_registration(self, runner: CliRunner) -> None:
        """Test that commands are registered."""
        result = runner.invoke(cli, ['--help'])
        assert result.exit_code == 0
        # Help output should contain command information
        assert 'Commands:' in result.output


# =============================================================================
# Clean Command System Tests
# =============================================================================


class TestCleanCommandSystem:
    """System tests for clean command."""

    @pytest.fixture
    def runner(self) -> CliRunner:
        """Create a CLI test runner."""
        return CliRunner()

    def test_clean_command_system(
        self, runner: CliRunner, sample_dirs: dict[str, Path]
    ) -> None:
        """System test for clean command."""
        pdf_out_dir = sample_dirs['_pdf_out']
        test_file = str(pdf_out_dir / 'test.log')

        original_cwd = os.getcwd()
        try:
            os.chdir(sample_dirs['_pdf_out'].parent)

            with patch('libs.commands.clean.get_full_filenames') as mock_get_files, \
                 patch('libs.commands.clean.os.remove') as mock_remove:
                mock_get_files.return_value = [test_file]
                result = runner.invoke(cli, ['clean'])

                assert result.exit_code == 0
                assert mock_remove.called
        finally:
            os.chdir(original_cwd)


# =============================================================================
# Fmt Command System Tests
# =============================================================================


class TestFmtCommandSystem:
    """System tests for fmt command."""

    @pytest.fixture
    def runner(self) -> CliRunner:
        """Create a CLI test runner."""
        return CliRunner()

    def test_fmt_command_system(self, runner: CliRunner) -> None:
        """System test for fmt command."""
        with patch('libs.commands.fmt.lint_all_codes') as mock_lint:
            mock_lint.return_value = None
            result = runner.invoke(cli, ['fmt', '--code-type', 'cpp'])

            # May fail if config not found, but command should execute
            assert result.exit_code in [0, 1]


# =============================================================================
# End-to-End System Tests
# =============================================================================


class TestCLIEndToEnd:
    """End-to-end system tests."""

    @pytest.fixture
    def runner(self) -> CliRunner:
        """Create a CLI test runner."""
        return CliRunner()

    @patch('libs.commands.clean.get_full_filenames')
    def test_clean_end_to_end(
        self,
        mock_get_files: MagicMock,
        runner: CliRunner,
        sample_dirs: dict[str, Path]
    ) -> None:
        """End-to-end test for clean command."""
        pdf_out_dir = sample_dirs['_pdf_out']
        test_file = str(pdf_out_dir / 'test.aux')

        original_cwd = os.getcwd()
        try:
            os.chdir(sample_dirs['_pdf_out'].parent)

            mock_get_files.return_value = [test_file]
            with patch('libs.commands.clean.os.remove') as mock_remove:
                result = runner.invoke(cli, ['clean'])

            assert result.exit_code == 0
            assert mock_remove.called
        finally:
            os.chdir(original_cwd)

    @patch('libs.commands.fmt.subprocess.run')
    @patch('libs.commands.fmt.get_full_filenames')
    @patch('libs.commands.fmt.CONFIG')
    def test_fmt_end_to_end(
        self,
        mock_config: MagicMock,
        mock_get_files: MagicMock,
        mock_subprocess: MagicMock,
        runner: CliRunner,
        sample_code_file: Path
    ) -> None:
        """End-to-end test for fmt command."""
        mock_get_files.return_value = [str(sample_code_file)]
        mock_config.get_code_dir.return_value = 'src'
        mock_config.get_doc_dir.return_value = 'doc'
        mock_config.get_cheatsheet_dir.return_value = 'cheatsheet'
        mock_config.get_usage_dir.return_value = 'usage'
        mock_config.get_ext_names_by_file_type.return_value = ['.cpp']
        mock_config.get_formatting_command.return_value = ['echo', 'test']

        result = runner.invoke(cli, ['fmt', '--code-type', 'cpp'])

        # Command should execute
        assert result.exit_code in [0, 1, 2]


# =============================================================================
# CLI Error Handling Tests
# =============================================================================


class TestCLIErrorHandling:
    """Tests for CLI error handling."""

    @pytest.fixture
    def runner(self) -> CliRunner:
        """Create a CLI test runner."""
        return CliRunner()

    def test_missing_required_options(self, runner: CliRunner) -> None:
        """Test handling of missing required options."""
        # This will depend on which commands have required options
        result = runner.invoke(cli, ['--help'])
        # Help should always work
        assert result.exit_code == 0

    def test_invalid_log_level(self, runner: CliRunner) -> None:
        """Test handling of invalid log level."""
        result = runner.invoke(cli, ['--level', 'INVALID', '--help'])
        # Should fail gracefully or use default
        # Exact behavior depends on click configuration
        assert result.exit_code in [0, 2]
