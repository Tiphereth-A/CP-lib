from unittest.mock import patch

import click
import orjson
import pytest
from click.testing import CliRunner

from libs.cmd.cpv_merged_result import _register_cpv_merged_result, cpv_merged_result


@pytest.mark.unit
class TestCpvMergedResultCommands:
    def test_cpv_merged_result_updates_commit_hashes(self, tmp_path):
        merged_result = tmp_path / 'merged-result.json'
        merged_result.write_bytes(orjson.dumps({
            'files': {
                'src/a.cpp': {
                    'verifications': [
                        {'last_execution_time': '2026-04-21T11:00:00'},
                    ],
                },
                'src/b.cpp': {
                    'verifications': [
                        {'last_execution_time': '2026-04-21T18:30:00+09:00'},
                    ],
                },
                'src/c.cpp': {
                    'verifications': [],
                },
            }
        }))

        git_history = '\n'.join([
            'hash_recent\t2026-04-21T12:00:00+00:00',
            'hash_mid\t2026-04-21T10:00:00+00:00',
            'hash_old\t2026-04-20T00:00:00+00:00',
        ])
        with patch('libs.cmd.cpv_merged_result.subprocess.check_output', return_value=git_history.encode()):
            cpv_merged_result(str(merged_result))

        patched = orjson.loads(merged_result.read_bytes())
        assert patched['files']['src/a.cpp']['commit_hash'] == 'hash_mid'
        assert patched['files']['src/b.cpp']['commit_hash'] == 'hash_old'
        assert patched['files']['src/c.cpp']['commit_hash'] == '<outdated-or-invalid>'

    def test_register_cpv_merged_result_registers_and_invokes_command(self, tmp_path):
        merged_result = tmp_path / 'merged-result.json'
        merged_result.write_bytes(orjson.dumps({'files': {}}))

        @click.group()
        def cli():
            pass

        _register_cpv_merged_result(cli)
        assert 'merged-result' in cli.commands

        runner = CliRunner()
        with patch('libs.cmd.cpv_merged_result.cpv_merged_result') as mock_cpv_merged_result:
            result = runner.invoke(
                cli, ['merged-result', '-m', str(merged_result)])

        assert result.exit_code == 0
        mock_cpv_merged_result.assert_called_once_with(str(merged_result))
