from unittest.mock import patch

import pytest
from click.testing import CliRunner

from libs.cmd.fmt import lint_all_codes


@pytest.mark.unit
class TestFmtCommands:
    def test_lint_all_codes_no_failures(self, tmp_path):
        (tmp_path / 'a.py').write_text('x=1\n')
        with patch('libs.cmd.fmt.run_command', return_value=[]) as mock_run:
            lint_all_codes([str(tmp_path)], 'py', 4)
            mock_run.assert_called_once()

    def test_lint_all_codes_with_failures_logs(self, tmp_path, caplog):
        import logging

        (tmp_path / 'a.py').write_text('x=1\n')
        with patch('libs.cmd.fmt.run_command', return_value=['a.py']):
            with caplog.at_level(logging.ERROR):
                lint_all_codes([str(tmp_path)], 'py', 1)
        assert caplog.messages == ['1 file(s) failed:', '  a.py']

    def test_fmt_cli_registered(self, cli):
        assert 'fmt' in cli.commands

    def test_fmt_cli_invocation(self, cli, tmp_path):
        runner = CliRunner()
        with patch('libs.cmd.fmt.run_command', return_value=[]):
            result = runner.invoke(cli, ['fmt', '-d', str(tmp_path), '-t', 'py', '-l', '2'])
        assert result.exit_code == 0
