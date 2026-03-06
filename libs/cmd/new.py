import click

from libs.content import ContentTree
from libs.decorator import with_logger, with_timer


@with_logger
@with_timer
def new_section(content_tree: ContentTree, fullname: str, title: str, **kwargs):
    logger = kwargs.get('logger')

    section = content_tree.touch(fullname, title).get_section()
    section.init_files()

    logger.info('finished')


def _register_new(cli):
    @cli.command('new')
    @click.option('-s', '--src', type=click.Path(exists=True, file_okay=False), help='Source directory', default='src')
    @click.option('-n', '--fullname', type=str, prompt='Section fullname', help='fullname of the new section, e.g., comb.binom')
    @click.option('-t', '--title', type=str, prompt='Section title', help='title of the new section, default to the last part of fullname', default='')
    def _new(src: str, fullname: str,  title: str):
        content_tree = ContentTree(src)
        new_section(content_tree, fullname,  title)
