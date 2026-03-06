import os
from typing import Iterable


def get_files_with_exts(directories: Iterable[str], extnames: Iterable[str]) -> list[str]:
    files: list[str] = []
    for directory in directories:
        if not os.path.exists(directory):
            continue
        for filepath, _, filenames in os.walk(directory):
            for filename in filenames:
                if any(os.path.splitext(filename)[1] == ext for ext in extnames):
                    files.append(os.path.join(filepath, filename))
    return files
