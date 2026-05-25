from pathlib import Path


def get_src_files(src_path: str | Path) -> list[str]:
    from libs.conf import ConfigIndex

    files: list[str] = []
    src_root = Path(src_path)
    for index_path in src_root.rglob('index.yml'):
        root_path = index_path.parent
        config = ConfigIndex(index_path)
        for name in config.get_section_name():
            subdir = root_path / name
            if not subdir.is_dir():
                continue
            if not (subdir / 'index.yml').exists():
                for filepath in subdir.iterdir():
                    if filepath.is_file():
                        files.append(str(filepath))
    return files
