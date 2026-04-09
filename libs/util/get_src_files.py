import os


def get_src_files(src_path: str) -> list[str]:
    from libs.conf import ConfigIndex

    files: list[str] = []
    for root, _, dir_files in os.walk(src_path):
        if 'index.yml' not in dir_files:
            continue
        config = ConfigIndex(os.path.join(root, 'index.yml'))
        for name in config.get_section_name():
            subdir = os.path.join(root, name)
            if not os.path.isdir(subdir):
                continue
            if 'index.yml' not in os.listdir(subdir):
                for filename in os.listdir(subdir):
                    filepath = os.path.join(subdir, filename)
                    if os.path.isfile(filepath):
                        files.append(filepath)
    return files
