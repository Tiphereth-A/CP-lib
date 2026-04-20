import os

import yaml


def write_yaml(path, data):
    with open(path, 'w', encoding='utf8') as f:
        yaml.dump(data, f, sort_keys=False)


def make_src_tree(base_dir):
    """Create src/ relative to base_dir. Caller must chdir to base_dir."""
    src = os.path.join(base_dir, 'src')
    math_dir = os.path.join(src, 'math')
    gcd_dir = os.path.join(math_dir, 'gcd')
    os.makedirs(gcd_dir, exist_ok=True)
    write_yaml(os.path.join(src, 'index.yml'), [{'math': 'Math'}])
    write_yaml(os.path.join(math_dir, 'index.yml'), [{'gcd': 'GCD'}])
    with open(os.path.join(gcd_dir, 'lib.hpp'), 'w') as f:
        f.write('#pragma once\n')
    with open(os.path.join(gcd_dir, 'doc.tex'), 'w') as f:
        f.write('% {lib.hpp}\n')
    return 'src'
