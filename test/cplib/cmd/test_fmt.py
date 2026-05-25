import io
from unittest.mock import patch

import pytest
from click.testing import CliRunner

from libs.cmd.fmt import lint_all_codes


@pytest.mark.unit
class TestFmtCommands:
    def test_lint_all_codes_no_failures(self, tmp_path):
        (tmp_path / 'a.py').write_text('x=1\n')
        with patch('libs.cmd.fmt.run_command', return_value=[]) as mock_run:
            lint_all_codes([str(tmp_path / 'a.py')], 4, True)
            mock_run.assert_called_once()

    def test_lint_all_codes_with_failures_logs(self, tmp_path, caplog):
        import logging

        (tmp_path / 'a.py').write_text('x=1\n')
        with patch('libs.cmd.fmt.run_command', return_value=['a.py']):
            with caplog.at_level(logging.ERROR):
                lint_all_codes([str(tmp_path / 'a.py')], 1, True)
        assert caplog.messages == ['1 file(s) failed for py:', '  a.py']

    def test_fmt_cli_registered(self, cli):
        assert 'fmt' in cli.commands

    def test_fmt_cli_invocation(self, cli, tmp_path):
        runner = CliRunner()
        file_path = tmp_path / 'a.py'
        file_path.write_text('x=1\n')
        with patch('libs.cmd.fmt.run_command', return_value=[]):
            result = runner.invoke(
                cli, ['fmt', str(file_path), '-j', '2'])
        assert result.exit_code == 0

    def test_lint_all_codes_skips_when_version_too_low(self, tmp_path, caplog):
        import logging

        file_path = tmp_path / 'a.cpp'
        file_path.write_text('int main() {}\n')
        with patch('libs.cmd.fmt.os.popen', return_value=io.StringIO('clang-format version 1.0.0 (mock)')):
            with patch('libs.cmd.fmt.run_command') as mock_run:
                with caplog.at_level(logging.WARNING):
                    lint_all_codes([str(file_path)], 1, True)
        expected = 'cpp formatter version (1.0.0) is less than the required version (22.0.0), skipping...'
        assert expected in caplog.messages
        mock_run.assert_not_called()

    def test_lint_all_codes_version_parse_error_raises(self, tmp_path, caplog):
        import logging

        file_path = tmp_path / 'a.cpp'
        file_path.write_text('int main() {}\n')
        with patch('libs.cmd.fmt.os.popen', return_value=io.StringIO('clang-format ???')):
            with patch('libs.cmd.fmt.run_command'):
                with caplog.at_level(logging.ERROR), pytest.raises(Exception):
                    lint_all_codes([str(file_path)], 1, True)
        expected = "failed to get version for cpp formatter: 'NoneType' object has no attribute 'group'\nversion command output: 'clang-format ???'"
        assert expected in caplog.messages

    def test_lint_all_codes_skips_unknown_files(self, tmp_path):
        file_path = tmp_path / 'a.unknown'
        file_path.write_text('data\n')
        with patch('libs.cmd.fmt.run_command') as mock_run:
            lint_all_codes([str(file_path)], 1, True)
        mock_run.assert_not_called()
