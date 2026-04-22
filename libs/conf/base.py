from pathlib import Path
import yaml
from abc import ABC


class ConfigBase(ABC):
    def __init__(self, conf_path: Path, readonly: bool = False):
        self._conf_path = conf_path
        self._config: dict = {}
        self._readonly = readonly
        self.reload()

    def __repr__(self) -> str:
        return f"{self.__class__.__name__}(path={self._conf_path}, config={self._config})"

    def reload(self):
        if not self._conf_path.exists():
            raise PermissionError(f"{self._conf_path} is inaccessible")
        self._config = yaml.safe_load(
            self._conf_path.read_text(encoding='utf8'))

    def output(self):
        if self._readonly:
            raise AssertionError(f"{self._conf_path} is readonly")
        self._conf_path.write_text(
            yaml.dump(self._config, sort_keys=False, allow_unicode=True),
            encoding='utf8'
        )

    def items(self, *args: str):
        result = self._config
        for arg in args:
            result = result[arg]
        return result
