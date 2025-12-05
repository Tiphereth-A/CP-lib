"""Compile notebook command."""

import os
import subprocess

from libs.consts import CONFIG, CONTENTS_DIR, CONTENTS_NB, CONTENTS_CS
from libs.decorator import with_logger, with_timer
from libs.latex_utils import LATEX_COMPILE_COMMAND_GROUP
from libs.commands.clean import clean
from libs.commands.gen_nb import generate_notebook_contents
from libs.commands.gen_cs import generate_cheatsheet_contents
from libs.commands.run_usage import run_usage_codes
from libs.commands.fmt import lint_all_codes


@with_logger
@with_timer
def compile_all(_no_fmt: bool, _no_run_usage: bool, _no_gen: bool, _no_clean: bool, **kwargs):
    """Compile LaTeX notebook."""
    logger = kwargs.get('logger')
    total_steps = len(LATEX_COMPILE_COMMAND_GROUP)

    for step_num, procedure in enumerate(LATEX_COMPILE_COMMAND_GROUP, start=1):
        command = procedure(CONFIG.get_notebook_file())
        logger.info(f'Step {step_num} / {total_steps}\n' + '-' * 80)
        subprocess.run(command, encoding='utf8', check=True)

    logger.info('Finished')


def register_compile_command(cli):
    """Register the compile command with the CLI."""
    import click

    @cli.command('run')
    @click.option('--no-fmt', is_flag=True, help='Do not lint codes before compile')
    @click.option('--no-run-usage', is_flag=True, help='Do not run test usage codes before compile')
    @click.option('--no-gen', is_flag=True, help='Do not generate content before compile')
    @click.option('--no-clean', is_flag=True, help='Do not clean files after compile')
    def _compile(no_fmt: bool, no_run_usage: bool, no_gen: bool, no_clean: bool):
        """Compile notebook"""
        # Cache code styles to avoid repeated calls
        all_code_styles = CONFIG.get_all_code_styles()

        if not no_fmt:
            for code_style in all_code_styles:
                lint_all_codes(code_style)

        if not no_run_usage:
            for code_style in all_code_styles:
                run_usage_codes(code_style, 8)

        if not no_gen:
            generate_notebook_contents()
            generate_cheatsheet_contents()
        else:
            # Ensure content files exist even if not generating
            os.makedirs(CONTENTS_DIR, exist_ok=True)
            for content_file in [CONTENTS_NB, CONTENTS_CS]:
                if not os.path.exists(content_file):
                    with open(content_file, 'w', encoding='utf8') as f:
                        f.write('%-*- coding: utf-8 -*-\n')

        compile_all(no_fmt, no_run_usage, no_gen, no_clean)

        if not no_clean:
            clean()
