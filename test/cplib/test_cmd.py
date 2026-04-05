import os
import sys
import pytest
import yaml
import click
from click.testing import CliRunner
from unittest.mock import patch, MagicMock

import libs
from libs.cmd import register_main_commands, register_cpv_patch_commands
from libs.cmd.doc import gen_tex, gen_typst
from libs.cmd.fmt import lint_all_codes
from libs.cmd.meta import generate_testcode
from libs.cmd.new import new_section
from libs.cmd.pack import packing_codes
from libs.cmd.verify import verify_codes
from libs.content.tree import ContentTree


# ------------------------------------------------------------------ helpers --

def write_yaml(path, data):
    with open(path, 'w', encoding='utf8') as f:
        yaml.dump(data, f, sort_keys=False)


def make_src_tree(base_dir):
    """Create src/ relative to base_dir. Caller must chdir to base_dir."""
    src = os.path.join(base_dir, 'src')
    math_dir = os.path.join(src, 'math')
    gcd_dir = os.path.join(math_dir, 'gcd')
    os.makedirs(gcd_dir, exist_ok=True)
    write_yaml(os.path.join(src, 'index.yml'), [{'math': 'Math'}])
    write_yaml(os.path.join(math_dir, 'index.yml'), [{'gcd': 'GCD'}])
    with open(os.path.join(gcd_dir, 'lib.hpp'), 'w') as f:
        f.write('#pragma once\n')
    with open(os.path.join(gcd_dir, 'doc.tex'), 'w') as f:
        f.write('% {lib.hpp}\n')
    return 'src'


@pytest.fixture
def cli():
    @click.group()
    def _cli():
        pass
    register_main_commands(_cli)
    return _cli


# ------------------------------------------------------------------ __init__ --

@pytest.mark.unit
class TestLibsInit:
    def test_register_main_commands_importable(self):
        from libs import register_main_commands
        assert callable(register_main_commands)

    def test_register_cpv_patch_commands_importable(self):
        from libs import register_cpv_patch_commands
        assert callable(register_cpv_patch_commands)

    def test_register_main_commands_registers_cmds(self):
        @click.group()
        def group():
            pass
        register_main_commands(group)
        cmd_names = set(group.commands.keys())
        assert cmd_names == {'doc', 'new', 'verify', 'fmt', 'meta', 'pack'}

    def test_register_cpv_patch_commands_registers_cmds(self):
        @click.group()
        def group():
            pass
        register_cpv_patch_commands(group)
        assert set(group.commands.keys()) == {'doc'}

    def test_cli_callback_installs_coloredlogs(self):
        with patch('libs.coloredlogs.install') as install:
            libs.cli.callback(level='INFO')
        install.assert_called_once()


# ------------------------------------------------------------------ doc.py --

@pytest.mark.unit
class TestDocCommands:
    def test_gen_typst_raises(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        with pytest.raises(AssertionError):
            gen_typst(tree)

    def test_gen_tex_runs(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        os.makedirs('temp', exist_ok=True)
        gen_tex(tree, 'temp')
        assert os.path.exists(os.path.join('temp', 'src', 'math', 'doc.tex'))

    def test_doc_cli_tex(self, cli, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        os.makedirs('temp', exist_ok=True)
        runner = CliRunner()
        result = runner.invoke(
            cli, ['doc', '-s', 'src', '-t', 'tex', '-T', 'temp'])
        assert result.exit_code == 0

    def test_doc_cli_typ_raises(self, cli, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        os.makedirs('temp', exist_ok=True)
        runner = CliRunner()
        result = runner.invoke(
            cli, ['doc', '-s', 'src', '-t', 'typ', '-T', 'temp'])
        assert result.exit_code != 0

    def test_gen_tex_with_chapter_doc_tex(self, tmp_path, monkeypatch):
        # Covers lines 38-39: chapter_doc_path exists → read and replace {content}
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        # Add a doc.tex at the math chapter level with {content} placeholder
        with open(os.path.join(str(tmp_path), 'src', 'math', 'doc.tex'), 'w') as f:
            f.write('% {content}\n')
        tree = ContentTree('src')
        os.makedirs('temp', exist_ok=True)
        gen_tex(tree, 'temp')
        result_path = os.path.join('temp', 'src', 'math', 'doc.tex')
        assert os.path.exists(result_path)

    def test_doc_unsupported_type_raises(self, cli, tmp_path, monkeypatch):
        # Covers cmd/doc.py line 72: else branch raises ValueError for unknown type
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        doc_cmd = cli.commands['doc']
        with pytest.raises(ValueError, match='Unsupported document type'):
            doc_cmd.callback(src='src', type='unsupported', temp_path='temp')


# ------------------------------------------------------------------ fmt.py --

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
            result = runner.invoke(
                cli, ['fmt', '-d', str(tmp_path), '-t', 'py', '-l', '2'])
        assert result.exit_code == 0


# ------------------------------------------------------------------ meta.py --

@pytest.mark.unit
class TestMetaCommands:
    def _make_cppmeta(self, base_dir):
        """Create a minimal .cppmeta file."""
        import textwrap
        meta_src = os.path.join(base_dir, 'meta_src')
        os.makedirs(meta_src)
        code = textwrap.dedent("""\
            #include <bits/stdc++.h>
            // ---<GENTC>--- begin
            // ---<GENTC>--- append mints
            // ---<GENTC>--- end
            int main() {
            }
        """)
        with open(os.path.join(meta_src, 'mytest.cppmeta'), 'w') as f:
            f.write(code)
        return 'meta_src'

    def test_generate_testcode_creates_files(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        src = self._make_cppmeta(str(tmp_path))
        os.makedirs('target')
        generate_testcode(src, 'target')
        generated = []
        for root, _, files in os.walk('target'):
            generated.extend(files)
        assert {os.path.splitext(f)[1] for f in generated} == {'.cpp'}

    def test_generate_testcode_removes_existing_auto_generated(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        src = self._make_cppmeta(str(tmp_path))
        os.makedirs('target')
        old_file = os.path.join('target', 'old.cpp')
        with open(old_file, 'w') as f:
            f.write('#define AUTO_GENERATED\n// old content\n')
        generate_testcode(src, 'target')
        assert not os.path.exists(old_file)

    def test_generate_testcode_skips_non_auto_generated(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        src = self._make_cppmeta(str(tmp_path))
        os.makedirs('target')
        keep_file = os.path.join('target', 'keep.cpp')
        with open(keep_file, 'w') as f:
            f.write('// normal file\n')
        generate_testcode(src, 'target')
        assert os.path.exists(keep_file)

    def test_generate_testcode_unreadable_file_raises(self, tmp_path, monkeypatch):
        # Covers lines 27-29: exception reading a target file propagates
        from unittest.mock import patch, mock_open
        import builtins
        monkeypatch.chdir(tmp_path)
        src = self._make_cppmeta(str(tmp_path))
        os.makedirs('target')
        bad_file = os.path.join('target', 'bad.cpp')
        with open(bad_file, 'w') as f:
            f.write('some content\n')
        # Patch open so that opening the .cpp file raises PermissionError
        real_open = builtins.open

        def patched_open(file, *args, **kwargs):
            if str(file).endswith('.cpp'):
                raise PermissionError("mocked permission error")
            return real_open(file, *args, **kwargs)

        with patch('builtins.open', side_effect=patched_open):
            with pytest.raises(PermissionError):
                generate_testcode(src, 'target')

    def test_pack_cli_invocation(self, cli, tmp_path, monkeypatch):
        # Covers cmd/pack.py line 34: CLI body
        monkeypatch.chdir(tmp_path)
        src = os.path.join(str(tmp_path), 'src')
        os.makedirs(src, exist_ok=True)
        out = os.path.join(str(tmp_path), 'out')
        os.makedirs(out, exist_ok=True)
        with open(os.path.join(src, 'lib.hpp'), 'w') as f:
            f.write('#pragma once\n')
        runner = CliRunner()
        result = runner.invoke(
            cli, ['pack', '-s', src, '-e', '.hpp', '-t', out])
        assert result.exit_code == 0

    def test_meta_cli_registered(self, cli):
        assert 'meta' in cli.commands

    def test_meta_cli_invocation(self, cli, tmp_path, monkeypatch):
        # Covers cmd/meta.py line 56: CLI body
        monkeypatch.chdir(tmp_path)
        src = os.path.join(str(tmp_path), 'meta_src')
        target = os.path.join(str(tmp_path), 'target')
        os.makedirs(src, exist_ok=True)
        os.makedirs(target, exist_ok=True)
        runner = CliRunner()
        result = runner.invoke(cli, ['meta', '-s', src, '-t', target])
        assert result.exit_code == 0


# ------------------------------------------------------------------ new.py --

@pytest.mark.unit
class TestNewCommands:
    def test_new_section_creates_files(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        os.makedirs(os.path.join(str(tmp_path), 'src',
                    'math', 'lcm'), exist_ok=True)
        new_section(tree, 'math.lcm', 'LCM')
        assert os.path.exists(os.path.join('src', 'math', 'lcm', 'lib.hpp'))

    def test_new_cli_registered(self, cli):
        assert 'new' in cli.commands

    def test_new_cli_invocation(self, cli, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        os.makedirs(os.path.join(str(tmp_path), 'src',
                    'math', 'mod'), exist_ok=True)
        runner = CliRunner()
        result = runner.invoke(
            cli, ['new', '-s', 'src', '-n', 'math.mod', '-t', 'Modular'])
        assert result.exit_code == 0


# ------------------------------------------------------------------ pack.py --

@pytest.mark.unit
class TestPackCommands:
    def _make_pack_src(self, base_dir):
        src = os.path.join(base_dir, 'src')
        cat = os.path.join(src, 'math')
        sect = os.path.join(cat, 'gcd')
        os.makedirs(sect, exist_ok=True)
        write_yaml(os.path.join(src, 'index.yml'), [{'math': 'Math'}])
        write_yaml(os.path.join(cat, 'index.yml'), [{'gcd': 'GCD'}])
        with open(os.path.join(sect, 'lib.hpp'), 'w') as f:
            f.write('#pragma once\n')
        return 'src'

    def test_packing_codes_copies_files(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        src = self._make_pack_src(str(tmp_path))
        os.makedirs('out')
        packing_codes(src, '.hpp', 'out')
        copied = []
        for root, _, files in os.walk('out'):
            copied.extend(files)
        assert copied == ['lib.hpp']

    def test_packing_codes_filters_by_ext(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        src = self._make_pack_src(str(tmp_path))
        with open(os.path.join(str(tmp_path), 'src', 'math', 'gcd', 'usage.cpp'), 'w') as f:
            f.write('')
        os.makedirs('out_hpp')
        packing_codes(src, '.hpp', 'out_hpp')
        copied = []
        for root, _, files in os.walk('out_hpp'):
            copied.extend(files)
        assert copied == ['lib.hpp']

    def test_pack_cli_registered(self, cli):
        assert 'pack' in cli.commands


# ------------------------------------------------------------------ test.py --

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
            verify_codes(src, thread_limit=2,
                         time_limit=0.5, temp_path='temp')

    def test_verify_codes_cmd_function_exercises(self, tmp_path, monkeypatch):
        # Covers cmd/verify.py lines 28-30: _cmd function body is exercised
        # by letting run_command actually call _cmd, but mocking subprocess.run
        import subprocess
        monkeypatch.chdir(tmp_path)
        src = self._make_src_with_usage(str(tmp_path))
        os.makedirs('temp', exist_ok=True)
        mock_result = MagicMock()
        mock_result.returncode = 0
        mock_result.stdout = ''
        mock_result.stderr = ''
        with patch('subprocess.run', return_value=mock_result):
            verify_codes(src, thread_limit=1,
                         time_limit=0.5, temp_path='temp')

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

        from queue import Queue
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
