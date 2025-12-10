"""Unit tests for ConfigTCGen class.

This module tests the test case generation configuration handling,
including category management, member lists, and content retrieval.
"""

from pathlib import Path
from typing import Any

import pytest
import yaml

from libs.classes.config_tcgen import ConfigTCGen


pytestmark = pytest.mark.unit


# =============================================================================
# Helper Functions
# =============================================================================


def make_tcgen_yaml(tmp_path: Path, data: dict[str, Any] | None = None) -> str:
    """Create a tcgen YAML file with given or default data.

    Args:
        tmp_path: Temporary directory path.
        data: Optional configuration data. If None, uses default test data.

    Returns:
        Path to the created YAML file as string.
    """
    if data is None:
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
    path = tmp_path / 'tcgen.yml'
    path.write_text(yaml.dump(data), encoding='utf-8')
    return str(path)


# =============================================================================
# ConfigTCGen Tests
# =============================================================================


class TestConfigTCGenBasic:
    """Basic tests for ConfigTCGen class."""

    @pytest.fixture
    def tcgen_config(self, tmp_path: Path) -> ConfigTCGen:
        """Create a ConfigTCGen instance with default test data."""
        path = make_tcgen_yaml(tmp_path)
        return ConfigTCGen(path)

    def test_get_categories(self, tcgen_config: ConfigTCGen) -> None:
        """Test retrieving all categories."""
        categories = tcgen_config.get_categories()
        assert 'cat1' in categories
        assert 'cat2' in categories
        assert 'cat3' in categories

    def test_get_memberlist_single_category(self, tcgen_config: ConfigTCGen) -> None:
        """Test getting member list for a single category string."""
        member_list = tcgen_config.get_memberlist('cat1')
        assert any(isinstance(x, tuple) for x in member_list)
        assert len(member_list) >= 2  # m1 and m2

    def test_get_memberlist_multiple_categories(self, tcgen_config: ConfigTCGen) -> None:
        """Test getting member list for multiple categories."""
        member_list_single = tcgen_config.get_memberlist('cat1')
        member_list_multi = tcgen_config.get_memberlist(['cat1', 'cat2'])
        assert len(member_list_multi) >= len(member_list_single)


class TestConfigTCGenMemberContent:
    """Tests for ConfigTCGen member content retrieval."""

    @pytest.fixture
    def tcgen_config(self, tmp_path: Path) -> ConfigTCGen:
        """Create a ConfigTCGen instance with default test data."""
        path = make_tcgen_yaml(tmp_path)
        return ConfigTCGen(path)

    def test_get_member_content_single_category(self, tcgen_config: ConfigTCGen) -> None:
        """Test getting member content for a single category."""
        content = tcgen_config.get_member_content('cat1', 'm1')
        assert 'category_name' in content
        assert 'member_name' in content

    def test_get_member_content_list_category(self, tcgen_config: ConfigTCGen) -> None:
        """Test getting member content with list-category resolution."""
        content = tcgen_config.get_member_content(['cat1', 'cat2'], 'm3')
        assert isinstance(content, dict)


class TestConfigTCGenPriority:
    """Tests for ConfigTCGen priority handling."""

    @pytest.fixture
    def tcgen_config(self, tmp_path: Path) -> ConfigTCGen:
        """Create a ConfigTCGen instance with default test data."""
        path = make_tcgen_yaml(tmp_path)
        return ConfigTCGen(path)

    def test_get_categories_with_same_priority(self, tcgen_config: ConfigTCGen) -> None:
        """Test getting categories with the same priority."""
        same_priority = tcgen_config.get_categories_with_same_priority('cat1')
        assert 'cat2' in same_priority

    def test_different_priorities_raises_error(self, tcgen_config: ConfigTCGen) -> None:
        """Test that differing priorities raise RuntimeError."""
        with pytest.raises(RuntimeError):
            tcgen_config.get_memberlist(['cat1', 'cat3'])
