from abc import ABC, abstractmethod
import logging


class DecoratorResultHandlerBase(ABC):
    def __init__(self, result, func_name: str):
        super().__init__()

        self.result = result
        self.func_name = func_name

    @abstractmethod
    def write_to_logger(self, logger: logging.Logger) -> None:
        ...
