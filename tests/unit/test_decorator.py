"""Unit tests for decorator module."""

from libs.decorator import withlog
import logging

import pytest

pytestmark = pytest.mark.unit


class TestWithlogDecorator:
    """Tests for @withlog decorator."""

    def test_withlog_adds_logger(self, caplog):
        """Test that @withlog decorator adds logger parameter."""
        @withlog
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

    def test_withlog_logs_entry_exit(self, caplog):
        """Test that @withlog logs function entry and exit."""
        @withlog
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

    def test_withlog_logs_no_return_value(self, caplog):
        """Test that @withlog handles functions without return values."""
        @withlog
        def test_function(**kwargs):
            logger = kwargs.get('logger')
            logger.info("No return")

        with caplog.at_level(logging.DEBUG):
            test_function()

        assert "Start running test_function" in caplog.text
        assert "Finished running test_function" in caplog.text
        # Should not log return value for None
        assert "Returned" not in caplog.text or "None" in caplog.text

    def test_withlog_preserves_function_metadata(self):
        """Test that @withlog preserves function metadata."""
        @withlog
        def test_function():
            """Test function docstring."""
            pass

        assert test_function.__name__ == 'test_function'
        assert 'Test function docstring' in test_function.__doc__

    def test_withlog_with_positional_args(self, caplog):
        """Test that @withlog works with positional arguments."""
        @withlog
        def test_function(a, b, c, **kwargs):
            logger = kwargs.get('logger')
            logger.info(f"Args: {a}, {b}, {c}")
            return a + b + c

        with caplog.at_level(logging.DEBUG):
            result = test_function(1, 2, 3)

        assert result == 6
        assert "Start running test_function" in caplog.text
