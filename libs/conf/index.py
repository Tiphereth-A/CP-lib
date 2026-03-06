import os

from libs.conf.base import ConfigBase
from libs.decorator import with_logger


class ConfigIndex(ConfigBase):
    def __init__(self, conf_path: str):
        super().__init__(conf_path)
        if self._config is None:
            self._config = []

    def _get_section_list_raw(self) -> list[dict[str, str]]:
        return self._config

    @with_logger
    def get_section_list(self, **kwargs) -> list[tuple[str, str]]:
        return [(list(dic.keys())[0], list(dic.values())[0]) for dic in self._get_section_list_raw()]

    @with_logger
    def get_section_name(self, **kwargs) -> set[str]:
        return set(i[0] for i in self.get_section_list())

    @with_logger
    def new_section(self, name: str, title: str, **kwargs) -> bool:
        logger = kwargs.get('logger')
        if name in self.get_section_name():
            logger.warning(f"section '{name}' already exists, skip")
            return False
        self._config.append({name: title})
        os.makedirs(os.path.join(os.path.dirname(
            self._conf_path), name), exist_ok=True)
        self.output()
        return True
