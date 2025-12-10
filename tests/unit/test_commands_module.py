"""Unit tests for command modules.

This module tests the various command modules including notebook generation,
cheatsheet generation, test code generation, and usage running.
"""

import os
import subprocess
from pathlib import Path
from typing import Any

import pytest

import libs.commands.gen_cs as gen_cs
import libs.commands.gen_nb as gen_nb
import libs.commands.gentc as gentc
import libs.commands.new as newmod
import libs.commands.run_usage as run_usage_mod
import libs.testcase_matrix as tm
from libs.classes.section import Section


pytestmark = pytest.mark.unit


# =============================================================================
# Helper Classes
# =============================================================================


class FakeConfig:
    """Fake config for testing command modules."""

    def __init__(self, base: Path) -> None:
        self.base = str(base)
        self._appended = False

    def get_chapter_key(self) -> list[str]:
        return ['c1']

    def get_sections_by_chapter(self, ch: str) -> list[Any]:
        return []

    def get_code_dir(self) -> str:
        return self.base

    def get_doc_dir(self, doc_type: str = 'tex') -> str:
        return self.base

    def get_cvdoc_dir(self) -> str:
        return self.base

    def get_usage_dir(self) -> str:
        return self.base

    def get_chapter_title(self, ch: str) -> str:
        return 'Title'

    def get_all_code_ext_names(self) -> list[str]:
        return ['.cpp']

    def get_cheatsheets(self) -> list[str]:
        return ['cs1']

    def get_cheatsheet_dir(self) -> str:
        return self.base

    def get_cheatsheet_name(self, name: str) -> str:
        return name.upper()

    def get_file_type(self, ext: str) -> str:
        return 'cs'

    def export_usage_code_in_notebook(self) -> bool:
        return True

    def append_section(self, sec: Section) -> None:
        self._appended = True

    def get_ext_names_by_file_type(self, code: str) -> list[str]:
        return ['in']

    def get_run_usage_command(self, code: str, filepath: str) -> list[str]:
        return ['echo', filepath]


# =============================================================================
# gen_nb Module Tests
# =============================================================================


class TestGenNbLoadFrom:
    """Tests for gen_nb.load_from function."""

    def test_no_duplicates(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test load_from with no duplicate files."""
        monkeypatch.setattr(
            gen_nb, 'scandir_file_merge',
            lambda exts, d: ['a.cpp', 'b.py']
        )
        monkeypatch.setattr(
            gen_nb, 'parse_filename',
            lambda fn: (fn.rsplit('.', 1)[0], fn.rsplit('.', 1)[1])
        )

        result = gen_nb.load_from('some_dir')
        assert isinstance(result, list)

    def test_debug_branch(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test load_from triggers debug logging with non-empty results."""
        monkeypatch.setattr(
            gen_nb, 'scandir_file_merge',
            lambda exts, d: ['x.cpp']
        )
        monkeypatch.setattr(
            gen_nb, 'parse_filename',
            lambda fn: (fn.rsplit('.', 1)[0], fn.rsplit('.', 1)[1])
        )

        result = gen_nb.load_from('some_dir')
        assert result

    def test_duplicates_raises(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test load_from raises FileExistsError for duplicates."""
        monkeypatch.setattr(
            gen_nb, 'scandir_file_merge',
            lambda exts, d: ['a.cpp', 'a.py']
        )
        monkeypatch.setattr(
            gen_nb, 'parse_filename',
            lambda fn: (fn.rsplit('.', 1)[0], fn.rsplit('.', 1)[1])
        )

        with pytest.raises(FileExistsError):
            gen_nb.load_from('d')


class TestGenerateNotebookContents:
    """Tests for notebook content generation."""

    def test_generate_notebook(
        self, tmp_path: Path, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """Test generating notebook contents."""
        fake = FakeConfig(tmp_path)
        monkeypatch.setattr(gen_nb, 'CONFIG', fake)
        monkeypatch.setattr(
            gen_nb, 'file_preprocess',
            lambda a, b, logger=None: ['c1']
        )
        monkeypatch.setattr(gen_nb, 'scandir_dir_merge', lambda a, b: [])
        monkeypatch.setattr(gen_nb, 'scandir_file_merge', lambda exts, d: [])

        gen_nb.generate_notebook_contents()

        contents_nb = os.path.join(gen_nb.CONTENTS_DIR, 'contents_notebook.tex')
        assert os.path.exists(contents_nb)


# =============================================================================
# gen_cs Module Tests
# =============================================================================


class TestGenerateCheatsheetContents:
    """Tests for cheatsheet content generation."""

    def test_generate_cheatsheet(
        self, tmp_path: Path, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """Test generating cheatsheet contents."""
        fake = FakeConfig(tmp_path)
        monkeypatch.setattr(gen_cs, 'CONFIG', fake)
        monkeypatch.setattr(
            gen_cs, 'scandir_file_merge',
            lambda exts, d: ['cs1.tex']
        )
        monkeypatch.setattr(
            gen_cs, 'file_preprocess',
            lambda a, b, logger=None: ['cs1.tex']
        )

        gen_cs.generate_cheatsheet_contents()

        contents_cs = os.path.join(gen_cs.CONTENTS_DIR, 'contents_cheatsheet.tex')
        assert os.path.exists(contents_cs)

    def test_generate_cheatsheet_with_subdir(
        self, tmp_path: Path, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """Test generating cheatsheet with subdirectory."""
        base = tmp_path / 'cheats'
        base.mkdir()
        sub = base / 'subdir'
        sub.mkdir()
        f = sub / 'mycs.tex'
        f.write_text('content', encoding='utf-8')

        class FakeCfgWithSubdir:
            def get_cheatsheets(self) -> list[str]:
                return ['subdir/mycs']

            def get_cheatsheet_dir(self) -> str:
                return str(base)

            def get_cheatsheet_name(self, name: str) -> str:
                return name.upper()

        monkeypatch.setattr(gen_cs, 'CONFIG', FakeCfgWithSubdir())
        monkeypatch.setattr(
            gen_cs, 'scandir_file_merge',
            lambda exts, d: ['subdir/mycs.tex']
        )

        gen_cs.generate_cheatsheet_contents()

        contents_cs = os.path.join(gen_cs.CONTENTS_DIR, 'contents_cheatsheet.tex')
        assert os.path.exists(contents_cs)


# =============================================================================
# gentc Module Tests
# =============================================================================


class TestGentcGenerateTestcode:
    """Tests for gentc.generate_testcode function."""

    def test_no_source_files(
        self, monkeypatch: pytest.MonkeyPatch, tmp_path: Path
    ) -> None:
        """Test generate_testcode with no source files."""
        monkeypatch.setattr(gentc, 'get_full_filenames', lambda paths, exts: [])
        # Should run without exception
        gentc.generate_testcode(str(tmp_path), str(tmp_path))

    def test_full_generate_and_remove_old(
        self, monkeypatch: pytest.MonkeyPatch, tmp_path: Path
    ) -> None:
        """Test full generation and removal of old files."""
        src = tmp_path / 'src'
        tgt = tmp_path / 'tgt'
        src.mkdir()
        tgt.mkdir()

        src_file = src / 'f.cppmeta'
        src_file.write_text(
            'header\n' + tm._GENTC_BEGIN + tm._GENTC_END + tm._GENTC_MAIN + '\n'
        )

        old_target = tgt / 'old.cpp'
        old_target.write_text('#define AUTO_GENERATED\nold', encoding='utf-8')

        def fake_get_full_filenames(paths: list[str], exts: list[str]) -> list[str]:
            if exts == ['cppmeta']:
                return [str(src_file)]
            if exts == ['cpp']:
                return [str(old_target)]
            return []

        monkeypatch.setattr(gentc, 'get_full_filenames', fake_get_full_filenames)

        class FakeParser:
            def __init__(self, noext: str, target_dir: str, lines: list[str]) -> None:
                self.target_dir = target_dir

            def get_results(self) -> list[tuple[str, list[str]]]:
                return [(
                    str(tgt / 'new.test.cpp'),
                    ['#define AUTO_GENERATED\n', 'int main(){}\n']
                )]

        monkeypatch.setattr(gentc, 'cppmeta_parser', FakeParser)

        gentc.generate_testcode(str(src), str(tgt))

        assert not old_target.exists()
        assert (tgt / 'new.test.cpp').exists()


# =============================================================================
# Section Writing Tests
# =============================================================================


class TestWriteSection:
    """Tests for section writing in gen_nb."""

    def test_write_section_hpp_and_usage(
        self, tmp_path: Path, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """Test writing section with hpp and usage files."""
        fake = FakeConfig(tmp_path)
        monkeypatch.setattr(gen_nb, 'CONFIG', fake)

        # Create files expected by section
        chdir = tmp_path / 'ch'
        chdir.mkdir()
        code_file = chdir / 'n.hpp'
        code_file.write_text('\n'.join('line' + str(i) for i in range(20)), encoding='utf-8')
        doc_file = chdir / 'n.tex'
        doc_file.write_text('doc', encoding='utf-8')
        usage_file = chdir / 'n.in'
        usage_file.write_text('u', encoding='utf-8')

        sec = Section('ch', 'n', 'MyTitle', 'hpp', 'in')
        out = tmp_path / 'out.tex'

        class MockLogger:
            def info(self, *args: Any, **kwargs: Any) -> None:
                pass

            def isEnabledFor(self, *args: Any, **kwargs: Any) -> bool:
                return False

            def debug(self, *args: Any, **kwargs: Any) -> None:
                pass

        with open(out, 'w', encoding='utf-8') as f:
            gen_nb._write_section(f, sec, logger=MockLogger())

        txt = out.read_text(encoding='utf-8')
        assert 'inputminted' in txt or 'Path:' in txt


class TestGenerateSectionsFromFiles:
    """Tests for _generate_sections_from_files function."""

    def test_doc_and_code_sections(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """Test generating sections from doc and code files."""
        def fake_load(dir_name: str) -> list[tuple[str, str]]:
            if 'code' in dir_name:
                return [('a', 'cpp'), ('b', 'cpp')]
            if 'doc' in dir_name:
                return [('a', 'tex')]
            if 'usage' in dir_name:
                return [('b', 'in')]
            return []

        monkeypatch.setattr(gen_nb, 'load_from', fake_load)

        class FakeCfg:
            def get_code_dir(self) -> str:
                return 'code'

            def get_doc_dir(self, doc_type: str = 'tex') -> str:
                return 'doc'

            def get_usage_dir(self) -> str:
                return 'usage'

        monkeypatch.setattr(gen_nb, 'CONFIG', FakeCfg())

        class MockLogger:
            def info(self, *args: Any, **kwargs: Any) -> None:
                pass

            def debug(self, *args: Any, **kwargs: Any) -> None:
                pass

        result = gen_nb._generate_sections_from_files('ch', logger=MockLogger())
        assert any(s.name == 'a' for s in result)


# =============================================================================
# new and run_usage Module Tests
# =============================================================================


class TestNewAndRunUsage:
    """Tests for new and run_usage modules."""

    def test_add_new_note(
        self, tmp_path: Path, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """Test adding a new note."""
        fake = FakeConfig(tmp_path)
        monkeypatch.setattr(newmod, 'CONFIG', fake)

        newmod.add_new_note('ch', 'f', 'T', 'cpp', 'in')
        # CVDoc should be created (tested by the function not raising)

    def test_run_usage_codes(
        self, tmp_path: Path, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """Test running usage codes."""
        fake = FakeConfig(tmp_path)
        monkeypatch.setattr(run_usage_mod, 'CONFIG', fake)

        p1 = tmp_path / 'u1.in'
        p1.write_text('x')

        monkeypatch.setattr(
            run_usage_mod, 'get_full_filenames',
            lambda paths, exts: [str(p1)]
        )

        calls: list[list[str]] = []

        def fake_run(cmd: list[str], **kwargs: Any) -> None:
            calls.append(cmd)

        monkeypatch.setattr(subprocess, 'run', fake_run)

        run_usage_mod.run_usage_codes('code', 2)
        assert calls
