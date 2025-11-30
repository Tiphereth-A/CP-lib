from copy import deepcopy
from fnmatch import fnmatch
import itertools
import logging
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
        # Process requirements: find matching members from other categories
        # Build category to case mapping once for all cases (optimization)
        category_to_case_map = {
            c['category_name']: c for c in self._case_dict
        }

        self._requirement_members_list: list[list[str]] = []
        for case in self._case_dict:
            requirements = deepcopy(case.get('requirements', []))
            category_name = case['category_name']
            req_members: list[str] = []

            if requirements:
                # Find matching requirement and extract member
                for req_list in requirements:
                    for cat2 in req_list:
                        if cat2 != category_name and cat2 in category_to_case_map:
                            req_members.append(
                                category_to_case_map[cat2]['member_name'])
                            req_list.remove(cat2)
                            break

            self._requirement_members_list.append(req_members)

    def __str__(self):
        return str(self._case_dict)

    def _apply_format_specifiers(self, content: str, member: str, requirement_members: list[str]) -> str:
        """Apply format specifiers to content string."""
        if not content:
            return ''
        result = content
        for idx, mem in enumerate(requirement_members):
            result = result.replace(f"$mb{idx}b", mem)
        result = result.replace('$m', member)
        return result

    def _get_content_ignore(self, content_type: str) -> str:
        """Get content of specified type, ignoring duplicate categories."""
        processed_categories: set[str] = set()
        result: str = ''
        for case, requirements in zip(self._case_dict, self._requirement_members_list):
            category_name = case['category_name']
            if category_name in processed_categories:
                continue
            # Mark all categories with same priority as processed
            same_priority_cats = CONFIG_TCGEN.get_categories_with_same_priority(
                category_name)
            processed_categories.update(same_priority_cats)
            result += self._apply_format_specifiers(
                case[content_type], case['member_name'], requirements
            )
        return result

    @withlog
    def get_include_list(self, **kwargs) -> list[str]:
        """Get list of unique include statements."""
        result: set[str] = set()
        for case, req in zip(self._case_dict, self._requirement_members_list):
            if case.get('include'):
                for include in case['include']:
                    result.add(self._apply_format_specifiers(
                        include, case['member_name'], req
                    ))
        return sorted(result)

    @withlog
    def get_content_after_include(self, **kwargs) -> str:
        return self._get_content_ignore('after_include')

    @withlog
    def get_content_main_begin(self, **kwargs) -> str:
        return self._get_content_ignore('main_begin')

    @withlog
    def get_label(self, **kwargs) -> str:
        """Get label for this case (same as case_tag)."""
        return self._case_tag


class testcase_matrix:
    def __init__(self):
        self._cat_list: list[list[str]] = []
        self._all_cases: list[case_parser] = []

    def _get_member_list(self) -> list[list[tuple[str, str]]]:
        """Get member lists for all categories, sorted by priority."""
        categories = sorted(
            self._cat_list,
            key=lambda cat_list: CONFIG_TCGEN.get_priority(cat_list[0])
        )
        return [CONFIG_TCGEN.get_memberlist(cat) for cat in categories]

    @withlog
    def append(self, categories: Iterable[str], **kwargs):
        self._cat_list.append(list(categories))
        return self

    @withlog
    def make_all_cases(self, **kwargs):
        """Generate all test cases from the test case matrix."""
        logger = kwargs.get('logger')

        def _single_iteration(all_cases, all_cases_new):
            """Process one iteration of case expansion."""
            result: list[list[tuple[str, str]]] = []
            result_new: list[list[tuple[str, str]]] = []

            for current_case, current_case_new in zip(all_cases, all_cases_new):
                required_cats: list[tuple[str, ...]] = []

                # Collect all requirements from new cases
                for cat, mem in current_case_new:
                    member_content = CONFIG_TCGEN.get_member_content(cat, mem)
                    requirements = member_content.get('requirements')
                    if requirements:
                        required_cats.extend(itertools.product(*requirements))

                # If no requirements, keep case as-is
                if not required_cats:
                    result.append(current_case)
                    result_new.append([])
                    continue

                # Expand cases with requirements
                for required_categories in required_cats:
                    member_lists = [
                        CONFIG_TCGEN.get_memberlist(cat)
                        for cat in required_categories
                    ]
                    product_cases = list(itertools.product(*member_lists))
                    result.extend([[*current_case, *req_case]
                                  for req_case in product_cases])
                    result_new.extend([[*req_case]
                                      for req_case in product_cases])

            return result, result_new

        # Initialize with base cases
        all_cases = [list(i)
                     for i in itertools.product(*self._get_member_list())]
        all_cases_new = deepcopy(all_cases)

        # Only do expensive debug logging if debug level is enabled
        if logger.isEnabledFor(logging.DEBUG):
            logger.debug('Initial:')
            logger.debug(' ' * 2 + f'all_cases:')
            logger.debug('\n'.join(str(i) for i in all_cases))
            logger.debug(' ' * 2 + f'all_cases_new:')
            logger.debug('\n'.join(str(i) for i in all_cases_new))

        # Iterate until no new cases are generated
        iter_limit = len(CONFIG_TCGEN.get_categories())
        cnt = 0
        while True:
            all_cases, all_cases_new = _single_iteration(
                all_cases, all_cases_new)

            if logger.isEnabledFor(logging.DEBUG):
                logger.debug(f'Iteration {cnt}:')
                logger.debug(' ' * 2 + f'all_cases:')
                logger.debug('\n'.join(str(i) for i in all_cases))

            if not any(all_cases_new):
                break

            cnt += 1
            if cnt > iter_limit:
                raise RuntimeError('Max iteration limit exceeded!')

        # Only deepcopy if case_parser modifies input, otherwise create new instances
        self._all_cases = [case_parser(now_case) for now_case in all_cases]

    @withlog
    def get_all_cases(self, **kwargs):
        if not self._all_cases:
            self.make_all_cases()
        return self._all_cases

    @withlog
    def exclude(self, case: list[tuple[str, str]], **kwargs):
        """Exclude a specific case from the test matrix."""
        if not self._all_cases:
            self.make_all_cases()

        sorted_case = sorted(
            case, key=lambda x: CONFIG_TCGEN.get_priority(x[0]))

        # Use tuple for faster lookup (hashable)
        sorted_case_tuple = tuple(sorted_case)
        case_list_tuples = {
            tuple(i._case_list): idx for idx, i in enumerate(self._all_cases)}

        if sorted_case_tuple in case_list_tuples:
            index = case_list_tuples[sorted_case_tuple]
            self._all_cases.pop(index)
        else:
            kwargs.get('logger').warning(
                f"Case {sorted_case} not found in test matrix")

        return self

    @withlog
    def exclude_wildcard(self, pattern: str, **kwargs):
        """Exclude cases matching a wildcard pattern."""
        if not self._all_cases:
            self.make_all_cases()

        # Filter out matching cases
        original_count = len(self._all_cases)
        self._all_cases = [
            case for case in self._all_cases
            if not fnmatch(case._case_tag, pattern)
        ]
        removed = original_count - len(self._all_cases)

        if removed > 0:
            kwargs.get('logger').info(
                f"Excluded {removed} case(s) matching pattern '{pattern}'")

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
        """Parse GENTC block and return case information."""
        block_begin, block_end = -1, -1
        inblock, appended, excluded = False, False, False

        try:
            main_index = self._code_lines.index(_GENTC_MAIN)
        except ValueError:
            raise RuntimeError('Parse error: main function not found')

        for index, codeline in enumerate(self._code_lines):
            if codeline == _GENTC_BEGIN:
                if inblock:
                    raise RuntimeError(
                        'Parse error: `GENTC begin` cannot appear in a GENTC block')
                block_begin = index
                inblock = True
                continue

            if codeline == _GENTC_END:
                if not inblock:
                    raise RuntimeError('Parse error: `GENTC end` mismatched')
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
                categories = [
                    cat for cat in codeline.removeprefix(_GENTC_COMMAND_APPEND).strip().split()
                    if cat
                ]
                self._testcase_mat.append(categories)
                continue

            if codeline.startswith(_GENTC_COMMAND_EXCLIDE):
                if not appended:
                    raise RuntimeError(
                        'Parse error: `GENTC exclude` found before `GENTC append`')
                excluded = True
                exclude_pattern = codeline.removeprefix(
                    _GENTC_COMMAND_EXCLIDE).strip()

                if '*' in exclude_pattern or '?' in exclude_pattern:
                    self._testcase_mat.exclude_wildcard(exclude_pattern)
                else:
                    case_list = [
                        tuple(x.split('-'))
                        for x in exclude_pattern.split('.')
                        if x
                    ]
                    self._testcase_mat.exclude(case_list)
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
        """Generate all target file contents from parsed cases."""
        block_begin, block_end, main_index, all_cases = self._get_all_cases()
        result = []

        for case in all_cases:
            target_filepath = os.path.join(
                self._target_dir,
                f"{self._filename_noext}.{case.get_label()}.test.cpp"
            )

            code_lines: list[str] = ['#define AUTO_GENERATED\n']

            # Code before GENTC block
            code_lines.extend(self._code_lines[0:block_begin])

            # Include statements
            include_list = case.get_include_list()
            if include_list:
                code_lines.extend(
                    f'#include "{self._get_include_relpath(include)}"\n'
                    for include in include_list
                )

            # Code after includes
            after_include = case.get_content_after_include()
            if after_include:
                code_lines.append('\n')
                code_lines.extend(after_include.splitlines(True))

            # Code between GENTC block and main
            code_lines.extend(self._code_lines[block_end:main_index + 1])

            # Main function beginning
            main_begin = case.get_content_main_begin()
            if main_begin:
                for line in main_begin.splitlines(True):
                    code_lines.append(
                        line if line.startswith('  ') else '  ' + line)

            # Remaining code after main
            code_lines.extend(self._code_lines[main_index + 1:])

            result.append((target_filepath, code_lines))

        return result

    @withlog
    def get_results(self, **kwargs) -> list[tuple[str, list[str]]]:
        return self._get_all_target_content()
