import logging
import time
from functools import wraps
from libs.classes.decorator_result_handler import DecoratorResultHandlerBase


def with_logger(func):
    """Decorator that injects a `logger` and logs entry/exit.

    If the wrapped function returns a tuple `(result, elapsed_ms)` (as
    produced by `with_timer`), this decorator will log the elapsed time
    (in milliseconds) via `logger.info` and return `result` to the caller.
    """
    logger: logging.Logger = logging.getLogger(func.__name__)
    if logger.level == logging.NOTSET:
        logger.setLevel(logging.DEBUG)

    class WithLoggerResultHandler(DecoratorResultHandlerBase):
        """Container returned by `with_timer` to carry result and elapsed_ms."""

        def __init__(self, result, func_name: str) -> None:
            super().__init__(result=result, func_name=func_name)

        def write_to_logger(self, logger: logging.Logger) -> None:
            if self.result is not None:
                logger.debug(f"Returned: '{self.result}'")

    @wraps(func)
    def inner(*args, **kwargs):
        logger.debug(
            f"Start running {func.__name__} with args: {args}, kwargs: {kwargs}")
        result = func(*args, **kwargs, logger=logger)
        logger.debug(f"Finished running {func.__name__}")

        final_result = WithLoggerResultHandler(result=result,
                                               func_name=func.__name__)
        while isinstance(final_result, DecoratorResultHandlerBase):
            final_result.write_to_logger(logger)
            final_result = final_result.result

        return final_result

    return inner


def with_timer(func):
    """Decorator that measures execution time and returns timing metadata.

    This decorator returns a `WithTimerResultHandler` so that an outer
    decorator like `with_logger` can log the elapsed time. The elapsed time
    is returned in milliseconds.
    """
    class WithTimerResultHandler(DecoratorResultHandlerBase):
        """Container returned by `with_timer` to carry result and elapsed_ms."""

        def __init__(self, result, func_name: str, elapsed_ms: float) -> None:
            super().__init__(result=result, func_name=func_name)
            self.elapsed_ms = elapsed_ms

        def write_to_logger(self, logger: logging.Logger) -> None:
            logger.info(f"{self.func_name} took {self.elapsed_ms:.3f}ms")

    @wraps(func)
    def inner(*args, **kwargs):
        start = time.perf_counter()
        result = func(*args, **kwargs)
        end = time.perf_counter()
        return WithTimerResultHandler(result=result, func_name=func.__name__, elapsed_ms=(end - start) * 1000.0)

    return inner
