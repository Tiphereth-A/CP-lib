"""Add new note command."""

import os

import click

from libs.classes.section import Section
from libs.consts import CONFIG
from libs.decorator import withlog


@withlog
def add_new_note(_chapter_name: str, _file_name: str, _section_title: str,
                 _code_ext_name: str, _usage_ext_name: str, **kwargs):
    """Create a new note section with all required files."""
    logger = kwargs.get('logger')

    section = Section(
        _chapter_name, _file_name, _section_title, _code_ext_name, _usage_ext_name
    )

    # Create all files
    _, _, f_cvdoc, _ = section.open(
        CONFIG.get_code_dir(),
        CONFIG.get_doc_dir(),
        CONFIG.get_cvdoc_dir(),
        CONFIG.get_usage_dir(),
        'x'
    )
    logger.info('Created')

    # Log created file paths
    code_path, doc_path, cvdoc_path, usage_path = section.get_filenames(
        CONFIG.get_code_dir(),
        CONFIG.get_doc_dir(),
        CONFIG.get_cvdoc_dir(),
        CONFIG.get_usage_dir()
    )
    logger.info(f"Code: {os.path.join(os.curdir, code_path)}")
    logger.info(f"Doc: {os.path.join(os.curdir, doc_path)}")
    logger.info(f"CVDoc: {os.path.join(os.curdir, cvdoc_path)}")
    logger.info(f"Usage: {os.path.join(os.curdir, usage_path)}")

    # Update config
    CONFIG.append_section(section)
    logger.info('Config updated')

    # Write CVDoc content
    fixed_codepath = '//' + \
        os.path.join(os.curdir, code_path).replace(
            '\\', '/').removeprefix('./')
    cvdoc_content = f"""---
title: {_file_name}
documentation_of: {fixed_codepath}
---
"""
    f_cvdoc.write(cvdoc_content)
    f_cvdoc.close()


def register_new_command(cli):
    """Register the new command with the CLI."""
    @cli.command('new')
    @click.option('-c', '--chapter-name', type=str, prompt='Chapter name', help='Chapter name (key)')
    @click.option('-f', '--file-name', type=str, prompt='File name (without ext name)', help='File name to be added')
    @click.option('-s', '--section-title', type=str, prompt='Section title', help='Section title in notebook')
    @click.option('-e', '--code-ext-name', type=str, prompt='Ext name of code file', help='Ext name of code file',
                  default='hpp')
    @click.option('-u', '--usage-ext-name', type=str, prompt='Ext name of usage file', help='Ext name of usage file',
                  default='cpp')
    def _new_note(chapter_name: str, file_name: str, section_title: str, code_ext_name: str,
                  usage_ext_name: str):
        """Add new note"""
        add_new_note(chapter_name, file_name, section_title,
                     code_ext_name, usage_ext_name)
