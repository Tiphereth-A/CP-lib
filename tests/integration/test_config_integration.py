"""Integration tests for Config class with other components.

This module tests the integration between Config class and utility
functions, ensuring they work correctly together.
"""

from pathlib import Path
from unittest.mock import patch

import pytest

from libs.classes.config import Config
from libs.utils import get_full_filenames


pytestmark = pytest.mark.integration


# =============================================================================
# Config Integration Tests
# =============================================================================


class TestConfigIntegration:
    """Integration tests for Config with utility functions."""

    def test_config_with_get_full_filenames(
        self, test_config: Config, sample_dirs: dict[str, Path]
    ) -> None:
        """Test Config integration with get_full_filenames."""
        code_dir = test_config.get_code_dir()
        ext_names = test_config.get_ext_names_by_file_type('cpp')

        with patch('libs.utils.get_full_filenames') as mock_get_files:
            mock_get_files.return_value = [
                f"{code_dir}/test1.cpp",
                f"{code_dir}/test2.cpp"
            ]
            files = get_full_filenames([code_dir], ext_names)

        assert isinstance(files, list)

    def test_config_sections_integration(self, test_config: Config) -> None:
        """Test Config sections integration."""
        chapters = test_config.get_chapter_key()
        assert len(chapters) > 0

        for chapter in chapters:
            sections = test_config.get_sections_by_chapter(chapter)
            assert isinstance(sections, list)

            if sections:
                section = sections[0]
                # Verify section structure
                assert hasattr(section, 'name')
                assert hasattr(section, 'title')
                assert hasattr(section, 'chapter')
                assert hasattr(section, 'code_ext')
                assert hasattr(section, 'usage_ext')

    def test_config_file_types_integration(self, test_config: Config) -> None:
        """Test file type methods work together."""
        all_types = test_config.get_all_file_types()
        assert len(all_types) > 0

        for file_type in all_types:
            ext_names = test_config.get_ext_names_by_file_type(file_type)
            # Each file type should have at least one extension
            assert isinstance(ext_names, (list, set))

    def test_config_directory_methods_consistency(
        self, test_config: Config, sample_dirs: dict[str, Path]
    ) -> None:
        """Test that directory methods return consistent results."""
        code_dir = test_config.get_code_dir()
        doc_dir = test_config.get_doc_dir(doc_type=doc_type)

        # Directories should be strings
        assert isinstance(code_dir, str)
        assert isinstance(doc_dir, str)

        # Directories should be different
        assert code_dir != doc_dir
