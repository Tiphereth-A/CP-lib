"""Run test codes command."""

import os
import re
import shlex

from libs.run_command import run_command
from libs.decorator import with_logger, with_timer
from libs.utils import SRC_PATH, TEMP_PATH, TEST_PATH, THREAD_LIMIT, get_full_filenames

RE_USAGE_MARKER = re.compile(
    r'(# *define|// *(?:competitive-verifier|cplib\.manager):) PROBLEM ')


@with_logger
@with_timer
def test_codes(**kwargs):
    """Run usage code files in parallel threads."""
    logger = kwargs.get('logger')

    files = list(filter(
        lambda x: os.path.getsize(x) > 0 and RE_USAGE_MARKER.search(open(
            x, 'r').read()),
        get_full_filenames([SRC_PATH, TEST_PATH], ['.cpp'])))

    logger.info(f'{len(files)} file(s) found')

    def _cmd(x):
        _dir = os.path.join(TEMP_PATH, os.path.dirname(x))
        os.makedirs(_dir, exist_ok=True)
        return shlex.split(
            'g++ -std=gnu++20 -fmax-errors=1 -ftrapv {src} -o {out}'.format(
                src=shlex.quote(x),
                out=shlex.quote(os.path.join(_dir, os.path.basename(x).replace('.', '_')))))

    failed = run_command(_cmd, THREAD_LIMIT, files)

    if failed:
        logger.error(f'{len(failed)} file(s) failed:')
        for f in failed:
            logger.error(f'  {f}')
    logger.info('finished')


def register_test_command(cli):
    """Register the test command with the CLI."""
    @cli.command('test')
    def _test():
        """Run usage codes"""
        test_codes()
