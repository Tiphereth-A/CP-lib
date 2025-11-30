"""Integration tests for command modules."""

from libs.consts import CLEAN_EXT_NAME
from libs.commands.fmt import lint_all_codes
from libs.commands.clean import clean
import os
import subprocess
from pathlib import Path
from unittest.mock import patch, MagicMock

import pytest

pytestmark = pytest.mark.integration


class TestCleanCommand:
    """Integration tests for clean command."""

    def test_clean_removes_files(self, sample_dirs, caplog):
        """Test that clean command removes files with clean extensions."""
        pdf_out_dir = sample_dirs['_pdf_out']
        # Use mocks instead of creating real files
        test_files = [str(pdf_out_dir / f'test{ext}')
                      for ext in CLEAN_EXT_NAME[:3]]

        with patch('libs.commands.clean.get_full_filenames') as mock_get_files, \
                patch('libs.commands.clean.os.remove') as mock_remove:
            mock_get_files.return_value = test_files
            clean()

            # os.remove should be called for each file
            assert mock_remove.call_count == len(test_files)

    def test_clean_logs_removal(self, sample_dirs, caplog):
        """Test that clean command logs file removals."""
        pdf_out_dir = sample_dirs['_pdf_out']
        test_file = str(pdf_out_dir / 'test.log')

        with patch('libs.commands.clean.get_full_filenames') as mock_get_files, \
                patch('libs.commands.clean.os.remove') as mock_remove:
            mock_get_files.return_value = [test_file]
            clean()

        assert 'removed successfully' in caplog.text.lower()


class TestFmtCommand:
    """Integration tests for fmt command."""

    @patch('libs.commands.fmt.subprocess.run')
    @patch('libs.commands.fmt.get_full_filenames')
    @patch('libs.commands.fmt.CONFIG')
    def test_fmt_runs_formatting_command(self, mock_config, mock_get_files, mock_subprocess, sample_code_file, caplog):
        """Test that fmt command runs formatting commands."""
        mock_get_files.return_value = [str(sample_code_file)]

        # Mock config methods
        mock_config.get_code_dir.return_value = 'src'
        mock_config.get_doc_dir.return_value = 'doc'
        mock_config.get_cheatsheet_dir.return_value = 'cheatsheet'
        mock_config.get_usage_dir.return_value = 'usage'
        mock_config.get_ext_names_by_code_style.return_value = ['.cpp']
        mock_config.get_formatting_command.return_value = [
            'clang-format', '-i', str(sample_code_file)]

        lint_all_codes('cpp')

        # Verify subprocess.run was called
        mock_subprocess.assert_called()
        assert mock_subprocess.call_count > 0

    @patch('libs.commands.fmt.subprocess.run')
    @patch('libs.commands.fmt.get_full_filenames')
    @patch('libs.commands.fmt.CONFIG')
    def test_fmt_logs_file_count(self, mock_config, mock_get_files, mock_subprocess, sample_code_file, caplog):
        """Test that fmt command logs file count."""
        mock_get_files.return_value = [
            str(sample_code_file), str(sample_code_file)]
        mock_config.get_code_dir.return_value = 'src'
        mock_config.get_doc_dir.return_value = 'doc'
        mock_config.get_cheatsheet_dir.return_value = 'cheatsheet'
        mock_config.get_usage_dir.return_value = 'usage'
        mock_config.get_ext_names_by_code_style.return_value = ['.cpp']
        mock_config.get_formatting_command.return_value = [
            'clang-format', '-i', str(sample_code_file)]

        lint_all_codes('cpp')

        assert 'file(s) found' in caplog.text.lower()


class TestCommandIntegration:
    """Integration tests for command interactions."""

    def test_clean_with_config_integration(self, sample_dirs, test_config):
        """Test clean command integration with config."""
        pdf_out_dir = sample_dirs['_pdf_out']
        test_file = pdf_out_dir / 'test.log'
        test_file.write_text('test')

        # This tests the integration between clean command and file system
        with patch('libs.commands.clean.get_full_filenames') as mock_get_files:
            mock_get_files.return_value = [str(test_file)]
            clean()

        assert not test_file.exists()

    @patch('libs.commands.fmt.subprocess.run')
    def test_fmt_with_multiple_file_types(self, mock_subprocess, sample_dirs, test_config):
        """Test fmt command with multiple file types."""
        src_dir = sample_dirs['src']
        (src_dir / 'file1.cpp').write_text('test')
        (src_dir / 'file2.cpp').write_text('test')

        with patch('libs.commands.fmt.get_full_filenames') as mock_get_files, \
                patch('libs.commands.fmt.CONFIG', test_config):
            mock_get_files.return_value = [
                str(src_dir / 'file1.cpp'),
                str(src_dir / 'file2.cpp')
            ]
            test_config.get_formatting_command = MagicMock(
                return_value=['clang-format', '-i', ''])

            lint_all_codes('cpp')

        # Should be called for each file
        assert mock_subprocess.call_count == 2
