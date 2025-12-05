"""Unit tests for utility functions."""

from libs.utils import (
    get_full_filenames,
    unique,
    get_difference,
    file_preprocess,
    execute_if_file_exist,
    scandir_merge_filter,
    scandir_file_merge,
    scandir_dir_merge,
    parse_filename
)
from unittest.mock import patch, MagicMock

import pytest

pytestmark = pytest.mark.unit


class TestGetFullFilenames:
    """Tests for get_full_filenames function."""

    def test_get_full_filenames_single_dir(self, temp_dir):
        """Test finding files in a single directory."""
        test_dir = str(temp_dir / 'test_dir')

        # Mock os.path.exists and os.walk to avoid filesystem writes
        with patch('os.path.exists') as mock_exists, patch('os.walk') as mock_walk:
            mock_exists.return_value = True
            mock_walk.return_value = [
                (test_dir, [], ['file1.cpp', 'file2.cpp', 'file3.txt'])]

            result = get_full_filenames([test_dir], ['.cpp'])

        assert len(result) == 2
        assert all('file' in f and f.endswith('.cpp') for f in result)

    def test_get_full_filenames_multiple_dirs(self, temp_dir):
        """Test finding files in multiple directories."""
        dir1 = str(temp_dir / 'dir1')
        dir2 = str(temp_dir / 'dir2')

        with patch('os.path.exists') as mock_exists, patch('os.walk') as mock_walk:
            mock_exists.return_value = True
            # os.walk will be called once per directory; return different results per call
            mock_walk.side_effect = [[(dir1, [], ['file1.cpp'])], [
                (dir2, [], ['file2.cpp'])]]

            result = get_full_filenames([dir1, dir2], ['.cpp'])

        assert len(result) == 2

    def test_get_full_filenames_nonexistent_dir(self, temp_dir):
        """Test handling of non-existent directories."""
        nonexistent = str(temp_dir / 'nonexistent')
        with patch('os.path.exists') as mock_exists:
            mock_exists.return_value = False
            result = get_full_filenames([nonexistent], ['.cpp'])
        assert result == []

    def test_get_full_filenames_nested_dirs(self, temp_dir):
        """Test finding files in nested directories."""
        parent = str(temp_dir / 'parent')
        nested = str(temp_dir / 'parent' / 'child')

        with patch('os.path.exists') as mock_exists, patch('os.walk') as mock_walk:
            mock_exists.return_value = True
            mock_walk.return_value = [(nested, [], ['file.cpp'])]

            result = get_full_filenames([parent], ['.cpp'])

        assert len(result) == 1


class TestUnique:
    """Tests for unique function."""

    def test_unique_preserves_order(self):
        """Test that unique preserves order of first occurrence."""
        result = unique([3, 1, 2, 1, 3, 2])
        assert result == [3, 1, 2]

    def test_unique_empty_list(self):
        """Test unique with empty list."""
        assert unique([]) == []

    def test_unique_all_different(self):
        """Test unique with all different elements."""
        result = unique([1, 2, 3])
        assert result == [1, 2, 3]

    def test_unique_with_hash_func(self):
        """Test unique with custom hash function."""
        result = unique([(1, 2), (3, 4), (1, 2)], hash_func=lambda x: x[0])
        assert len(result) == 2


class TestGetDifference:
    """Tests for get_difference function."""

    def test_get_difference_basic(self):
        """Test basic difference calculation."""
        total = {1, 2, 3, 4}
        seq = [1, 5, 2, 6, 3]
        result = get_difference(total, seq)

        assert 1 in result  # index 0: 5 not in total
        assert 3 in result  # index 3: 6 not in total
        assert result[1] == 5
        assert result[3] == 6

    def test_get_difference_no_difference(self):
        """Test when all elements are in total."""
        total = {1, 2, 3}
        seq = [1, 2, 3]
        result = get_difference(total, seq)
        assert result == {}


class TestFilePreprocess:
    """Tests for file_preprocess function."""

    def test_file_preprocess_merge(self, temp_dir, caplog):
        """Test file preprocessing merges config and existing files."""
        # Avoid creating files; provide existing file list directly
        files_in_config = ['file1.cpp', 'file3.cpp']
        files_exist = [str(temp_dir / 'file1.cpp'),
                       str(temp_dir / 'file2.cpp')]

        import logging
        logger = logging.getLogger('test')
        result = file_preprocess(files_in_config, files_exist, logger)

        # Should include file1 from config and file2 from existing
        assert len(result) >= 2
        assert 'file1.cpp' in result or any('file1' in f for f in result)

    def test_file_preprocess_warns_missing(self, temp_dir, caplog):
        """Test that file_preprocess warns about missing config files."""
        files_in_config = ['nonexistent.cpp']
        files_exist = []

        import logging
        logger = logging.getLogger('test')
        result = file_preprocess(files_in_config, files_exist, logger)

        assert len(result) == 0


class TestExecuteIfFileExist:
    """Tests for execute_if_file_exist function."""

    def test_execute_if_file_exist_file_exists(self, temp_dir):
        """Test execution when file exists."""
        test_file = str(temp_dir / 'test.txt')

        def read_file(path):
            return 'test'

        with patch('os.access') as mock_access:
            mock_access.return_value = True
            result = execute_if_file_exist(test_file, read_file)
        assert result == 'test'

    def test_execute_if_file_exist_file_not_exists(self, temp_dir, caplog):
        """Test execution when file doesn't exist."""
        nonexistent = str(temp_dir / 'nonexistent.txt')

        def read_file(path):
            return 'bad'

        with patch('os.access') as mock_access:
            mock_access.return_value = False
            result = execute_if_file_exist(nonexistent, read_file)
        assert result is None


class TestScandirMergeFilter:
    """Tests for scandir_merge_filter function."""

    def test_scandir_merge_filter_files(self, temp_dir):
        """Test filtering files from directories."""
        # Mock execute_if_file_exist to return DirEntry-like mocks
        entry1 = MagicMock()
        entry1.name = 'file1.txt'
        entry1.is_file.return_value = True
        entry2 = MagicMock()
        entry2.name = 'file2.txt'
        entry2.is_file.return_value = True

        with patch('libs.utils.execute_if_file_exist') as mock_exec:
            mock_exec.return_value = [entry1, entry2]

            def is_file(entry):
                return entry.is_file()

            result = scandir_merge_filter(is_file, str(temp_dir))

        assert len(result) == 2
        assert 'file1.txt' in result
        assert 'file2.txt' in result


class TestScandirFileMerge:
    """Tests for scandir_file_merge function."""

    def test_scandir_file_merge_valid_ext(self, temp_dir):
        """Test merging files with valid extensions."""
        entry1 = MagicMock()
        entry1.name = 'file1.cpp'
        entry1.is_file.return_value = True
        entry2 = MagicMock()
        entry2.name = 'file2.cpp'
        entry2.is_file.return_value = True
        entry3 = MagicMock()
        entry3.name = 'file3.txt'
        entry3.is_file.return_value = True

        with patch('libs.utils.execute_if_file_exist') as mock_exec:
            mock_exec.return_value = [entry1, entry2, entry3]
            result = scandir_file_merge(['cpp'], str(temp_dir))

        assert len(result) == 2
        assert 'file1.cpp' in result
        assert 'file2.cpp' in result
        assert 'file3.txt' not in result


class TestScandirDirMerge:
    """Tests for scandir_dir_merge function."""

    def test_scandir_dir_merge(self, temp_dir):
        """Test merging directory names."""
        d1 = MagicMock()
        d1.name = 'dir1'
        d1.is_dir.return_value = True
        d2 = MagicMock()
        d2.name = 'dir2'
        d2.is_dir.return_value = True
        f = MagicMock()
        f.name = 'file.txt'
        f.is_dir.return_value = False

        with patch('libs.utils.execute_if_file_exist') as mock_exec:
            mock_exec.return_value = [d1, d2, f]
            result = scandir_dir_merge(str(temp_dir))

        assert len(result) == 2
        assert 'dir1' in result
        assert 'dir2' in result


class TestParseFilename:
    """Tests for parse_filename function."""

    def test_parse_filename_with_ext(self):
        """Test parsing filename with extension."""
        name, ext = parse_filename('test.cpp')
        assert name == 'test'
        assert ext == 'cpp'

    def test_parse_filename_no_ext(self):
        """Test parsing filename without extension."""
        name, ext = parse_filename('test')
        assert name == 'test'
        assert ext == ''

    def test_parse_filename_multiple_dots(self):
        """Test parsing filename with multiple dots."""
        name, ext = parse_filename('test.file.cpp')
        assert name == 'test'
        assert ext == 'file.cpp'
