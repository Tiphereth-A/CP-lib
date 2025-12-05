from pathlib import Path

from libs.testcase_matrix import cppmeta_parser


class FakeCase:
    def __init__(self):
        pass

    def get_label(self):
        return 'cat-mem'

    def get_include_list(self):
        return [str(Path('inc') / 'file.h')]

    def get_content_after_include(self):
        return '// after\nline2\n'

    def get_content_main_begin(self):
        return 'first\n  second\n'


def test_get_all_target_content_various(tmp_path, monkeypatch):
    # prepare a cppmeta parser with fake code lines
    lines = [
        '// header\n',
        '// ---<GENTC>--- begin\n',
        '// ---<GENTC>--- append A B\n',
        '// ---<GENTC>--- end\n',
        'int main() {\n',
        '// after main\n'
    ]

    p = cppmeta_parser('f', str(tmp_path), lines)

    # monkeypatch internal _get_all_cases to return a single fake case
    def fake_get_all_cases():
        # block_begin = 1 (index of GENTC begin), block_end = 4 (index+1 of end), main_index=4
        return 1, 4, 4, [FakeCase()]

    monkeypatch.setattr(p, '_get_all_cases', fake_get_all_cases)

    results = p._get_all_target_content()
    assert results
    target_path, code_lines = results[0]
    # include line should be present
    assert any('#include' in s for s in code_lines if isinstance(s, str))
    # after_include block was added as lines
    assert any('after' in s for s in code_lines if isinstance(s, str))
    # main_begin lines should be indented at least once
    assert any(isinstance(s, str) and s.startswith('  first')
               for s in code_lines)
    # target path should include filename noext and label
    assert 'cat-mem' in target_path
