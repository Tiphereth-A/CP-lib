import re
import shlex

import orjson
import subprocess
from pathlib import Path

import click

from libs.decorator import with_logger, with_timer
from libs.util.run_command import run_command

RE_COMPARISON = re.compile(r'/\*comparison\n(.*?)\*/', re.DOTALL)


@with_logger
@with_timer
def run_benchmarks(
    bench_dir: str,
    bin_dir: str,
    raw_dir: str,
    compare_py_dir: str,
    thread_limit: int,
    dry_run: bool,
    **kwargs,
):
    logger = kwargs.get('logger')

    bench_path = Path(bench_dir)
    bin_path = Path(bin_dir)
    raw_path = Path(raw_dir)

    sources = sorted(bench_path.rglob('*.cpp'))
    if not sources:
        raise RuntimeError(f'No benchmark sources found in {bench_path}')

    logger.info(f'{len(sources)} benchmark source file(s) found')

    bin_path.mkdir(parents=True, exist_ok=True)
    raw_path.mkdir(parents=True, exist_ok=True)
    for stale in raw_path.glob('*.json'):
        stale.unlink()

    params = [(src,
               bin_path /
               f"{src.as_posix().removesuffix('.cpp').replace('%', r'%25').replace('/', r'%2F')}.out"
               ) for src in sources]

    run_command(
        lambda x: (shlex.split(
            'g++ -std=gnu++20 -O2 {src} -lbenchmark -o {out}'.format(
                src=shlex.quote(str(x[0])),
                out=shlex.quote(str(x[1])))), {}),  params, thread_limit)

    cmds = []

    for src, exe in params:
        comp = RE_COMPARISON.search(src.read_text(encoding='utf-8'))
        if comp:
            comp = comp.group(1).splitlines()
            logger.info(f'{len(comp)} comparison(s) found in {src}')
            for arg in comp:
                cmd = shlex.split(
                    'uv run python {compare_py_dir}/compare.py filters ./{exe} {arg}'.format(
                        compare_py_dir=str(compare_py_dir),
                        exe=shlex.quote(str(exe)),
                        arg=arg.strip(),
                    ))
                if dry_run:
                    cmds.append(cmd)
                else:
                    logger.info(f'\n::group::{src} {arg.strip()}\n' + subprocess.run(
                        cmd,
                        capture_output=True,
                        text=True,
                        encoding='utf-8',
                    ).stdout+'\n::endgroup::')

    logger.info('finished')
    return cmds


def _register_bench(cli):
    @cli.command('bench')
    @click.option('-s', '--src', 'bench_dir', type=click.Path(exists=True, file_okay=False), default='test/bench', help='Benchmark source directory')
    @click.option('--bin-dir', type=click.Path(file_okay=False), default='.cp-lib/bench-bin', help='Directory for compiled benchmark binaries')
    @click.option('--raw-dir', type=click.Path(file_okay=False), default='.cp-lib/bench-raw', help='Directory for raw benchmark json output files')
    @click.option('--compare-py-dir', type=click.Path(file_okay=False), default='.cp-lib/compare', help='Directory for comparison Python scripts')
    @click.option('-l', '--thread-limit', type=int, help='limit of threads to run', default=8)
    @click.option('--dry-run', is_flag=True, help='Perform a dry run without executing benchmarks')
    def _benchmark(bench_dir: str, bin_dir: str, raw_dir: str, compare_py_dir: str,  thread_limit: int, dry_run: bool):
        cmds = run_benchmarks(bench_dir, bin_dir, raw_dir,
                              compare_py_dir, thread_limit, dry_run)
        if dry_run:
            print('\n'.join(shlex.join(cmd) for cmd in cmds))
