"""Unit tests for decorator module.

This module tests the logging and timing decorators used throughout
the project for function instrumentation and profiling.
"""

import logging
import time

import pytest

from libs.classes.decorator_result_handler import DecoratorResultHandlerBase
from libs.decorator import with_logger, with_timer


pytestmark = pytest.mark.unit


# =============================================================================
# @with_logger Decorator Tests
# =============================================================================


class TestWithLoggerDecorator:
    """Tests for @with_logger decorator."""

    def test_adds_logger_parameter(self, caplog: pytest.LogCaptureFixture) -> None:
        """Test that @with_logger decorator adds logger parameter."""
        @with_logger
        def test_function(arg1: int, arg2: int, **kwargs) -> int:
            logger = kwargs.get('logger')
            assert logger is not None
            assert isinstance(logger, logging.Logger)
            logger.info(f"Processing {arg1} and {arg2}")
            return arg1 + arg2

        with caplog.at_level(logging.DEBUG):
            result = test_function(1, 2)

        assert result == 3
        assert 'test_function' in caplog.text

    def test_logs_entry_and_exit(self, caplog: pytest.LogCaptureFixture) -> None:
        """Test that @with_logger logs function entry and exit."""
        @with_logger
        def test_function(**kwargs) -> str:
            logger = kwargs.get('logger')
            logger.info("Inside function")
            return "result"

        with caplog.at_level(logging.DEBUG):
            result = test_function()

        assert result == "result"
        assert "Start running test_function" in caplog.text
        assert "Finished running test_function" in caplog.text
        assert "Returned: 'result'" in caplog.text

    def test_handles_no_return_value(self, caplog: pytest.LogCaptureFixture) -> None:
        """Test that @with_logger handles functions without return values."""
        @with_logger
        def test_function(**kwargs) -> None:
            logger = kwargs.get('logger')
            logger.info("No return")

        with caplog.at_level(logging.DEBUG):
            test_function()

        assert "Start running test_function" in caplog.text
        assert "Finished running test_function" in caplog.text
        # Should not log return value for None
        assert "Returned" not in caplog.text or "None" in caplog.text

    def test_preserves_function_metadata(self) -> None:
        """Test that @with_logger preserves function metadata."""
        @with_logger
        def test_function() -> None:
            """Test function docstring."""
            pass

        assert test_function.__name__ == 'test_function'
        assert 'Test function docstring' in test_function.__doc__

    def test_works_with_positional_args(self, caplog: pytest.LogCaptureFixture) -> None:
        """Test that @with_logger works with positional arguments."""
        @with_logger
        def test_function(a: int, b: int, c: int, **kwargs) -> int:
            logger = kwargs.get('logger')
            logger.info(f"Args: {a}, {b}, {c}")
            return a + b + c

        with caplog.at_level(logging.DEBUG):
            result = test_function(1, 2, 3)

        assert result == 6
        assert "Start running test_function" in caplog.text


# =============================================================================
# @with_timer Decorator Tests
# =============================================================================


class TestWithTimerDecorator:
    """Tests for @with_timer decorator."""

    def test_returns_result_container(self) -> None:
        """Test that @with_timer returns a DecoratorResultHandlerBase."""
        @with_timer
        def test_fn() -> int:
            return 42

        result = test_fn()
        assert isinstance(result, DecoratorResultHandlerBase)
        assert result.result == 42
        assert isinstance(result.elapsed_ms, float)
        assert result.elapsed_ms >= 0

    def test_measures_time_accurately(self) -> None:
        """Test that @with_timer measures elapsed time."""
        @with_timer
        def test_sleep() -> str:
            time.sleep(0.02)
            return 'ok'

        result = test_sleep()
        assert result.result == 'ok'
        assert result.elapsed_ms >= 20

    def test_preserves_function_metadata(self) -> None:
        """Test that @with_timer preserves function metadata."""
        @with_timer
        def sample_function() -> None:
            """Sample docstring."""
            return None

        assert sample_function.__name__ == 'sample_function'
        assert 'Sample docstring' in sample_function.__doc__


# =============================================================================
# Combined Decorator Tests
# =============================================================================


class TestDecoratorCombinations:
    """Tests for decorator combinations."""

    def test_timer_under_logger(self, caplog: pytest.LogCaptureFixture) -> None:
        """Test using @with_timer under @with_logger."""
        @with_logger
        @with_timer
        def sample_function(**kwargs) -> str:
            time.sleep(0.01)
            return 'ok'

        with caplog.at_level(logging.INFO):
            result = sample_function()

        assert result == 'ok'
        # Should log timing info
        assert 'took' in caplog.text or 'ms' in caplog.text
