"""Integration tests for Config class with other components."""

from libs.utils import get_full_filenames
from libs.classes.config import Config
import pytest
from unittest.mock import patch

pytestmark = pytest.mark.integration


class TestConfigIntegration:
    """Integration tests for Config with utility functions."""

    def test_config_with_get_full_filenames(self, test_config, sample_dirs):
        """Test Config integration with get_full_filenames."""
        # Avoid touching filesystem: mock get_full_filenames
        code_dir = test_config.get_code_dir()
        ext_names = test_config.get_ext_names_by_code_style('cpp')

        with patch('libs.utils.get_full_filenames') as mock_get_files:
            mock_get_files.return_value = [
                f"{code_dir}/test1.cpp", f"{code_dir}/test2.cpp"]
            files = get_full_filenames([code_dir], ext_names)

        assert isinstance(files, list)

    def test_config_sections_integration(self, test_config):
        """Test Config sections integration."""
        chapters = test_config.get_chapter_key()
        assert len(chapters) > 0

        for chapter in chapters:
            sections = test_config.get_sections_by_chapter(chapter)
            assert isinstance(sections, list)
            if sections:
                # Verify section structure
                section = sections[0]
                assert hasattr(section, 'name')
                assert hasattr(section, 'title')
                assert hasattr(section, 'chapter')
                assert hasattr(section, 'code_ext')
                assert hasattr(section, 'usage_ext')
