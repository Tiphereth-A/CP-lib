import os
import pytest
from libs.util.get_files_with_exts import get_files_with_exts


@pytest.mark.unit
class TestGetFilesWithExts:
    def test_empty_directories(self):
        result = get_files_with_exts([], ['.py'])
        assert result == []

    def test_nonexistent_directory_skipped(self, tmp_path):
        result = get_files_with_exts([str(tmp_path / 'nonexistent')], ['.py'])
        assert result == []

    def test_finds_matching_files(self, tmp_path):
        (tmp_path / 'a.py').write_text('x')
        (tmp_path / 'b.cpp').write_text('x')
        result = get_files_with_exts([str(tmp_path)], ['.py'])
        assert len(result) == 1
        assert result[0].endswith('a.py')

    def test_multiple_extensions(self, tmp_path):
        (tmp_path / 'a.py').write_text('x')
        (tmp_path / 'b.cpp').write_text('x')
        (tmp_path / 'c.txt').write_text('x')
        result = get_files_with_exts([str(tmp_path)], ['.py', '.cpp'])
        assert len(result) == 2

    def test_recursive_walk(self, tmp_path):
        subdir = tmp_path / 'sub'
        subdir.mkdir()
        (tmp_path / 'a.py').write_text('x')
        (subdir / 'b.py').write_text('x')
        result = get_files_with_exts([str(tmp_path)], ['.py'])
        assert len(result) == 2

    def test_no_matching_extension(self, tmp_path):
        (tmp_path / 'a.txt').write_text('x')
        result = get_files_with_exts([str(tmp_path)], ['.py'])
        assert result == []

    def test_multiple_directories(self, tmp_path):
        d1 = tmp_path / 'dir1'
        d2 = tmp_path / 'dir2'
        d1.mkdir()
        d2.mkdir()
        (d1 / 'a.py').write_text('x')
        (d2 / 'b.py').write_text('x')
        result = get_files_with_exts([str(d1), str(d2)], ['.py'])
        assert len(result) == 2

    def test_one_dir_missing_one_exists(self, tmp_path):
        (tmp_path / 'a.hpp').write_text('x')
        result = get_files_with_exts(
            [str(tmp_path / 'missing'), str(tmp_path)], ['.hpp'])
        assert len(result) == 1
