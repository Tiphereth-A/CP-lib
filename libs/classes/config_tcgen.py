from copy import deepcopy
from libs.classes.config_base import ConfigBase
from libs.decorator import withlog
from multipledispatch import dispatch


class ConfigTCGen(ConfigBase):
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

    def _get_categories_raw(self) -> list[str]:
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
        for category in categories:
            try:
                return self._get_member_content_raw(category, member)
            except:
                pass
        raise RuntimeError(
            f"member '{member}' is invalid in categories '{categories}'")

    @withlog
    def get_categories(self, **kwargs) -> list[str]:
        return self._get_categories_raw()

    @withlog
    def get_priority(self, category: str, **kwargs) -> int:
        return self._get_priority_raw(category)

    @withlog
    def get_categories_by_priority(self, priority: int, **kwargs) -> int:
        return self._get_categories_by_priority_raw(priority)

    @withlog
    def get_categories_with_same_priority(self, category: str, **kwargs) -> int:
        return self._get_categories_by_priority_raw(self._get_priority_raw(category))

    @withlog
    def get_memberlist(self, category: str | list[str], **kwargs) -> list[tuple[str, str]]:
        return self._get_memberlist_raw(category)

    @withlog
    def get_member_content(self, category: str, member: str, **kwargs) -> dict:
        return self._get_member_content_raw(category, member)
