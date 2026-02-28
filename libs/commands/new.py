"""New section command."""

import click

from libs.configs import CONTENT_TREE
from libs.decorator import with_logger, with_timer


@with_logger
@with_timer
def new_section(fullname: str, title: str, **kwargs):
    """Create a new section at the given fullname."""
    logger = kwargs.get('logger')

    section = CONTENT_TREE.touch(fullname, title).get_section()
    section.init_files()

    logger.info('finished')


def register_new_command(cli):
    """Register the new command with the CLI."""
    @cli.command('new')
    @click.option('-n', '--fullname', type=str, prompt='Section fullname', help='fullname of the new section, e.g., comb.binom')
    @click.option('-t', '--title', type=str, prompt='Section title', help='title of the new section, default to the last part of fullname', default='')
    def _new(fullname: str, title: str):
        new_section(fullname,  title)
