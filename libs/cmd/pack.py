import os
import shutil
import click

from libs.decorator import with_logger, with_timer
from libs.util.get_src_files import get_src_files


@with_logger
@with_timer
def packing_codes(src: str, ext: str, target: str, **kwargs):
    logger = kwargs.get('logger')
    logger.info(f"searching {ext} codes...")

    files = list(filter(lambda x: x.endswith(ext), get_src_files(src)))

    logger.info(f"{len(files)} file(s) found")

    for file in files:
        new_path = os.path.join(target, *file.split(os.sep)[1:])
        os.makedirs(os.path.dirname(new_path), exist_ok=True)
        shutil.copy(file, new_path)

    logger.info('finished')


def _register_pack(cli):
    @cli.command('pack')
    @click.option('-s', '--src', type=click.Path(exists=True, file_okay=False), help='source path to pack', default='src')
    @click.option('-e', '--ext', type=str, help='file extension to pack', default='.hpp')
    @click.option('-t', '--target', type=str, help='target path to pack', default='.cp-lib/include')
    def _pack(src: str, ext: str, target: str):
        packing_codes(src, ext, target)
