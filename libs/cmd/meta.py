from pathlib import Path

import click

from libs.conf.tcgen import ConfigTcgen
from libs.decorator import with_logger, with_timer
from libs.meta import cppmeta_parser


@with_logger
@with_timer
def generate_testcode(src: str, target: str, **kwargs):
    logger = kwargs.get('logger')
    src_path = Path(src)
    target_path = Path(target)

    all_src_files = [filepath for filepath in src_path.glob(
        f"**/*.cppmeta") if filepath.is_file()]
    logger.info(f"{len(all_src_files)} file(s) found")

    # Remove previously generated files
    all_tar_files = [filepath for filepath in target_path.glob(
        f"**/*.cpp") if filepath.is_file()]
    for file_path in all_tar_files:
        try:
            file_path
            with file_path.open(encoding='utf8') as f:
                first_line = f.readline()
            if first_line.strip() == '#define AUTO_GENERATED':
                file_path.unlink()
        except Exception as e:
            logger.error(f"Failed to read {file_path}: {e}")
            return

    conf = ConfigTcgen(src_path / 'config.yml')

    # Generate new test files
    for src_file in all_src_files:
        src_dir = src_file.parent
        dst_dir = target_path / src_dir.relative_to(src_path)
        filename_noext = src_file.stem

        code_lines = src_file.read_text(encoding='utf8').splitlines(True)
        parser = cppmeta_parser(filename_noext, dst_dir, code_lines, conf)

        for target_file, content in parser.get_results():
            logger.debug(f"writing to {target_file}")
            target_file_path = Path(target_file)
            target_file_path.parent.mkdir(parents=True, exist_ok=True)
            with target_file_path.open('w', encoding='utf8') as tf:
                tf.writelines(content)

    logger.info('finished')


def _register_meta(cli):
    @cli.command('meta')
    @click.option('-s', '--src', type=click.Path(exists=True, file_okay=False), help='Source dir', default='test/cpv_meta')
    @click.option('-t', '--target', type=click.Path(exists=True, file_okay=False), help='Target dir', default='test/cpv')
    def _generate_testcode(src: str, target: str):
        generate_testcode(src, target)
