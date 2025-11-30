"""Format/lint codes command."""

import subprocess

import click

from libs.consts import CONFIG
from libs.decorator import withlog
from libs.utils import get_full_filenames


@withlog
def lint_all_codes(_code_type: str, **kwargs):
    """Format all code files of the specified type."""
    logger = kwargs.get('logger')

    filepaths = get_full_filenames(
        [
            CONFIG.get_code_dir(),
            CONFIG.get_doc_dir(),
            CONFIG.get_cheatsheet_dir(),
            CONFIG.get_usage_dir()
        ],
        CONFIG.get_ext_names_by_code_style(_code_type)
    )

    logger.info(f"{len(filepaths)} file(s) found")

    for filepath in filepaths:
        cmd = CONFIG.get_formatting_command(_code_type, filepath)
        subprocess.run(cmd, encoding='utf8', check=True)

    logger.info('finished')


def register_fmt_command(cli):
    """Register the fmt command with the CLI."""
    @cli.command('fmt')
    @click.option('-t', '--code-type', help='Code type, default: cpp', default='cpp')
    def _format(code_type: str):
        """Lint all codes"""
        lint_all_codes(code_type)
