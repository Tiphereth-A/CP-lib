from collections.abc import Iterable
import shlex

import click

from libs.content.section import _TYPE_EXT
from libs.util.run_command import run_command
from libs.decorator import with_logger, with_timer
from libs.util.get_files_with_exts import get_files_with_exts


TYPE_LINT_COMMAND_MP: dict[str, str] = {
    'cpp': 'clang-format --Wno-error=unknown -style=file -i {src}',
    # tip: use `perl -MCPAN -e shell` then `isntall YAML::Tiny`, `install File::HomeDir` to install the dependency of latexindent
    'tex': 'latexindent --cruft=/ -l -s {src} -o {src}',
    'py': 'autopep8 -i {src}'
}


@with_logger
@with_timer
def lint_all_codes(dirs: Iterable[str], code_type: str, thread_limit: int, **kwargs):
    logger = kwargs.get('logger')
    logger.info(f"formatting {code_type} codes...")

    files = get_files_with_exts(dirs, _TYPE_EXT[code_type])

    logger.info(f"{len(files)} file(s) found")

    failed = run_command(
        lambda x: shlex.split(
            TYPE_LINT_COMMAND_MP[code_type].format(src=shlex.quote(x))),  files, thread_limit)

    if failed:
        logger.error(f'{len(failed)} file(s) failed:')
        for f in failed:
            logger.error(f'  {f}')
    logger.info('finished')


def _register_fmt(cli):
    @cli.command('fmt')
    @click.option('-d', '--dirs', multiple=True, type=click.Path(exists=True, file_okay=False), help='directories')
    @click.option('-t', '--type', type=click.Choice(TYPE_LINT_COMMAND_MP.keys()), help='code type to format', default='cpp')
    @click.option('-l', '--thread-limit', type=int, help='limit of threads to run', default=8)
    def _format(dirs: tuple[str], type: str, thread_limit: int):
        lint_all_codes(dirs, type, thread_limit)
