"""Generate test codes command."""

import os

import click

from libs.consts import CONFIG
from libs.decorator import with_logger, with_timer
from libs.testcase_matrix import cppmeta_parser
from libs.utils import get_full_filenames


@with_logger
@with_timer
def get_codelines(file: str, **kwargs) -> list[str]:
    """Read code lines from a file."""
    logger = kwargs.get('logger')
    logger.debug(f"opening {file}")
    with open(file, 'r', encoding='utf8') as f:
        return f.read().splitlines(True)


@with_logger
@with_timer
def generate_testcode(_source_dir: str, _target_dir: str, **kwargs):
    """Generate test code files from cppmeta source files."""
    logger = kwargs.get('logger')

    all_src_files = get_full_filenames([_source_dir], ['cppmeta'])
    logger.info(f"{len(all_src_files)} file(s) found")

    # Remove previously generated files
    all_tar_files = get_full_filenames([_target_dir], ['cpp'])
    for file_path in all_tar_files:
        try:
            f = open(file_path, 'r', encoding='utf8')
            first_line = f.readline()
            f.close()
            if first_line.strip() == '#define AUTO_GENERATED':
                os.remove(file_path)
        except Exception as e:
            logger.error(f"Failed to read {file_path}: {e}")
            raise e

    # Generate new test files
    for src_file in all_src_files:
        src_dir, basename = os.path.split(src_file)
        target_dir = os.path.join(
            _target_dir, os.path.relpath(src_dir, _source_dir))
        filename_noext = basename.removesuffix('.cppmeta')

        code_lines = get_codelines(src_file)
        parser = cppmeta_parser(filename_noext, target_dir, code_lines)

        for target_file, content in parser.get_results():
            logger.debug(f"writing to {target_file}")
            os.makedirs(os.path.dirname(target_file), exist_ok=True)
            with open(target_file, 'w', encoding='utf8') as tf:
                tf.writelines(content)

    logger.info('finished')


def register_gentc_command(cli):
    """Register the gentc command with the CLI."""
    @cli.command('gentc')
    @click.option('-s', '--source-dir', help='Source dir', default='meta_test')
    @click.option('-t', '--target-dir', help='Target dir', default='test')
    def _generate_testcode(source_dir: str, target_dir: str):
        """Generate test codes from test matrices"""
        generate_testcode(source_dir, target_dir)
