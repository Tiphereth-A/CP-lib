import os
import pytest
from unittest.mock import patch, MagicMock
from libs.util.get_src_files import get_src_files


def _make_src_tree(tmp_path):
    """Create a minimal src layout with index.yml and section files."""
    import yaml
    src = tmp_path / 'src'
    cat = src / 'math'
    sect = cat / 'gcd'
    sect.mkdir(parents=True)

    index_src = [{'math': 'Math'}]
    with open(src / 'index.yml', 'w') as f:
        import yaml
        yaml.dump(index_src, f)

    index_cat = [{'gcd': 'GCD'}]
    with open(cat / 'index.yml', 'w') as f:
        yaml.dump(index_cat, f)

    (sect / 'lib.hpp').write_text('#pragma once\n')
    (sect / 'usage.cpp').write_text('// code\n')
    return src


@pytest.mark.unit
class TestGetSrcFiles:
    def test_empty_dir_no_index(self, tmp_path):
        result = get_src_files(str(tmp_path))
        assert result == []

    def test_finds_section_files(self, tmp_path):
        src = _make_src_tree(tmp_path)
        result = get_src_files(str(src))
        # math/gcd should have files discovered
        assert {os.path.basename(f) for f in result} == {
            'lib.hpp', 'usage.cpp'}

    def test_skips_dir_without_index(self, tmp_path):
        # No index.yml anywhere
        (tmp_path / 'foo').mkdir()
        (tmp_path / 'foo' / 'bar.hpp').write_text('')
        result = get_src_files(str(tmp_path))
        assert result == []

    def test_subdir_is_not_dir_skipped(self, tmp_path):
        import yaml
        src = tmp_path / 'src'
        src.mkdir()
        # index.yml at root level of src with a section name
        index_data = [{'notadir': 'NotADir'}]
        with open(src / 'index.yml', 'w') as f:
            yaml.dump(index_data, f)
        # 'notadir' doesn't exist as a directory
        result = get_src_files(str(src))
        assert result == []

    def test_section_with_own_index_skipped(self, tmp_path):
        """A section subdir that itself has index.yml should be skipped."""
        import yaml
        src = tmp_path / 'src'
        cat = src / 'cat'
        section_with_index = cat / 'meta'
        section_with_index.mkdir(parents=True)

        with open(src / 'index.yml', 'w') as f:
            yaml.dump([{'cat': 'Cat'}], f)
        with open(cat / 'index.yml', 'w') as f:
            yaml.dump([{'meta': 'Meta'}], f)
        # meta has its own index.yml, so files inside are NOT returned
        with open(section_with_index / 'index.yml', 'w') as f:
            yaml.dump([], f)
        (section_with_index / 'lib.hpp').write_text('')
        result = get_src_files(str(src))
        # The section itself has no index.yml check - but files inside should be found
        # by a deeper walk. Actually the logic: if 'index.yml' not in dir_files: continue
        # So meta's own walk will also have 'index.yml' and get processed...
        # Actually looking at the code: it iterates os.walk(src_path), finds dirs with
        # index.yml, then for each section listed, if section subdir has NO index.yml
        # it lists files. If the section subdir DOES have index.yml in its listing it is
        # skipped (the inner if 'index.yml' not in os.listdir(subdir): check).
        assert result == []
