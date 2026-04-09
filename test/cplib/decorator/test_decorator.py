import logging
import pytest
from unittest.mock import MagicMock
from libs.decorator.result_handler import DecoratorResultHandlerBase
from libs.decorator.timer import with_timer
from libs.decorator.logger import with_logger


@pytest.mark.unit
class TestDecoratorResultHandlerBase:
    def test_cannot_instantiate_abstract(self):
        with pytest.raises(TypeError):
            DecoratorResultHandlerBase(result=None, func_name='test')

    def test_concrete_subclass(self):
        class Concrete(DecoratorResultHandlerBase):
            def write_to_logger(self, logger):
                pass

        obj = Concrete(result=42, func_name='fn')
        assert obj.result == 42
        assert obj.func_name == 'fn'

    def test_write_to_logger_called(self):
        class Concrete(DecoratorResultHandlerBase):
            def write_to_logger(self, logger):
                logger.info('called')

        mock_logger = MagicMock()
        obj = Concrete(result=None, func_name='fn')
        obj.write_to_logger(mock_logger)
        mock_logger.info.assert_called_once_with('called')


@pytest.mark.unit
class TestWithTimer:
    def test_returns_correct_value(self):
        @with_timer
        def add(a, b):
            return a + b

        result = add(2, 3)
        # with_timer wraps result in WithTimerResultHandler
        from libs.decorator.result_handler import DecoratorResultHandlerBase
        assert isinstance(result, DecoratorResultHandlerBase)
        assert result.result == 5

    def test_elapsed_ms_positive(self):
        @with_timer
        def noop():
            return None

        result = noop()
        assert result.elapsed_ms >= 0

    def test_write_to_logger(self):
        @with_timer
        def noop():
            return 'x'

        result = noop()
        mock_logger = MagicMock()
        result.write_to_logger(mock_logger)
        mock_logger.debug.assert_called_once()
        call_args = mock_logger.debug.call_args[0][0]
        assert call_args == f"noop took {result.elapsed_ms:.3f}ms"

    def test_preserves_function_name(self):
        @with_timer
        def my_function():
            return 1

        assert my_function.__name__ == 'my_function'


@pytest.mark.unit
class TestWithLogger:
    def test_basic_invocation(self):
        @with_logger
        def greet(name, **kwargs):
            return f"Hello {name}"

        result = greet("World")
        assert result == "Hello World"

    def test_preserves_function_name(self):
        @with_logger
        def my_func(**kwargs):
            return 42

        assert my_func.__name__ == 'my_func'

    def test_returns_none_result(self):
        @with_logger
        def returns_none(**kwargs):
            return None

        result = returns_none()
        assert result is None

    def test_with_logger_injects_logger(self):
        captured = {}

        @with_logger
        def capture(**kwargs):
            captured['logger'] = kwargs.get('logger')
            return 'ok'

        result = capture()
        assert result == 'ok'
        assert captured['logger'] is not None
        assert isinstance(captured['logger'], logging.Logger)

    def test_logger_wraps_nested_result_handler(self):
        """with_logger unwraps nested DecoratorResultHandlerBase."""
        @with_logger
        @with_timer
        def compute(**kwargs):
            return 99

        result = compute()
        assert result == 99

    def test_stacked_decorators(self):
        @with_logger
        @with_timer
        def multiply(a, b, **kwargs):
            return a * b

        assert multiply(3, 4) == 12

    def test_stacked_decorators_logs_unwrapped_return_value(self, caplog):
        @with_logger
        @with_timer
        def compute(**kwargs):
            return 99

        with caplog.at_level(logging.DEBUG):
            result = compute()

        assert result == 99
        assert "Returned: '99'" in caplog.messages
        assert not any(
            'ResultHandler object at' in msg for msg in caplog.messages)

    def test_logger_with_non_none_result(self, caplog):
        @with_logger
        def ret_val(**kwargs):
            return [1, 2, 3]

        with caplog.at_level(logging.DEBUG):
            result = ret_val()
        assert result == [1, 2, 3]
