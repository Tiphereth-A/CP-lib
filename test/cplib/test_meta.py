import os
from pathlib import Path
import textwrap
import pytest
import yaml
from unittest.mock import patch, MagicMock
from libs.meta.testcase_matrix import testcase_matrix
from libs.meta.cppmeta_parser import cppmeta_parser
from libs.conf.tcgen import ConfigTcgen

testcase_matrix.__test__ = False


# Shared test config used by cppmeta_parser tests
_REAL_CONFIG_PATH = Path(__file__).parent.parent / 'cpv_meta' / 'config.yml'
_REAL_CONFIG = ConfigTcgen(_REAL_CONFIG_PATH)

# ------------------------------------------------------------------ helpers --


def _simple_config(tmp_path):
    """Create a minimal ConfigTcgen from a temp file."""
    data = {
        'catA': {
            'priority': 0,
            'default_content': {
                'requirements': None,
                'include': ['src/catA/$m/lib.hpp'],
                'after_include': 'using catA = $m;\n',
                'main_begin': None,
            },
            'member': {
                'alpha': None,
                'beta': None,
            }
        },
        'catB': {
            'priority': 0,
            'default_content': {
                'requirements': None,
                'include': None,
                'after_include': 'using catB = $m;\n',
                'main_begin': None,
            },
            'member': {
                'x': None,
                'y': None,
            }
        },
    }
    cfg_path = tmp_path / 'tcgen.yml'
    with open(cfg_path, 'w') as f:
        yaml.dump(data, f, sort_keys=False)
    return ConfigTcgen(str(cfg_path))


def _single_config(tmp_path):
    data = {
        'catA': {
            'priority': 0,
            'default_content': {
                'requirements': None,
                'include': ['src/catA/$m/lib.hpp'],
                'after_include': 'using catA = $m;\n',
                'main_begin': 'catA::init();\n',
            },
            'member': {
                'alpha': None,
            }
        },
    }
    cfg_path = tmp_path / 'tcgen_single.yml'
    with open(cfg_path, 'w') as f:
        yaml.dump(data, f, sort_keys=False)
    return ConfigTcgen(str(cfg_path))


def _config_with_requirement(tmp_path, priority_a=0, priority_b=10):
    data = {
        'base': {
            'priority': priority_a,
            'default_content': {
                'requirements': None,
                'include': ['src/base/$m/lib.hpp'],
                'after_include': 'using base_t = $m;\n',
                'main_begin': None,
            },
            'member': {
                'v1': None,
                'v2': None,
            }
        },
        'derived': {
            'priority': priority_b,
            'default_content': {
                'requirements': [['base']],
                'include': ['src/derived/$m/lib.hpp'],
                'after_include': 'using derived_t = $m<base_t>;\n',
                'main_begin': None,
            },
            'member': {
                'd1': None,
            }
        },
    }
    cfg_path = tmp_path / 'tcgen_req.yml'
    with open(cfg_path, 'w') as f:
        yaml.dump(data, f, sort_keys=False)
    return ConfigTcgen(str(cfg_path))


# ------------------------------------------------------------ testcase_matrix --

@pytest.mark.unit
class TestTestcaseMatrix:
    def test_append_and_make_cases(self, tmp_path):
        cfg = _simple_config(tmp_path)
        mat = testcase_matrix(cfg)
        mat.append(['catA', 'catB'])
        cases = mat.get_all_cases()
        # catA x catB = 2 x 2 = 4
        assert len(cases) == 4

    def test_single_category(self, tmp_path):
        cfg = _single_config(tmp_path)
        mat = testcase_matrix(cfg)
        mat.append(['catA'])
        cases = mat.get_all_cases()
        assert len(cases) == 1

    def test_make_all_cases_idempotent(self, tmp_path):
        cfg = _simple_config(tmp_path)
        mat = testcase_matrix(cfg)
        mat.append(['catA'])
        cases1 = mat.get_all_cases()
        cases2 = mat.get_all_cases()
        assert len(cases1) == len(cases2)

    def test_exclude_removes_case(self, tmp_path):
        cfg = _simple_config(tmp_path)  # catA: alpha, beta
        mat = testcase_matrix(cfg)
        mat.append(['catA'])
        mat.make_all_cases()
        assert len(mat._all_cases) == 2
        mat.exclude([('catA', 'alpha')])
        # directly check _all_cases since get_all_cases() would rebuild when empty
        assert len(mat._all_cases) == 1

    def test_exclude_nonexistent_logs_warning(self, tmp_path, caplog):
        import logging
        cfg = _single_config(tmp_path)
        mat = testcase_matrix(cfg)
        mat.append(['catA'])
        mat.make_all_cases()
        with caplog.at_level(logging.WARNING):
            mat.exclude([('catA', 'nonexistent')])
        assert caplog.messages[-1] == "Case [('catA', 'nonexistent')] not found in test matrix"

    def test_exclude_wildcard(self, tmp_path):
        cfg = _simple_config(tmp_path)  # catA: alpha, beta
        mat = testcase_matrix(cfg)
        mat.append(['catA'])
        mat.make_all_cases()
        assert len(mat._all_cases) == 2
        # exclude only 'alpha' using wildcard
        mat.exclude_wildcard('catA-alpha')
        assert len(mat._all_cases) == 1

    def test_exclude_wildcard_no_match(self, tmp_path, caplog):
        cfg = _single_config(tmp_path)
        mat = testcase_matrix(cfg)
        mat.append(['catA'])
        mat.make_all_cases()
        before = len(mat.get_all_cases())
        mat.exclude_wildcard('zzz-*')
        assert len(mat.get_all_cases()) == before

    def test_case_label(self, tmp_path):
        cfg = _single_config(tmp_path)
        mat = testcase_matrix(cfg)
        mat.append(['catA'])
        cases = mat.get_all_cases()
        label = cases[0].get_label()
        assert label == 'catA-alpha'

    def test_case_include_list(self, tmp_path):
        cfg = _single_config(tmp_path)
        mat = testcase_matrix(cfg)
        mat.append(['catA'])
        cases = mat.get_all_cases()
        includes = cases[0].get_include_list()
        assert includes == ['src/catA/alpha/lib.hpp']

    def test_case_after_include(self, tmp_path):
        cfg = _single_config(tmp_path)
        mat = testcase_matrix(cfg)
        mat.append(['catA'])
        cases = mat.get_all_cases()
        after = cases[0].get_content_after_include()
        assert after == 'using catA = alpha;\n'

    def test_case_main_begin(self, tmp_path):
        cfg = _single_config(tmp_path)
        mat = testcase_matrix(cfg)
        mat.append(['catA'])
        cases = mat.get_all_cases()
        main = cases[0].get_content_main_begin()
        assert main == 'catA::init();\n'

    def test_with_requirements(self, tmp_path):
        cfg = _config_with_requirement(tmp_path)
        mat = testcase_matrix(cfg)
        mat.append(['derived'])
        cases = mat.get_all_cases()
        # derived has requirements on base (2 members), so 1 * 2 = 2 cases
        assert len(cases) == 2

    def test_case_parser_str(self, tmp_path):
        cfg = _single_config(tmp_path)
        mat = testcase_matrix(cfg)
        mat.append(['catA'])
        cases = mat.get_all_cases()
        s = str(cases[0])
        assert isinstance(s, str)

    def test_append_returns_self(self, tmp_path):
        cfg = _single_config(tmp_path)
        mat = testcase_matrix(cfg)
        result = mat.append(['catA'])
        assert result is mat

    def test_exclude_returns_self(self, tmp_path):
        cfg = _single_config(tmp_path)
        mat = testcase_matrix(cfg)
        mat.append(['catA'])
        mat.make_all_cases()
        result = mat.exclude([('catA', 'alpha')])
        assert result is mat

    def test_exclude_wildcard_returns_self(self, tmp_path):
        cfg = _single_config(tmp_path)
        mat = testcase_matrix(cfg)
        mat.append(['catA'])
        result = mat.exclude_wildcard('*')
        assert result is mat

    def test_format_specifier_mb_replacement(self, tmp_path):
        """Cover _apply_format_specifiers $mb0b replacement (line 53)."""
        data = {
            'base': {
                'priority': 0,
                'default_content': {
                    'requirements': None,
                    'include': ['src/base/$m/lib.hpp'],
                    'after_include': 'using base_t = $m;\n',
                    'main_begin': None,
                },
                'member': {'v1': None},
            },
            'derived': {
                'priority': 10,
                'default_content': {
                    'requirements': [['base']],
                    'include': ['src/derived/$m/lib.hpp'],
                    'after_include': 'using derived_t = derived<$mb0b>;\n',
                    'main_begin': None,
                },
                'member': {'d1': None},
            },
        }
        cfg_path = tmp_path / 'tcgen_mb.yml'
        with open(cfg_path, 'w') as f:
            yaml.dump(data, f, sort_keys=False)
        cfg = ConfigTcgen(str(cfg_path))
        mat = testcase_matrix(cfg)
        mat.append(['derived'])
        cases = mat.get_all_cases()
        assert len(cases) == 1
        after_include = cases[0].get_content_after_include()
        assert after_include == 'using base_t = v1;\nusing derived_t = derived<v1>;\n'

    def test_same_priority_dedup_in_content(self, tmp_path):
        """Cover _get_content_ignore 'continue' branch (line 63)."""
        data = {
            'catA': {
                'priority': 0,
                'default_content': {
                    'requirements': None,
                    'include': None,
                    'after_include': 'using typeA = $m;\n',
                    'main_begin': None,
                },
                'member': {'a': None, 'b': None},
            },
            'catB': {
                'priority': 0,
                'default_content': {
                    'requirements': None,
                    'include': None,
                    'after_include': 'using typeB = $m;\n',
                    'main_begin': None,
                },
                'member': {'x': None},
            },
        }
        cfg_path = tmp_path / 'tcgen_dedup.yml'
        with open(cfg_path, 'w') as f:
            yaml.dump(data, f, sort_keys=False)
        cfg = ConfigTcgen(str(cfg_path))
        mat = testcase_matrix(cfg)
        # Two separate appends — each becomes its own group, but both have priority 0
        # so get_categories_with_same_priority returns ['catA', 'catB'] for each.
        # When a case has catA then catB, second iteration hits 'continue' at line 63.
        mat.append(['catA'])
        mat.append(['catB'])
        cases = mat.get_all_cases()
        assert len(cases) > 0
        # get_content_after_include exercises _get_content_ignore which has dedup logic
        for case in cases:
            after = case.get_content_after_include()
            assert isinstance(after, str)

    def test_make_all_cases_raises_on_cyclic_requirements(self, tmp_path):
        """Cover testcase_matrix.py line 182: RuntimeError on max iteration exceeded."""
        data = {
            'cycleA': {
                'priority': 0,
                'default_content': {
                    'requirements': [['cycleB']],
                    'include': None,
                    'after_include': None,
                    'main_begin': None,
                },
                'member': {'a': None},
            },
            'cycleB': {
                'priority': 10,
                'default_content': {
                    'requirements': [['cycleA']],
                    'include': None,
                    'after_include': None,
                    'main_begin': None,
                },
                'member': {'b': None},
            },
        }
        cfg_path = tmp_path / 'tcgen_cyclic.yml'
        with open(cfg_path, 'w') as f:
            yaml.dump(data, f, sort_keys=False)
        cfg = ConfigTcgen(str(cfg_path))
        mat = testcase_matrix(cfg)
        mat.append(['cycleA'])
        with pytest.raises(RuntimeError, match='Max iteration limit exceeded'):
            mat.make_all_cases()


# ------------------------------------------------------------ cppmeta_parser --

@pytest.mark.unit
class TestCppmetaParser:
    """Test cppmeta_parser using small synthetic .cppmeta content."""

    def _make_parser(self, tmp_path, code, filename='test'):
        lines = [
            l + '\n' if not l.endswith('\n') else l for l in code.splitlines()]
        return cppmeta_parser(filename, 'target', lines, _REAL_CONFIG)

    def _simple_code(self, categories):
        """Generate minimal .cppmeta code."""
        append_lines = '\n'.join(
            f'// ---<GENTC>--- append {cat}' for cat in categories
        )
        return textwrap.dedent(f"""\
            #include <bits/stdc++.h>
            // ---<GENTC>--- begin
            {append_lines}
            // ---<GENTC>--- end
            int main() {{
            }}
        """)

    def test_get_results_returns_list(self, tmp_path):
        code = self._simple_code(['mints'])
        parser = self._make_parser(tmp_path, code)
        results = parser.get_results()
        assert isinstance(results, list)
        assert len(results) > 0

    def test_get_results_tuple_structure(self, tmp_path):
        code = self._simple_code(['mints'])
        parser = self._make_parser(tmp_path, code)
        results = parser.get_results()
        for filepath, content in results:
            assert isinstance(filepath, str)
            assert isinstance(content, list)

    def test_auto_generated_marker(self, tmp_path):
        code = self._simple_code(['mints'])
        parser = self._make_parser(tmp_path, code)
        for _fp, content in parser.get_results():
            assert content[0].strip() == '#define AUTO_GENERATED'

    def test_no_main_raises(self, tmp_path):
        code = textwrap.dedent("""\
            #include <bits/stdc++.h>
            // ---<GENTC>--- begin
            // ---<GENTC>--- append mints
            // ---<GENTC>--- end
        """)
        lines = code.splitlines(True)
        parser = cppmeta_parser('t', str(tmp_path), lines, _REAL_CONFIG)
        with pytest.raises(RuntimeError, match='main function not found'):
            parser.get_results()

    def test_no_gentc_block_raises(self, tmp_path):
        code = textwrap.dedent("""\
            #include <bits/stdc++.h>
            int main() {
            }
        """)
        lines = code.splitlines(True)
        parser = cppmeta_parser('t', str(tmp_path), lines, _REAL_CONFIG)
        with pytest.raises(RuntimeError, match='GENTC block not found'):
            parser.get_results()

    def test_begin_without_end_raises(self, tmp_path):
        code = textwrap.dedent("""\
            // ---<GENTC>--- begin
            // ---<GENTC>--- append mints
            int main() {
            }
        """)
        lines = code.splitlines(True)
        parser = cppmeta_parser('t', str(tmp_path), lines, _REAL_CONFIG)
        with pytest.raises(RuntimeError, match="unknown GENTC command"):
            parser.get_results()

    def test_end_without_begin_raises(self, tmp_path):
        code = textwrap.dedent("""\
            // ---<GENTC>--- end
            int main() {
            }
        """)
        lines = code.splitlines(True)
        parser = cppmeta_parser('t', str(tmp_path), lines, _REAL_CONFIG)
        with pytest.raises(RuntimeError, match='`GENTC end` mismatched'):
            parser.get_results()

    def test_nested_begin_raises(self, tmp_path):
        code = textwrap.dedent("""\
            // ---<GENTC>--- begin
            // ---<GENTC>--- begin
            // ---<GENTC>--- end
            int main() {
            }
        """)
        lines = code.splitlines(True)
        parser = cppmeta_parser('t', str(tmp_path), lines, _REAL_CONFIG)
        with pytest.raises(RuntimeError, match='cannot appear in a GENTC block'):
            parser.get_results()

    def test_exclude_before_append_raises(self, tmp_path):
        code = textwrap.dedent("""\
            // ---<GENTC>--- begin
            // ---<GENTC>--- exclude mints-ms
            // ---<GENTC>--- end
            int main() {
            }
        """)
        lines = code.splitlines(True)
        parser = cppmeta_parser('t', str(tmp_path), lines, _REAL_CONFIG)
        with pytest.raises(RuntimeError, match='`GENTC exclude` found before `GENTC append`'):
            parser.get_results()

    def test_unknown_command_raises(self, tmp_path):
        code = textwrap.dedent("""\
            // ---<GENTC>--- begin
            // ---<GENTC>--- unknown
            // ---<GENTC>--- end
            int main() {
            }
        """)
        lines = code.splitlines(True)
        parser = cppmeta_parser('t', str(tmp_path), lines, _REAL_CONFIG)
        with pytest.raises(RuntimeError, match="unknown GENTC command"):
            parser.get_results()

    def test_block_after_main_raises(self, tmp_path):
        code = textwrap.dedent("""\
            int main() {
            }
            // ---<GENTC>--- begin
            // ---<GENTC>--- append mints
            // ---<GENTC>--- end
        """)
        lines = code.splitlines(True)
        parser = cppmeta_parser('t', str(tmp_path), lines, _REAL_CONFIG)
        with pytest.raises(RuntimeError, match='GENTC block must be before main'):
            parser.get_results()

    def test_exclude_wildcard_via_cppmeta(self, tmp_path):
        code = textwrap.dedent("""\
            // ---<GENTC>--- begin
            // ---<GENTC>--- append mints
            // ---<GENTC>--- exclude mints-*
            // ---<GENTC>--- end
            int main() {
            }
        """)
        lines = code.splitlines(True)
        parser = cppmeta_parser('t', str(tmp_path), lines, _REAL_CONFIG)
        results = parser.get_results()
        assert results == []

    def test_exclude_specific_via_cppmeta(self, tmp_path):
        code = textwrap.dedent("""\
            // ---<GENTC>--- begin
            // ---<GENTC>--- append mints
            // ---<GENTC>--- exclude mints-nonexistent
            // ---<GENTC>--- end
            int main() {
            }
        """)
        lines = code.splitlines(True)
        parser = cppmeta_parser('t', 'target', lines, _REAL_CONFIG)
        # mints-nonexistent is not a valid case, so exclusion has no effect
        results = parser.get_results()
        assert isinstance(results, list)

    def test_append_after_exclude_raises(self, tmp_path):
        code = textwrap.dedent("""\
            // ---<GENTC>--- begin
            // ---<GENTC>--- append mints
            // ---<GENTC>--- exclude mints-ms
            // ---<GENTC>--- append mintd
            // ---<GENTC>--- end
            int main() {
            }
        """)
        lines = code.splitlines(True)
        parser = cppmeta_parser('t', str(tmp_path), lines, _REAL_CONFIG)
        with pytest.raises(RuntimeError, match='`GENTC append` found after `GENTC exclude`'):
            parser.get_results()

    def test_relative_include_path(self, monkeypatch, tmp_path):
        monkeypatch.chdir(tmp_path)
        os.makedirs('sub', exist_ok=True)
        code = self._simple_code(['mints'])
        lines = code.splitlines(True)
        parser = cppmeta_parser('t', 'sub', lines, _REAL_CONFIG)
        for _fp, content in parser.get_results():
            includes = [l for l in content if l.startswith('#include')]
            # includes should use relative paths with /
            for inc in includes:
                assert inc.count('\\') == 0

    def test_begin_no_end_no_unknown_raises(self, tmp_path):
        # Block starts but has no end — 'GENTC begin mismatched' (line 89)
        # main must exist so we pass the 'main function not found' check first
        code = textwrap.dedent("""\
            int main() {
            }
            // ---<GENTC>--- begin
            // ---<GENTC>--- append mints
        """)
        lines = code.splitlines(True)
        parser = cppmeta_parser('t', str(tmp_path), lines, _REAL_CONFIG)
        with pytest.raises(RuntimeError, match='`GENTC begin` mismatched'):
            parser.get_results()

    def test_main_begin_content_in_output(self, monkeypatch, tmp_path):
        # 'mintd' has a main_begin, so the code at lines 133-134 is exercised
        monkeypatch.chdir(tmp_path)
        code = self._simple_code(['mintd'])
        lines = code.splitlines(True)
        parser = cppmeta_parser('t', 'target', lines, _REAL_CONFIG)
        for _fp, content in parser.get_results():
            # main_begin code should appear indented
            main_begin_lines = [
                l for l in content if 'set_mod' in l or 'mint' in l.lower()]
            assert len(main_begin_lines) > 0
