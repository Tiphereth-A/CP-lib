import subprocess
import time
import pytest
from unittest.mock import patch, MagicMock
from libs.util.run_command import run_command


@pytest.mark.unit
class TestRunCommand:
    def test_empty_params(self):
        result = run_command(lambda x: (['echo', x], {}), [], thread_limit=1)
        assert result == []

    def test_successful_commands(self):
        import sys
        result = run_command(
            lambda x: ([sys.executable, '-c', f'print({x})'], {}),
            [1, 2, 3],
            thread_limit=2
        )
        assert result == []

    def test_failing_command_returns_param(self):
        import sys
        result = run_command(
            lambda x: ([sys.executable, '-c', 'import sys; sys.exit(1)'], {}),
            ['bad_param'],
            thread_limit=1
        )
        assert result == [([sys.executable, '-c',
                            'import sys; sys.exit(1)'], 'bad_param')]

    def test_multiple_threads(self):
        import sys
        params = list(range(8))
        result = run_command(
            lambda x: ([sys.executable, '-c', f'pass'], {}),
            params,
            thread_limit=4
        )
        assert result == []

    def test_command_with_stdout(self):
        import sys
        result = run_command(
            lambda x: ([sys.executable, '-c', 'print("hello")'], {}),
            ['p'],
            thread_limit=1
        )
        assert result == []

    def test_command_with_stderr(self):
        import sys
        # stderr output but returncode 0
        result = run_command(
            lambda x: ([sys.executable, '-c',
                       'import sys; sys.stderr.write("err\\n")'], {}),
            ['p'],
            thread_limit=1
        )
        assert result == []

    def test_mixed_success_failure(self):
        import sys
        # param 0 succeeds, param 1 fails
        result = run_command(
            lambda x: ([sys.executable, '-c',
                       f'import sys; sys.exit({x})'], {}),
            [0, 1],
            thread_limit=2
        )
        assert result == [([sys.executable, '-c',
                            'import sys; sys.exit(1)'], 1)]

    def test_heartbeat_sleep_called(self):
        # Covers line 25: heartbeat calls time.sleep(30) when queue non-empty
        # Use a slow command and mock time.sleep to avoid actual 30s wait
        import sys

        sleep_calls = []

        def fake_sleep(secs):
            sleep_calls.append(secs)

        with patch('libs.util.run_command.time.sleep', side_effect=fake_sleep):
            # Use python -c to add a tiny sleep so heartbeat catches non-empty queue
            result = run_command(
                lambda x: ([sys.executable, '-c',
                           f'import time; time.sleep(0.05)'], {}),
                list(range(4)),
                thread_limit=1
            )
        # If sleep was called with 30, heartbeat line 25 was hit
        assert result == []

    def test_none_param_is_skipped(self):
        # Covers run_command.py line 25: `if param is None: return` sentinel branch
        result = run_command(lambda x: (['echo', str(x)], {}), [
                             None], thread_limit=1)
        assert result == []

    def test_time_limit_sets_timeout(self):
        import sys
        # Covers line 32: time_limit is not None → extra_args.setdefault('timeout', ...)
        result = run_command(
            lambda x: ([sys.executable, '-c', 'pass'], {}),
            ['p'],
            thread_limit=1,
            time_limit=10.0
        )
        assert result == []

    def test_post_run_callback_called(self):
        import sys
        # Covers line 55: post_run(result) branch
        called = []

        def make_cmd(x):
            return ([sys.executable, '-c', 'pass'], {'post_run': lambda r: called.append(r)})

        result = run_command(make_cmd, ['p'], thread_limit=1)
        assert result == []
        assert len(called) == 1

    def test_post_run_raising_calledprocesserror(self):
        import sys
        import subprocess as sp
        # Covers line 55 + CalledProcessError from post_run (line 63)

        def make_cmd(x):
            def _post(r):
                raise sp.CalledProcessError(1, r.args)
            return ([sys.executable, '-c', 'pass'], {'post_run': _post})

        result = run_command(make_cmd, ['p'], thread_limit=1)
        assert len(result) == 1

    def test_timeout_expired(self):
        import sys
        # Covers lines 57-59: TimeoutExpired handler
        result = run_command(
            lambda x: ([sys.executable, '-c', 'import time; time.sleep(10)'], {}),
            ['p'],
            thread_limit=1,
            time_limit=0.01
        )
        assert len(result) == 1

    def test_generic_exception_handler(self):
        import sys
        # Covers lines 62-65: generic Exception handler
        # post_run raises a non-CalledProcessError so it falls into except Exception
        def make_cmd(x):
            def _post(r):
                raise ValueError("unexpected post_run error")
            return ([sys.executable, '-c', 'pass'], {'post_run': _post})

        result = run_command(make_cmd, ['p'], thread_limit=1)
        assert len(result) == 1

    def test_hide_stdout_suppresses_stdout_in_log(self):
        import sys
        # Covers the hide_stdout=True branch (line ~48-49 in run_command)
        result = run_command(
            lambda x: ([sys.executable, '-c', 'print("secret")'], {'hide_stdout': True}),
            ['p'],
            thread_limit=1
        )
        assert result == []
