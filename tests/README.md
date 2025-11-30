# Test Suite for CP-lib Manager System

This directory contains comprehensive tests for the manager system using pytest.

## Test Structure

The tests are organized into three categories:

### Unit Tests (UT) - `tests/unit/`
Tests for individual components in isolation:
- `test_utils.py` - Utility functions (file operations, filtering, etc.)
- `test_decorator.py` - `@withlog` decorator functionality
- `test_config.py` - Config class methods and properties

### Integration Tests (IT) - `tests/integration/`
Tests for component interactions:
- `test_commands.py` - Command module interactions (clean, fmt, etc.)
- `test_config_integration.py` - Config integration with utility functions

### System Tests (ST) - `tests/system/`
End-to-end tests for CLI execution:
- `test_cli.py` - Full CLI command execution and workflow

## Running Tests

### Run all tests
```bash
pytest
```

### Run specific test categories
```bash
# Unit tests only
pytest -m unit

# Integration tests only
pytest -m integration

# System tests only
pytest -m system
```

### Run specific test file
```bash
pytest tests/unit/test_utils.py
```

### Run with coverage
```bash
pytest --cov=libs --cov-report=html

## Recommended quick coverage check
pytest --maxfail=1 --disable-warnings -q --cov=libs --cov-report=term-missing
```

### Run with verbose output
```bash
pytest -v
```

## Test Fixtures

The `conftest.py` file provides shared fixtures:
- `temp_dir` - Temporary directory for test files
- `sample_config_file` - Sample config.yml for testing
- `sample_tcgen_file` - Sample tcgen.yml for testing
- `test_config` - Config instance for testing
- `test_config_tcgen` - ConfigTCGen instance for testing
- `sample_code_file` - Sample code file for testing
- `sample_dirs` - Sample directory structure

## Dependencies

Tests require:
- `pytest>=9.0.1`
- `pytest-cov>=4.1.0` (optional, for coverage)
- All project dependencies (click, pyyaml, etc.)

Install test dependencies:
```bash
uv sync --group dev
```

## Writing New Tests

When adding new tests:
1. Place unit tests in `tests/unit/`
2. Place integration tests in `tests/integration/`
3. Place system tests in `tests/system/`
4. Use appropriate pytest markers (`@pytest.mark.unit`, etc.)
5. Leverage fixtures from `conftest.py` when possible
6. Follow the naming convention: `test_*.py` for files, `test_*` for functions

## Test Coverage Goals

- Unit tests: Cover all utility functions, decorators, and class methods
- Integration tests: Cover command interactions and component integration
- System tests: Cover end-to-end CLI workflows
