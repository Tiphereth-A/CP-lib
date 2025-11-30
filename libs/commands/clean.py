"""Clean command for removing nonessential files."""

import logging
import os

from libs.consts import CLEAN_EXT_NAME
from libs.decorator import withlog
from libs.utils import get_full_filenames


@withlog
def clean(logger: logging.Logger):
    """Clean up nonessential files during PDF building."""
    for full_filename in get_full_filenames(['_pdf_out'], CLEAN_EXT_NAME):
        os.remove(full_filename)
        logger.info(f"{full_filename} removed successfully")


def register_clean_command(cli):
    """Register the clean command with the CLI."""
    @cli.command('clean')
    def _clean():
        """Clean up nonessential files during PDF building"""
        clean()
