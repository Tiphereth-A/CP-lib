# Test Suite

Comprehensive pytest test suite for the CP-lib manager system.

## Structure

```
tests/
├── conftest.py      # Shared fixtures
├── unit/            # Component tests
├── integration/     # Component interaction tests
└── system/          # End-to-end CLI tests
```

## Running Tests

```bash
# All tests
pytest

# By category
pytest -m unit
pytest -m integration
pytest -m system

# With coverage
pytest --cov=libs --cov-report=term-missing
```

## Fixtures

Available in `conftest.py`:
- `temp_dir` - Temporary directory
- `sample_config_file` / `test_config` - Config testing
- `sample_tcgen_file` / `test_config_tcgen` - TCGen testing
- `sample_code_file` - Sample C++ file
- `sample_dirs` - Directory structure
- `mock_logger` - Mock logger instance

## Adding Tests

1. Place in appropriate directory (`unit/`, `integration/`, `system/`)
2. Add pytest marker: `pytestmark = pytest.mark.unit`
3. Use fixtures from `conftest.py`
4. Follow naming: `test_*.py` files, `test_*` functions
