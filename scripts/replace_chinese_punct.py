#!/usr/bin/env python3
from __future__ import annotations

import pathlib
import sys

REPLACEMENTS = [
    ('……', '...'),
    ('…', '...'),
    ('——', '---'),
    ('—', '--'),
    ('，', ', '),
    ('。', '. '),
    ('、', ', '),
    ('・', '.'),
    ('·', '.'),
    ('；', '; '),
    ('：', ': '),
    ('？', '? '),
    ('！', '! '),
    ('〜', '~'),
    ('～', '~'),
    ('（', ' ('),
    ('）', ') '),
    ('【', ' ['),
    ('】', '] '),
    ('「', ' "'),
    ('」', '" '),
    ('『', ' \''),
    ('』', '\' '),
    ('《', ' <'),
    ('》', '> '),
    ('“', ' "'),
    ('”', '" '),
    ('‘', ' \''),
    ('’', '\' '),
]


def replace_text(text: str) -> str:
    for src, dst in REPLACEMENTS:
        text = text.replace(src, dst)
    return text


def process_file(path: pathlib.Path) -> bool:
    try:
        original = path.read_bytes().decode('utf-8')
    except OSError | UnicodeDecodeError:
        return False

    updated = replace_text(original)
    if updated == original:
        return False

    with path.open('w', encoding='utf-8', newline='') as handle:
        handle.write(updated)

    return True


def main(argv: list[str]) -> int:
    if not argv:
        return 0

    changed = False
    for name in argv:
        path = pathlib.Path(name)
        if path.exists() and path.is_file():
            changed |= process_file(path)

    if changed:
        print('Replaced Chinese punctuation. Please re-stage files.', file=sys.stderr)
        return 1

    return 0


if __name__ == '__main__':
    raise SystemExit(main(sys.argv[1:]))
