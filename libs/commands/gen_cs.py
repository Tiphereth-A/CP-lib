"""Generate cheatsheet contents command."""

import logging
import os

from libs.consts import CONFIG, CONTENTS_DIR, CONTENTS_CS
from libs.decorator import withlog
from libs.latex_utils import latex_chapter, latex_section, latex_input, PathLaTeX, NameLaTeX
from libs.utils import file_preprocess, scandir_file_merge


@withlog
def generate_cheatsheet_contents(logger: logging.Logger):
    """Generate cheatsheet contents from configured cheatsheet files."""
    os.makedirs(CONTENTS_DIR, exist_ok=True)

    with open(CONTENTS_CS, 'w', encoding='utf8') as f:
        f.write('%-*- coding: utf-8 -*-\n')

        # Get cheatsheet files
        cheatsheet_names = [
            f'{name}.tex' for name in CONFIG.get_cheatsheets()]
        existing_files = scandir_file_merge(
            ['tex'], CONFIG.get_cheatsheet_dir())
        files = file_preprocess(cheatsheet_names, existing_files, logger)

        # Convert to full paths
        cheatsheet_dir = CONFIG.get_cheatsheet_dir()
        full_paths = [os.path.join(cheatsheet_dir, item) for item in files]

        logger.info(f"{len(full_paths)} file(s) found:")
        if logger.isEnabledFor(logging.DEBUG):
            logger.debug('Which are:\n\t' + '\n\t'.join(full_paths))
            logger.debug('Will include in listed order')

        f.writelines(latex_chapter(NameLaTeX('Cheatsheet')))

        for file_path in full_paths:
            # Extract cheatsheet name from path
            rel_path = os.path.relpath(file_path, cheatsheet_dir)
            # Normalize path separators and remove extension
            name = rel_path.replace(
                '\\', '/').replace('/', '').removesuffix('.tex')
            cheatsheet_name = CONFIG.get_cheatsheet_name(name)

            f.writelines(latex_section(NameLaTeX(cheatsheet_name)))
            f.writelines(latex_input(PathLaTeX(file_path)))


def register_gen_cs_command(cli):
    """Register the gen-cs command with the CLI."""
    @cli.command('gen-cs')
    def _gen_csc():
        """Generate cheatsheet contents"""
        generate_cheatsheet_contents()
