from copy import deepcopy
from fnmatch import fnmatch
import itertools
import os
from typing import Iterable

from libs.consts import CONFIG_TCGEN
from libs.decorator import withlog


class case_parser:
    def __init__(self, case_list: Iterable[tuple[str, str]]):
        self._case_list: list[tuple[str, str]] = sorted(case_list,
                                                        key=lambda x: CONFIG_TCGEN.get_priority(x[0]))
        self._case_tag: str = '.'.join(
            f"{cat}-{mem}" for cat, mem in self._case_list)
        self._case_dict: list[dict] = [CONFIG_TCGEN.get_member_content(cat, mem)
                                       for cat, mem in self._case_list]
        self._requirement_members_list: list[list[str]] = []
        for case in self._case_dict:
            req, cat = deepcopy(case['requirements']), case['category_name']
            req_members: list[str] = []
            if req:
                for case2 in self._case_dict:
                    cat2 = case2['category_name']
                    if cat2 == cat:
                        continue
                    for idx, single_req in enumerate(req):
                        if cat2 not in single_req:
                            continue
                        req_members.append(case2['member_name'])
                        req[idx].pop(single_req.index(cat2))
                        break
            self._requirement_members_list.append(req_members)

    def __str__(self):
        return str(self._case_dict)

    def _apply_format_specifiers(self, content: str, member: str, requirement_members: list[str]) -> str:
        if not content:
            return ''
        for idx, mem in enumerate(requirement_members):
            content = content.replace(f"$mb{idx}b", mem)
        content = content.replace('$m', member)
        return content

    def _get_content_ignore(self, type: str) -> str:
        cat_list: list[str] = []
        result: str = ''
        for case, requirements in zip(self._case_dict, self._requirement_members_list):
            category_name = case['category_name']
            if category_name in cat_list:
                continue
            cat_list.extend(
                CONFIG_TCGEN.get_categories_with_same_priority(category_name))
            result += self._apply_format_specifiers(
                case[type], case['member_name'], requirements)
        return result

    @withlog
    def get_include_list(self, **kwargs) -> list[str]:
        result: list[str] = []
        for case, req in zip(self._case_dict, self._requirement_members_list):
            if not case['include']:
                continue
            result.extend([self._apply_format_specifiers(
                i, case['member_name'], req) for i in case['include']])
        return sorted(list(set(result)))

    @withlog
    def get_content_after_include(self, **kwargs) -> str:
        return self._get_content_ignore('after_include')

    @withlog
    def get_content_main_begin(self, **kwargs) -> str:
        return self._get_content_ignore('main_begin')

    @withlog
    def get_label(self, **kwargs) -> str:
        return '.'.join(f"{cat}-{mem}" for cat, mem in self._case_list)


class testcase_matrix:
    def __init__(self):
        self._cat_list: list[list[str]] = []
        self._all_cases: list[case_parser] = []

    def _get_member_list(self) -> list[list[tuple[str, str]]]:
        categories = sorted(self._cat_list,
                            key=lambda x: CONFIG_TCGEN.get_priority(x[0]))
        result: list = []
        for cat in categories:
            result.append(CONFIG_TCGEN.get_memberlist(cat))
        return result

    @withlog
    def append(self, categories: Iterable[str], **kwargs):
        self._cat_list.append(list(categories))
        return self

    @withlog
    def make_all_cases(self, **kwargs):
        def _single_iteration(all_cases, all_cases_new):
            result: list[list[tuple[str, str]]] = []
            result_new: list[list[tuple[str, str]]] = []
            for now_case, now_case_new in zip(all_cases, all_cases_new):
                required_cats: list[tuple[str, ...]] = []
                for cat, mem in now_case_new:
                    req: list[list[str]] | None = CONFIG_TCGEN.get_member_content(cat, mem)[
                        'requirements']
                    if req:
                        required_cats.extend(itertools.product(*req))
                if not required_cats:
                    result.append(now_case)
                    result_new.append([])
                    continue
                for cats in required_cats:
                    ls = [CONFIG_TCGEN.get_memberlist(cat) for cat in cats]
                    prod = list(itertools.product(*ls))
                    result.extend([[*now_case, *req]
                                   for req in prod])
                    result_new.extend([[*req] for req in prod])
            return result, result_new

        all_cases = [list(i)
                     for i in itertools.product(*self._get_member_list())]
        all_cases_new = deepcopy(all_cases)
        kwargs.get('logger').debug(f'Initial:')
        kwargs.get('logger').debug(' ' * 2 + f'all_cases:')
        kwargs.get('logger').debug('\n'.join(str(i)
                                             for i in all_cases))
        kwargs.get('logger').debug(' ' * 2 + f'all_cases_new:')
        kwargs.get('logger').debug('\n'.join(str(i)
                                             for i in all_cases_new))
        iter_limit = len(CONFIG_TCGEN.get_categories())
        cnt = 0
        while True:
            all_cases, all_cases_new = _single_iteration(
                all_cases, all_cases_new)
            kwargs.get('logger').debug(f'Iteration {cnt}:')
            kwargs.get('logger').debug(' ' * 2 + f'all_cases:')
            kwargs.get('logger').debug('\n'.join(str(i)
                                                 for i in all_cases))
            if not sum([len(i) for i in all_cases_new]):
                break
            cnt += 1
            if cnt > iter_limit:
                raise RuntimeError('Max iteration limit exceed!')
        self._all_cases = [deepcopy(case_parser(now_case))
                           for now_case in all_cases]

    @withlog
    def get_all_cases(self, **kwargs):
        if not self._all_cases:
            self.make_all_cases()
        return self._all_cases

    @withlog
    def exclude(self, case: list[tuple[str, str]], **kwargs):
        if not self._all_cases:
            self.make_all_cases()
        case_list = [i._case_list for i in self._all_cases]
        self._all_cases.pop(case_list.index(
            sorted(case, key=lambda x: CONFIG_TCGEN.get_priority(x[0]))))
        return self

    @withlog
    def exclude_wildcard(self, pattern: str, **kwargs):
        if not self._all_cases:
            self.make_all_cases()
        for index, val in reversed(list(enumerate(self._all_cases))):
            if fnmatch(val._case_tag, pattern):
                self._all_cases.pop(index)
        return self


_GENTC_BEGIN = '// ---<GENTC>--- begin\n'
_GENTC_END = '// ---<GENTC>--- end\n'
_GENTC_MAIN = 'int main() {\n'
_GENTC_COMMAND_APPEND = '// ---<GENTC>--- append '
_GENTC_COMMAND_EXCLIDE = '// ---<GENTC>--- exclude '


class cppmeta_parser:
    def __init__(self, cppmeta_filename_noext: str, target_dir: str, cppmeta_code_lines: list[str]):
        self._filename_noext = cppmeta_filename_noext
        self._target_dir = target_dir
        self._code_lines = cppmeta_code_lines
        self._testcase_mat = testcase_matrix()

    def _get_all_cases(self):
        block_begin, block_end = -1, -1
        inblock, appended, excluded = False, False, False
        main_index = self._code_lines.index(_GENTC_MAIN)

        for index, codeline in enumerate(self._code_lines):
            if codeline == _GENTC_BEGIN:
                if inblock:
                    raise RuntimeError(
                        f'Parse error: `GENTC begin` can not appear in a GENTC block')
                block_begin = index
                inblock = True
                continue

            if codeline == _GENTC_END:
                if not inblock:
                    raise RuntimeError(f'Parse error: `GENTC end` mismatched')
                block_end = index + 1
                inblock = False
                break
            if not inblock:
                continue

            if codeline.startswith(_GENTC_COMMAND_APPEND):
                if excluded:
                    raise RuntimeError(
                        'Parse error: `GENTC append` found after `GENTC exclude`')
                appended = True
                self._testcase_mat.append(list(filter(
                    lambda x: x, codeline.removeprefix(_GENTC_COMMAND_APPEND).strip().split())))
                continue
            if codeline.startswith(_GENTC_COMMAND_EXCLIDE):
                if not appended:
                    raise RuntimeError(
                        'Parse error: `GENTC exclude` found before `GENTC append`')
                excluded = True
                if codeline.find('*') != -1:
                    self._testcase_mat.exclude_wildcard(codeline.removeprefix(
                        _GENTC_COMMAND_EXCLIDE).strip())
                else:
                    self._testcase_mat.exclude([tuple(x.split('-')) for x in filter(
                        lambda x: x, codeline.removeprefix(_GENTC_COMMAND_EXCLIDE).strip().split('.'))])
                continue

            raise RuntimeError(
                f"Parse error: unknown GENTC command '{codeline.rstrip()}'")

        if block_begin < 0:
            raise RuntimeError('Parse error: GENTC block not found')
        if inblock or block_end < 0:
            raise RuntimeError('Parse error: `GENTC begin` mismatched')
        if not (block_begin < block_end <= main_index):
            raise RuntimeError('GENTC block must be before main function')
        return block_begin, block_end, main_index, self._testcase_mat.get_all_cases()

    def _get_include_relpath(self, include_filepath: str) -> str:
        return os.path.relpath(include_filepath, self._target_dir).replace("\\", '/')

    def _get_all_target_content(self) -> list[tuple[str, list[str]]]:
        block_begin, block_end, main_index, all_cases = self._get_all_cases()
        result = []
        for case in all_cases:
            target_filepath = os.path.join(
                self._target_dir, f"{self._filename_noext}.{case.get_label()}.test.cpp")
            now_codelines: list[str] = ['#define AUTO_GENERATED\n']
            # before include
            now_codelines += self._code_lines[0:block_begin]
            # include
            now_codelines += [f'#include "{self._get_include_relpath(include)}"\n'
                              for include in case.get_include_list()]
            # after include
            now_codelines += ['\n'] + \
                case.get_content_after_include().splitlines(True)
            # before main
            now_codelines += self._code_lines[block_end:main_index + 1]
            # main begin
            now_codelines += [i if i.startswith('  ') else '  ' + i
                              for i in case.get_content_main_begin().splitlines(True)]
            # remains
            now_codelines += self._code_lines[main_index + 1:]
            result.append((target_filepath, now_codelines))
        return result

    @withlog
    def get_results(self, **kwargs) -> list[tuple[str, list[str]]]:
        return self._get_all_target_content()
