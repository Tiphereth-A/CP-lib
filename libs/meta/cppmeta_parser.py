import os

from libs.conf import ConfigTcgen
from libs.decorator import with_logger
from libs.meta import testcase_matrix


_GENTC_BEGIN = '// ---<GENTC>--- begin\n'
_GENTC_END = '// ---<GENTC>--- end\n'
_GENTC_MAIN = 'int main() {\n'
_GENTC_COMMAND_APPEND = '// ---<GENTC>--- append '
_GENTC_COMMAND_EXCLIDE = '// ---<GENTC>--- exclude '

_CONFIG_TCGEN = ConfigTcgen('tcgen.yml')


class cppmeta_parser:
    def __init__(self, cppmeta_filename_noext: str, target_dir: str, cppmeta_code_lines: list[str]):
        self._filename_noext = cppmeta_filename_noext
        self._target_dir = target_dir
        self._code_lines = cppmeta_code_lines
        self._testcase_mat = testcase_matrix(_CONFIG_TCGEN)

    def _get_all_cases(self):
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
        block_begin, block_end, main_index, all_cases = self._get_all_cases()
        result = []

        for case in all_cases:
            target_filepath = os.path.join(
                self._target_dir,
                f"{self._filename_noext}.{case.get_label()}.cpp"
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

    @with_logger
    def get_results(self, **kwargs) -> list[tuple[str, list[str]]]:
        return self._get_all_target_content()
