import yaml
from pathlib import Path

from libs.classes.config_tcgen import ConfigTCGen


def make_tcgen_yaml(tmp_path: Path):
    data = {
        'cat1': {
            'priority': 1,
            'member': {
                'm1': {},
                'm2': {}
            },
            'default_content': {
                'after_include': '// after default\n'
            }
        },
        'cat2': {
            'priority': 1,
            'member': {
                'm3': {}
            },
            'default_content': {
                'after_include': '// after default2\n'
            }
        },
        'cat3': {
            'priority': 2,
            'member': {
                'm4': {}
            }
        }
    }
    p = tmp_path / 'tcgen.yml'
    p.write_text(yaml.dump(data), encoding='utf8')
    return str(p)


def test_config_tcgen_basic(tmp_path):
    p = make_tcgen_yaml(tmp_path)
    c = ConfigTCGen(p)
    cats = c.get_categories()
    assert 'cat1' in cats
    # memberlist for str
    ml = c.get_memberlist('cat1')
    assert any(isinstance(x, tuple) for x in ml)
    # memberlist for list
    ml2 = c.get_memberlist(['cat1', 'cat2'])
    assert len(ml2) >= len(ml)

    # get member content
    content = c.get_member_content('cat1', 'm1')
    assert 'category_name' in content and 'member_name' in content

    # list-category member content resolution
    content2 = c.get_member_content(['cat1', 'cat2'], 'm3')
    assert isinstance(content2, dict)

    # categories with same priority
    same = c.get_categories_with_same_priority('cat1')
    assert 'cat2' in same

    # check that differing priorities raise in check
    try:
        c.get_memberlist(['cat1', 'cat3'])
        assert False, 'should have raised RuntimeError for differing priorities'
    except RuntimeError:
        pass
