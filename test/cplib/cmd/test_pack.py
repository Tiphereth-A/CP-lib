import os

import pytest

from libs.cmd.pack import packing_codes

from .helpers import write_yaml


@pytest.mark.unit
class TestPackCommands:
    def _make_pack_src(self, base_dir):
        src = os.path.join(base_dir, 'src')
        cat = os.path.join(src, 'math')
        sect = os.path.join(cat, 'gcd')
        os.makedirs(sect, exist_ok=True)
        write_yaml(os.path.join(src, 'index.yml'), [{'math': 'Math'}])
        write_yaml(os.path.join(cat, 'index.yml'), [{'gcd': 'GCD'}])
        with open(os.path.join(sect, 'lib.hpp'), 'w') as f:
            f.write('#pragma once\n')
        return 'src'

    def test_packing_codes_copies_files(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        src = self._make_pack_src(str(tmp_path))
        os.makedirs('out')
        packing_codes(src, '.hpp', 'out')
        copied = []
        for root, _, files in os.walk('out'):
            copied.extend(files)
        assert copied == ['lib.hpp']

    def test_packing_codes_filters_by_ext(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        src = self._make_pack_src(str(tmp_path))
        with open(os.path.join(str(tmp_path), 'src', 'math', 'gcd', 'usage.cpp'), 'w') as f:
            f.write('')
        os.makedirs('out_hpp')
        packing_codes(src, '.hpp', 'out_hpp')
        copied = []
        for root, _, files in os.walk('out_hpp'):
            copied.extend(files)
        assert copied == ['lib.hpp']

    def test_pack_cli_registered(self, cli):
        assert 'pack' in cli.commands
