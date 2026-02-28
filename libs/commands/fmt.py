"""Format/lint codes command."""

import shlex

from libs.run_command import run_command
from libs.decorator import with_logger, with_timer
from libs.utils import SRC_PATH, TEST_PATH, THREAD_LIMIT, TYPE_EXT_MP, get_full_filenames


TYPE_LINT_COMMAND_MP: dict[str, str] = {
    'cpp': 'clang-format --Wno-error=unknown -style=file -i {src}',
    # tip: use `perl -MCPAN -e shell` then `isntall YAML::Tiny`, `install File::HomeDir` to install the dependency of latexindent
    'tex': 'latexindent --cruft=/ -l -s {src} -o {src}',
    'py': 'autopep8 -i {src}'
}


@with_logger
@with_timer
def lint_all_codes(code_type: str, **kwargs):
    """Format all code files of the specified type."""
    logger = kwargs.get('logger')
    logger.info(f"formatting {code_type} codes...")

    files = get_full_filenames(
        [SRC_PATH, TEST_PATH], TYPE_EXT_MP[code_type])

    logger.info(f"{len(files)} file(s) found")

    failed = run_command(
        lambda x: shlex.split(
            TYPE_LINT_COMMAND_MP[code_type].format(src=shlex.quote(x))), THREAD_LIMIT, files)

    if failed:
        logger.error(f'{len(failed)} file(s) failed:')
        for f in failed:
            logger.error(f'  {f}')
    logger.info('finished')


def register_fmt_command(cli):
    """Register the fmt command with the CLI."""
    @cli.command('fmt')
    def _format():
        """Lint all codes"""
        lint_all_codes('cpp')
        lint_all_codes('tex')
        lint_all_codes('py')
