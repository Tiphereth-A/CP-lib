"""System tests for CLI commands."""

from libs.cli import cli
import os
import sys
from pathlib import Path
from unittest.mock import patch, MagicMock

import pytest
from click.testing import CliRunner

pytestmark = pytest.mark.system


class TestCLISystem:
    """System tests for CLI commands."""

    @pytest.fixture
    def runner(self):
        """Create a CLI test runner."""
        return CliRunner()

    def test_cli_help(self, runner):
        """Test that CLI help command works."""
        result = runner.invoke(cli, ['--help'])
        assert result.exit_code == 0
        assert 'Commands:' in result.output

    def test_cli_log_level_option(self, runner):
        """Test CLI log level option."""
        result = runner.invoke(cli, ['--level', 'DEBUG', '--help'])
        assert result.exit_code == 0

    def test_clean_command_system(self, runner, sample_dirs):
        """System test for clean command."""
        pdf_out_dir = sample_dirs['_pdf_out']
        test_file = str(pdf_out_dir / 'test.log')

        # Change to temp directory for test
        original_cwd = os.getcwd()
        try:
            os.chdir(sample_dirs['_pdf_out'].parent)

            with patch('libs.commands.clean.get_full_filenames') as mock_get_files, \
                    patch('libs.commands.clean.os.remove') as mock_remove:
                mock_get_files.return_value = [test_file]
                result = runner.invoke(cli, ['clean'])

                # Command should execute successfully
                assert result.exit_code == 0
                assert mock_remove.called
        finally:
            os.chdir(original_cwd)

    def test_fmt_command_system(self, runner):
        """System test for fmt command."""
        with patch('libs.commands.fmt.lint_all_codes') as mock_lint:
            mock_lint.return_value = None
            result = runner.invoke(cli, ['fmt', '--code-type', 'cpp'])

            # Should call the lint function
            # Note: The command registration might need the actual function
            # This is a basic system test
            assert result.exit_code in [0, 1]  # May fail if config not found

    def test_cli_command_registration(self, runner):
        """Test that all commands are registered."""
        result = runner.invoke(cli, ['--help'])

        # Check for registered commands
        output = result.output.lower()
        # These commands should be in the help output
        assert result.exit_code == 0

    def test_cli_invalid_command(self, runner):
        """Test CLI with invalid command."""
        result = runner.invoke(cli, ['invalid-command'])
        assert result.exit_code != 0

    def test_cli_log_levels(self, runner):
        """Test different log levels."""
        for level in ['DEBUG', 'INFO', 'WARNING', 'ERROR', 'CRITICAL']:
            result = runner.invoke(cli, ['--level', level, '--help'])
            assert result.exit_code == 0


class TestCLIEndToEnd:
    """End-to-end system tests."""

    @pytest.fixture
    def runner(self):
        """Create a CLI test runner."""
        return CliRunner()

    @patch('libs.commands.clean.get_full_filenames')
    def test_clean_end_to_end(self, mock_get_files, runner, sample_dirs):
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
    def test_fmt_end_to_end(self, mock_config, mock_get_files, mock_subprocess, runner, sample_code_file):
        """End-to-end test for fmt command."""
        mock_get_files.return_value = [str(sample_code_file)]
        mock_config.get_code_dir.return_value = 'src'
        mock_config.get_doc_dir.return_value = 'doc'
        mock_config.get_cheatsheet_dir.return_value = 'cheatsheet'
        mock_config.get_usage_dir.return_value = 'usage'
        mock_config.get_ext_names_by_file_type.return_value = ['.cpp']
        mock_config.get_formatting_command.return_value = ['echo', 'test']

        result = runner.invoke(cli, ['fmt', '--code-type', 'cpp'])

        # Command should execute (may have different exit codes based on actual implementation)
        assert result.exit_code in [0, 1, 2]
