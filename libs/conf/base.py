import os
import yaml
from abc import ABC


class ConfigBase(ABC):
    def __init__(self, conf_path: str, readonly: bool = False):
        self._conf_path = conf_path
        self._config: dict = {}
        self._readonly = readonly
        self.reload()

    def __repr__(self) -> str:
        return f"{self.__class__.__name__}(path={self._conf_path}, config={self._config})"

    def reload(self):
        if not os.access(self._conf_path, os.R_OK):
            raise PermissionError(f"{self._conf_path} is inaccessible")
        with open(self._conf_path, 'r', encoding='utf8') as f:
            self._config = yaml.safe_load(f)

    def output(self):
        if self._readonly:
            raise AssertionError(f"{self._conf_path} is readonly")
        if not os.access(self._conf_path, os.W_OK):
            raise PermissionError(f"{self._conf_path} is inaccessible")
        with open(self._conf_path, 'w', encoding='utf8') as f:
            yaml.dump(self._config, f, sort_keys=False, allow_unicode=True)

    def items(self, *args: str):
        result = self._config
        for arg in args:
            result = result[arg]
        return result
