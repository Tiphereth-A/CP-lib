import os
import shlex
from collections.abc import Iterable
from pathlib import Path

import click

from libs.content.section import _EXT_TYPE
from libs.decorator import with_logger, with_timer
from libs.util.run_command import run_command

TYPE_LINT_COMMAND_MP: dict[str, str] = {
    'cpp': 'clang-format --Wno-error=unknown -style=file -i {src}',
    # tip: use `perl -MCPAN -e shell` then `isntall YAML::Tiny`, `install File::HomeDir` to install the dependency of latexindent
    'tex': 'latexindent -c=/ -l=.latexindent.yaml -s {src} -o {src}',
    'py': 'autopep8 -i {src}'
}


@with_logger
@with_timer
def lint_all_codes(files: Iterable[str], jobs: int, **kwargs):
    logger = kwargs.get('logger')
    logger.info('formatting codes...')

    type_to_files: dict[str, list[str]] = {}
    unknown_files: list[str] = []
    for file in files:
        ext = os.path.splitext(file)[1].lower()
        code_type = _EXT_TYPE.get(ext)
        if not code_type:
            unknown_files.append(file)
            continue
        type_to_files.setdefault(code_type, []).append(file)

    total_files = sum(len(type_files) for type_files in type_to_files.values())
    logger.info(f"{total_files} file(s) found")

    for code_type, type_files in type_to_files.items():
        logger.info(f"formatting {code_type} files...")
        failed = run_command(
            lambda x: (
                shlex.split(TYPE_LINT_COMMAND_MP[code_type].format(
                    src=shlex.quote(x))),
                {'post_run': (lambda _: Path(x).write_bytes(
                    Path(x).read_bytes().replace(
                        b'\r\n', b'\n').replace(b'\r', b'\n')
                ))}
                if code_type == 'tex'
                else {},
            ),
            type_files,
            jobs)

        if failed:
            logger.error(f'{len(failed)} file(s) failed for {code_type}:')
            for f in failed:
                logger.error(f'  {f}')
    logger.info('finished')


def _register_fmt(cli):
    @cli.command('fmt')
    @click.argument('files', nargs=-1, type=click.Path(exists=True, dir_okay=False, file_okay=True, readable=True))
    @click.option('-j', '--jobs', type=int, help='limit of jobs to run', default=8)
    def _format(files: tuple[str], jobs: int):
        lint_all_codes(files, jobs)
