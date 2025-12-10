"""Pytest configuration and shared fixtures."""

import tempfile
import shutil
from pathlib import Path
from typing import Generator

import pytest
import yaml

from libs.classes.config import Config
from libs.classes.config_tcgen import ConfigTCGen


@pytest.fixture
def temp_dir() -> Generator[Path, None, None]:
    """Create a temporary directory for testing."""
    temp_path = Path(tempfile.mkdtemp())
    yield temp_path
    shutil.rmtree(temp_path, ignore_errors=True)


@pytest.fixture
def sample_config_file(temp_dir: Path) -> Path:
    """Create a sample config.yml file for testing."""
    config_data = {
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
                        }
                        ]
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

    config_path = temp_dir / 'config.yml'
    with open(config_path, 'w', encoding='utf-8') as f:
        yaml.dump(config_data, f)
    return config_path


@pytest.fixture
def sample_tcgen_file(temp_dir: Path) -> Path:
    """Create a sample tcgen.yml file for testing."""
    tcgen_data = {
        'test_cases': {
            'test1': {
                'input': '1 2',
                'output': '3'
            }
        }
    }

    tcgen_path = temp_dir / 'tcgen.yml'
    with open(tcgen_path, 'w', encoding='utf-8') as f:
        yaml.dump(tcgen_data, f)
    return tcgen_path


@pytest.fixture
def test_config(sample_config_file: Path) -> Config:
    """Create a Config instance for testing."""
    return Config(str(sample_config_file))


@pytest.fixture
def test_config_tcgen(sample_tcgen_file: Path) -> ConfigTCGen:
    """Create a ConfigTCGen instance for testing."""
    return ConfigTCGen(str(sample_tcgen_file))


@pytest.fixture
def sample_code_file(temp_dir: Path) -> Path:
    """Create a sample code file for testing."""
    code_file = temp_dir / 'test.cpp'
    code_file.write_text('#include <iostream>\nint main() { return 0; }\n')
    return code_file


@pytest.fixture
def sample_dirs(temp_dir: Path) -> dict[str, Path]:
    """Create sample directory structure for testing."""
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
