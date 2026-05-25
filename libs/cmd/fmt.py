import os
import re
import shlex
from collections.abc import Iterable
from pathlib import Path

import click
from packaging.version import Version

from libs.content.section import _EXT_TYPE
from libs.decorator import with_logger, with_timer
from libs.util.run_command import run_command


class FmtConfig:
    def __init__(self, lint_command_template: str, min_version: Version, version_command: str, version_regex: re.Pattern):
        self.lint_command_template = lint_command_template
        self.min_version = min_version
        self.version_command = version_command
        self.version_regex = version_regex


# code type -> (lint command template, minimum version, version command, version regex)
TYPE_LINT_COMMAND_MP: dict[str, FmtConfig] = {
    'cpp': FmtConfig(
        'clang-format --Wno-error=unknown -style=file -i {src}',
        Version('22.0.0'),
        'clang-format --version',
        re.compile(r'^.*?clang-format version (?P<version>\d+(?:\.\d+)*) .*$')),
    # tip: use `perl -MCPAN -e shell` then `isntall YAML::Tiny`, `install File::HomeDir` to install the dependency of latexindent
    'tex': FmtConfig(
        'latexindent -c=/ -l=.latexindent.yaml -s {src} -o {src}',
        Version('3.24.7'),
        'latexindent --version',
        re.compile(r'^(?P<version>\d+(?:\.\d+)*), .*$')),
    'py': FmtConfig(
        'autopep8 -i {src}',
        Version('2.3.2'),
        'autopep8 --version',
        re.compile(r'^autopep8 (?P<version>\d+(?:\.\d+)*) .*$'))
}


@with_logger
@with_timer
def lint_all_codes(files: Iterable[str], jobs: int, force_lf: bool, **kwargs):
    logger = kwargs.get('logger')
    logger.info('formatting codes...')

    type_to_files: dict[str, list[str]] = {}
    unknown_files: list[str] = []
    for file in files:
        ext = Path(file).suffix.lower()
        code_type = _EXT_TYPE.get(ext)
        if not code_type:
            unknown_files.append(file)
            continue
        type_to_files.setdefault(code_type, []).append(file)

    total_files = sum(len(type_files) for type_files in type_to_files.values())
    logger.info(f"{total_files} file(s) found")

    for code_type, type_files in type_to_files.items():
        logger.info(f"formatting {code_type} files...")
        conf: FmtConfig = TYPE_LINT_COMMAND_MP[code_type]
        try:
            version_output = os.popen(conf.version_command).read()
            current_version = Version(conf.version_regex.match(
                version_output).group('version'))
            if current_version < conf.min_version:
                logger.warning(
                    f"{code_type} formatter version ({current_version}) is less than the required version ({conf.min_version}), skipping...")
                continue
        except Exception as e:
            logger.error(
                f"failed to get version for {code_type} formatter: {e}\nversion command output: '{version_output}'")
            raise e

        failed = run_command(
            lambda x: (
                shlex.split(conf.lint_command_template.format(
                    src=shlex.quote(x))),
                {'post_run': (lambda _: Path(x).write_bytes(
                    Path(x).read_bytes().replace(
                        b'\r\n', b'\n').replace(b'\r', b'\n')
                ))}
                if force_lf
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
    @click.option('--force-lf', is_flag=True, default=True, help='force line feed (LF) as line ending')
    def _format(files: tuple[str], jobs: int, force_lf: bool):
        lint_all_codes(files, jobs, force_lf)
