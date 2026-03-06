import logging
import time
from functools import wraps
from libs.decorator.result_handler import DecoratorResultHandlerBase


def with_timer(func):
    class WithTimerResultHandler(DecoratorResultHandlerBase):
        def __init__(self, result, func_name: str, elapsed_ms: float) -> None:
            super().__init__(result=result, func_name=func_name)
            self.elapsed_ms = elapsed_ms

        def write_to_logger(self, logger: logging.Logger) -> None:
            logger.debug(f"{self.func_name} took {self.elapsed_ms:.3f}ms")

    @wraps(func)
    def inner(*args, **kwargs):
        start = time.perf_counter()
        result = func(*args, **kwargs)
        end = time.perf_counter()
        return WithTimerResultHandler(result=result, func_name=func.__name__, elapsed_ms=(end - start) * 1000.0)

    return inner
