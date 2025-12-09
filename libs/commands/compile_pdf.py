"""Compile notebook command."""

import subprocess

from libs.consts import CONFIG
from libs.decorator import with_logger, with_timer
from libs.commands.clean import clean
from libs.commands.gen_nb import generate_empty_notebook_contents, generate_notebook_contents
from libs.commands.gen_cs import generate_cheatsheet_contents, generate_empty_cheatsheet_contents
from libs.commands.run_usage import run_usage_codes
from libs.commands.fmt import lint_all_codes


@with_logger
@with_timer
def compile_pdf(code_type: str, **kwargs):
    """Compile notebook using selected backend (latex or typst)."""
    logger = kwargs.get('logger')

    command_args = CONFIG.get_compile_pdf_command(code_type)

    logger.info(f"Running compile command for {code_type}")
    subprocess.run(command_args, encoding='utf8', check=True)
    logger.info('Finished')


def register_compile_command(cli):
    """Register the compile command with the CLI."""
    import click

    @cli.command('run')
    @click.option('--no-fmt', is_flag=True, help='Do not lint codes before compile')
    @click.option('--no-run-usage', is_flag=True, help='Do not run test usage codes before compile')
    @click.option('--no-gen', is_flag=True, help='Do not generate content before compile')
    @click.option('--no-clean', is_flag=True, help='Do not clean files after compile')
    @click.option('-t', '--code-type', type=str, default='tex', help='Code type, default: tex')
    def _compile(no_fmt: bool, no_run_usage: bool, no_gen: bool, no_clean: bool, code_type: str):
        """Compile notebook"""
        # Cache file types to avoid repeated calls
        all_file_types = CONFIG.get_all_file_types()

        if not no_fmt:
            for file_type in all_file_types:
                lint_all_codes(file_type)

        if not no_run_usage:
            for file_type in all_file_types:
                run_usage_codes(file_type, 8)

        if not no_gen:
            generate_notebook_contents(doc_type=code_type)
            generate_cheatsheet_contents(doc_type=code_type)
        else:
            # Ensure content files exist even if not generating
            generate_empty_notebook_contents(doc_type=code_type, override_exists=False)
            generate_empty_cheatsheet_contents(doc_type=code_type, override_exists=False)

        compile_pdf(code_type)

        if not no_clean:
            clean()
