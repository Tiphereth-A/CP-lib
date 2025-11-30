import logging
import os
from typing import Iterable, Any

from libs.decorator import withlog


def get_full_filenames(_dirs: list[str], valid_extname: list[str]) -> list[str]:
    """Get all files with valid extensions from given directories."""
    files: list[str] = []
    valid_extname_set = set(valid_extname)
    for _dir in _dirs:
        if not os.path.exists(_dir):
            continue
        for filepath, _, filenames in os.walk(_dir):
            for filename in filenames:
                # Check if filename ends with any valid extension
                if any(filename.endswith(ext) for ext in valid_extname_set):
                    files.append(os.path.join(filepath, filename))
    return files


def unique(seq: list, hash_func=lambda x: x) -> list:
    """Remove duplicates from sequence while preserving order."""
    seen: set = set()
    result: list[Any] = []
    for item in seq:
        marker = hash_func(item)
        if marker not in seen:
            seen.add(marker)
            result.append(item)
    return result


def get_difference(total_elements: set, seq: list) -> dict[int, Any]:
    """Get items from seq that are not in total_elements, indexed by position."""
    return {
        index: item
        for index, item in enumerate(seq)
        if item not in total_elements
    }


def file_preprocess(files_in_config: list[str], files_exist: list[str], logger: logging.Logger) -> list[str]:
    """
    Merge files_in_config and files_exist, removing duplicates.
    Items in files_in_config but not in files_exist will be removed from results.
    """
    files_exist_set = set(files_exist)
    not_exist_config: dict[int, str] = get_difference(
        files_exist_set, files_in_config)

    if not_exist_config:
        logger.warning(
            f"{len(not_exist_config)} config(s) are not exist:\n\t" +
            '\n\t'.join(f'{i}: {v}' for i, v in not_exist_config.items())
        )
        # Remove files that don't exist
        not_exist_indices = set(not_exist_config.keys())
        file_c = [f for i, f in enumerate(
            files_in_config) if i not in not_exist_indices]
    else:
        file_c = files_in_config.copy()

    return unique(file_c + files_exist)


@withlog
def execute_if_file_exist(filepath: str, func, **kwargs):
    if os.access(filepath, os.F_OK):
        return func(filepath)
    else:
        kwargs.get('logger').warning(f"{filepath} is inaccessible, skipped")


@withlog
def scandir_merge_filter(filter_func, *paths: str, **kwargs) -> list[str]:
    """Scan directories and filter entries, returning unique names."""
    result: list[os.DirEntry] = []
    for path in paths:
        _scandir = execute_if_file_exist(path, os.scandir)
        if _scandir:
            result.extend(filter(filter_func, _scandir))
    return unique([f.name for f in result])


@withlog
def scandir_file_merge(valid_ext_name: Iterable[str], *paths: str, **kwargs) -> list[str]:
    """Scan directories and merge file names with valid extensions."""
    valid_ext_set = set(valid_ext_name)

    def is_valid_file(entry: os.DirEntry) -> bool:
        if not entry.is_file():
            return False
        _, _, ext = entry.name.partition('.')
        return ext in valid_ext_set

    return scandir_merge_filter(is_valid_file, *paths)


@withlog
def scandir_dir_merge(*paths: str, **kwargs) -> list[str]:
    return scandir_merge_filter(lambda x: x.is_dir(), *paths)


@withlog
def parse_filename(filename: str, **kwargs) -> tuple[str, str]:
    """return [filename without ext, ext name]"""

    _ = filename.partition('.')
    return _[0], _[-1]
