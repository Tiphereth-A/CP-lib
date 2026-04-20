import json
from unittest.mock import patch

import pytest

from libs.cmd.cpv_delegate import cpv_delegate


@pytest.mark.unit
class TestCpvDelegateCommands:
    def test_cpv_delegate_skips_unverifiable_and_missing_files(self, tmp_path):
        verify_files = tmp_path / 'verify_files.json'
        merged_result = tmp_path / 'merged-result.json'
        result_dir = tmp_path / 'verify-list'

        verify_files.write_text(
            json.dumps(
                {
                    'files': {
                        'src/ok.cpp': {
                            'dependencies': ['src/ok.cpp'],
                            'verification': [{'type': 'local'}],
                        },
                        'src/empty.hpp': {
                            'dependencies': ['src/empty.hpp'],
                            'verification': [],
                        },
                    }
                }
            ),
            encoding='utf8',
        )
        merged_result.write_text(json.dumps({'files': {}}), encoding='utf8')

        with patch(
            'libs.cmd.cpv_delegate.files_listing',
            return_value=['src/ok.cpp', 'src/empty.hpp', 'src/missing.cpp'],
        ):
            cpv_delegate(('*',), str(verify_files), str(merged_result), 1, str(result_dir))

        delegated = json.loads((result_dir / '0.json').read_text(encoding='utf8'))
        assert set(delegated['files'].keys()) == {'src/ok.cpp'}

    def test_cpv_delegate_handles_empty_previous_verifications(self, tmp_path):
        verify_files = tmp_path / 'verify_files.json'
        merged_result = tmp_path / 'merged-result.json'
        result_dir = tmp_path / 'verify-list'

        verify_files.write_text(
            json.dumps(
                {
                    'files': {
                        'src/ok.cpp': {
                            'dependencies': ['src/ok.cpp'],
                            'verification': [{'type': 'local'}],
                        },
                    }
                }
            ),
            encoding='utf8',
        )
        merged_result.write_text(
            json.dumps(
                {
                    'files': {
                        'src/ok.cpp': {
                            'verifications': [],
                        }
                    }
                }
            ),
            encoding='utf8',
        )

        with patch('libs.cmd.cpv_delegate.files_listing', return_value=['src/ok.cpp']):
            cpv_delegate(('*',), str(verify_files), str(merged_result), 1, str(result_dir))

        delegated = json.loads((result_dir / '0.json').read_text(encoding='utf8'))
        assert set(delegated['files'].keys()) == {'src/ok.cpp'}
