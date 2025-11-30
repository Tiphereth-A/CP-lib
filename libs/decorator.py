import logging
from functools import wraps


def withlog(func):
    """Decorator that adds logging to a function."""
    logger: logging.Logger = logging.getLogger(func.__name__)
    if logger.level == logging.NOTSET:
        logger.setLevel(logging.DEBUG)

    @wraps(func)
    def inner(*args, **kwargs):
        logger.debug(
            f"Start running {func.__name__} with args: {args}, kwargs: {kwargs}")
        return_val = func(*args, **kwargs, logger=logger)
        logger.debug(f"Finished running {func.__name__}")
        if return_val is not None:
            logger.debug(f"Returned: '{return_val}'")
        return return_val

    return inner
