from libs.classes.config_base import ConfigBase
from libs.classes.section import Section
from libs.decorator import withlog


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

    def _get_notebook_file_raw(self) -> str:
        return self.items('notebook_file')

    def _get_export_usage_code_in_notebook_raw(self) -> bool:
        return self.items('export_usage_code_in_notebook')

    def _get_default_code_style_raw(self) -> str:
        return self.items('default_code_style')

    def _get_code_styles_raw(self) -> dict[str, str]:
        return self.items('code_styles')

    def _get_run_usage_commands_raw(self) -> dict[str, list[str]]:
        return self.items('run_usage_commands')

    def _get_formatting_commands_raw(self) -> dict[str, list[str]]:
        return self.items('formatting_commands')

    @withlog
    def get_code_dir(self, **kwargs) -> str:
        return self._get_code_dir_raw()

    @withlog
    def get_doc_dir(self, **kwargs) -> str:
        return self._get_doc_dir_raw()

    @withlog
    def get_cvdoc_dir(self, **kwargs) -> str:
        return self._get_cvdoc_dir_raw()

    @withlog
    def get_cheatsheet_dir(self, **kwargs) -> str:
        return self._get_cheatsheet_dir_raw()

    @withlog
    def get_usage_dir(self, **kwargs) -> str:
        return self._get_usage_dir_raw()

    @withlog
    def get_notebook_file(self, **kwargs) -> str:
        return self._get_notebook_file_raw()

    @withlog
    def get_chapter_key(self, **kwargs) -> list[str]:
        return list(self._get_chapters_raw().keys())

    @withlog
    def get_chapter_title(self, chapter: str, **kwargs) -> str:
        try:
            return self._get_chapters_raw()[chapter]
        except KeyError:
            kwargs.get('logger').warning(
                rf"title name of chapter '{chapter}' is not found, use '{chapter}' instead")
            return chapter

    @withlog
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

    @withlog
    def set_sections_by_chapter(self, chapter: str, sections: list[Section], **kwargs):
        try:
            self._get_sections_raw()[chapter]
        except KeyError:
            kwargs.get('logger').warning(
                f"chapter with key '{chapter}' is not found, try to generate one")
            self.append_chapter(chapter)

        self._get_sections_raw()[chapter] = [sec.get_dict()
                                             for sec in sections]

    @withlog
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

    @withlog
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

    @withlog
    def get_cheatsheets(self, **kwargs) -> list[str]:
        return list(self._get_cheatsheet_raw().keys())

    @withlog
    def get_cheatsheet_name(self, cheatsheet: str, **kwargs) -> str:
        try:
            return self._get_cheatsheet_raw()[cheatsheet]
        except KeyError:
            kwargs.get('logger').warning(
                rf"title name of cheatsheet section '{cheatsheet}' is not found, use '{cheatsheet}' instead")
            return cheatsheet

    @withlog
    def export_usage_code_in_notebook(self, **kwargs) -> bool:
        return self._get_export_usage_code_in_notebook_raw()

    @withlog
    def get_default_code_style(self, **kwargs) -> str:
        return self._get_default_code_style_raw()

    @withlog
    def get_code_style(self, extname: str, **kwargs) -> str:
        """Get code style for extension name."""
        code_styles = self._get_code_styles_raw()
        return code_styles.get(extname, self.get_default_code_style())

    @withlog
    def get_all_code_styles(self, **kwargs) -> set[str]:
        return set(self._get_code_styles_raw().values())

    @withlog
    def get_all_code_ext_names(self, **kwargs) -> set[str]:
        return set(self._get_code_styles_raw().keys())

    @withlog
    def get_ext_names_by_code_style(self, code_style: str, **kwargs) -> list[str]:
        """Get all extension names for a given code style."""
        code_styles = self._get_code_styles_raw()
        return [ext for ext, style in code_styles.items() if style == code_style]

    @withlog
    def get_run_usage_command(self, code_style: str, filepath: str, **kwargs) -> list[str]:
        """Get run usage command for a code style, replacing ${filename} placeholder."""
        logger = kwargs.get('logger')
        try:
            result = self._get_run_usage_commands_raw()[code_style].copy()
            return [
                filepath if item == '${filename}' else item
                for item in result
            ]
        except KeyError:
            logger.warning(
                f"run_usage command of code style '{code_style}' is not found, return empty command"
            )
            return []

    @withlog
    def get_formatting_command(self, code_style: str, filepath: str, **kwargs) -> list[str]:
        """Get formatting command for a code style, replacing ${filename} placeholder."""
        logger = kwargs.get('logger')
        try:
            result = self._get_formatting_commands_raw()[code_style].copy()
            return [
                filepath if item == '${filename}' else item
                for item in result
            ]
        except KeyError:
            logger.warning(
                f"formatting command of code style '{code_style}' is not found, return empty command"
            )
            return []
