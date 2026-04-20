import os

from click.testing import CliRunner
import pytest

from libs.cmd.meta import generate_testcode


@pytest.mark.unit
class TestMetaCommands:
    def _make_cppmeta(self, base_dir):
        """Create a minimal .cppmeta file."""
        import textwrap

        meta_src = os.path.join(base_dir, 'meta_src')
        os.makedirs(meta_src)
        code = textwrap.dedent(
            """\
            #include <bits/stdc++.h>
            // ---<GENTC>--- begin
            // ---<GENTC>--- append mints
            // ---<GENTC>--- end
            int main() {
            }
        """
        )
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

    def test_pack_cli_invocation(self, cli, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        src = os.path.join(str(tmp_path), 'src')
        os.makedirs(src, exist_ok=True)
        out = os.path.join(str(tmp_path), 'out')
        os.makedirs(out, exist_ok=True)
        with open(os.path.join(src, 'lib.hpp'), 'w') as f:
            f.write('#pragma once\n')
        runner = CliRunner()
        result = runner.invoke(cli, ['pack', '-s', src, '-e', '.hpp', '-t', out])
        assert result.exit_code == 0

    def test_meta_cli_registered(self, cli):
        assert 'meta' in cli.commands

    def test_meta_cli_invocation(self, cli, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        src = os.path.join(str(tmp_path), 'meta_src')
        target = os.path.join(str(tmp_path), 'target')
        os.makedirs(src, exist_ok=True)
        os.makedirs(target, exist_ok=True)
        runner = CliRunner()
        result = runner.invoke(cli, ['meta', '-s', src, '-t', target])
        assert result.exit_code == 0
