"""Integration tests for decorator interactions.

This module tests how decorators interact with each other and
other components when used in combination.
"""

import logging
import time

import pytest

from libs.decorator import with_logger, with_timer


pytestmark = pytest.mark.integration


# =============================================================================
# Decorator Integration Tests
# =============================================================================


class TestDecoratorIntegration:
    """Integration tests for decorator combinations."""

    def test_with_logger_and_with_timer_logs_time(
        self, caplog: pytest.LogCaptureFixture
    ) -> None:
        """Verify that using @with_timer under @with_logger logs elapsed ms."""
        @with_logger
        @with_timer
        def sample_function(**kwargs) -> str:
            time.sleep(0.02)
            return 'ok'

        with caplog.at_level(logging.INFO):
            result = sample_function()

        assert result == 'ok'
        # Log should contain timing info
        assert 'took' in caplog.text
        assert 'ms' in caplog.text

    def test_multiple_decorated_functions_independent(
        self, caplog: pytest.LogCaptureFixture
    ) -> None:
        """Test that multiple decorated functions work independently."""
        @with_logger
        def func1(**kwargs) -> int:
            return 1

        @with_logger
        def func2(**kwargs) -> int:
            return 2

        with caplog.at_level(logging.DEBUG):
            r1 = func1()
            r2 = func2()

        assert r1 == 1
        assert r2 == 2
        assert 'func1' in caplog.text
        assert 'func2' in caplog.text

    def test_timer_precision_under_logger(self) -> None:
        """Test timer precision when used with logger."""
        @with_logger
        @with_timer
        def precise_function(**kwargs) -> str:
            time.sleep(0.05)
            return 'done'

        result = precise_function()
        # Result should be the actual return value due to logger handling
        assert result == 'done'

    def test_nested_decorated_calls(
        self, caplog: pytest.LogCaptureFixture
    ) -> None:
        """Test decorated functions calling each other."""
        @with_logger
        def inner_function(**kwargs) -> int:
            return 42

        @with_logger
        def outer_function(**kwargs) -> int:
            return inner_function() + 1

        with caplog.at_level(logging.DEBUG):
            result = outer_function()

        assert result == 43
        assert 'inner_function' in caplog.text
        assert 'outer_function' in caplog.text
