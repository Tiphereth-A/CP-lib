#!/usr/bin/python3
# -*- coding: utf-8 -*-

import logging
import os
import random
import subprocess
from threading import Thread

import click
import coloredlogs

from libs.classes.section import Section
from libs.consts import CONFIG, CLEAN_EXT_NAME, CONTENTS_CS, CONTENTS_DIR, CONTENTS_NB
from libs.decorator import withlog
from libs.latex_utils import latex_input, latex_chapter, latex_listing_code_range, latex_section, latex_listing_code, PathLaTeX, NameLaTeX, LATEX_COMPILE_COMMAND_GROUP
from libs.testcase_matrix import cppmeta_parser
from libs.utils import get_full_filenames, file_preprocess, scandir_dir_merge, scandir_file_merge, parse_filename, unique


@click.group()
@click.option('-l', '--level', type=click.Choice(['CRITICAL', 'ERROR', 'WARNING', 'INFO', 'DEBUG']), help='log level',
              default='INFO')
def cli(level: str):
    coloredlogs.install(level=level,
                        fmt='%(asctime)s %(levelname)s %(programname)s::%(name)s [%(process)d] %(message)s',
                        field_styles={'asctime': {'color': 'green'},
                                      'hostname': {'color': 'red'},
                                      'levelname': {'bold': True, 'color': 'magenta'},
                                      'name': {'faint': True, 'color': 'blue'},
                                      'programname': {'bold': True, 'color': 'cyan'},
                                      'process': {'faint': True, 'color': 'green'},
                                      'username': {'color': 'yellow'}},
                        level_styles={'critical': {'bold': True, 'color': 'red'},
                                      'debug': {'color': 'cyan'},
                                      'error': {'color': 'red'},
                                      'info': {'bright': True, 'color': 'white'},
                                      'notice': {'color': 'magenta'},
                                      'spam': {'color': 'green', 'faint': True},
                                      'success': {'bold': True, 'color': 'green'},
                                      'verbose': {'color': 'blue'},
                                      'warning': {'bright': True, 'color': 'yellow'}})


@cli.command('clean')
def _clean():
    """Clean up nonessential files during PDF building"""

    @withlog
    def clean(logger: logging.Logger):
        for fullFilename in get_full_filenames(['_pdf_out'], CLEAN_EXT_NAME):
            os.remove(fullFilename)
            logger.info(rf"{fullFilename} removed successfully")

    clean()


@cli.command('gen-nb')
def _gen_nbc():
    """Generate notebook contents"""

    @withlog
    def generate_notebook_contents(logger: logging.Logger):
        if not os.access(CONTENTS_DIR, os.R_OK):
            os.makedirs(CONTENTS_DIR)
        with open(CONTENTS_NB, 'w', encoding='utf8') as f:
            f.write('%-*- coding: utf-8 -*-\n')
            chapters = file_preprocess(CONFIG.get_chapter_key(), scandir_dir_merge(
                CONFIG.get_code_dir(), CONFIG.get_doc_dir()), logger)
            logger.info(rf"{len(chapters)} chapter(s) found")
            logger.debug('Which are:\n\t' + '\n\t'.join(chapters))
            logger.debug('Will include in listed order')

            for chapter in chapters:
                f.writelines(latex_chapter(
                    NameLaTeX(CONFIG.get_chapter_title(chapter))))

                sections: list[Section] = CONFIG.get_sections_by_chapter(
                    chapter)
                logger.info(f"{len(sections)} section(s) found in config")

                logger.debug(f"Getting section from existing files")
                _sections_generated: list[Section] = []
                _partitioned_code_filename = load_from(
                    os.path.join(CONFIG.get_code_dir(), chapter))
                _partitioned_doc_filename = load_from(
                    os.path.join(CONFIG.get_doc_dir(), chapter))
                __dict: dict[str, str] = dict(_partitioned_code_filename)
                _partitioned_usage_filename = load_from(
                    os.path.join(CONFIG.get_usage_dir(), chapter))
                for k, v in _partitioned_usage_filename:
                    try:
                        _sections_generated.append(
                            Section(chapter, k, k, __dict.pop(k), v))
                    except KeyError as e:
                        logger.error(
                            f"Test file '{k}.{v}' found, while code file is not")
                        raise e
                __null_ext_name: str = f"{random.randint(0, 114514)}.null"
                for k, v in _partitioned_doc_filename:
                    _sections_generated.append(
                        Section(chapter, k, k, __dict.pop(k, __null_ext_name), __null_ext_name))
                for k, v in __dict.items():
                    _sections_generated.append(
                        Section(chapter, k, k, v, __null_ext_name))
                logger.info(
                    f"{len(_sections_generated)} section(s) generated from existing files")

                sections = unique(
                    sections + _sections_generated, lambda x: x.name)
                logger.info(f"{len(sections)} section(s) in total")

                for section in sections:
                    f.writelines(latex_section(NameLaTeX(section.title)))
                    code_filepath, doc_filepath, _, usage_filepath = section.get_filenames(
                        CONFIG.get_code_dir(), CONFIG.get_doc_dir(), CONFIG.get_cvdoc_dir(), CONFIG.get_usage_dir())
                    f.writelines(latex_input(PathLaTeX(doc_filepath)))
                    if section.code_ext == 'hpp':
                        f.writelines(latex_listing_code_range(PathLaTeX(code_filepath), CONFIG.get_code_style(
                            section.code_ext), 4, len(open(code_filepath).readlines())-2))
                    else:
                        f.writelines(latex_listing_code(
                            PathLaTeX(code_filepath), CONFIG.get_code_style(section.code_ext)))
                    if CONFIG.export_usage_code_in_notebook():
                        if not os.path.getsize(usage_filepath):
                            continue
                        f.writelines(latex_listing_code(
                            PathLaTeX(usage_filepath), CONFIG.get_code_style(section.usage_ext)))

    @withlog
    def load_from(dir_name: str, **kwargs) -> list[tuple[str, str]]:
        filename_in_dir: list[str] = scandir_file_merge(
            CONFIG.get_all_code_ext_names(), dir_name)
        kwargs.get('logger').info(rf"{len(filename_in_dir)} file(s) found")
        if len(filename_in_dir):
            kwargs.get('logger').debug(
                'Which are:\n\t' + '\n\t'.join(filename_in_dir))

        _partitioned_filename: list[tuple[str, str]] = [
            parse_filename(filename) for filename in filename_in_dir]
        if len(set([k for k, v in _partitioned_filename])) != len(_partitioned_filename):
            kwargs.get('logger').error(
                f'File with duplicate name found in dir: {dir_name}')
            kwargs.get('logger').info(
                'Each filenames in the same folder should not be the same after removing the ext names')
            raise FileExistsError()

        return _partitioned_filename

    generate_notebook_contents()


@cli.command('gen-cs')
def _gen_csc():
    """Generate cheatsheet contents"""

    @withlog
    def generate_cheatsheet_contents(logger: logging.Logger):
        if not os.access(CONTENTS_DIR, os.R_OK):
            os.makedirs(CONTENTS_DIR)
        with open(CONTENTS_CS, 'w', encoding='utf8') as f:
            f.write('%-*- coding: utf-8 -*-\n')
            files: list[str] = file_preprocess([f'{f}.tex' for f in CONFIG.get_cheatsheets()],
                                               scandir_file_merge(['tex'], CONFIG.get_cheatsheet_dir()), logger)
            files = [os.path.join(CONFIG.get_cheatsheet_dir(), item)
                     for item in files]
            logger.info(rf"{len(files)} file(s) found:")
            logger.debug('Which are:\n\t' + '\n\t'.join(files))
            logger.debug('Will include in listed order')

            f.writelines(latex_chapter(NameLaTeX('Cheatsheet')))
            for file in files:
                f.writelines(latex_section(NameLaTeX(CONFIG.get_cheatsheet_name(file.removeprefix(CONFIG.get_cheatsheet_dir())
                                                                                .removeprefix('/')
                                                                                .removeprefix('\\')
                                                                                .removesuffix('.tex')))))
                f.writelines(latex_input(PathLaTeX(file)))

    generate_cheatsheet_contents()


@cli.command('run-usage')
@click.option('-t', '--code-type', help='Code type, default: cpp', default='cpp')
@click.option('-l', '--thlimit', type=int, default=8, help='Thread number limit, default 8')
def _run_usage(code_type: str, thlimit: int):
    """Run usage codes"""

    @withlog
    def run_usage_codes(_code_type: str, _thlimit: int, **kwargs):
        all_files: list[str] = list(filter(lambda x: os.path.getsize(x), get_full_filenames(
            [CONFIG.get_usage_dir()], CONFIG.get_ext_names_by_code_style(_code_type))))

        kwargs.get('logger').info(f'{len(all_files)} file(s) found')

        def single_process(filepaths: str, id: int):
            for filepath in filepaths:
                kwargs.get('logger').debug(
                    f'Thread #{id}: Compiling {filepath}')
                cmd: list[str] = CONFIG.get_run_usage_command(
                    _code_type, filepath)
                subprocess.run(cmd, encoding='utf8', check=True)

        thread_all: list[Thread] = [Thread(target=single_process, args=(
            all_files[x::_thlimit], x), name=str(x)) for x in range(_thlimit)]
        for th in thread_all:
            th.start()
        for th in thread_all:
            th.join()

        kwargs.get('logger').info('Finished')

    run_usage_codes(code_type, thlimit)


@cli.command('run')
@click.option('--no-fmt', is_flag=True, help='Do not lint codes before compile')
@click.option('--no-run-usage', is_flag=True, help='Do not run test usage codes before compile')
@click.option('--no-gen', is_flag=True, help='Do not generate content before compile')
@click.option('--no-clean', is_flag=True, help='Do not clean files after compile')
def _compile(no_fmt: bool, no_run_usage: bool, no_gen: bool, no_clean: bool):
    """Compile notebook"""

    @withlog
    def compile_all(_no_fmt: bool, _no_run_usage: bool, _no_gen: bool, _no_clean: bool, **kwargs):
        cnt: int = 0
        for procedure in LATEX_COMPILE_COMMAND_GROUP:
            now_proc: list[str] = procedure(CONFIG.get_notebook_file())
            cnt += 1
            kwargs.get('logger').info(
                f'Step {cnt} / {len(LATEX_COMPILE_COMMAND_GROUP)}' + '\n' + '-' * 80)
            subprocess.run(now_proc, encoding='utf8', check=True)

        kwargs.get('logger').info('Finished')

    if not no_fmt:
        for code_style in CONFIG.get_all_code_styles():
            _format.callback(code_style)

    if not no_run_usage:
        for code_style in CONFIG.get_all_code_styles():
            _run_usage.callback(code_style, 8)

    if not no_gen:
        _gen_nbc.callback()
        _gen_csc.callback()
    else:
        with open(CONTENTS_NB, 'a', encoding='utf8'):
            pass
        with open(CONTENTS_CS, 'a', encoding='utf8'):
            pass

    compile_all(no_fmt, no_run_usage, no_gen, no_clean)

    if not no_clean:
        _clean.callback()


@cli.command('fmt')
@click.option('-t', '--code-type', help='Code type, default: cpp', default='cpp')
def _format(code_type: str):
    """Lint all codes"""

    @withlog
    def lint_all_codes(_code_type: str, **kwargs):
        filepaths: list[str] = get_full_filenames([CONFIG.get_code_dir(),
                                                   CONFIG.get_doc_dir(),
                                                   CONFIG.get_cheatsheet_dir(),
                                                   CONFIG.get_usage_dir()],
                                                  CONFIG.get_ext_names_by_code_style(_code_type))
        kwargs.get('logger').info(f"{len(filepaths)} file(s) found")
        for filepath in filepaths:
            cmd: list[str] = CONFIG.get_formatting_command(
                _code_type, filepath)
            subprocess.run(cmd, encoding='utf8', check=True)

        kwargs.get('logger').info('finished')

    lint_all_codes(code_type)


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

    @withlog
    def add_new_note(_chapter_name: str, _file_name: str, _section_title: str,
                     _code_ext_name: str, _usage_ext_name: str, **kwargs):
        section: Section = Section(
            _chapter_name, _file_name, _section_title, _code_ext_name, _usage_ext_name)

        _, _, f_cvdoc, _ = section.open(CONFIG.get_code_dir(), CONFIG.get_doc_dir(),
                                        CONFIG.get_cvdoc_dir(), CONFIG.get_usage_dir(), 'x')
        kwargs.get('logger').info('Created')

        _code, _doc, _cvdoc, _usage = section.get_filenames(CONFIG.get_code_dir(), CONFIG.get_doc_dir(),
                                                            CONFIG.get_cvdoc_dir(), CONFIG.get_usage_dir())
        kwargs.get('logger').info(f"Code: {os.path.join(os.curdir, _code)}")
        kwargs.get('logger').info(f"Doc: {os.path.join(os.curdir, _doc)}")
        kwargs.get('logger').info(f"CVDoc: {os.path.join(os.curdir, _cvdoc)}")
        kwargs.get('logger').info(f"Usage: {os.path.join(os.curdir, _usage)}")

        CONFIG.append_section(section)
        kwargs.get('logger').info('Config updated')

        _fixed_codepath = '//' + \
            os.path.join(os.curdir, _code).replace(
                '\\', '/').removeprefix('./')
        _cvdoc_content = f"""---
title: {_file_name}
documentation_of: {_fixed_codepath}
---
"""
        f_cvdoc.write(_cvdoc_content)

    add_new_note(chapter_name, file_name, section_title,
                 code_ext_name, usage_ext_name)


@cli.command('gentc')
@click.option('-s', '--source-dir', help='Source dir', default='meta_test')
@click.option('-t', '--target-dir', help='Target dir', default='test')
def _generate_testcode(source_dir: str, target_dir: str):
    """Generate test codes from test matrices"""

    @withlog
    def get_codelines(file: str, **kwargs) -> list[str]:
        with open(file, 'r') as f:
            kwargs.get('logger').debug(f"opening {file}")
            return f.read().splitlines(True)

    @withlog
    def generate_testcode(_source_dir: str, _target_dir: str, **kwargs):
        _source_dir = _source_dir
        _target_dir = _target_dir

        all_src_files: list[str] = get_full_filenames(
            [_source_dir], ['cppmeta'])
        kwargs.get('logger').info(f"{len(all_src_files)} file(s) found")

        # remove generated files in previous
        all_tar_files: list[str] = get_full_filenames([_target_dir], ['cpp'])
        for file in all_tar_files:
            with open(file, 'r') as f:
                first_line = f.readline()
                if first_line.strip() == '#define AUTO_GENERATED':
                    f.close()
                    os.remove(file)

        for file in all_src_files:
            tfdir, bname = os.path.split(file)
            tfdir = _target_dir + tfdir.removeprefix(_source_dir)
            bname = bname.removesuffix('.cppmeta')

            code_lines = get_codelines(file)
            parser = cppmeta_parser(bname, tfdir, code_lines)

            for tfile, content in parser.get_results():
                kwargs.get('logger').debug(f"writing to {tfile}")
                with open(tfile, 'w') as tf:
                    tf.writelines(content)

        kwargs.get('logger').info('finished')

    generate_testcode(source_dir, target_dir)


if __name__ == '__main__':
    cli()
