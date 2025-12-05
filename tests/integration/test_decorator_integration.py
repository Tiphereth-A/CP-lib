"""Integration tests for decorator interactions."""

import logging
import time

from libs.decorator import with_logger, with_timer

import pytest

pytestmark = pytest.mark.integration


def test_with_logger_and_with_timer_integration_logs_time(caplog):
    """Verify that using `@with_timer` under `@with_logger` logs elapsed ms."""

    @with_logger
    @with_timer
    def sample_function(**kwargs):
        # do a small sleep to ensure measurable elapsed time
        time.sleep(0.02)
        return 'ok'

    with caplog.at_level(logging.INFO):
        result = sample_function()

    assert result == 'ok'
    # Log should contain timing info in ms
    assert 'took' in caplog.text
    assert 'ms' in caplog.text
