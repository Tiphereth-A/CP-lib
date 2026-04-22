import shlex

import orjson
import subprocess
from pathlib import Path

import click

from libs.decorator import with_logger, with_timer
from libs.util.run_command import run_command


@with_logger
@with_timer
def run_benchmarks(
    bench_dir: str,
    bin_dir: str,
    raw_dir: str,
    output_file: str,
    min_time: str,
    thread_limit: int,
    **kwargs,
):
    logger = kwargs.get('logger')

    root_dir = Path(__file__).resolve().parents[2]
    bench_path = Path(bench_dir)
    bin_path = Path(bin_dir)
    raw_path = Path(raw_dir)
    output_path = Path(output_file)

    sources = sorted(bench_path.rglob('*.cpp'))
    if not sources:
        raise RuntimeError(f'No benchmark sources found in {bench_path}')

    logger.info(f'{len(sources)} benchmark source file(s) found')

    bin_path.mkdir(parents=True, exist_ok=True)
    raw_path.mkdir(parents=True, exist_ok=True)
    for stale in raw_path.glob('*.json'):
        stale.unlink()

    def _santize_src(src: Path) -> str:
        return src.as_posix().removesuffix('.cpp').replace('%', r'%25').replace('/', r'%2F')

    params = [(src,
               bin_path / f"{_santize_src(src)}.out",
               raw_path / f"{_santize_src(src)}.json"
               ) for src in sources]

    run_command(
        lambda x: (shlex.split(
            'g++ -std=gnu++20 -O2 {src} -lbenchmark -o {out}'.format(
                src=shlex.quote(str(x[0])),
                out=shlex.quote(str(x[1])))), {}),  params, thread_limit)

    for src, exe, out in params:
        logger.debug(f'Run {src}')
        subprocess.run(
            shlex.split(
                '{exe} --benchmark_format=json --benchmark_min_time={min_time} --benchmark_out={out}'.format(
                    exe=shlex.quote(str(exe)),
                    min_time=min_time,
                    out=shlex.quote(str(out)))),
            check=True,
            capture_output=True,
            text=True,
            encoding='utf-8',
        )

    files = sorted(raw_path.glob('*.json'))
    if not files:
        raise RuntimeError('No benchmark outputs were generated')

    merged: dict = {
        'context': {},
        'benchmarks': [],
    }

    for idx, file in enumerate(files):
        payload = orjson.loads(file.read_bytes())
        if idx == 0 and isinstance(payload.get('context'), dict):
            merged['context'] = payload['context']

        suite_name = file.stem.replace(r'%2F', '/').replace(r'%25', '%')
        entries: list[dict] = payload.get('benchmarks', [])
        for benchmark in entries:
            current = dict(benchmark)
            name = str(current.get('name', ''))
            current['name'] = f'{suite_name}::{name}' if name else suite_name
            bench_list = merged['benchmarks']
            assert isinstance(bench_list, list)
            bench_list.append(current)

    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_bytes(orjson.dumps(merged))

    bench_count = len(merged['benchmarks']) if isinstance(
        merged['benchmarks'], list) else 0
    logger.info(f'Merged {len(files)} benchmark files into {output_path}')
    logger.info(f'Total benchmark entries: {bench_count}')
    logger.info('finished')


def _register_bench(cli):
    @cli.command('bench')
    @click.option('-s', '--src', 'bench_dir', type=click.Path(exists=True, file_okay=False), default='test/bench', help='Benchmark source directory')
    @click.option('--bin-dir', type=click.Path(file_okay=False), default='.cp-lib/bench-bin', help='Directory for compiled benchmark binaries')
    @click.option('--raw-dir', type=click.Path(file_okay=False), default='.cp-lib/bench-raw', help='Directory for raw benchmark json output files')
    @click.option('-o', '--output', 'output_file', type=click.Path(dir_okay=False), default='.cp-lib/benchmark_result.json', help='Merged benchmark json output path')
    @click.option('-m', '--min-time', type=str, default='0.01', help='Google Benchmark --benchmark_min_time value')
    @click.option('-l', '--thread-limit', type=int, help='limit of threads to run', default=8)
    def _benchmark(bench_dir: str, bin_dir: str, raw_dir: str, output_file: str, min_time: str, thread_limit: int):
        run_benchmarks(bench_dir, bin_dir, raw_dir,
                       output_file, min_time, thread_limit)
