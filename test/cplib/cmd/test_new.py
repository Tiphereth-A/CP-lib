import os

from click.testing import CliRunner
import pytest

from libs.cmd.new import new_section
from libs.content.tree import ContentTree

from .helpers import make_src_tree


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
