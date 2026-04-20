import click
import pytest
import yaml
from click.testing import CliRunner
from unittest.mock import patch

from libs.cmd.cpv_doc import cpv_doc, _register_cpv_doc


def _write_index_md(path, yml_dict, tail='\n# tail\n'):
    with open(path, 'w', encoding='utf-8') as f:
        f.write(f"---\n{yaml.safe_dump(yml_dict, sort_keys=False)}---{tail}")


@pytest.mark.unit
class TestPatchCpvdoc:
    def test_cpv_doc_merges_categories_and_sets_filename(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        src_dir = tmp_path / 'src'
        jekyll_dir = tmp_path / '_jekyll'
        src_dir.mkdir()
        jekyll_dir.mkdir()

        index_md = jekyll_dir / 'index.md'
        yml_dict = {
            'data': {
                'top': [
                    {
                        'categories': [
                            {
                                'name': 'src/math/gcd/',
                                'pages': [
                                    {
                                        'path': 'src/math/gcd/lib.hpp',
                                        'title': 'gcd',
                                        'filename': 'lib.hpp',
                                    },
                                ],
                            },
                            {
                                'name': 'src/math/lcm/',
                                'pages': [
                                    {
                                        'path': 'src/math/lcm/lib.hpp',
                                        'title': 'lcm',
                                        'filename': 'lib.hpp',
                                    },
                                ],
                            },
                            {
                                'name': 'extra/',
                                'pages': [
                                    {
                                        'path': 'extra/note.md',
                                        'title': 'note',
                                        'filename': 'note.md',
                                    },
                                ],
                            },
                        ],
                    }
                ]
            }
        }
        _write_index_md(index_md, yml_dict)

        cpv_doc('src', '_jekyll')

        content = index_md.read_text(encoding='utf-8')
        sections = content.split('---', 2)
        patched = yaml.safe_load(sections[1])

        expected = {
            'data': {
                'top': [
                    {
                        'categories': [
                            {
                                'name': 'src/math/',
                                'pages': [
                                    {
                                        'path': 'src/math/gcd/lib.hpp',
                                        'title': 'gcd',
                                        'filename': 'gcd/lib.hpp',
                                    },
                                    {
                                        'path': 'src/math/lcm/lib.hpp',
                                        'title': 'lcm',
                                        'filename': 'lcm/lib.hpp',
                                    },
                                ],
                            },
                            {
                                'name': 'extra/',
                                'pages': [
                                    {
                                        'path': 'extra/note.md',
                                        'title': 'note',
                                        'filename': 'note.md',
                                    },
                                ],
                            },
                        ],
                    }
                ]
            }
        }
        assert patched == expected

    def test_cpv_doc_broken_yaml_filename_mismatch_logs_and_returns(self, tmp_path, monkeypatch, caplog):
        monkeypatch.chdir(tmp_path)
        src_dir = tmp_path / 'src'
        jekyll_dir = tmp_path / '_jekyll'
        src_dir.mkdir()
        jekyll_dir.mkdir()

        index_md = jekyll_dir / 'index.md'
        yml_dict = {
            'data': {
                'top': [
                    {
                        'categories': [
                            {
                                'name': 'src/math/gcd/',
                                'pages': [
                                    {
                                        'path': 'src/math/gcd/lib.hpp',
                                        'title': 'gcd',
                                        'filename': 'wrong.hpp',
                                    },
                                ],
                            }
                        ],
                    }
                ]
            }
        }
        _write_index_md(index_md, yml_dict)
        original = index_md.read_text(encoding='utf-8')

        cpv_doc('src', '_jekyll')

        assert 'broken YAML: name: src/math/gcd/, filename: wrong.hpp, but path: src/math/gcd/lib.hpp' in caplog.text
        assert index_md.read_text(encoding='utf-8') == original

    def test_cpv_doc_invalid_category_name_logs_and_returns(self, tmp_path, monkeypatch, caplog):
        monkeypatch.chdir(tmp_path)
        src_dir = tmp_path / 'src'
        jekyll_dir = tmp_path / '_jekyll'
        src_dir.mkdir()
        jekyll_dir.mkdir()

        index_md = jekyll_dir / 'index.md'
        yml_dict = {
            'data': {
                'top': [
                    {
                        'categories': [
                            {
                                'name': 'src/math/gcd',
                                'pages': [
                                    {
                                        'path': 'src/math/gcd/lib.hpp',
                                        'title': 'gcd',
                                        'filename': 'lib.hpp',
                                    },
                                ],
                            }
                        ],
                    }
                ]
            }
        }
        _write_index_md(index_md, yml_dict)
        original = index_md.read_text(encoding='utf-8')

        cpv_doc('src', '_jekyll')

        assert 'invalid category name: src/math/gcd (must end with /)' in caplog.text
        assert index_md.read_text(encoding='utf-8') == original

    def test_cpv_doc_invalid_front_matter_logs_and_returns(self, tmp_path, monkeypatch, caplog):
        monkeypatch.chdir(tmp_path)
        src_dir = tmp_path / 'src'
        jekyll_dir = tmp_path / '_jekyll'
        src_dir.mkdir()
        jekyll_dir.mkdir()

        index_md = jekyll_dir / 'index.md'
        original = 'no front matter here\n'
        index_md.write_text(original, encoding='utf-8')

        cpv_doc('src', '_jekyll')

        assert 'invalid index.md format: YAML front matter is required' in caplog.text
        assert index_md.read_text(encoding='utf-8') == original

    def test_register_cpv_doc_registers_and_invokes_command(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        src_dir = tmp_path / 'src'
        jekyll_dir = tmp_path / '_jekyll'
        src_dir.mkdir()
        jekyll_dir.mkdir()

        @click.group()
        def cli():
            pass

        _register_cpv_doc(cli)
        assert 'doc' in cli.commands

        runner = CliRunner()
        with patch('libs.cmd.cpv_doc.cpv_doc') as mock_cpv_doc:
            result = runner.invoke(
                cli,
                ['doc', '-s', 'src', '-j', '_jekyll'],
            )

        assert result.exit_code == 0
        mock_cpv_doc.assert_called_once_with('src', '_jekyll')
