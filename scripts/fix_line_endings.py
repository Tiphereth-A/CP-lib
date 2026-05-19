import sys
from pathlib import Path


def iter_targets(args: list[str]) -> list[Path]:
    targets = [Path(arg) for arg in args]

    expanded: list[Path] = []
    for item in targets:
        if isinstance(item, Path):
            if item.is_dir():
                expanded.extend(item.rglob('*') )
            else:
                expanded.append(item)
        else:
            expanded.extend(list(item))

    return [p for p in expanded if p.is_file()]


def normalize_line_endings(path: Path) -> bool:
    data = path.read_bytes()
    try:
        text = data.decode('utf-8')
    except UnicodeDecodeError:
        print(f"skip non-utf8: {path}", file=sys.stderr)
        return False

    normalized = text.replace('\r\n', '\n').replace('\r', '\n')
    if normalized == text:
        return False

    path.write_text(normalized, encoding='utf-8')
    return True


def main() -> int:
    targets = iter_targets(sys.argv[1:])
    if not targets:
        print('no files matched', file=sys.stderr)
        return 1

    changed = 0
    for path in targets:
        if normalize_line_endings(path):
            changed += 1
            print(f"fixed: {path}")

    print(f"updated {changed} file(s)")
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
