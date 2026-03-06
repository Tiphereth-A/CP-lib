def trailing_str(s: str, start: int = 100, end: int = 100):
    if len(s) > start+end+5:
        return f"{s[:start]} ... {s[-end:]}"
    return s
