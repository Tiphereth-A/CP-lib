import os
import pytest
import yaml
from libs.content.tree import ContentTree
from libs.conf.index import ConfigIndex


def write_yaml(path, data):
    with open(path, 'w', encoding='utf8') as f:
        yaml.dump(data, f, sort_keys=False)


def make_src_tree(base_dir):
    """Create src/ tree under base_dir. Returns relative path 'src'.
    Caller must have cwd = base_dir.
    """
    src = os.path.join(base_dir, 'src')
    math_dir = os.path.join(src, 'math')
    gcd_dir = os.path.join(math_dir, 'gcd')
    os.makedirs(gcd_dir, exist_ok=True)
    write_yaml(os.path.join(src, 'index.yml'), [{'math': 'Math'}])
    write_yaml(os.path.join(math_dir, 'index.yml'), [{'gcd': 'GCD'}])
    with open(os.path.join(gcd_dir, 'lib.hpp'), 'w') as f:
        f.write('#pragma once\n')
    return 'src'


@pytest.mark.unit
class TestContentTreeNode:
    def test_fullname_root(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        assert tree.root.fullname() == 'src'

    def test_fullname_child(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        assert list(tree.root._children) == ['math']

    def test_repr_node(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        r = repr(tree.root)
        assert r == "ContentTree.Node(name=src, title=src, father=None, children=['math'])"

    def test_load_config_on_non_leaf(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        math_node = tree.root._children['math']
        config = math_node.get_config()
        assert isinstance(config, ConfigIndex)

    def test_get_section_on_leaf(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        gcd_node = tree.root._children['math']._children['gcd']
        from libs.content.section import Section
        section = gcd_node.get_section()
        assert isinstance(section, Section)

    def test_load_config_on_leaf_raises(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        gcd_node = tree.root._children['math']._children['gcd']
        with pytest.raises(RuntimeError):
            gcd_node._load_config()

    def test_load_section_on_non_leaf_raises(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        math_node = tree.root._children['math']
        with pytest.raises(RuntimeError):
            math_node._load_section()


@pytest.mark.unit
class TestContentTree:
    def test_construction_from_src(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        assert list(tree.root._children) == ['math']
        assert list(tree.root._children['math']._children) == ['gcd']

    def test_touch_creates_node(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        os.makedirs(os.path.join(str(tmp_path), 'src',
                    'math', 'lcm'), exist_ok=True)
        node = tree.touch('math.lcm', 'LCM')
        assert set(tree.root._children['math']._children) == {'gcd', 'lcm'}
        assert node._title == 'LCM'

    def test_touch_default_title(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        os.makedirs(os.path.join(str(tmp_path), 'src',
                    'math', 'lcm2'), exist_ok=True)
        node = tree.touch('math.lcm2')
        assert node._title == 'lcm2'

    def test_touch_existing_node_returns_same(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        n1 = tree.touch('math.gcd', 'GCD')
        n2 = tree.touch('math.gcd', 'GCD')
        assert n1 is n2

    def test_node_add_child_idempotent(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        math_node = tree.root._children['math']
        c1 = math_node._add_child('newchild')
        c2 = math_node._add_child('newchild')
        assert c1 is c2

    def test_config_written_when_new_section_added(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        os.makedirs(os.path.join(str(tmp_path), 'src',
                    'math', 'mod'), exist_ok=True)
        node = tree.touch('math.mod', 'Modular')
        config = tree.root._children['math'].get_config()
        assert config.get_section_name() == {'gcd', 'mod'}

    def test_empty_src_tree(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        empty = os.path.join(str(tmp_path), 'empty_src')
        os.makedirs(empty)
        tree = ContentTree('empty_src')
        assert tree.root._children == {}

    def test_load_config_creates_index_when_missing(self, tmp_path, monkeypatch):
        # Covers lines 39-40: _load_config when index.yml doesn't exist
        monkeypatch.chdir(tmp_path)
        src = os.path.join(str(tmp_path), 'src')
        math_dir = os.path.join(src, 'math')
        os.makedirs(math_dir, exist_ok=True)
        # Create src/index.yml only, NOT math/index.yml
        with open(os.path.join(src, 'index.yml'), 'w') as f:
            import yaml
            yaml.dump([{'math': 'Math'}], f)
        tree = ContentTree('src')
        # Touch a node under math — this triggers _load_config for math without existing index.yml
        os.makedirs(os.path.join(str(tmp_path), 'src',
                    'math', 'gcd'), exist_ok=True)
        node = tree.touch('math.gcd', 'GCD')
        # The math node config should now exist
        assert os.path.exists(os.path.join('src', 'math', 'index.yml'))

    def test_get_section_via_get_section_method(self, tmp_path, monkeypatch):
        # Covers line 71: get_section() when _section is None (reset)
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        gcd_node = tree.root._children['math']._children['gcd']
        # Reset section to None to force lazy load via get_section()
        gcd_node._section = None
        from libs.content.section import Section
        section = gcd_node.get_section()
        assert isinstance(section, Section)

    def test_load_config_outputs_existing_config(self, tmp_path, monkeypatch):
        # Covers line 35: _load_config when _config is not None (re-load)
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        math_node = tree.root._children['math']
        # Load config first
        config = math_node.get_config()
        # Add a new child to trigger re-output on next _load_config
        os.makedirs(os.path.join(str(tmp_path), 'src',
                    'math', 'lcm'), exist_ok=True)
        math_node._add_child('lcm')
        # Call _load_config again when _config is already set (covers line 35)
        math_node._load_config()
        # Should still have a valid config
        assert math_node._config is not None
