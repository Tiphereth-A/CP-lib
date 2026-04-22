from unittest.mock import patch

import click
import libs
import pytest

from libs.cmd import register_cpv_patch_commands, register_main_commands


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
        assert cmd_names == {'bench', 'doc',
                             'new', 'verify', 'fmt', 'meta', 'pack'}

    def test_register_cpv_patch_commands_registers_cmds(self):
        @click.group()
        def group():
            pass

        register_cpv_patch_commands(group)
        assert set(group.commands.keys()) == {
            'doc', 'delegate', 'merged-result'}

    def test_cli_callback_installs_coloredlogs(self):
        with patch('libs.coloredlogs.install') as install:
            libs.cli.callback(level='INFO')
        install.assert_called_once()
