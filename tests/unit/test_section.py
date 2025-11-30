import os
from pathlib import Path

from libs.classes.section import Section


def test_parse_from_dict_valid(tmp_path, caplog):
    s = Section('ch1')
    d = {'file1': 'Title 1', 'code_ext': 'cpp', 'usage_ext': 'in'}
    caplog.set_level('DEBUG')
    res = s.parse_from_dict(d.copy())
    assert res is s
    assert s.name == 'file1'
    assert s.title == 'Title 1'
    assert s.code_ext == 'cpp'
    assert s.usage_ext == 'in'


def test_parse_from_dict_missing_title_warns(tmp_path, caplog):
    s = Section('ch2')
    d = {'file2': '', 'code_ext': 'py', 'usage_ext': 'out'}
    caplog.set_level('WARNING')
    res = s.parse_from_dict(d.copy())
    assert res.title == 'file2'
    assert any(
        "title name not found" in r.message for r in caplog.records if r.levelname == 'WARNING')


def test_parse_from_dict_invalid_raises(tmp_path, caplog):
    s = Section('ch3')
    d = {'a': 'A', 'b': 'B', 'code_ext': 'c', 'usage_ext': 'u'}
    caplog.set_level('ERROR')
    try:
        s.parse_from_dict(d.copy())
        assert False, "Should have raised KeyError"
    except KeyError:
        assert any(
            'Invalid section config' in r.message for r in caplog.records if r.levelname == 'ERROR')


def test_get_dict_and_filenames_and_open(tmp_path):
    base = tmp_path
    code_root = base / 'code'
    doc_root = base / 'doc'
    cvdoc_root = base / 'cvdoc'
    usage_root = base / 'usage'

    s = Section('ch', 'name1', 'Title', 'cpp', 'in')
    d = s.get_dict()
    assert d['name1'] == 'Title' or d.get('name1') == 'Title'

    code_p, doc_p, cv_p, usage_p = s.get_filenames(
        str(code_root), str(doc_root), str(cvdoc_root), str(usage_root))
    # directories are created
    assert os.path.isdir(os.path.join(str(code_root), 'ch'))
    assert code_p.endswith('name1.cpp')
    # test open creates files and returns file objects
    f_code, f_doc, f_cvdoc, f_usage = s.open(str(code_root), str(
        doc_root), str(cvdoc_root), str(usage_root), 'w', encoding='utf8')
    f_code.write('x')
    f_code.close()
    f_doc.close()
    f_cvdoc.close()
    f_usage.close()

    # ensure files exist
    assert Path(code_p).exists()
    assert Path(doc_p).exists()
    assert Path(cv_p).exists()
    assert Path(usage_p).exists()
