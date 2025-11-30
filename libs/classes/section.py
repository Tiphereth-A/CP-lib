import os
from typing import IO

from libs.decorator import withlog


class Section:
    def __init__(self, chapter: str, filename_without_ext: str = '', title: str = '', code_ext: str = '',
                 usage_ext: str = ''):
        self.name = filename_without_ext
        self.title = title
        self.chapter = chapter
        self.code_ext = code_ext
        self.usage_ext = usage_ext

    @withlog
    def parse_from_dict(self, dict_section: dict, **kwargs):
        """Parse section data from a dictionary."""
        logger = kwargs.get('logger')

        # Extract required fields
        self.code_ext = dict_section.pop('code_ext')
        self.usage_ext = dict_section.pop('usage_ext')

        # Should have exactly one remaining key-value pair (name: title)
        if len(dict_section) != 1:
            logger.error(
                f"Invalid section config {dict_section}: "
                f"expected exactly one file candidate, got {len(dict_section)}"
            )
            raise KeyError("Invalid section configuration")

        # Extract name and title
        self.name, self.title = next(iter(dict_section.items()))
        if not self.title:
            logger.warning(
                f"{self.name}'s title name not found, use '{self.name}' instead"
            )
            self.title = self.name

        return self

    def get_dict(self) -> dict:
        return {self.name: self.title, 'code_ext': self.code_ext, 'usage_ext': self.usage_ext}

    def get_filenames(self, code_root_dir: str, doc_root_dir: str, cvdoc_root_dir: str, usage_root_dir: str) -> tuple[str, str, str, str]:
        """Get filenames for all section files, creating directories if needed."""
        dirs = [
            os.path.join(code_root_dir, self.chapter),
            os.path.join(doc_root_dir, self.chapter),
            os.path.join(cvdoc_root_dir, self.chapter),
            os.path.join(usage_root_dir, self.chapter)
        ]

        for dir_path in dirs:
            os.makedirs(dir_path, exist_ok=True)

        return (
            os.path.join(dirs[0], f"{self.name}.{self.code_ext}"),
            os.path.join(dirs[1], f"{self.name}.tex"),
            os.path.join(dirs[2], f"{self.name}.md"),
            os.path.join(dirs[3], f"{self.name}.{self.usage_ext}")
        )

    def open(self, code_root_dir: str, doc_root_dir: str, cvdoc_root_dir: str, usage_root_dir: str, *args, **kwargs) -> tuple[IO, IO, IO, IO]:
        """
        Open all section files and return file handles.
        Note: Caller is responsible for closing these files.
        """
        code_path, doc_path, cvdoc_path, usage_path = self.get_filenames(
            code_root_dir, doc_root_dir, cvdoc_root_dir, usage_root_dir)

        f_code = open(code_path, *args, **kwargs)
        f_doc = open(doc_path, *args, **kwargs)
        f_cvdoc = open(cvdoc_path, *args, **kwargs)
        f_usage = open(usage_path, *args, **kwargs)
        return f_code, f_doc, f_cvdoc, f_usage
