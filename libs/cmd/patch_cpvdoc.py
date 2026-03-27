import os
import click
import yaml

from libs.decorator import with_logger, with_timer


@with_logger
@with_timer
def patch_cpvdoc(src: str, jekyll_src: str, **kwargs):
    logger = kwargs.get('logger')

    def _group_key(src: str, category_name: str) -> str:
        return '/'.join(category_name.split('/', 2)[0:2])+'/' if category_name.startswith(src + '/') else category_name

    index_md = os.path.join(jekyll_src, 'index.md')
    logger.info(f"patching {index_md}...")

    with open(index_md, 'r', encoding='utf-8') as f:
        content = f.read()
    sections = content.split('---', 2)
    if len(sections) < 3:
        logger.error('invalid index.md format: YAML front matter is required')
        return

    yml_dict: dict = yaml.safe_load(sections[1])

    for group in yml_dict['data']['top']:
        merged_categories: dict[str, list[dict]] = {}
        ordered_keys: list[str] = []

        for category in group['categories']:
            source_name = category['name']
            if not source_name.endswith('/'):
                logger.error(
                    f"invalid category name: {source_name} (must end with /)")
                return
            key = _group_key(src, source_name)
            if key not in merged_categories:
                merged_categories[key] = []
                ordered_keys.append(key)

            for page in category['pages']:
                if f"{source_name}{page['filename']}" != page['path']:
                    logger.error(
                        f"broken YAML: name: {source_name}, filename: {page['filename']}, but path: {page['path']}")
                    return
                new_page = dict(page)
                new_page['filename'] = page['path'][len(key):]
                merged_categories[key].append(new_page)

        group['categories'] = [
            {'name': key, 'pages': merged_categories[key]} for key in ordered_keys]

    new_yml = yaml.safe_dump(yml_dict, sort_keys=False)
    with open(index_md, 'w', encoding='utf-8') as f:
        f.write(f"---\n{new_yml}---{sections[2]}")

    logger.info('finished')


def _register_patch_cpvdoc(cli):
    @cli.command('patch-cpvdoc')
    @click.option('-s', '--src', type=click.Path(exists=True, file_okay=False), help='Source directory', default='src')
    @click.option('-j', '--jekyll-src', type=click.Path(exists=True, file_okay=False), help='Source path to patch', default='_jekyll')
    def _patch_cpvdoc(src: str, jekyll_src: str):
        patch_cpvdoc(src, jekyll_src)
