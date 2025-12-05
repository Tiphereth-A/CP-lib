import os
import shlex
from libs.classes.config_base import ConfigBase
from libs.classes.section import Section
from libs.decorator import with_logger


class Config(ConfigBase):
    def __init__(self, conf_path: str):
        super().__init__(conf_path)

    def _get_chapters_raw(self) -> dict[str, str]:
        return self.items('notebook', 'chapters')

    def _get_sections_raw(self) -> dict:
        return self.items('notebook', 'sections')

    def _get_cheatsheet_raw(self) -> dict[str, str]:
        return self.items('cheatsheets')

    def _get_code_dir_raw(self) -> str:
        return self.items('notebook_code_dir')

    def _get_doc_dir_raw(self) -> str:
        return self.items('notebook_doc_dir')

    def _get_cvdoc_dir_raw(self) -> str:
        return self.items('competitive_verifier_doc_dir')

    def _get_cheatsheet_dir_raw(self) -> str:
        return self.items('cheatsheet_dir')

    def _get_usage_dir_raw(self) -> str:
        return self.items('usage_dir')

    def _get_notebook_file_dir_raw(self) -> str:
        return self.items('notebook_file_dir')

    def _get_notebook_file_raw(self) -> str:
        return self.items('notebook_file')

    def _get_export_usage_code_in_notebook_raw(self) -> bool:
        return self.items('export_usage_code_in_notebook')

    def _get_default_file_type_raw(self) -> str:
        return self.items('default_file_type')

    def _get_file_types_raw(self) -> dict[str, str]:
        return self.items('file_types')

    def _get_run_usage_commands_raw(self) -> dict[str, str]:
        return self.items('run_usage_commands')

    def _get_formatting_commands_raw(self) -> dict[str, str]:
        return self.items('formatting_commands')

    def _get_code_type_list_raw(self) -> list[str]:
        return self.items('code_type_list')

    def _get_doc_type_list_raw(self) -> list[str]:
        return self.items('doc_type_list')

    @with_logger
    def get_code_dir(self, **kwargs) -> str:
        return self._get_code_dir_raw()

    @with_logger
    def get_doc_dir(self, **kwargs) -> str:
        return self._get_doc_dir_raw()

    @with_logger
    def get_cvdoc_dir(self, **kwargs) -> str:
        return self._get_cvdoc_dir_raw()

    @with_logger
    def get_cheatsheet_dir(self, **kwargs) -> str:
        return self._get_cheatsheet_dir_raw()

    @with_logger
    def get_usage_dir(self, **kwargs) -> str:
        return self._get_usage_dir_raw()

    @with_logger
    def get_notebook_file_dir(self, **kwargs) -> str:
        return self._get_notebook_file_dir_raw()

    @with_logger
    def get_notebook_file(self, **kwargs) -> str:
        return self._get_notebook_file_raw()

    @with_logger
    def get_chapter_key(self, **kwargs) -> list[str]:
        return list(self._get_chapters_raw().keys())

    @with_logger
    def get_chapter_title(self, chapter: str, **kwargs) -> str:
        try:
            return self._get_chapters_raw()[chapter]
        except KeyError:
            kwargs.get('logger').warning(
                rf"title name of chapter '{chapter}' is not found, use '{chapter}' instead")
            return chapter

    @with_logger
    def get_sections_by_chapter(self, chapter: str, **kwargs) -> list[Section]:
        """Get all sections for a chapter."""
        logger = kwargs.get('logger')
        sections_raw: list[dict] = self._get_sections_raw().get(chapter, [])

        if not sections_raw:
            logger.warning(
                f"No section config found with chapter key '{chapter}'")
            return []

        # Use list comprehension for better performance
        return [Section(chapter).parse_from_dict(item) for item in sections_raw]

    @with_logger
    def set_sections_by_chapter(self, chapter: str, sections: list[Section], **kwargs):
        try:
            self._get_sections_raw()[chapter]
        except KeyError:
            kwargs.get('logger').warning(
                f"chapter with key '{chapter}' is not found, try to generate one")
            self.append_chapter(chapter)

        self._get_sections_raw()[chapter] = [sec.get_dict()
                                             for sec in sections]

    @with_logger
    def append_chapter(self, chapter: str, **kwargs):
        """Append a new chapter to the config."""
        logger = kwargs.get('logger')
        chapter_keys = self.get_chapter_key()

        if chapter in chapter_keys:
            logger.warning(
                f"chapter with key '{chapter}' already exists, skipped")
            return

        self._get_chapters_raw().update({chapter: chapter})
        self._get_sections_raw().update({chapter: []})
        self.output()

    @with_logger
    def append_section(self, section: Section, **kwargs):
        """Append a new section to a chapter."""
        logger = kwargs.get('logger')
        sections = self.get_sections_by_chapter(section.chapter)

        # Check if section already exists
        existing_names = {sec.name for sec in sections}
        if section.name in existing_names:
            logger.warning(
                f"section with key '{section.name}' already exists, skipped")
            return

        sections.append(section)
        self.set_sections_by_chapter(section.chapter, sections)
        self.output()

    @with_logger
    def get_cheatsheets(self, **kwargs) -> list[str]:
        return list(self._get_cheatsheet_raw().keys())

    @with_logger
    def get_cheatsheet_name(self, cheatsheet: str, **kwargs) -> str:
        try:
            return self._get_cheatsheet_raw()[cheatsheet]
        except KeyError:
            kwargs.get('logger').warning(
                rf"title name of cheatsheet section '{cheatsheet}' is not found, use '{cheatsheet}' instead")
            return cheatsheet

    @with_logger
    def export_usage_code_in_notebook(self, **kwargs) -> bool:
        return self._get_export_usage_code_in_notebook_raw()

    @with_logger
    def get_default_file_type(self, **kwargs) -> str:
        return self._get_default_file_type_raw()

    @with_logger
    def get_file_type(self, extname: str, **kwargs) -> str:
        """Get file type for extension name."""
        file_types = self._get_file_types_raw()
        return file_types.get(extname, self.get_default_file_type())

    @with_logger
    def get_code_type_list(self, **kwargs) -> set[str]:
        return set(self._get_code_type_list_raw())

    @with_logger
    def get_doc_type_list(self, **kwargs) -> set[str]:
        return set(self._get_doc_type_list_raw())

    @with_logger
    def get_all_file_types(self, **kwargs) -> set[str]:
        return set(self._get_file_types_raw().values())

    @with_logger
    def get_all_code_ext_names(self, **kwargs) -> set[str]:
        return set(self._get_file_types_raw().keys())

    @with_logger
    def get_ext_names_by_file_type(self, file_type: str, **kwargs) -> list[str]:
        """Get all extension names for a given file type."""
        file_types = self._get_file_types_raw()
        return [ext for ext, style in file_types.items() if style == file_type]

    @with_logger
    def get_run_usage_command(self, file_type: str, src: str, **kwargs) -> list[str]:
        """Get run usage command for a file type, replacing {src} placeholder."""
        logger = kwargs.get('logger')
        if file_type not in self.get_code_type_list():
            logger.warning(
                f"'{file_type}' is not code type, return empty command")
            return []
        try:
            return shlex.split(self._get_run_usage_commands_raw()[file_type].format(src=shlex.quote(src)))
        except KeyError:
            logger.warning(
                f"run_usage command of file type '{file_type}' is not found, return empty command"
            )
            return []

    @with_logger
    def get_formatting_command(self, file_type: str, src: str, **kwargs) -> list[str]:
        """Get formatting command for a file type, replacing {src} placeholder."""
        logger = kwargs.get('logger')
        if file_type not in self.get_code_type_list() and \
                file_type not in self.get_doc_type_list():
            logger.warning(
                f"'{file_type}' is neither code type nor doc type, return empty command")
            return []
        try:
            return shlex.split(self._get_formatting_commands_raw()[file_type].format(src=shlex.quote(src)))
        except KeyError:
            logger.warning(
                f"formatting command of file type '{file_type}' is not found, return empty command"
            )
            return []

    @with_logger
    def get_compile_pdf_command(self, file_type: str, **kwargs) -> list[str]:
        """Get compile PDF command for a file type, replacing {src} {out} placeholder."""
        logger = kwargs.get('logger')
        if file_type not in self.get_doc_type_list():
            logger.warning(
                f"'{file_type}' is not doc type, return empty command")
            return []
        try:
            source = os.path.join(self._get_notebook_file_dir_raw(),
                                  f"{self._get_notebook_file_raw()}.{file_type}")
            command_line = self._get_compile_pdf_commands_raw()[file_type].format(
                src=shlex.quote(source))
            if command_line.find(r'{out}') != -1:
                pdf_path = os.path.join(
                    "_pdf_out", f"{self._get_notebook_file_raw()}.pdf")
                command_line = command_line.format(out=shlex.quote(pdf_path))
            return shlex.split(command_line)
        except KeyError:
            logger.warning(
                f"compiling PDF command of file type '{file_type}' is not found, return empty command"
            )
            return []
