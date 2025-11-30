import itertools
import pytest
from pathlib import Path
from libs import testcase_matrix as tm


class FakeTCGen:
    def __init__(self):
        self._members = {
            'A': ['a1', 'a2'],
            'B': ['b1']
        }

    def get_priority(self, cat):
        return 0

    def get_memberlist(self, cat):
        # support both str and list inputs like the real ConfigTCGen
        if isinstance(cat, list):
            result = []
            for c in cat:
                result.extend(self.get_memberlist(c))
            return result
        return [(cat, m) for m in self._members.get(cat, [])]

    def get_member_content(self, cat, mem):
        return {
            'category_name': cat,
            'member_name': mem,
            'include': [f"inc_{mem}.h"] if mem.endswith('1') else [],
            'after_include': f"//after_{mem}\n" if mem.endswith('1') else '',
            'main_begin': f"//main_{mem}\n" if mem.endswith('1') else '',
            'requirements': []
        }

    def get_categories(self):
        return list(self._members.keys())

    def get_categories_with_same_priority(self, cat):
        return [cat]


def test_case_parser_and_matrix(monkeypatch):
    fake = FakeTCGen()
    monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

    m = tm.testcase_matrix()
    m.append(['A', 'B'])
    m.make_all_cases()
    all_cases = m.get_all_cases()
    assert all(isinstance(c, tm.case_parser) for c in all_cases)

    # test exclude by exact case
    if all_cases:
        case0 = all_cases[0]._case_list
        m.exclude(case0)
        # excluded: ensure that the case is not present anymore
        tags = [c._case_list for c in m.get_all_cases()]
        assert tuple(case0) not in [tuple(x) for x in tags]

    # test exclude_wildcard
    m = tm.testcase_matrix()
    monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)
    m.append(['A', 'B'])
    m.make_all_cases()
    before = len(m.get_all_cases())
    m.exclude_wildcard('A-*')
    after = len(m.get_all_cases())
    assert after <= before


def test_cppmeta_parser_basic(monkeypatch, tmp_path):
    fake = FakeTCGen()
    monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

    # create a cppmeta-like code
    lines = [
        '// header\n',
        tm._GENTC_BEGIN,
        tm._GENTC_COMMAND_APPEND + ' A B\n',
        tm._GENTC_END,
        tm._GENTC_MAIN,
        '// after main\n'
    ]

    cpp = tm.cppmeta_parser('f', str(tmp_path), lines)
    results = cpp.get_results()
    assert isinstance(results, list)
    # each result is (target_path, code_lines)
    assert all(isinstance(fp, str) and isinstance(cl, list)
               for fp, cl in results)


class FakeReqTCGen:
    def __init__(self):
        self._members = {
            'A': ['a1', 'a2'],
            'B': ['b1', 'b2']
        }

    def get_priority(self, cat):
        return 0

    def get_memberlist(self, cat):
        if isinstance(cat, list):
            result = []
            for c in cat:
                result.extend(self.get_memberlist(c))
            return result
        return [(cat, m) for m in self._members.get(cat, [])]

    def get_member_content(self, cat, mem):
        # make a1 require B so expansion happens
        if mem == 'a1':
            return {'category_name': cat, 'member_name': mem, 'requirements': [['B']], 'include': ['inc_$m.h'], 'after_include': '', 'main_begin': ''}
        return {'category_name': cat, 'member_name': mem, 'requirements': [], 'include': [], 'after_include': '', 'main_begin': ''}

    def get_categories(self):
        return list(self._members.keys())

    def get_categories_with_same_priority(self, cat):
        return [cat]


def test_apply_format_and_include_and_expansion(monkeypatch):
    fake = FakeReqTCGen()
    monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)
    # create a case parser directly
    case = tm.case_parser([('A', 'a1'), ('B', 'b1')])
    # apply format specifiers
    out = case._apply_format_specifiers('file_$m_$mb0b', 'a1', ['b1'])
    assert 'a1' in out and 'b1' in out

    # content ignore and include list
    lst = case.get_include_list()
    assert isinstance(lst, list)

    # matrix expansion
    m = tm.testcase_matrix()
    m.append(['A', 'B'])
    m.make_all_cases()
    all_cases = m.get_all_cases()
    assert len(all_cases) >= 1


def test_cppmeta_parser_main_begin_indentation(monkeypatch, tmp_path):
    # create fake CONFIG_TCGEN that returns a case with main_begin lines
    class FakeMainTCGen:
        def get_priority(self, cat):
            return 0

        def get_memberlist(self, cat):
            return [(cat, 'm1')]

        def get_member_content(self, cat, mem):
            return {
                'category_name': str(cat),
                'member_name': mem,
                'include': [str(tmp_path / 'inc.h')],
                'after_include': '// after\n',
                'main_begin': 'Xline\n  Yline\n',
                'requirements': []
            }

        def get_categories(self):
            return ['A']

        def get_categories_with_same_priority(self, cat):
            return [cat]

    monkeypatch.setattr(tm, 'CONFIG_TCGEN', FakeMainTCGen())
    lines = ['// hdr\n', tm._GENTC_BEGIN, tm._GENTC_COMMAND_APPEND +
             ' A\n', tm._GENTC_END, tm._GENTC_MAIN, '// tail\n']
    cpp = tm.cppmeta_parser('f', str(tmp_path), lines)
    results = cpp.get_results()
    assert results
    _, content = results[0]
    # ensure main_begin lines were prefixed with two spaces
    assert any(line.startswith('  Xline') for line in content)


def test_cppmeta_parser_errors_and_parsing(monkeypatch, tmp_path):
    fake = FakeReqTCGen()
    monkeypatch.setattr(tm, 'CONFIG_TCGEN', fake)

    # missing main raises
    lines1 = ['// header\n', tm._GENTC_BEGIN, tm._GENTC_END]
    cpp = tm.cppmeta_parser('f', str(tmp_path), lines1)
    with pytest.raises(RuntimeError):
        cpp.get_results()

    # exclude before append should raise
    lines2 = [tm._GENTC_BEGIN, tm._GENTC_COMMAND_EXCLIDE +
              ' A-B1\n', tm._GENTC_END, tm._GENTC_MAIN]
    cpp2 = tm.cppmeta_parser('g', str(tmp_path), lines2)
    with pytest.raises(RuntimeError):
        cpp2.get_results()


def test_gentc_duplicate_begin_raises():
    lines = [tm._GENTC_BEGIN, tm._GENTC_BEGIN, tm._GENTC_END, tm._GENTC_MAIN]
    p = tm.cppmeta_parser('f', '.', lines)
    with pytest.raises(RuntimeError):
        p.get_results()


def test_gentc_end_without_begin_raises():
    lines = [tm._GENTC_END, tm._GENTC_BEGIN, tm._GENTC_END, tm._GENTC_MAIN]
    p = tm.cppmeta_parser('f', '.', lines)
    with pytest.raises(RuntimeError):
        p.get_results()


def test_gentc_block_after_main_raises():
    lines = [tm._GENTC_MAIN, tm._GENTC_BEGIN, tm._GENTC_END]
    p = tm.cppmeta_parser('f', '.', lines)
    with pytest.raises(RuntimeError):
        p.get_results()


def test_gentc_append_after_exclude_error():
    # construct block where append after exclude occurs
    lines = [tm._GENTC_BEGIN, tm._GENTC_COMMAND_EXCLIDE + ' A-B\n',
             tm._GENTC_COMMAND_APPEND + ' A B\n', tm._GENTC_END, tm._GENTC_MAIN]
    p = tm.cppmeta_parser('f', '.', lines)
    with pytest.raises(RuntimeError):
        p.get_results()
