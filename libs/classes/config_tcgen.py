import os


from libs.classes.config_base import ConfigBase
from libs.decorator import withlog


class ConfigTCGen(ConfigBase):
    def __init__(self, conf_path: str):
        super().__init__(conf_path)

    def _get_keys_raw(self):
        return self._config.keys()

    def _get_content_raw(self, key: str):
        return self._config[key]

    @withlog
    def get_keys(self, **kwargs):
        return self._get_keys_raw()

    @withlog
    def get_content(self, key: str, **kwargs) -> str:
        return self._get_content_raw(key)
