import os
import subprocess

import libs.commands.gen_nb as gen_nb
import libs.commands.gen_cs as gen_cs
import libs.commands.compile_pdf as compile_mod
import libs.commands.gentc as gentc
import libs.commands.new as newmod
import libs.commands.run_usage as run_usage_mod
import libs.testcase_matrix as tm


def test_load_from_no_duplicates(monkeypatch):
    # monkeypatch scandir_file_merge to return filenames
    monkeypatch.setattr(gen_nb, 'scandir_file_merge',
                        lambda exts, d: ['a.cpp', 'b.py'])
    monkeypatch.setattr(gen_nb, 'parse_filename', lambda fn: (
        fn.rsplit('.', 1)[0], fn.rsplit('.', 1)[1]))
    # should not raise
    res = gen_nb.load_from('some_dir')
    assert isinstance(res, list)


def test_load_from_debug_branch(monkeypatch):
    # ensure scandir_file_merge returns non-empty to trigger debug logging
    monkeypatch.setattr(gen_nb, 'scandir_file_merge',
                        lambda exts, d: ['x.cpp'])
    monkeypatch.setattr(gen_nb, 'parse_filename', lambda fn: (
        fn.rsplit('.', 1)[0], fn.rsplit('.', 1)[1]))
    res = gen_nb.load_from('some_dir')
    assert res


def test_load_from_duplicates_raises(monkeypatch):
    monkeypatch.setattr(gen_nb, 'scandir_file_merge',
                        lambda exts, d: ['a.cpp', 'a.py'])
    monkeypatch.setattr(gen_nb, 'parse_filename', lambda fn: (
        fn.rsplit('.', 1)[0], fn.rsplit('.', 1)[1]))
    try:
        gen_nb.load_from('d')
        assert False, 'should have raised FileExistsError'
    except FileExistsError:
        pass


def test_generate_notebook_and_cheatsheet(tmp_path, monkeypatch):
    # fake CONFIG for both modules
    class FakeCfg:
        def __init__(self, base):
            self.base = str(base)

        def get_chapter_key(self):
            return ['c1']

        def get_sections_by_chapter(self, ch):
            return []

        def get_code_dir(self):
            return self.base

        def get_doc_dir(self):
            return self.base

        def get_cvdoc_dir(self):
            return self.base

        def get_usage_dir(self):
            return self.base

        def get_chapter_title(self, ch):
            return 'Title'

        def get_all_code_ext_names(self):
            return ['.cpp']

        def get_cheatsheets(self):
            return ['cs1']

        def get_cheatsheet_dir(self):
            return self.base

        def get_cheatsheet_name(self, name):
            return name.upper()

    fake = FakeCfg(tmp_path)
    monkeypatch.setattr(gen_nb, 'CONFIG', fake)
    monkeypatch.setattr(gen_nb, 'file_preprocess',
                        lambda a, b, logger=None: ['c1'])
    monkeypatch.setattr(gen_nb, 'scandir_dir_merge', lambda a, b: [])
    monkeypatch.setattr(gen_nb, 'scandir_file_merge', lambda exts, d: [])
    # write
    gen_nb.generate_notebook_contents()
    assert os.path.exists(gen_nb.CONTENTS_NB)

    # cheatsheet
    monkeypatch.setattr(gen_cs, 'CONFIG', fake)
    monkeypatch.setattr(gen_cs, 'scandir_file_merge',
                        lambda exts, d: ['cs1.tex'])
    monkeypatch.setattr(gen_cs, 'file_preprocess',
                        lambda a, b, logger=None: ['cs1.tex'])
    gen_cs.generate_cheatsheet_contents()
    assert os.path.exists(gen_cs.CONTENTS_CS)


def test_compile_writes_content_files_when_no_gen(tmp_path, monkeypatch):
    # ensure CONTENTS_NB and CONTENTS_CS point to tmp files that don't exist
    monkeypatch.setattr(compile_mod, 'CONTENTS_DIR', str(tmp_path))
    monkeypatch.setattr(compile_mod, 'CONTENTS_NB', str(
        tmp_path / 'contents_notebook.tex'))
    monkeypatch.setattr(compile_mod, 'CONTENTS_CS', str(
        tmp_path / 'contents_cheatsheet.tex'))

    # fake CONFIG to have get_all_code_styles and get_notebook_file
    class FakeCfg:
        def get_all_code_styles(self):
            return []

        def get_notebook_file(self):
            return 'nb'

    monkeypatch.setattr(compile_mod, 'CONFIG', FakeCfg())
    # mock compile_all to avoid external calls
    monkeypatch.setattr(compile_mod, 'compile_all', lambda *a, **k: None)
    # register and call inner
    cmds = {}

    class FakeCLI:
        def command(self, name):
            def deco(fn):
                cmds[name] = fn
                return fn
            return deco

    compile_mod.register_compile_command(FakeCLI())
    fn = cmds.get('run')
    assert fn is not None
    # call with no_gen True so it writes content files
    fn(True, True, True, True)
    assert os.path.exists(compile_mod.CONTENTS_NB)
    assert os.path.exists(compile_mod.CONTENTS_CS)


def test_gen_cs_with_subdir(tmp_path, monkeypatch):
    # setup fake CONFIG and a subdir containing cs file
    base = tmp_path / 'cheats'
    base.mkdir()
    sub = base / 'subdir'
    sub.mkdir()
    f = sub / 'mycs.tex'
    f.write_text('content', encoding='utf8')

    class FakeCfg:
        def get_cheatsheets(self):
            return ['subdir/mycs']

        def get_cheatsheet_dir(self):
            return str(base)

        def get_cheatsheet_name(self, name):
            return name.upper()

    monkeypatch.setattr(gen_cs, 'CONFIG', FakeCfg())
    # ensure scandir_file_merge returns the file
    monkeypatch.setattr(gen_cs, 'scandir_file_merge',
                        lambda exts, d: ['subdir/mycs.tex'])
    # write
    gen_cs.generate_cheatsheet_contents()
    assert os.path.exists(gen_cs.CONTENTS_CS)


def test_compile_all_invokes_subprocess(monkeypatch):
    # monkeypatch LATEX_COMPILE_COMMAND_GROUP to simple callables
    monkeypatch.setattr(compile_mod, 'LATEX_COMPILE_COMMAND_GROUP', [
                        lambda f: ['echo', 'x'], lambda f: ['echo', 'y']])
    calls = []

    def fake_run(cmd, **kwargs):
        calls.append(cmd)

    monkeypatch.setattr(subprocess, 'run', fake_run)
    # monkeypatch CONFIG.get_notebook_file used by compile_all

    class FakeC:
        def get_notebook_file(self):
            return 'notebook'

    monkeypatch.setattr(compile_mod, 'CONFIG', FakeC())
    compile_mod.compile_all(False, False, False, False)
    assert len(calls) == 2


def test_gentc_generate_testcode_no_src(monkeypatch, tmp_path):
    monkeypatch.setattr(gentc, 'get_full_filenames', lambda paths, exts: [])
    # should run without exception
    gentc.generate_testcode(str(tmp_path), str(tmp_path))


def test_gentc_full_generate_and_remove_old(monkeypatch, tmp_path):
    # prepare source and target
    src = tmp_path / 'src'
    tgt = tmp_path / 'tgt'
    src.mkdir()
    tgt.mkdir()
    src_file = src / 'f.cppmeta'
    src_file.write_text('header\n' + tm._GENTC_BEGIN +
                        tm._GENTC_END + tm._GENTC_MAIN + '\n')

    old_target = tgt / 'old.cpp'
    old_target.write_text('#define AUTO_GENERATED\nold', encoding='utf8')

    def fake_get_full_filenames(paths, exts):
        if exts == ['cppmeta']:
            return [str(src_file)]
        if exts == ['cpp']:
            return [str(old_target)]
        return []

    monkeypatch.setattr(gentc, 'get_full_filenames', fake_get_full_filenames)

    # fake parser that returns a new file to be written
    class FakeParser:
        def __init__(self, noext, target_dir, lines):
            pass

        def get_results(self):
            return [(str(tgt / 'new.test.cpp'), ['#define AUTO_GENERATED\n', 'int main(){}\n'])]

    monkeypatch.setattr(gentc, 'cppmeta_parser', FakeParser)

    # run
    gentc.generate_testcode(str(src), str(tgt))
    assert not old_target.exists()
    assert (tgt / 'new.test.cpp').exists()


def test_write_section_hpp_and_usage(tmp_path, monkeypatch):
    # prepare fake CONFIG
    class FakeCfg:
        def __init__(self, base):
            self.base = str(base)

        def get_code_dir(self):
            return self.base

        def get_doc_dir(self):
            return self.base

        def get_cvdoc_dir(self):
            return self.base

        def get_usage_dir(self):
            return self.base

        def get_code_style(self, ext):
            return 'cs'

        def export_usage_code_in_notebook(self):
            return True

    fake = FakeCfg(tmp_path)
    monkeypatch.setattr(gen_nb, 'CONFIG', fake)

    # create files expected by section
    chdir = tmp_path / 'ch'
    chdir.mkdir()
    code_file = chdir / 'n.hpp'
    code_file.write_text('\n'.join('line' + str(i)
                         for i in range(20)), encoding='utf8')
    doc_file = chdir / 'n.tex'
    doc_file.write_text('doc', encoding='utf8')
    usage_file = chdir / 'n.in'
    usage_file.write_text('u', encoding='utf8')

    from libs.classes.section import Section
    sec = Section('ch', 'n', 'MyTitle', 'hpp', 'in')
    out = tmp_path / 'out.tex'
    f = open(out, 'w', encoding='utf8')
    gen_nb._write_section(f, sec, logger=type('L', (), {
                          'info': lambda *a, **k: None, 'isEnabledFor': lambda *a, **k: False, 'debug': lambda *a, **k: None}))
    f.close()
    txt = out.read_text(encoding='utf8')
    assert 'inputminted' in txt or 'Path:' in txt


def test_generate_sections_from_files_doc_and_code(monkeypatch):
    # monkeypatch load_from to return different lists based on dir
    def fake_load(dir_name):
        if 'code' in dir_name:
            return [('a', 'cpp'), ('b', 'cpp')]
        if 'doc' in dir_name:
            return [('a', 'tex')]
        if 'usage' in dir_name:
            return [('b', 'in')]
        return []

    monkeypatch.setattr(gen_nb, 'load_from', fake_load)

    class FakeC:
        def get_code_dir(self):
            return 'code'

        def get_doc_dir(self):
            return 'doc'

        def get_usage_dir(self):
            return 'usage'

    monkeypatch.setattr(gen_nb, 'CONFIG', FakeC())

    # call generator
    res = gen_nb._generate_sections_from_files('ch', logger=type(
        'L', (), {'info': lambda *a, **k: None, 'debug': lambda *a, **k: None}))
    assert any(s.name == 'a' for s in res)


def test_register_compile_command_inner(monkeypatch, tmp_path):
    called = {'lint': 0, 'run_usage': 0, 'gen': 0, 'clean': 0}

    monkeypatch.setattr(compile_mod, 'lint_all_codes',
                        lambda cs: called.update({'lint': called['lint'] + 1}))
    monkeypatch.setattr(compile_mod, 'run_usage_codes', lambda cs, t: called.update(
        {'run_usage': called['run_usage'] + 1}))
    monkeypatch.setattr(compile_mod, 'generate_notebook_contents',
                        lambda: called.update({'gen': called['gen'] + 1}))
    monkeypatch.setattr(compile_mod, 'generate_cheatsheet_contents',
                        lambda: called.update({'gen': called['gen'] + 1}))
    monkeypatch.setattr(compile_mod, 'clean', lambda: called.update(
        {'clean': called['clean'] + 1}))

    # fake CLI to capture inner function
    cmds = {}

    class FakeCLI:
        def command(self, name):
            def deco(fn):
                cmds[name] = fn
                return fn
            return deco

    class FakeCfg2:
        def get_all_code_styles(self):
            return ['cs']

        def get_notebook_file(self):
            return 'nb'

    monkeypatch.setattr(compile_mod, 'CONFIG', FakeCfg2())
    compile_mod.register_compile_command(FakeCLI())
    # call inner _compile with no_gen True to hit branch that creates files
    fn = cmds.get('run')
    assert fn is not None
    # ensure LATEX commands won't actually call external processes
    monkeypatch.setattr(compile_mod, 'LATEX_COMPILE_COMMAND_GROUP', [
                        lambda f: ['echo']])
    monkeypatch.setattr(subprocess, 'run', lambda *a, **k: None)
    # call with flags: no_fmt True (skip lint), no_run_usage True, no_gen True, no_clean True
    fn(True, True, True, True)


def test_register_compile_command_all_false(monkeypatch, tmp_path):
    called = {'lint': 0, 'run_usage': 0, 'gen': 0, 'clean': 0}

    monkeypatch.setattr(compile_mod, 'lint_all_codes',
                        lambda cs: called.update({'lint': called['lint'] + 1}))
    monkeypatch.setattr(compile_mod, 'run_usage_codes', lambda cs, t: called.update(
        {'run_usage': called['run_usage'] + 1}))
    monkeypatch.setattr(compile_mod, 'generate_notebook_contents',
                        lambda: called.update({'gen': called['gen'] + 1}))
    monkeypatch.setattr(compile_mod, 'generate_cheatsheet_contents',
                        lambda: called.update({'gen': called['gen'] + 1}))
    monkeypatch.setattr(compile_mod, 'clean', lambda: called.update(
        {'clean': called['clean'] + 1}))

    cmds = {}

    class FakeCLI:
        def command(self, name):
            def deco(fn):
                cmds[name] = fn
                return fn
            return deco

    class FakeCfg2:
        def get_all_code_styles(self):
            return ['cs']

        def get_notebook_file(self):
            return 'nb'

    monkeypatch.setattr(compile_mod, 'CONFIG', FakeCfg2())
    monkeypatch.setattr(compile_mod, 'LATEX_COMPILE_COMMAND_GROUP', [
                        lambda f: ['echo']])
    monkeypatch.setattr(subprocess, 'run', lambda *a, **k: None)
    compile_mod.register_compile_command(FakeCLI())
    fn = cmds.get('run')
    assert fn is not None
    fn(False, False, False, False)


def test_add_new_note_and_run_usage(tmp_path, monkeypatch):
    # fake CONFIG for new and run_usage
    class FakeC:
        def __init__(self, base):
            self.base = str(base)

        def get_code_dir(self):
            return self.base

        def get_doc_dir(self):
            return self.base

        def get_cvdoc_dir(self):
            return self.base

        def get_usage_dir(self):
            return self.base

        def append_section(self, sec):
            # record called
            self._appended = True

        def get_ext_names_by_code_style(self, code):
            return ['in']

        def get_usage_dir(self):
            return self.base

        def get_run_usage_command(self, code, filepath):
            return ['echo', filepath]

    fake = FakeC(tmp_path)
    monkeypatch.setattr(newmod, 'CONFIG', fake)
    # call add_new_note
    newmod.add_new_note('ch', 'f', 'T', 'cpp', 'in')
    # CVDoc should be created
    # run_usage: create files
    monkeypatch.setattr(run_usage_mod, 'CONFIG', fake)
    p1 = tmp_path / 'u1.in'
    p1.write_text('x')
    monkeypatch.setattr(run_usage_mod, 'get_full_filenames',
                        lambda paths, exts: [str(p1)])
    calls = []

    def fake_run(cmd, **kwargs):
        calls.append(cmd)

    monkeypatch.setattr(subprocess, 'run', fake_run)
    run_usage_mod.run_usage_codes('code', 2)
    assert calls
