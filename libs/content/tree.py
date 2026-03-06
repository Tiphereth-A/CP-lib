import os

from libs.conf import ConfigIndex
from libs.content import Section
from libs.decorator import with_logger


class ContentTree:
    class Node:
        def __init__(self, name: str, father=None):
            self._name: str = name
            self._title: str = name
            self._father: ContentTree.Node | None = father
            self._children: dict[str, ContentTree.Node] = {}
            self._config_path: str | None = None  # only for non-leaf node
            self._config: ConfigIndex | None = None  # only for non-leaf node
            self._section: Section | None = None  # only for leaf node

        def __repr__(self) -> str:
            return f"ContentTree.Node(name={self._name}, title={self._title}, father={self._father._name if self._father else None}, children={[child for child in self._children]})"

        def _add_child(self, child_name: str) -> 'ContentTree.Node':
            if child_name in self._children:
                return self._children[child_name]
            new_node = ContentTree.Node(child_name, father=self)
            self._children[child_name] = new_node
            return new_node

        @with_logger
        def _load_config(self, **kwargs):
            if not self._children:
                raise RuntimeError(
                    f"node '{self.fullname()}' is a leaf node, no config to load")
            if self._config is not None:
                self._config.output()
            self._config_path = os.path.join(
                *self.fullname().split('.'), 'index.yml')
            if not os.path.exists(self._config_path):
                with open(self._config_path, 'w', encoding='utf8') as f:
                    pass
            self._config = ConfigIndex(self._config_path)

        @with_logger
        def _load_section(self, **kwargs):
            if self._children:
                raise RuntimeError(
                    f"node '{self.fullname()}' is not a leaf node, no section to load")
            self._section = Section(os.path.join(
                *self.fullname().split('.')), self._title)

        @with_logger
        def _sync_file(self, **kwargs):
            if not self._children:
                self._load_section()
            else:
                self._load_config()
                for child in self._children.values():
                    if child._name not in self._config.get_section_name():
                        self._config.new_section(child._name, child._title)

        def fullname(self) -> str:
            return self._name if self._father is None else self._father.fullname() + '.' + self._name

        def get_config(self) -> ConfigIndex:
            if self._config is None:
                self._load_config()
            return self._config

        def get_section(self) -> Section:
            if self._section is None:
                self._load_section()
            return self._section

    def __init__(self, start_path: str):
        self.root: ContentTree.Node = self.Node(start_path)
        for root, _, files in os.walk(start_path):
            if 'index.yml' in files:
                sections = ConfigIndex(os.path.join(
                    root, 'index.yml')).get_section_list()
                for name, title in sections:
                    self.touch(os.path.join(
                        *root.split(os.sep)[1:], name).replace(os.sep, '.'), title)

    @with_logger
    def touch(self, fullname: str, title: str = '', **kwargs) -> Node:
        if not title:
            title = fullname.split('.')[-1]
        current_node = self.root
        for node_name in fullname.split('.'):
            current_node = current_node._add_child(node_name)
        current_node._title = title
        current_node = self.root
        for node_name in fullname.split('.'):
            current_node = current_node._children[node_name]
            current_node._sync_file()
        return current_node
