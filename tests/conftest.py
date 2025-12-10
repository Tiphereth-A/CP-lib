"""Pytest configuration and shared fixtures.

This module provides common fixtures and configuration for all test types:
- Unit tests: Basic component testing
- Integration tests: Testing component interactions
- System tests: End-to-end CLI testing
"""

import tempfile
import shutil
from pathlib import Path
from typing import Any, Generator

import pytest
import yaml

from libs.classes.config import Config
from libs.classes.config_tcgen import ConfigTCGen


# =============================================================================
# Helper Functions
# =============================================================================


def make_yaml_file(path: Path, data: dict[str, Any]) -> Path:
    """Create a YAML file with the given data.

    Args:
        path: Path where the YAML file should be created.
        data: Dictionary to serialize to YAML.

    Returns:
        Path to the created file.
    """
    path.write_text(yaml.dump(data), encoding='utf-8')
    return path


# =============================================================================
# Core Fixtures
# =============================================================================


@pytest.fixture
def temp_dir() -> Generator[Path, None, None]:
    """Create a temporary directory for testing.

    Yields:
        Path to the temporary directory.

    Note:
        The directory is automatically cleaned up after the test.
    """
    temp_path = Path(tempfile.mkdtemp())
    yield temp_path
    shutil.rmtree(temp_path, ignore_errors=True)


# =============================================================================
# Config Fixtures
# =============================================================================


@pytest.fixture
def sample_config_data() -> dict[str, Any]:
    """Return sample configuration data for testing.

    Returns:
        Dictionary containing valid configuration data.
    """
    return {
        'notebook_code_dir': 'src',
        'notebook_doc_dir': {
            'tex': 'doc',
            'typ': 'doc_typ'
        },
        'notebook_file': 'notebook.tex',
        'default_file_type': 'cpp',
        'file_types': {
            'cpp': 'cpp'
        },
        'code_type_list': ['cpp'],
        'doc_type_list': [],
        'notebook': {
            'chapters': {
                'ch1': 'Chapter 1'
            },
            'sections': {
                'ch1': [{
                    'sec1': 'Section 1',
                    'code_ext': '.hpp',
                    'usage_ext': '.cpp'
                }]
            }
        },
        'cheatsheets': {
            'cs1': 'Cheatsheet 1'
        },
        'cheatsheet_dir': 'cheatsheet',
        'usage_dir': 'usage',
        'formatting_commands': {
            'cpp': 'clang-format -i {src}'
        },
        'run_usage_commands': {
            'cpp': 'g++ {src}'
        }
    }


@pytest.fixture
def sample_config_file(temp_dir: Path, sample_config_data: dict[str, Any]) -> Path:
    """Create a sample config.yml file for testing.

    Args:
        temp_dir: Temporary directory fixture.
        sample_config_data: Configuration data fixture.

    Returns:
        Path to the created config file.
    """
    return make_yaml_file(temp_dir / 'config.yml', sample_config_data)


@pytest.fixture
def sample_tcgen_data() -> dict[str, Any]:
    """Return sample tcgen configuration data for testing.

    Returns:
        Dictionary containing valid tcgen configuration data.
    """
    return {
        'test_cases': {
            'test1': {
                'input': '1 2',
                'output': '3'
            }
        }
    }


@pytest.fixture
def sample_tcgen_file(temp_dir: Path, sample_tcgen_data: dict[str, Any]) -> Path:
    """Create a sample tcgen.yml file for testing.

    Args:
        temp_dir: Temporary directory fixture.
        sample_tcgen_data: TCGen configuration data fixture.

    Returns:
        Path to the created tcgen file.
    """
    return make_yaml_file(temp_dir / 'tcgen.yml', sample_tcgen_data)


@pytest.fixture
def test_config(sample_config_file: Path) -> Config:
    """Create a Config instance for testing.

    Args:
        sample_config_file: Path to sample config file.

    Returns:
        Configured Config instance.
    """
    return Config(str(sample_config_file))


@pytest.fixture
def test_config_tcgen(sample_tcgen_file: Path) -> ConfigTCGen:
    """Create a ConfigTCGen instance for testing.

    Args:
        sample_tcgen_file: Path to sample tcgen file.

    Returns:
        Configured ConfigTCGen instance.
    """
    return ConfigTCGen(str(sample_tcgen_file))


# =============================================================================
# File and Directory Fixtures
# =============================================================================


@pytest.fixture
def sample_code_file(temp_dir: Path) -> Path:
    """Create a sample C++ code file for testing.

    Args:
        temp_dir: Temporary directory fixture.

    Returns:
        Path to the created code file.
    """
    code_file = temp_dir / 'test.cpp'
    code_file.write_text('#include <iostream>\nint main() { return 0; }\n')
    return code_file


@pytest.fixture
def sample_dirs(temp_dir: Path) -> dict[str, Path]:
    """Create sample directory structure for testing.

    Creates a standard project directory structure with:
    - src: Source code directory
    - doc: Documentation directory
    - usage: Usage examples directory
    - cheatsheet: Cheatsheet files directory
    - _gen: Generated content directory
    - _pdf_out: PDF output directory

    Args:
        temp_dir: Temporary directory fixture.

    Returns:
        Dictionary mapping directory names to their paths.
    """
    dirs = {
        'src': temp_dir / 'src',
        'doc': temp_dir / 'doc',
        'usage': temp_dir / 'usage',
        'cheatsheet': temp_dir / 'cheatsheet',
        '_gen': temp_dir / '_gen',
        '_pdf_out': temp_dir / '_pdf_out'
    }
    for dir_path in dirs.values():
        dir_path.mkdir(parents=True, exist_ok=True)
    return dirs


# =============================================================================
# Mock Fixtures
# =============================================================================


@pytest.fixture
def mock_logger():
    """Create a mock logger for testing.

    Returns:
        A mock object that implements common logger methods.
    """
    class MockLogger:
        """Mock logger that captures all log calls."""

        def __init__(self):
            self.messages: list[tuple[str, str]] = []

        def debug(self, msg: str, *args, **kwargs) -> None:
            self.messages.append(('debug', msg))

        def info(self, msg: str, *args, **kwargs) -> None:
            self.messages.append(('info', msg))

        def warning(self, msg: str, *args, **kwargs) -> None:
            self.messages.append(('warning', msg))

        def error(self, msg: str, *args, **kwargs) -> None:
            self.messages.append(('error', msg))

        def isEnabledFor(self, level: int) -> bool:
            return True

    return MockLogger()
