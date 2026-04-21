import json
import click
from click.testing import CliRunner
from unittest.mock import patch

import pytest

from libs.cmd.cpv_delegate import _register_cpv_delegate, cpv_delegate, files_listing, partition


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
                            'verification': [{'type': 'local', 'input': 'in.txt'}],
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
            cpv_delegate(('*',), str(verify_files),
                         str(merged_result), 1, str(result_dir))

        delegated = json.loads(
            (result_dir / '0.json').read_text(encoding='utf8'))
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
                            'verification': [{'type': 'local', 'input': 'in.txt'}],
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
            cpv_delegate(('*',), str(verify_files),
                         str(merged_result), 1, str(result_dir))

        delegated = json.loads(
            (result_dir / '0.json').read_text(encoding='utf8'))
        assert set(delegated['files'].keys()) == {'src/ok.cpp'}

    def test_cpv_delegate_supports_exclude_only_patterns(self, tmp_path):
        verify_files = tmp_path / 'verify_files.json'
        merged_result = tmp_path / 'merged-result.json'
        result_dir = tmp_path / 'verify-list'

        verify_files.write_text(
            json.dumps(
                {
                    'files': {
                        'src/keep.cpp': {
                            'dependencies': ['src/keep.cpp'],
                            'verification': [{'type': 'local', 'input': 'in.txt'}],
                        },
                        'src/_skip.cpp': {
                            'dependencies': ['src/_skip.cpp'],
                            'verification': [{'type': 'local', 'input': 'in.txt'}],
                        },
                    }
                }
            ),
            encoding='utf8',
        )
        merged_result.write_text(json.dumps({'files': {}}), encoding='utf8')

        with patch(
            'libs.cmd.cpv_delegate.files_listing',
            return_value=['src/keep.cpp', 'src/_skip.cpp'],
        ):
            cpv_delegate(('!src/_*',), str(verify_files),
                         str(merged_result), 1, str(result_dir))

        delegated = json.loads(
            (result_dir / '0.json').read_text(encoding='utf8'))
        assert delegated == {'files': {}}

    def test_files_listing_without_previous_info_uses_git_ls_files(self):
        with patch(
            'libs.cmd.cpv_delegate.subprocess.check_output',
            return_value=b'src/a.cpp\nsrc/b.hpp\n',
        ):
            listed = files_listing({})

        assert listed == ['src/a.cpp', 'src/b.hpp']

    def test_files_listing_with_previous_info_collects_changed_non_ancestor_files(self):
        previous_info = {
            'src/kept.cpp': {'commit_hash': 'h1', 'verifications': [{'status': 'success'}]},
            'src/reverify.cpp': {'commit_hash': 'missing-hash', 'verifications': [{'status': 'success'}]},
        }

        def _mock_check_output(args):
            if args[:2] == ['git', 'rev-list']:
                return b'h1\nh2\n'
            if args[:2] == ['git', 'diff-tree'] and args[-1] == 'h1':
                return b'src/kept.cpp\nsrc/dep.cpp\n'
            raise AssertionError(f'unexpected git command: {args}')

        with patch('libs.cmd.cpv_delegate.subprocess.check_output', side_effect=_mock_check_output):
            listed = files_listing(previous_info)

        assert set(listed) == {'src/reverify.cpp', 'src/dep.cpp'}

    def test_files_listing_with_previous_info_deduplicates_hash_queries_and_results(self):
        previous_info = {
            'src/kept-a.cpp': {'commit_hash': 'h1', 'verifications': [{'status': 'success'}]},
            'src/kept-a-2.cpp': {'commit_hash': 'h1', 'verifications': [{'status': 'success'}]},
            'src/kept-b.cpp': {'commit_hash': 'h2', 'verifications': [{'status': 'success'}]},
            'src/reverify.cpp': {'commit_hash': 'missing-hash', 'verifications': [{'status': 'success'}]},
            'src/reverify-unknown.cpp': {},
        }

        def _mock_check_output(args):
            if args[:2] == ['git', 'rev-list']:
                return b'h1\nh2\nh3\n'
            if args[:2] == ['git', 'diff-tree'] and args[-1] == 'h1':
                return b'src/kept-a.cpp\nsrc/dep/shared.hpp\nsrc/dep/a.hpp\n'
            if args[:2] == ['git', 'diff-tree'] and args[-1] == 'h2':
                return b'src/kept-b.cpp\nsrc/dep/shared.hpp\nsrc/dep/b.hpp\n'
            raise AssertionError(f'unexpected git command: {args}')

        with patch('libs.cmd.cpv_delegate.subprocess.check_output', side_effect=_mock_check_output) as mocked:
            listed = files_listing(previous_info)

        assert set(listed) == {
            'src/reverify.cpp',
            'src/reverify-unknown.cpp',
            'src/dep/shared.hpp',
            'src/dep/a.hpp',
            'src/dep/b.hpp',
        }
        diff_hashes = [
            call_args.args[0][-1]
            for call_args in mocked.call_args_list
            if call_args.args and call_args.args[0][:2] == ['git', 'diff-tree']
        ]
        assert set(diff_hashes) == {'h1', 'h2'}
        assert len(diff_hashes) == 2

    def test_files_listing_with_previous_info_and_no_known_hashes_skips_diff_tree(self):
        previous_info = {
            'src/reverify-a.cpp': {'commit_hash': 'missing-hash-a'},
            'src/reverify-b.cpp': {},
        }

        with patch(
            'libs.cmd.cpv_delegate.subprocess.check_output',
            return_value=b'h1\nh2\n',
        ) as mocked:
            listed = files_listing(previous_info)

        assert set(listed) == {'src/reverify-a.cpp', 'src/reverify-b.cpp'}
        mocked.assert_called_once_with(
            ['git', 'rev-list', '--all', '--no-merges', '--first-parent']
        )

    def test_files_listing_with_previous_info_returns_empty_if_only_ancestor_files_changed(self):
        previous_info = {
            'src/kept.cpp': {'commit_hash': 'h1', 'verifications': [{'status': 'success'}]},
        }

        def _mock_check_output(args):
            if args[:2] == ['git', 'rev-list']:
                return b'h1\n'
            if args[:2] == ['git', 'diff-tree'] and args[-1] == 'h1':
                return b'src/kept.cpp\n'
            raise AssertionError(f'unexpected git command: {args}')

        with patch('libs.cmd.cpv_delegate.subprocess.check_output', side_effect=_mock_check_output):
            listed = files_listing(previous_info)

        assert listed == []

    def test_partition_rejects_negative_elapsed(self):
        files_info = {
            'src/a.cpp': {
                'tag': 'problem libchk https://judge.yosupo.jp/problem/sum_of_floor_of_linear',
                'total_elapsed': -1.0,
                'total_samples': 2,
            }
        }

        with pytest.raises(ValueError, match='invalid total_elapsed'):
            partition(files_info, 1)

    def test_partition_rejects_negative_samples(self):
        files_info = {
            'src/a.cpp': {
                'tag': 'problem aizu https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A',
                'total_elapsed': 1.0,
                'total_samples': -1,
            }
        }

        with pytest.raises(ValueError, match='invalid total_samples'):
            partition(files_info, 1)

    def test_cpv_delegate_logs_missing_merged_result_and_returns_when_no_verifiable(self, tmp_path, caplog):
        verify_files = tmp_path / 'verify_files.json'
        result_dir = tmp_path / 'verify-list'

        verify_files.write_text(
            json.dumps(
                {
                    'files': {
                        'src/empty.hpp': {
                            'dependencies': ['src/empty.hpp'],
                            'verification': [],
                        },
                    }
                }
            ),
            encoding='utf8',
        )

        missing_merged = tmp_path / 'missing-merged-result.json'

        with patch('libs.cmd.cpv_delegate.files_listing', return_value=['src/empty.hpp']):
            cpv_delegate(('*',), str(verify_files),
                         str(missing_merged), 1, str(result_dir))

        assert f"'{missing_merged}' not found. Proceeding without previous info." in caplog.text
        assert 'no verifiable files remain after filtering' in caplog.text
        assert not result_dir.exists()

    def test_cpv_delegate_supports_problem_and_command_tags(self, tmp_path):
        verify_files = tmp_path / 'verify_files.json'
        merged_result = tmp_path / 'merged-result.json'
        result_dir = tmp_path / 'verify-list'

        verify_files.write_text(
            json.dumps(
                {
                    'files': {
                        'src/problem.cpp': {
                            'dependencies': ['src/problem.cpp'],
                            'verification': [
                                {
                                    'type': 'problem',
                                    'problem': 'https://judge.yosupo.jp/problem/aplusb',
                                }
                            ],
                        },
                        'src/cmd.cpp': {
                            'dependencies': ['src/cmd.cpp'],
                            'verification': [
                                {
                                    'type': 'command',
                                    'compile': ['g++', '-std=c++20', 'src/cmd.cpp'],
                                }
                            ],
                        },
                    }
                }
            ),
            encoding='utf8',
        )
        merged_result.write_text(json.dumps({'files': {}}), encoding='utf8')

        with patch('libs.cmd.cpv_delegate.files_listing', return_value=['src/problem.cpp', 'src/cmd.cpp']):
            cpv_delegate(('*',), str(verify_files),
                         str(merged_result), 2, str(result_dir))

        delegated = {}
        for output in result_dir.glob('*.json'):
            delegated.update(json.loads(
                output.read_text(encoding='utf8'))['files'])

        assert set(delegated.keys()) == {'src/problem.cpp', 'src/cmd.cpp'}

    def test_cpv_delegate_raises_on_unknown_verification_type(self, tmp_path):
        verify_files = tmp_path / 'verify_files.json'
        merged_result = tmp_path / 'merged-result.json'

        verify_files.write_text(
            json.dumps(
                {
                    'files': {
                        'src/bad.cpp': {
                            'dependencies': ['src/bad.cpp'],
                            'verification': [{'type': 'mystery'}],
                        }
                    }
                }
            ),
            encoding='utf8',
        )
        merged_result.write_text(json.dumps({'files': {}}), encoding='utf8')

        with patch('libs.cmd.cpv_delegate.files_listing', return_value=['src/bad.cpp']):
            with pytest.raises(ValueError, match='Unknown verification type'):
                cpv_delegate(('*',), str(verify_files),
                             str(merged_result), 1, str(tmp_path / 'verify-list'))

    def test_register_cpv_delegate_invokes_handler(self, tmp_path):
        @click.group()
        def cli():
            pass

        _register_cpv_delegate(cli)

        verify_files = tmp_path / 'verify_files.json'
        verify_files.write_text(json.dumps({'files': {}}), encoding='utf8')
        merged_result = tmp_path / 'merged-result.json'
        result_dir = tmp_path / 'verify-list'

        runner = CliRunner()
        with patch('libs.cmd.cpv_delegate.cpv_delegate') as delegate:
            result = runner.invoke(
                cli,
                [
                    'delegate',
                    '-f',
                    'src/*.cpp !src/_*',
                    '-v',
                    str(verify_files),
                    '-m',
                    str(merged_result),
                    '-t',
                    '3',
                    '-d',
                    str(result_dir),
                ],
            )

        assert result.exit_code == 0
        delegate.assert_called_once_with(
            ['src/*.cpp', '!src/_*'],
            str(verify_files),
            str(merged_result),
            3,
            str(result_dir),
        )

    def test_register_cpv_delegate_rejects_non_positive_task_count(self, tmp_path):
        @click.group()
        def cli():
            pass

        _register_cpv_delegate(cli)

        verify_files = tmp_path / 'verify_files.json'
        verify_files.write_text(json.dumps({'files': {}}), encoding='utf8')
        merged_result = tmp_path / 'merged-result.json'
        result_dir = tmp_path / 'verify-list'

        runner = CliRunner()
        result = runner.invoke(
            cli,
            [
                'delegate',
                '-f',
                '*',
                '-v',
                str(verify_files),
                '-m',
                str(merged_result),
                '-t',
                '0',
                '-d',
                str(result_dir),
            ],
        )

        assert result.exit_code == 1
        assert isinstance(result.exception, ValueError)
        assert str(result.exception) == 'task_count must be a positive integer'
