import os
from typing import Iterable

SRC_PATH = 'src'
TEST_PATH = 'test'
TEMP_PATH = '.cp-lib'

THREAD_LIMIT = 32
EXT_TYPE_MP: dict[str, str] = {
    '.md': 'markdown',
    '.tex': 'tex',
    '.typ': 'typst',
    '.hpp': 'cpp',
    '.cpp': 'cpp',
    '.py': 'py'
}
TYPE_EXT_MP: dict[str, list[str]] = {}
for _ext, _type in EXT_TYPE_MP.items():
    TYPE_EXT_MP.setdefault(_type, []).append(_ext)


def trailing_str(s: str):
    _START, _END = 100, 100
    if len(s) > _START+_END+5:
        return f"{s[:_START]} ... {s[-_END:]}"
    return s


def get_full_filenames(directories: Iterable[str], valid_extnames: Iterable[str]) -> list[str]:
    """Get all files with valid extensions from given directories."""
    files: list[str] = []
    for directory in directories:
        if not os.path.exists(directory):
            continue
        for filepath, _, filenames in os.walk(directory):
            for filename in filenames:
                if any(filename.endswith(ext) for ext in valid_extnames):
                    files.append(os.path.join(filepath, filename))
    return files
