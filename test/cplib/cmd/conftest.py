import click
import pytest

from libs.cmd import register_main_commands


@pytest.fixture
def cli():
    @click.group()
    def _cli():
        pass

    register_main_commands(_cli)
    return _cli
