"""Format/lint codes command."""

import subprocess

import click

from libs.consts import CONFIG
from libs.decorator import with_logger, with_timer
from libs.utils import get_full_filenames


@with_logger
@with_timer
def lint_all_codes(code_type: str, **kwargs):
    """Format all code files of the specified type."""
    logger = kwargs.get('logger')

    # Collect directories - include both tex and typ directories for notebook and cheatsheet
    dirs = [CONFIG.get_code_dir(), CONFIG.get_usage_dir()]
    for doc_type in ['tex', 'typ']:
        dirs.append(CONFIG.get_doc_dir(doc_type=doc_type))
        dirs.append(CONFIG.get_cheatsheet_dir(doc_type=doc_type))
    
    filepaths = get_full_filenames(
        dirs,
        CONFIG.get_ext_names_by_file_type(code_type)
    )

    logger.info(f"{len(filepaths)} file(s) found")

    for filepath in filepaths:
        cmd = CONFIG.get_formatting_command(code_type, filepath)
        subprocess.run(cmd, encoding='utf8', check=True)

    logger.info('finished')


def register_fmt_command(cli):
    """Register the fmt command with the CLI."""
    @cli.command('fmt')
    @click.option('-t', '--code-type', type=str, default='cpp', help='Code type, default: cpp')
    def _format(code_type: str):
        """Lint all codes"""
        lint_all_codes(code_type)
