import os
import yaml

from copy import deepcopy
from multipledispatch import dispatch
from typing import Iterable
from libs.decorator import with_logger


class ConfigBase:
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


class ConfigTcgen(ConfigBase):
    def __init__(self, conf_path: str):
        super().__init__(conf_path, readonly=True)

    def __check_categories_priorities(self, categories: list[str]):
        if not categories:
            return
        priorities = [self.get_priority(cat) for cat in categories]
        if len(set(priorities)) != 1:
            _ = RuntimeError('Priorities not in same')
            _.add_note(f"categories: '{categories}'")
            _.add_note(f"priorities: '{priorities}'")
            raise _

    def _get_categories_raw(self) -> Iterable[str]:
        return self._config.keys()

    def _get_priority_raw(self, category: str) -> int:
        return self.items(category, 'priority')

    def _get_categories_by_priority_raw(self, priority: int) -> list[str]:
        return list(filter(lambda cat: self._get_priority_raw(cat) == priority, self._get_categories_raw()))

    @dispatch(str)
    def _get_memberlist_raw(self, category: str) -> list[tuple[str, str]]:
        return [(category, mem) for mem in self.items(category, 'member').keys()]

    @dispatch(list)
    def _get_memberlist_raw(self, categories: list[str]) -> list[tuple[str, str]]:
        self.__check_categories_priorities(categories)
        result = []
        for cat in categories:
            result.extend(self._get_memberlist_raw(cat))
        return result

    @dispatch(str, str)
    def _get_member_content_raw(self, category: str, member: str) -> dict:
        content = deepcopy(self.items(category, 'default_content'))
        member_content = deepcopy(self.items(category, 'member', member))
        if not content:
            content = deepcopy(member_content)
        if not content:
            raise RuntimeError(
                f"member '{member}' is invalid in category '{category}'")

        content.update(category_name=category)
        content.update(member_name=member)
        if member_content:
            for (k, v) in member_content.items():
                content[k] = v
        return content

    @dispatch(list, str)
    def _get_member_content_raw(self, categories: list[str], member: str) -> dict:
        """Get member content by trying each category until one succeeds."""
        for category in categories:
            try:
                return self._get_member_content_raw(category, member)
            except (KeyError, RuntimeError):
                continue
        raise RuntimeError(
            f"member '{member}' is invalid in categories '{categories}'"
        )

    @with_logger
    def get_categories(self, **kwargs) -> list[str]:
        return self._get_categories_raw()

    @with_logger
    def get_priority(self, category: str, **kwargs) -> int:
        return self._get_priority_raw(category)

    @with_logger
    def get_categories_by_priority(self, priority: int, **kwargs) -> list[str]:
        return self._get_categories_by_priority_raw(priority)

    @with_logger
    def get_categories_with_same_priority(self, category: str, **kwargs) -> list[str]:
        return self._get_categories_by_priority_raw(self._get_priority_raw(category))

    @with_logger
    def get_memberlist(self, category: str | list[str], **kwargs) -> list[tuple[str, str]]:
        return self._get_memberlist_raw(category)

    @with_logger
    def get_member_content(self, category: str, member: str, **kwargs) -> dict:
        return self._get_member_content_raw(category, member)
