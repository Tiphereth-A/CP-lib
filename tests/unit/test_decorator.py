"""Unit tests for decorator module."""

from libs.decorator import with_logger, with_timer
from libs.classes.decorator_result_handler import DecoratorResultHandlerBase
import time
import logging

import pytest

pytestmark = pytest.mark.unit


class TestWithlogDecorator:
    """Tests for @with_logger decorator."""

    def test_with_logger_adds_logger(self, caplog):
        """Test that @with_logger decorator adds logger parameter."""
        @with_logger
        def test_function(arg1, arg2, **kwargs):
            logger = kwargs.get('logger')
            assert logger is not None
            assert isinstance(logger, logging.Logger)
            logger.info(f"Processing {arg1} and {arg2}")
            return arg1 + arg2

        with caplog.at_level(logging.DEBUG):
            result = test_function(1, 2)

        assert result == 3
        assert 'test_function' in caplog.text

    def test_with_logger_logs_entry_exit(self, caplog):
        """Test that @with_logger logs function entry and exit."""
        @with_logger
        def test_function(**kwargs):
            logger = kwargs.get('logger')
            logger.info("Inside function")
            return "result"

        with caplog.at_level(logging.DEBUG):
            result = test_function()

        assert result == "result"
        assert "Start running test_function" in caplog.text
        assert "Finished running test_function" in caplog.text
        assert "Returned: 'result'" in caplog.text

    def test_with_logger_logs_no_return_value(self, caplog):
        """Test that @with_logger handles functions without return values."""
        @with_logger
        def test_function(**kwargs):
            logger = kwargs.get('logger')
            logger.info("No return")

        with caplog.at_level(logging.DEBUG):
            test_function()

        assert "Start running test_function" in caplog.text
        assert "Finished running test_function" in caplog.text
        # Should not log return value for None
        assert "Returned" not in caplog.text or "None" in caplog.text

    def test_with_logger_preserves_function_metadata(self):
        """Test that @with_logger preserves function metadata."""
        @with_logger
        def test_function():
            """Test function docstring."""
            pass

        assert test_function.__name__ == 'test_function'
        assert 'Test function docstring' in test_function.__doc__

    def test_with_logger_with_positional_args(self, caplog):
        """Test that @with_logger works with positional arguments."""
        @with_logger
        def test_function(a, b, c, **kwargs):
            logger = kwargs.get('logger')
            logger.info(f"Args: {a}, {b}, {c}")
            return a + b + c

        with caplog.at_level(logging.DEBUG):
            result = test_function(1, 2, 3)

        assert result == 6
        assert "Start running test_function" in caplog.text


class TestWithTimerDecorator:
    """Tests for @with_timer decorator."""

    def test_with_timer_returns_result_container(self):
        @with_timer
        def test_fn():
            return 42

        ret = test_fn()
        assert isinstance(ret, DecoratorResultHandlerBase)
        assert ret.result == 42
        assert isinstance(ret.elapsed_ms, float)
        assert ret.elapsed_ms >= 0

    def test_with_timer_measures_time(self):
        @with_timer
        def test_sleep():
            time.sleep(0.02)
            return 'ok'

        ret = test_sleep()
        assert ret.result == 'ok'
        assert ret.elapsed_ms >= 20

    def test_with_timer_preserves_metadata(self):
        @with_timer
        def sample_function():
            """Sample docstring."""
            return None

        assert sample_function.__name__ == 'sample_function'
        assert 'Sample docstring' in sample_function.__doc__
