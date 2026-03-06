import logging
from functools import wraps
from libs.decorator.result_handler import DecoratorResultHandlerBase
from libs.util.trailing_str import trailing_str


def with_logger(func):
    logger: logging.Logger = logging.getLogger(func.__name__)
    if logger.level == logging.NOTSET:
        logger.setLevel(logging.DEBUG)

    class WithLoggerResultHandler(DecoratorResultHandlerBase):
        def __init__(self, result, func_name: str) -> None:
            super().__init__(result=result, func_name=func_name)

        def write_to_logger(self, logger: logging.Logger) -> None:
            if self.result is not None:
                logger.debug(f"Returned: '{trailing_str(str(self.result))}'")

    @wraps(func)
    def inner(*args, **kwargs):
        logger.debug(
            f"Start running {func.__name__} with args: {trailing_str(str(args))}, kwargs: {trailing_str(str(kwargs))}")
        result = func(*args, **kwargs, logger=logger)
        logger.debug(f"Finished running {func.__name__}")

        final_result = WithLoggerResultHandler(result=result,
                                               func_name=func.__name__)
        while isinstance(final_result, DecoratorResultHandlerBase):
            final_result.write_to_logger(logger)
            final_result = final_result.result

        return final_result

    return inner
