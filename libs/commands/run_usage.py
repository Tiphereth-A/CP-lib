"""Run usage codes command."""

import os
import subprocess
from threading import Thread

import click

from libs.consts import CONFIG
from libs.decorator import withlog
from libs.utils import get_full_filenames


@withlog
def run_usage_codes(_code_type: str, _thlimit: int, **kwargs):
    """Run usage code files in parallel threads."""
    logger = kwargs.get('logger')

    # Get all non-empty usage files
    usage_dir = CONFIG.get_usage_dir()
    ext_names = CONFIG.get_ext_names_by_code_style(_code_type)
    all_files = get_full_filenames([usage_dir], ext_names)

    # Filter empty files efficiently
    all_files = [
        f for f in all_files
        if os.path.getsize(f) > 0
    ]

    logger.info(f'{len(all_files)} file(s) found')

    def single_process(filepaths: list[str], thread_id: int):
        """Process files in a single thread."""
        for filepath in filepaths:
            logger.debug(f'Thread #{thread_id}: Compiling {filepath}')
            cmd = CONFIG.get_run_usage_command(_code_type, filepath)
            subprocess.run(cmd, encoding='utf8', check=True)

    # Distribute files across threads
    threads = [
        Thread(
            target=single_process,
            args=(all_files[i::_thlimit], i),
            name=str(i)
        )
        for i in range(_thlimit)
    ]

    # Start all threads
    for thread in threads:
        thread.start()

    # Wait for all threads to complete
    for thread in threads:
        thread.join()

    logger.info('Finished')


def register_run_usage_command(cli):
    """Register the run-usage command with the CLI."""
    @cli.command('run-usage')
    @click.option('-t', '--code-type', help='Code type, default: cpp', default='cpp')
    @click.option('-l', '--thlimit', type=int, default=8, help='Thread number limit, default 8')
    def _run_usage(code_type: str, thlimit: int):
        """Run usage codes"""
        run_usage_codes(code_type, thlimit)
