import os
import click

from libs.decorator import with_logger, with_timer
from libs.meta import cppmeta_parser
from libs.util.get_files_with_exts import get_files_with_exts


@with_logger
@with_timer
def generate_testcode(src: str, target: str, **kwargs):
    logger = kwargs.get('logger')

    all_src_files = get_files_with_exts([src], ['.cppmeta'])
    logger.info(f"{len(all_src_files)} file(s) found")

    # Remove previously generated files
    all_tar_files = get_files_with_exts([target], ['.cpp'])
    for file_path in all_tar_files:
        try:
            f = open(file_path, 'r', encoding='utf8')
            first_line = f.readline()
            f.close()
            if first_line.strip() == '#define AUTO_GENERATED':
                os.remove(file_path)
        except Exception as e:
            logger.error(f"Failed to read {file_path}: {e}")
            return

    # Generate new test files
    for src_file in all_src_files:
        src_dir, basename = os.path.split(src_file)
        dst_dir = os.path.join(
            target, os.path.relpath(src_dir, src))
        filename_noext = basename.removesuffix('.cppmeta')

        with open(src_file, 'r', encoding='utf8') as f:
            code_lines = f.read().splitlines(True)
        parser = cppmeta_parser(filename_noext, dst_dir, code_lines)

        for target_file, content in parser.get_results():
            logger.debug(f"writing to {target_file}")
            os.makedirs(os.path.dirname(target_file), exist_ok=True)
            with open(target_file, 'w', encoding='utf8') as tf:
                tf.writelines(content)

    logger.info('finished')


def _register_meta(cli):
    @cli.command('meta')
    @click.option('-s', '--src', type=click.Path(exists=True, file_okay=False), help='Source dir', default='test/cpv_meta')
    @click.option('-t', '--target', type=click.Path(exists=True, file_okay=False), help='Target dir', default='test/cpv')
    def _generate_testcode(src: str, target: str):
        generate_testcode(src, target)
