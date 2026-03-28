import os
import re
import shlex
import subprocess
import sys
import click

from queue import Queue
from libs.util.get_src_files import get_src_files
from libs.util.run_command import run_command
from libs.decorator import with_logger, with_timer

RE_USAGE_MARKER = re.compile(
    r'(# *define|// *(?:competitive-verifier|cplib\.manager):) PROBLEM ')
RE_SAMPLE = re.compile(r'/\*sample\d*\n(.*?)={8,}\n(.*?)\*/', re.DOTALL)


@with_logger
@with_timer
def verify_codes(src: str, thread_limit: int, time_limit: float, temp_path: str, **kwargs):
    logger = kwargs.get('logger')

    files = list(filter(
        lambda x: x.endswith('.cpp') and os.path.getsize(x) > 0 and RE_USAGE_MARKER.search(open(
            x, 'r').read()),
        get_src_files(src)))

    logger.info(f'{len(files)} file(s) found')

    out_src_samples: Queue[tuple[str, list[tuple[str, str]]]] = Queue()

    def _compile(x):
        _dir = os.path.join(temp_path, os.path.dirname(x))
        os.makedirs(_dir, exist_ok=True)

        _samples: list[tuple[str, str]] = []
        with open(x, 'r', encoding='utf-8') as f:
            _samples = [(m.group(1), m.group(2))
                        for m in RE_SAMPLE.finditer(f.read())]

        _out_file = os.path.join(_dir, os.path.basename(x).replace(
            '.', '_').replace(' ', '-'))+{'win32': '.exe'}.get(sys.platform, '')
        out_src_samples.put((_out_file, x, _samples))

        return (shlex.split(
            'g++ -std=gnu++20 -fmax-errors=1 -ftrapv {src} -o {out}'.format(
                src=shlex.quote(x),
                out=shlex.quote(_out_file))), {})

    compile_failed = run_command(_compile, files, thread_limit)
    compile_failed_files = set(
        i[1] for i in compile_failed) if compile_failed else set()

    run_cases: list[tuple[str, str, str]] = []
    for out_f, src_f, samples in out_src_samples.queue:
        if src_f in compile_failed_files:
            continue
        for inp, expected in samples:
            run_cases.append((out_f, inp, expected))
    logger.info(f'{len(run_cases)} case(s) found')

    def _run(case: tuple[str, str, str]):
        out_f, inp, expected = case

        def _post(result):
            def _normalize(x: str):
                return '\n'.join(l.rstrip() for l in x.splitlines())
            _output = _normalize(result.stdout)
            _expected = _normalize(expected)

            if _output != _expected:
                raise subprocess.CalledProcessError(
                    1, result.args,
                    f'Wrong answer:\n'
                    f'    Input:    {inp!r}\n'
                    f'    Expected: {_expected!r}\n'
                    f'    Got:      {_output!r}'
                )

        return ([out_f], {'subprocess_args': {'input': inp}, 'post_run': _post, 'hide_stdout': True})

    run_failed = [i[1] for i in run_command(
        _run, run_cases, thread_limit, time_limit)] if run_cases else []

    if compile_failed:
        logger.error(
            f'{len(compile_failed)} file(s) failed in compilation:\n    '+'\n    '.join(str(i) for i in compile_failed))
    if run_failed:
        logger.error(
            f'{len(run_failed)} case(s) failed in execution:\n    '+'\n    '.join(str(i) for i in run_failed))

    logger.info('finished')
    if compile_failed or run_failed:
        raise RuntimeError('verification failed')


def _register_verify(cli):
    @cli.command('verify')
    @click.option('-s', '--src', type=click.Path(exists=True, file_okay=False), help='Source directory', default='src')
    @click.option('-l', '--thread-limit', type=int, help='limit of threads to run', default=8)
    @click.option('-t', '--time-limit', type=float, help='limit of time to run', default=3)
    @click.option('-T', '--temp-path', type=str, help='Temporary path for compiled files', default='.cp-lib/test')
    def _verify(src: str, thread_limit: int, time_limit: float, temp_path: str):
        verify_codes(src, thread_limit, time_limit, temp_path)
