import os
import click

from libs.content import ContentTree
from libs.decorator import with_logger, with_timer
from libs.content.latex_utils import NameLaTeX, PathLaTeX, latex_input, latex_section
from libs.content.typst_utils import NameTypst, PathTypst, typst_heading, typst_include


def _check_chapter_doc_consistency(fullname: str) -> tuple[bool, bool]:
    chapter_doc_tex = os.path.join(*fullname.split('.'), 'doc.tex')
    chapter_doc_typ = os.path.join(*fullname.split('.'), 'doc.typ')
    has_tex = os.access(chapter_doc_tex, os.F_OK)
    has_typ = os.access(chapter_doc_typ, os.F_OK)
    if has_tex != has_typ:
        raise ValueError(
            f"Chapter '{fullname}': 'doc.tex' and 'doc.typ' must both exist or neither")
    return has_tex, has_typ


@with_logger
@with_timer
def gen_tex(content_tree: ContentTree, temp_path: str, **kwargs):
    logger = kwargs.get('logger')

    @with_logger
    def dfs(node: ContentTree.Node, level: int, **kwargs):
        if not node._children:
            node.get_section().expand_tex(temp_path)
            return

        for child, _ in node.get_config().get_section_list():
            dfs(node._children[child], level+1)

        sections = node.get_config().get_section_list()

        chapter_dir = os.path.join(temp_path, *node.fullname().split('.'))
        chapter_content = []
        for name, title in sections:
            chapter_content.extend(latex_section(
                NameLaTeX(title),
                PathLaTeX(os.path.join(*node.fullname().split('.')[1:], name)),
                level))
            child_rel = os.path.join(chapter_dir, name, 'doc.tex')
            chapter_content.extend(latex_input(PathLaTeX(child_rel)))
        chapter_content = ''.join(chapter_content)

        chapter_doc_tex = os.path.join(*node.fullname().split('.'), 'doc.tex')
        has_tex, _ = _check_chapter_doc_consistency(node.fullname())
        if has_tex:
            with open(chapter_doc_tex, 'r', encoding='utf8') as f:
                chapter_content = f.read().replace(
                    r'% {content}', chapter_content)

        chapter_content = chapter_content.strip() + '\n'

        os.makedirs(chapter_dir, exist_ok=True)
        result_path = os.path.join(chapter_dir, 'doc.tex')
        with open(result_path, 'w', encoding='utf8') as f:
            f.write(chapter_content)

    dfs(content_tree.root, 0)

    logger.info('finished')


@with_logger
@with_timer
def gen_typst(content_tree: ContentTree, temp_path: str, **kwargs):
    logger = kwargs.get('logger')

    @with_logger
    def dfs(node: ContentTree.Node, level: int, **kwargs):
        if not node._children:
            node.get_section().expand_typ(temp_path)
            return

        for child, _ in node.get_config().get_section_list():
            dfs(node._children[child], level+1)

        sections = node.get_config().get_section_list()

        chapter_dir = os.path.join(temp_path, *node.fullname().split('.'))
        chapter_content = []
        for name, title in sections:
            chapter_content.extend(typst_heading(
                NameTypst(title),
                PathTypst(os.path.join(*node.fullname().split('.')[1:], name)),
                level))
            child_rel = os.path.join(name, 'doc.typ')
            chapter_content.extend(typst_include(PathTypst(child_rel)))
        chapter_content = ''.join(chapter_content)

        chapter_doc_typ = os.path.join(*node.fullname().split('.'), 'doc.typ')
        _, has_typ = _check_chapter_doc_consistency(node.fullname())
        if has_typ:
            with open(chapter_doc_typ, 'r', encoding='utf8') as f:
                chapter_content = f.read().replace('// {content}', chapter_content)

        chapter_content = chapter_content.strip() + '\n'

        os.makedirs(chapter_dir, exist_ok=True)
        result_path = os.path.join(chapter_dir, 'doc.typ')
        with open(result_path, 'w', encoding='utf8') as f:
            f.write(chapter_content)

    dfs(content_tree.root, 0)

    logger.info('finished')


def _register_doc(cli):
    @cli.command('doc')
    @click.option('-s', '--src', type=click.Path(exists=True, file_okay=False), help='Source directory', default='src')
    @click.option('-t', '--type', type=click.Choice(['tex', 'typ']), help='document type to generate', default='tex')
    @click.option('-T', '--temp-path', type=str, help='Temporary path', default='.cp-lib')
    def _doc(src: str, type: str, temp_path: str):
        content_tree = ContentTree(src)
        if type == 'tex':
            gen_tex(content_tree, temp_path)
        elif type == 'typ':
            gen_typst(content_tree, temp_path)
        else:
            raise ValueError(f"Unsupported document type: {type}")
