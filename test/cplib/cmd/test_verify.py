import os
from unittest.mock import MagicMock, patch

from click.testing import CliRunner
import pytest

from libs.cmd.verify import verify_codes

from .helpers import make_src_tree, write_yaml


@pytest.mark.unit
class TestVerifyCommands:
    def _make_src_with_usage(self, base_dir):
        src = os.path.join(base_dir, 'src')
        cat = os.path.join(src, 'math')
        sect = os.path.join(cat, 'gcd')
        os.makedirs(sect, exist_ok=True)
        write_yaml(os.path.join(src, 'index.yml'), [{'math': 'Math'}])
        write_yaml(os.path.join(cat, 'index.yml'), [{'gcd': 'GCD'}])
        with open(os.path.join(sect, 'lib.hpp'), 'w') as f:
            f.write('#pragma once\n')
        with open(os.path.join(sect, 'usage.cpp'), 'w') as f:
            f.write(
                '// competitive-verifier: PROBLEM "https://example.com"\n'
                '#include "lib.hpp"\nint main() {}\n'
            )
        return 'src'

    def test_verify_codes_runs(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        src = self._make_src_with_usage(str(tmp_path))
        os.makedirs('temp', exist_ok=True)
        with patch('libs.cmd.verify.run_command', return_value=[]):
            verify_codes(src, thread_limit=2, time_limit=0.5, temp_path='temp')

    def test_verify_codes_cmd_function_exercises(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        src = self._make_src_with_usage(str(tmp_path))
        os.makedirs('temp', exist_ok=True)
        mock_result = MagicMock()
        mock_result.returncode = 0
        mock_result.stdout = ''
        mock_result.stderr = ''
        with patch('subprocess.run', return_value=mock_result):
            verify_codes(src, thread_limit=1, time_limit=0.5, temp_path='temp')

    def test_verify_codes_logs_failures(self, tmp_path, caplog, monkeypatch):
        import logging

        monkeypatch.chdir(tmp_path)
        src = self._make_src_with_usage(str(tmp_path))
        os.makedirs('temp', exist_ok=True)
        with patch('libs.cmd.verify.run_command', return_value=['usage.cpp']):
            with caplog.at_level(logging.ERROR):
                with pytest.raises(RuntimeError):
                    verify_codes(src, thread_limit=1,
                                 time_limit=0.5, temp_path='temp')
        assert caplog.messages == [
            '1 file(s) failed in compilation:\n    usage.cpp']

    def test_verify_codes_run_path_exercised(self, tmp_path, monkeypatch):
        """Covers _run, _post, and run_cases loop in verify.py."""
        monkeypatch.chdir(tmp_path)
        src_dir = os.path.join(str(tmp_path), 'src')
        cat = os.path.join(src_dir, 'math')
        sect = os.path.join(cat, 'gcd')
        os.makedirs(sect, exist_ok=True)
        write_yaml(os.path.join(src_dir, 'index.yml'), [{'math': 'Math'}])
        write_yaml(os.path.join(cat, 'index.yml'), [{'gcd': 'GCD'}])
        with open(os.path.join(sect, 'lib.hpp'), 'w') as f:
            f.write('#pragma once\n')
        with open(os.path.join(sect, 'usage.cpp'), 'w') as f:
            f.write(
                '// competitive-verifier: PROBLEM "https://example.com"\n'
                '#include "lib.hpp"\nint main() {}\n'
                '/*sample\n1\n========\n1\n*/\n'
            )

        call_count = [0]

        def fake_run_command(command, params, thread_limit, time_limit=None, **kw):
            call_count[0] += 1
            results = []
            for p in params:
                command(p)
            return results

        with patch('libs.cmd.verify.run_command', side_effect=fake_run_command):
            verify_codes('src', thread_limit=1,
                         time_limit=0.5, temp_path='temp')
        assert call_count[0] == 2  # compile + run

    def test_verify_codes_run_failed_logged(self, tmp_path, caplog, monkeypatch):
        """Covers run_failed logging branch in verify.py."""
        import logging

        monkeypatch.chdir(tmp_path)
        src_dir = os.path.join(str(tmp_path), 'src')
        cat = os.path.join(src_dir, 'math')
        sect = os.path.join(cat, 'gcd')
        os.makedirs(sect, exist_ok=True)
        write_yaml(os.path.join(src_dir, 'index.yml'), [{'math': 'Math'}])
        write_yaml(os.path.join(cat, 'index.yml'), [{'gcd': 'GCD'}])
        with open(os.path.join(sect, 'lib.hpp'), 'w') as f:
            f.write('#pragma once\n')
        with open(os.path.join(sect, 'usage.cpp'), 'w') as f:
            f.write(
                '// competitive-verifier: PROBLEM "https://example.com"\n'
                '#include "lib.hpp"\nint main() {}\n'
                '/*sample\n1\n========\n1\n*/\n'
            )

        call_count = [0]

        def fake_run_command(command, params, thread_limit, time_limit=None, **kw):
            call_count[0] += 1
            for p in params:
                command(p)
            if call_count[0] == 1:
                return []  # compile OK
            return ['case1']  # run failed

        with patch('libs.cmd.verify.run_command', side_effect=fake_run_command):
            with caplog.at_level(logging.ERROR):
                with pytest.raises(RuntimeError):
                    verify_codes('src', thread_limit=1,
                                 time_limit=0.5, temp_path='temp')
        error_msgs = [m for m in caplog.messages if 'failed in execution' in m]
        assert len(error_msgs) == 1

    def test_verify_codes_compile_failed_skips_run_cases(self, tmp_path, monkeypatch):
        """Covers verify.py line 57: compile_failed file is skipped in run_cases loop."""
        monkeypatch.chdir(tmp_path)
        src_dir = os.path.join(str(tmp_path), 'src')
        cat = os.path.join(src_dir, 'math')
        sect = os.path.join(cat, 'gcd')
        os.makedirs(sect, exist_ok=True)
        write_yaml(os.path.join(src_dir, 'index.yml'), [{'math': 'Math'}])
        write_yaml(os.path.join(cat, 'index.yml'), [{'gcd': 'GCD'}])
        with open(os.path.join(sect, 'lib.hpp'), 'w') as f:
            f.write('#pragma once\n')
        with open(os.path.join(sect, 'usage.cpp'), 'w') as f:
            f.write(
                '// competitive-verifier: PROBLEM "https://example.com"\n'
                '#include "lib.hpp"\nint main() {}\n'
                '/*sample\n1\n========\n1\n*/\n'
            )

        call_count = [0]
        usage_rel = os.path.join('src', 'math', 'gcd', 'usage.cpp')

        def fake_run_command(command, params, thread_limit, time_limit=None, **kw):
            call_count[0] += 1
            for p in params:
                command(p)
            if call_count[0] == 1:
                # Match run_command failure tuple shape so i[1] is the file path.
                return [('compile_failed', usage_rel)]
            return []

        with patch('libs.cmd.verify.run_command', side_effect=fake_run_command):
            with pytest.raises(RuntimeError):
                verify_codes('src', thread_limit=1,
                             time_limit=0.5, temp_path='temp')

    def test_verify_codes_post_wrong_answer(self, tmp_path, monkeypatch):
        """Covers verify.py lines 66-67: _post raises CalledProcessError on wrong answer."""
        import subprocess as sp

        monkeypatch.chdir(tmp_path)
        src_dir = os.path.join(str(tmp_path), 'src')
        cat = os.path.join(src_dir, 'math')
        sect = os.path.join(cat, 'gcd')
        os.makedirs(sect, exist_ok=True)
        write_yaml(os.path.join(src_dir, 'index.yml'), [{'math': 'Math'}])
        write_yaml(os.path.join(cat, 'index.yml'), [{'gcd': 'GCD'}])
        with open(os.path.join(sect, 'lib.hpp'), 'w') as f:
            f.write('#pragma once\n')
        with open(os.path.join(sect, 'usage.cpp'), 'w') as f:
            f.write(
                '// competitive-verifier: PROBLEM "https://example.com"\n'
                '#include "lib.hpp"\nint main() {}\n'
                '/*sample\n1\n========\nexpected_output\n*/\n'
            )

        call_count = [0]

        def fake_run_command(command, params, thread_limit, time_limit=None, **kw):
            call_count[0] += 1
            if call_count[0] == 1:
                # compile phase: call command to populate out_src_samples
                for p in params:
                    command(p)
                return []
            # run phase: call command and invoke post_run with wrong output
            results = []
            for p in params:
                cmd_list, extra = command(p)
                post_run = extra.get('post_run')
                if post_run:
                    mock_result = MagicMock()
                    mock_result.stdout = 'wrong_output\n'
                    mock_result.args = cmd_list
                    try:
                        post_run(mock_result)
                    except sp.CalledProcessError:
                        results.append(p)
            return results

        with patch('libs.cmd.verify.run_command', side_effect=fake_run_command):
            with pytest.raises(RuntimeError):
                verify_codes('src', thread_limit=1,
                             time_limit=0.5, temp_path='temp')

    def test_verify_cli_registered(self, cli):
        assert 'verify' in cli.commands

    def test_verify_cli_invocation(self, cli, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        os.makedirs('temp', exist_ok=True)
        runner = CliRunner()
        with patch('libs.cmd.verify.run_command', return_value=[]):
            result = runner.invoke(
                cli, ['verify', '-s', 'src', '-l', '2', '-T', 'temp'])
        assert result.exit_code == 0
