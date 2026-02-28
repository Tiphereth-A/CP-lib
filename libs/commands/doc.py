"""TeX/Typst file generation command."""

import os
import click

from libs.classes.content_tree import ContentTree
from libs.configs import CONTENT_TREE
from libs.decorator import with_logger, with_timer
from libs.latex_utils import NameLaTeX, PathLaTeX, latex_input, latex_section
from libs.utils import TEMP_PATH


@with_logger
@with_timer
def gen_tex(**kwargs):
    logger = kwargs.get('logger')

    @with_logger
    def dfs(node: ContentTree.Node, level: int, **kwargs):
        if not node._children:
            node.get_section().expand_tex()
            return

        for child, _ in node.get_config().get_section_list():
            dfs(node._children[child], level+1)

        sections = node.get_config().get_section_list()

        chapter_dir = os.path.join(TEMP_PATH, *node.fullname().split('.'))
        chapter_content = []
        for name, title in sections:
            chapter_content.extend(latex_section(
                NameLaTeX(title),
                PathLaTeX(os.path.join(*node.fullname().split('.')[1:], name)),
                level))
            child_rel = os.path.join(chapter_dir, name, 'doc.tex')
            chapter_content.extend(latex_input(PathLaTeX(child_rel)))
        chapter_content = ''.join(chapter_content)

        chapter_doc_path = os.path.join(*node.fullname().split('.'), 'doc.tex')
        if os.access(chapter_doc_path, os.F_OK):
            with open(chapter_doc_path, 'r', encoding='utf8') as f:
                chapter_content = f.read().replace(
                    r'% {content}', chapter_content)

        chapter_content = chapter_content.strip() + '\n'

        os.makedirs(chapter_dir, exist_ok=True)
        result_path = os.path.join(chapter_dir, 'doc.tex')
        with open(result_path, 'w', encoding='utf8') as f:
            f.write(chapter_content)

    dfs(CONTENT_TREE.root, 0)

    logger.info('finished')


@with_logger
@with_timer
def gen_typst(**kwargs):
    assert False, "Not implemented yet"


def register_doc_command(cli):
    """Register the doc command with the CLI."""
    @cli.command('doc')
    @click.option('-t', '--type', type=click.Choice(['tex', 'typ']), help='document type to generate, default to tex', default='tex')
    def _doc(type: str):
        if type == 'tex':
            gen_tex()
        elif type == 'typ':
            gen_typst()
        else:
            raise ValueError(f"Unsupported document type: {type}")
