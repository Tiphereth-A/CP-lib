import os
import yaml


class ConfigBase:
    def __init__(self, conf_path: str):
        self.__conf_path = conf_path
        self._config: dict = {}
        self.reload()

    def __str__(self) -> str:
        return str(self._config)

    def reload(self):
        if not os.access(self.__conf_path, os.R_OK):
            raise PermissionError(f"{self.__conf_path} is inaccessible")
        with open(self.__conf_path, 'r', encoding='utf8') as f:
            self._config = yaml.safe_load(f)

    def output(self):
        if not os.access(self.__conf_path, os.W_OK):
            raise PermissionError(f"{self.__conf_path} is inaccessible")
        with open(self.__conf_path, 'w', encoding='utf8') as f:
            yaml.dump(self._config, f, sort_keys=False, allow_unicode=True)

    def items(self, *args: str):
        result = self._config
        for arg in args:
            result = result[arg]
        return result
