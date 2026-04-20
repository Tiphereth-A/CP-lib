import os

from click.testing import CliRunner
import pytest

from libs.cmd.doc import gen_tex, gen_typst
from libs.content.tree import ContentTree

from .helpers import make_src_tree


@pytest.mark.unit
class TestDocCommands:
    def test_gen_typst_raises(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        with pytest.raises(AssertionError):
            gen_typst(tree)

    def test_gen_tex_runs(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        tree = ContentTree('src')
        os.makedirs('temp', exist_ok=True)
        gen_tex(tree, 'temp')
        assert os.path.exists(os.path.join('temp', 'src', 'math', 'doc.tex'))

    def test_doc_cli_tex(self, cli, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        os.makedirs('temp', exist_ok=True)
        runner = CliRunner()
        result = runner.invoke(cli, ['doc', '-s', 'src', '-t', 'tex', '-T', 'temp'])
        assert result.exit_code == 0

    def test_doc_cli_typ_raises(self, cli, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        os.makedirs('temp', exist_ok=True)
        runner = CliRunner()
        result = runner.invoke(cli, ['doc', '-s', 'src', '-t', 'typ', '-T', 'temp'])
        assert result.exit_code != 0

    def test_gen_tex_with_chapter_doc_tex(self, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        # Add a doc.tex at the math chapter level with {content} placeholder
        with open(os.path.join(str(tmp_path), 'src', 'math', 'doc.tex'), 'w') as f:
            f.write('% {content}\n')
        tree = ContentTree('src')
        os.makedirs('temp', exist_ok=True)
        gen_tex(tree, 'temp')
        result_path = os.path.join('temp', 'src', 'math', 'doc.tex')
        assert os.path.exists(result_path)

    def test_doc_unsupported_type_raises(self, cli, tmp_path, monkeypatch):
        monkeypatch.chdir(tmp_path)
        make_src_tree(str(tmp_path))
        doc_cmd = cli.commands['doc']
        with pytest.raises(ValueError, match='Unsupported document type'):
            doc_cmd.callback(src='src', type='unsupported', temp_path='temp')
