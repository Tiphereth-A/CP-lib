import json
from unittest.mock import patch

import click
from click.testing import CliRunner
import orjson
import pytest

from libs.cmd.cpv_merged_result import _register_cpv_merged_result, cpv_merged_result


@pytest.mark.unit
class TestCpvMergedResultCommands:
    def test_set_commit_hash_if_absent(self, tmp_path):
        merged_result = tmp_path / 'merged-result.json'
        merged_result.write_bytes(
            orjson.dumps(
                {
                    'files': {
                        'src/a.cpp': {'verifications': []},
                        'src/b.cpp': {'commit_hash': 'keep', 'verifications': []},
                    }
                }
            )
        )

        with patch('libs.cmd.cpv_merged_result.subprocess.check_output', return_value=b'abc123\n'):
            cpv_merged_result(str(merged_result), 'set_commit_hash_if_absent')

        data = orjson.loads(merged_result.read_bytes())
        assert data['files']['src/a.cpp']['commit_hash'] == 'abc123'
        assert data['files']['src/b.cpp']['commit_hash'] == 'keep'

    def test_reset_last_execution_time(self, tmp_path):
        merged_result = tmp_path / 'merged-result.json'
        merged_result.write_bytes(
            orjson.dumps(
                {
                    'files': {
                        'src/a.cpp': {
                            'verifications': [
                                {'last_execution_time': '2026-01-01T00:00:00+00:00',
                                    'elapsed': 1.0},
                                {'last_execution_time': '2026-01-02T00:00:00+00:00',
                                    'elapsed': 2.0},
                            ]
                        }
                    }
                }
            )
        )

        cpv_merged_result(str(merged_result), 'reset_last_execution_time')

        data = orjson.loads(merged_result.read_bytes())
        verifications = data['files']['src/a.cpp']['verifications']
        for verification in verifications:
            assert verification['last_execution_time'].startswith(
                '1970-01-01T')

    def test_register_cpv_merged_result_invokes_handler(self, tmp_path):
        @click.group()
        def cli():
            pass

        _register_cpv_merged_result(cli)

        merged_result = tmp_path / 'merged-result.json'
        merged_result.write_text(json.dumps({'files': {}}), encoding='utf8')

        runner = CliRunner()
        with patch('libs.cmd.cpv_merged_result.cpv_merged_result') as handler:
            result = runner.invoke(
                cli,
                ['merged-result', '-m',
                    str(merged_result), '-t', 'set_commit_hash_if_absent'],
            )

        assert result.exit_code == 0
        handler.assert_called_once_with(
            str(merged_result), 'set_commit_hash_if_absent')
