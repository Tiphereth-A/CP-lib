"""Generate cheatsheet contents command."""

import click
import logging
import os

from libs.consts import CONFIG, CONTENTS_DIR
from libs.decorator import with_logger, with_timer
from libs.latex_utils import latex_chapter, latex_section, latex_input, PathLaTeX, NameLaTeX
from libs.typst_utils import typst_chapter, typst_section, typst_include, PathTypst, NameTypst
from libs.utils import file_preprocess, scandir_file_merge


@with_logger
@with_timer
def generate_empty_cheatsheet_contents(doc_type: str = 'tex', override_exists: bool = True, **kwargs):
    os.makedirs(CONTENTS_DIR, exist_ok=True)
    contents_file = os.path.join(CONTENTS_DIR, f'contents_cheatsheet.{doc_type}')
    if not override_exists and os.path.exists(contents_file):
        return
    with open(contents_file, 'w', encoding='utf8') as f:
        if doc_type == 'tex':
            f.write('%-*- coding: utf-8 -*-\n')
        else:
            f.write('#import "../template/common.typ": *\n')


@with_logger
@with_timer
def generate_cheatsheet_contents(doc_type: str = 'tex', logger: logging.Logger = None, **kwargs):
    """Generate cheatsheet contents from configured cheatsheet files."""
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

    generate_empty_cheatsheet_contents(doc_type=doc_type)
    contents_file = os.path.join(CONTENTS_DIR, f'contents_cheatsheet.{doc_type}')
    with open(contents_file, 'a', encoding='utf8') as f:
        if doc_type == 'tex':
            f.writelines(latex_chapter(NameLaTeX('Cheatsheet')))
        else:  # typst
            f.writelines(typst_chapter(NameTypst('Cheatsheet')))

        for file_path in full_paths:
            # Extract cheatsheet name from path
            rel_path = os.path.relpath(file_path, cheatsheet_dir)
            # Normalize path separators and remove extension
            name = rel_path.replace(
                '\\', '/').replace('/', '').removesuffix('.tex')
            cheatsheet_name = CONFIG.get_cheatsheet_name(name)

            if doc_type == 'tex':
                f.writelines(latex_section(NameLaTeX(cheatsheet_name)))
                f.writelines(latex_input(PathLaTeX(file_path)))
            else:  # typst
                f.writelines(typst_section(NameTypst(cheatsheet_name)))
                f.writelines(typst_include(PathTypst(file_path)))


def register_gen_cs_command(cli):
    """Register the gen-cs command with the CLI."""
    @cli.command('gen-cs')
    @click.option('-t', '--doc-type', type=str, default='tex', help='Document type (tex or typ), default: tex')
    def _gen_csc(doc_type: str):
        """Generate cheatsheet contents"""
        generate_cheatsheet_contents(doc_type=doc_type)
