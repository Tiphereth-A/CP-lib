"""Generate notebook contents command."""

import click
import logging
import os
import random

from libs.classes.section import Section
from libs.consts import CONFIG, CONTENTS_DIR
from libs.decorator import with_logger, with_timer
from libs.latex_utils import (
    latex_input, latex_chapter, latex_listing_code_range,
    latex_section, latex_listing_code, PathLaTeX, NameLaTeX
)
from libs.typst_utils import (
    typst_include, typst_chapter, typst_listing_code_range,
    typst_section, typst_listing_code, PathTypst, NameTypst
)
from libs.utils import (
    get_full_filenames, file_preprocess, scandir_dir_merge,
    scandir_file_merge, parse_filename, unique
)


@with_logger
@with_timer
def load_from(dir_name: str, **kwargs) -> list[tuple[str, str]]:
    """Load and parse filenames from a directory."""
    filename_in_dir: list[str] = scandir_file_merge(
        CONFIG.get_all_code_ext_names(), dir_name)
    logger = kwargs.get('logger')
    logger.info(f"{len(filename_in_dir)} file(s) found")

    if filename_in_dir and logger.isEnabledFor(logging.DEBUG):
        logger.debug('Which are:\n\t' + '\n\t'.join(filename_in_dir))

    partitioned_filename: list[tuple[str, str]] = [
        parse_filename(filename) for filename in filename_in_dir
    ]

    # Check for duplicate names (without extension)
    seen_names = set()
    for name, _ in partitioned_filename:
        if name in seen_names:
            logger.error(
                f'File with duplicate name found in dir: {dir_name}')
            logger.info(
                'Each filename in the same folder should not be the same after removing the ext names')
            raise FileExistsError()
        seen_names.add(name)

    return partitioned_filename


@with_logger
@with_timer
def generate_empty_notebook_contents(doc_type: str = 'tex', override_exists: bool = True, **kwargs):
    os.makedirs(CONTENTS_DIR, exist_ok=True)
    contents_file = os.path.join(CONTENTS_DIR, f'contents_notebook.{doc_type}')
    if not override_exists and os.path.exists(contents_file):
        return
    with open(contents_file, 'w', encoding='utf8') as f:
        if doc_type == 'tex':
            f.write('%-*- coding: utf-8 -*-\n')
        else:
            f.write('#import "../template/common.typ": *\n')


@with_logger
@with_timer
def generate_notebook_contents(doc_type: str = 'tex', **kwargs):
    """Generate notebook contents from chapters and sections."""
    logger = kwargs.get('logger')
    chapters = file_preprocess(
        CONFIG.get_chapter_key(),
        scandir_dir_merge(CONFIG.get_code_dir(), CONFIG.get_doc_dir()),
        logger
    )
    logger.info(f"{len(chapters)} chapter(s) found")
    if logger.isEnabledFor(logging.DEBUG):
        logger.debug('Which are:\n\t' + '\n\t'.join(chapters))
        logger.debug('Will include in listed order')

    generate_empty_notebook_contents(doc_type=doc_type)
    contents_file = os.path.join(CONTENTS_DIR, f'contents_notebook.{doc_type}')
    with open(contents_file, 'a', encoding='utf8') as f:
        for chapter in chapters:
            _write_chapter(f, chapter, logger, doc_type=doc_type)


def _write_chapter(f, chapter: str, logger: logging.Logger, doc_type: str = 'tex'):
    """Write a chapter and its sections to the notebook file."""
    chapter_title = CONFIG.get_chapter_title(chapter)
    if doc_type == 'tex':
        f.writelines(latex_chapter(NameLaTeX(chapter_title)))
    else:  # typst
        f.writelines(typst_chapter(NameTypst(chapter_title)))

    # Get sections from config
    sections: list[Section] = CONFIG.get_sections_by_chapter(chapter)
    logger.info(f"{len(sections)} section(s) found in config")

    # Generate sections from existing files
    logger.debug("Getting section from existing files")
    sections_generated = _generate_sections_from_files(chapter, logger)
    logger.info(
        f"{len(sections_generated)} section(s) generated from existing files")

    # Merge and deduplicate sections
    sections = unique(sections + sections_generated, lambda x: x.name)
    logger.info(f"{len(sections)} section(s) in total")

    # Write sections
    for section in sections:
        _write_section(f, section, logger, doc_type=doc_type)


def _generate_sections_from_files(chapter: str, logger: logging.Logger) -> list[Section]:
    """Generate sections from files found in filesystem."""
    # Cache config dirs to avoid repeated calls
    code_base_dir = CONFIG.get_code_dir()
    doc_base_dir = CONFIG.get_doc_dir()
    usage_base_dir = CONFIG.get_usage_dir()

    code_dir = os.path.join(code_base_dir, chapter)
    doc_dir = os.path.join(doc_base_dir, chapter)
    usage_dir = os.path.join(usage_base_dir, chapter)

    partitioned_code = load_from(code_dir)
    partitioned_doc = load_from(doc_dir)
    partitioned_usage = load_from(usage_dir)

    # Create mapping of name -> code_ext
    code_dict = dict(partitioned_code)
    null_ext_name = f"{random.randint(0, 114514)}.null"
    sections_generated: list[Section] = []

    # Process usage files (must have corresponding code files)
    for name, usage_ext in partitioned_usage:
        if name not in code_dict:
            logger.error(
                f"Test file '{name}.{usage_ext}' found, while code file is not")
            raise KeyError(
                f"Missing code file for usage file: {name}.{usage_ext}")
        sections_generated.append(
            Section(chapter, name, name, code_dict.pop(name), usage_ext)
        )

    # Process doc files (may not have code files)
    for name, doc_ext in partitioned_doc:
        code_ext = code_dict.pop(name, null_ext_name)
        sections_generated.append(
            Section(chapter, name, name, code_ext, null_ext_name)
        )

    # Process remaining code files (no doc or usage)
    for name, code_ext in code_dict.items():
        sections_generated.append(
            Section(chapter, name, name, code_ext, null_ext_name)
        )

    return sections_generated


def _write_section(f, section: Section, logger: logging.Logger, doc_type: str = 'tex'):
    """Write a section to the notebook file."""
    if doc_type == 'tex':
        f.writelines(latex_section(NameLaTeX(section.title)))
    else:  # typst
        f.writelines(typst_section(NameTypst(section.title)))

    # Cache config dirs to avoid repeated calls
    code_dir = CONFIG.get_code_dir()
    doc_dir = CONFIG.get_doc_dir(doc_type=doc_type)
    cvdoc_dir = CONFIG.get_cvdoc_dir()
    usage_dir = CONFIG.get_usage_dir()

    doc_ext = 'typ' if doc_type == 'typ' else 'tex'
    code_filepath, doc_filepath, _, usage_filepath = section.get_filenames(
        code_dir, doc_dir, cvdoc_dir, usage_dir, doc_ext=doc_ext)

    if doc_type == 'tex':
        f.writelines(latex_input(PathLaTeX(doc_filepath)))
    else:  # typst
        f.writelines(typst_include(PathTypst(doc_filepath)))

    # Write code listing
    file_type = CONFIG.get_file_type(section.code_ext)
    if section.code_ext == 'hpp':
        # Skip header guards (first 4 lines and last 2 lines)
        with open(code_filepath, 'rb') as code_file:
            total_lines = sum(1 for _ in code_file)
        if doc_type == 'tex':
            f.writelines(latex_listing_code_range(
                PathLaTeX(code_filepath), file_type, 4, total_lines - 2
            ))
        else:  # typst
            f.writelines(typst_listing_code_range(
                PathTypst(code_filepath), file_type, 4, total_lines - 2
            ))
    else:
        if doc_type == 'tex':
            f.writelines(latex_listing_code(
                PathLaTeX(code_filepath), file_type))
        else:  # typst
            f.writelines(typst_listing_code(
                PathTypst(code_filepath), file_type))

    # Write usage code if enabled and file is not empty
    if CONFIG.export_usage_code_in_notebook() and os.path.getsize(usage_filepath):
        usage_style = CONFIG.get_file_type(section.usage_ext)
        if doc_type == 'tex':
            f.writelines(latex_listing_code(
                PathLaTeX(usage_filepath), usage_style))
        else:  # typst
            f.writelines(typst_listing_code(
                PathTypst(usage_filepath), usage_style))


def register_gen_nb_command(cli):
    """Register the gen-nb command with the CLI."""
    @cli.command('gen-nb')
    @click.option('-t', '--doc-type', type=str, default='tex', help='Document type (tex or typ), default: tex')
    def _gen_nbc(doc_type: str):
        """Generate notebook contents"""
        generate_notebook_contents(doc_type=doc_type)
