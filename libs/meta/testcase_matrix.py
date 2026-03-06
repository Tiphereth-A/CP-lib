from copy import deepcopy
from fnmatch import fnmatch
import itertools
import logging
from typing import Iterable

from libs.conf import ConfigTcgen
from libs.decorator import with_logger


class testcase_matrix:
    class case_parser:
        def __init__(self, config: ConfigTcgen, case_list: Iterable[tuple[str, str]]):
            self._config = config
            self._case_list: list[tuple[str, str]] = sorted(case_list,
                                                            key=lambda x: self._config.get_priority(x[0]))
            self._case_tag: str = '.'.join(
                f"{cat}-{mem}" for cat, mem in self._case_list)
            self._case_dict: list[dict] = [self._config.get_member_content(cat, mem)
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
            if not content:
                return ''
            result = content
            for idx, mem in enumerate(requirement_members):
                result = result.replace(f"$mb{idx}b", mem)
            result = result.replace('$m', member)
            return result

        def _get_content_ignore(self, content_type: str) -> str:
            processed_categories: set[str] = set()
            result: str = ''
            for case, requirements in zip(self._case_dict, self._requirement_members_list):
                category_name = case['category_name']
                if category_name in processed_categories:
                    continue
                # Mark all categories with same priority as processed
                same_priority_cats = self._config.get_categories_with_same_priority(
                    category_name)
                processed_categories.update(same_priority_cats)
                result += self._apply_format_specifiers(
                    case[content_type], case['member_name'], requirements
                )
            return result

        @with_logger
        def get_include_list(self, **kwargs) -> list[str]:
            result: set[str] = set()
            for case, req in zip(self._case_dict, self._requirement_members_list):
                if case.get('include'):
                    for include in case['include']:
                        result.add(self._apply_format_specifiers(
                            include, case['member_name'], req
                        ))
            return sorted(result)

        @with_logger
        def get_content_after_include(self, **kwargs) -> str:
            return self._get_content_ignore('after_include')

        @with_logger
        def get_content_main_begin(self, **kwargs) -> str:
            return self._get_content_ignore('main_begin')

        @with_logger
        def get_label(self, **kwargs) -> str:
            return self._case_tag

    def __init__(self, config: ConfigTcgen):
        self._config = config
        self._cat_list: list[list[str]] = []
        self._all_cases: list[testcase_matrix.case_parser] = []
        self._cases_built: bool = False

    def _get_member_list(self) -> list[list[tuple[str, str]]]:
        categories = sorted(
            self._cat_list,
            key=lambda cat_list: self._config.get_priority(cat_list[0])
        )
        return [self._config.get_memberlist(cat) for cat in categories]

    @with_logger
    def append(self, categories: Iterable[str], **kwargs):
        self._cat_list.append(list(categories))
        return self

    @with_logger
    def make_all_cases(self, **kwargs):
        logger = kwargs.get('logger')

        def _single_iteration(all_cases, all_cases_new):
            result: list[list[tuple[str, str]]] = []
            result_new: list[list[tuple[str, str]]] = []

            for current_case, current_case_new in zip(all_cases, all_cases_new):
                required_cats: list[tuple[str, ...]] = []

                # Collect all requirements from new cases
                for cat, mem in current_case_new:
                    member_content = self._config.get_member_content(cat, mem)
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
                        self._config.get_memberlist(cat)
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
        iter_limit = len(self._config.get_categories())
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
        self._all_cases = [testcase_matrix.case_parser(self._config, now_case)
                           for now_case in all_cases]
        self._cases_built = True

    @with_logger
    def get_all_cases(self, **kwargs):
        if not self._cases_built:
            self.make_all_cases()
        return self._all_cases

    @with_logger
    def exclude(self, case: list[tuple[str, str]], **kwargs):
        if not self._cases_built:
            self.make_all_cases()

        sorted_case = sorted(
            case, key=lambda x: self._config.get_priority(x[0]))

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

    @with_logger
    def exclude_wildcard(self, pattern: str, **kwargs):
        if not self._cases_built:
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
