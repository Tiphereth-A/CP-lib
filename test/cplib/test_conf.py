import os
import pytest
import yaml
from unittest.mock import patch
from libs.conf.base import ConfigBase
from libs.conf.index import ConfigIndex
from libs.conf.tcgen import ConfigTcgen


# ---------------------------------------------------------------------------
# helpers
# ---------------------------------------------------------------------------

def write_yaml(path, data):
    with open(path, 'w', encoding='utf8') as f:
        yaml.dump(data, f, sort_keys=False, allow_unicode=True)


# ---------------------------------------------------------------------------
# ConfigBase
# ---------------------------------------------------------------------------

@pytest.mark.unit
class TestConfigBase:
    def test_load_success(self, tmp_path):
        cfg_path = tmp_path / 'cfg.yml'
        write_yaml(str(cfg_path), {'key': 'value'})

        class Concrete(ConfigBase):
            pass

        obj = Concrete(str(cfg_path))
        assert obj.items('key') == 'value'

    def test_file_not_accessible_raises(self, tmp_path):
        class Concrete(ConfigBase):
            pass

        with pytest.raises(PermissionError):
            Concrete(str(tmp_path / 'missing.yml'))

    def test_repr(self, tmp_path):
        cfg_path = tmp_path / 'cfg.yml'
        write_yaml(str(cfg_path), {'a': 1})

        class Concrete(ConfigBase):
            pass

        obj = Concrete(str(cfg_path))
        assert repr(
            obj) == f"Concrete(path={str(cfg_path)}, config={{'a': 1}})"

    def test_reload(self, tmp_path):
        cfg_path = tmp_path / 'cfg.yml'
        write_yaml(str(cfg_path), {'x': 1})

        class Concrete(ConfigBase):
            pass

        obj = Concrete(str(cfg_path))
        write_yaml(str(cfg_path), {'x': 2})
        obj.reload()
        assert obj.items('x') == 2

    def test_output_writes_file(self, tmp_path):
        cfg_path = tmp_path / 'cfg.yml'
        write_yaml(str(cfg_path), {'a': 1})

        class Concrete(ConfigBase):
            pass

        obj = Concrete(str(cfg_path))
        obj._config['a'] = 99
        obj.output()
        obj.reload()
        assert obj.items('a') == 99

    def test_output_readonly_raises(self, tmp_path):
        cfg_path = tmp_path / 'cfg.yml'
        write_yaml(str(cfg_path), {'a': 1})

        class Concrete(ConfigBase):
            pass

        obj = Concrete(str(cfg_path), readonly=True)
        with pytest.raises(AssertionError):
            obj.output()

    def test_output_not_writable_raises(self, tmp_path):
        import stat
        cfg_path = tmp_path / 'readonly_cfg.yml'
        write_yaml(str(cfg_path), {'a': 1})

        class Concrete(ConfigBase):
            pass

        obj = Concrete(str(cfg_path))
        # Make the file read-only
        cfg_path.chmod(stat.S_IREAD)
        try:
            with pytest.raises(PermissionError):
                obj.output()
        finally:
            cfg_path.chmod(stat.S_IWRITE | stat.S_IREAD)

    def test_items_nested(self, tmp_path):
        cfg_path = tmp_path / 'cfg.yml'
        write_yaml(str(cfg_path), {'outer': {'inner': 42}})

        class Concrete(ConfigBase):
            pass

        obj = Concrete(str(cfg_path))
        assert obj.items('outer', 'inner') == 42


# ---------------------------------------------------------------------------
# ConfigIndex
# ---------------------------------------------------------------------------

@pytest.mark.unit
class TestConfigIndex:
    def _make_index(self, tmp_path, data=None):
        if data is None:
            data = [{'gcd': 'GCD'}, {'lcm': 'LCM'}]
        path = tmp_path / 'index.yml'
        write_yaml(str(path), data)
        return ConfigIndex(str(path))

    def test_get_section_list(self, tmp_path):
        idx = self._make_index(tmp_path)
        sections = idx.get_section_list()
        assert sections == [('gcd', 'GCD'), ('lcm', 'LCM')]

    def test_get_section_name(self, tmp_path):
        idx = self._make_index(tmp_path)
        names = idx.get_section_name()
        assert names == {'gcd', 'lcm'}

    def test_empty_config(self, tmp_path):
        path = tmp_path / 'index.yml'
        write_yaml(str(path), None)
        idx = ConfigIndex(str(path))
        assert idx.get_section_list() == []
        assert idx.get_section_name() == set()

    def test_new_section_creates_dir(self, tmp_path):
        path = tmp_path / 'index.yml'
        write_yaml(str(path), [])
        idx = ConfigIndex(str(path))
        result = idx.new_section('newsect', 'New Section')
        assert result is True
        assert (tmp_path / 'newsect').is_dir()
        assert idx.get_section_name() == {'newsect'}

    def test_new_section_duplicate_skipped(self, tmp_path):
        idx = self._make_index(tmp_path)
        result = idx.new_section('gcd', 'GCD again')
        assert result is False

    def test_new_section_persists(self, tmp_path):
        path = tmp_path / 'index.yml'
        write_yaml(str(path), [])
        idx = ConfigIndex(str(path))
        idx.new_section('alpha', 'Alpha')
        idx.reload()
        assert idx.get_section_name() == {'alpha'}


# ---------------------------------------------------------------------------
# ConfigTcgen  (reads real tcgen.yml from workspace)
# ---------------------------------------------------------------------------

@pytest.mark.unit
class TestConfigTcgen:
    @pytest.fixture(autouse=True)
    def load_config(self):
        self.cfg = ConfigTcgen('tcgen.yml')

    def test_get_categories_not_empty(self):
        cats = list(self.cfg.get_categories())
        assert len(cats) > 0

    def test_get_priority_returns_int(self):
        cats = list(self.cfg.get_categories())
        p = self.cfg.get_priority(cats[0])
        assert isinstance(p, int)

    def test_get_categories_by_priority(self):
        cats = list(self.cfg.get_categories())
        p = self.cfg.get_priority(cats[0])
        result = self.cfg.get_categories_by_priority(p)
        assert [c for c in result if c == cats[0]] == [cats[0]]

    def test_get_categories_with_same_priority(self):
        cats = list(self.cfg.get_categories())
        # should at minimum return the category itself
        result = self.cfg.get_categories_with_same_priority(cats[0])
        assert [c for c in result if c == cats[0]] == [cats[0]]

    def test_get_memberlist_str(self):
        # 'mints' is a known category in tcgen.yml
        members = self.cfg.get_memberlist('mints')
        assert len(members) > 0
        for cat, mem in members:
            assert cat == 'mints'

    def test_get_memberlist_list_same_priority(self):
        # mints and mintd share priority 0
        members = self.cfg.get_memberlist(['mints', 'mintd'])
        assert len(members) > 0

    def test_get_member_content_str(self):
        content = self.cfg.get_member_content('mints', 'ms')
        assert content['category_name'] == 'mints'
        assert content['member_name'] == 'ms'

    def test_get_member_content_list(self):
        content = self.cfg.get_member_content('mints', 'ms')
        assert content is not None

    def test_readonly_output_raises(self):
        with pytest.raises(AssertionError):
            self.cfg.output()

    def test_get_member_content_invalid_member_raises(self):
        with pytest.raises((KeyError, RuntimeError)):
            self.cfg.get_member_content('mints', 'nonexistent_member')

    def test_get_memberlist_list_different_priority_raises(self):
        cats = list(self.cfg.get_categories())
        # Find two categories with different priorities
        priorities = {}
        for cat in cats:
            p = self.cfg.get_priority(cat)
            priorities.setdefault(p, []).append(cat)
        groups = [v for v in priorities.values() if len(v) >= 1]
        if len(groups) < 2:
            pytest.skip("Not enough different-priority categories")
        cat_a = groups[0][0]
        cat_b = groups[1][0]
        if self.cfg.get_priority(cat_a) != self.cfg.get_priority(cat_b):
            with pytest.raises(RuntimeError):
                self.cfg.get_memberlist([cat_a, cat_b])

    def test_get_member_content_list_fallback(self):
        # get_member_content with str, invalid member raises KeyError
        with pytest.raises((KeyError, RuntimeError)):
            self.cfg.get_member_content('mints', '__totally_invalid__')

    def test_get_member_content_list_dispatch_success(self, tmp_path):
        data = {
            'catA': {
                'priority': 0,
                'default_content': {
                    'requirements': None,
                    'include': None,
                    'after_include': 'using catA = $m;\n',
                    'main_begin': None,
                },
                'member': {'alpha': None, 'beta': None},
            },
            'catB': {
                'priority': 0,
                'default_content': {
                    'requirements': None,
                    'include': None,
                    'after_include': 'using catB = $m;\n',
                    'main_begin': None,
                },
                'member': {'x': None},
            },
        }
        cfg_path = tmp_path / 'tcgen_list.yml'
        write_yaml(str(cfg_path), data)
        cfg = ConfigTcgen(str(cfg_path))
        # list dispatch - member 'alpha' found in catA
        content = cfg.get_member_content(['catA', 'catB'], 'alpha')
        assert content['category_name'] == 'catA'
        assert content['member_name'] == 'alpha'

    def test_get_member_content_list_dispatch_fallback(self, tmp_path):
        data = {
            'catA': {
                'priority': 0,
                'default_content': {
                    'requirements': None,
                    'include': None,
                    'after_include': 'using catA = $m;\n',
                    'main_begin': None,
                },
                'member': {'alpha': None},
            },
        }
        cfg_path = tmp_path / 'tcgen_list_fb.yml'
        write_yaml(str(cfg_path), data)
        cfg = ConfigTcgen(str(cfg_path))
        with pytest.raises(RuntimeError, match='invalid in categories'):
            cfg.get_member_content(['catA'], 'zzz')

    def test_get_memberlist_empty_list(self, tmp_path):
        data = {'catA': {'priority': 0,
                         'default_content': None, 'member': {'a': None}}}
        cfg_path = tmp_path / 'tcgen_empty.yml'
        write_yaml(str(cfg_path), data)
        cfg = ConfigTcgen(str(cfg_path))
        # empty list should return [] without error
        result = cfg.get_memberlist([])
        assert result == []

    def test_get_member_content_null_default(self, tmp_path):
        data = {
            'catA': {
                'priority': 0,
                'default_content': None,
                'member': {
                    'alpha': {
                        'requirements': None,
                        'include': ['src/catA/alpha/lib.hpp'],
                        'after_include': 'using catA = alpha;\n',
                        'main_begin': None,
                    },
                    'ghost': None,  # both default and member are None → RuntimeError
                },
            }
        }
        cfg_path = tmp_path / 'tcgen_null.yml'
        write_yaml(str(cfg_path), data)
        cfg = ConfigTcgen(str(cfg_path))
        # alpha: default_content is None, member_content is not None → covers line 49
        content = cfg.get_member_content('catA', 'alpha')
        assert content['category_name'] == 'catA'
        # ghost: both None → covers line 51
        with pytest.raises(RuntimeError, match='is invalid'):
            cfg.get_member_content('catA', 'ghost')
