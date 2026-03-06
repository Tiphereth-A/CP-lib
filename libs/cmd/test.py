import os
import re
import shlex

import click

from libs.util.get_src_files import get_src_files
from libs.util.run_command import run_command
from libs.decorator import with_logger, with_timer

RE_USAGE_MARKER = re.compile(
    r'(# *define|// *(?:competitive-verifier|cplib\.manager):) PROBLEM ')


@with_logger
@with_timer
def test_codes(src: str, thread_limit: int, temp_path: str, **kwargs):
    logger = kwargs.get('logger')

    files = list(filter(
        lambda x: x.endswith('.cpp') and os.path.getsize(x) > 0 and RE_USAGE_MARKER.search(open(
            x, 'r').read()),
        get_src_files(src)))

    logger.info(f'{len(files)} file(s) found')

    def _cmd(x):
        _dir = os.path.join(temp_path, os.path.dirname(x))
        os.makedirs(_dir, exist_ok=True)
        return shlex.split(
            'g++ -std=gnu++20 -fmax-errors=1 -ftrapv {src} -o {out}'.format(
                src=shlex.quote(x),
                out=shlex.quote(os.path.join(_dir, os.path.basename(x).replace('.', '_')))))

    failed = run_command(_cmd, files, thread_limit)

    if failed:
        logger.error(f'{len(failed)} file(s) failed:')
        for f in failed:
            logger.error(f'  {f}')
    logger.info('finished')


def _register_test(cli):
    @cli.command('test')
    @click.option('-s', '--src', type=click.Path(exists=True, file_okay=False), help='Source directory', default='src')
    @click.option('-l', '--thread-limit', type=int, help='limit of threads to run', default=8)
    @click.option('-T', '--temp-path', type=str, help='Temporary path for compiled files', default='.cp-lib/test')
    def _test(src: str, thread_limit: int, temp_path: str):
        test_codes(src, thread_limit, temp_path)
