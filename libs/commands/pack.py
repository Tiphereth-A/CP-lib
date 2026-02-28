import os
import shutil

from libs.decorator import with_logger, with_timer
from libs.utils import SRC_PATH, TEMP_PATH, get_full_filenames


@with_logger
@with_timer
def packing_codes(ext: str, **kwargs):
    logger = kwargs.get('logger')
    logger.info(f"searching {ext} codes...")

    files = get_full_filenames([SRC_PATH], [ext])

    logger.info(f"{len(files)} file(s) found")

    for file in files:
        new_path = os.path.join(TEMP_PATH, 'include', *file.split(os.sep)[1:])
        os.makedirs(os.path.dirname(new_path), exist_ok=True)
        shutil.copy(file, new_path)

    logger.info('finished')


def register_pack_command(cli):
    """Register the pack command with the CLI."""
    @cli.command('pack')
    def _pack():
        """Pack all codes"""
        packing_codes('.hpp')
