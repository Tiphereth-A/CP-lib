import fnmatch
import heapq
import orjson
import os
import subprocess
from typing import Iterable
import click

from libs.decorator import with_logger, with_timer


@with_logger
@with_timer
def files_listing(previous_info: dict[str, dict[str]], **kwargs) -> list[str]:
    if not previous_info:
        return subprocess.check_output(['git', 'ls-files']).decode().splitlines()

    hashes = set(subprocess.check_output(
        ['git', 'rev-list', '--all', '--no-merges', '--first-parent']).decode().splitlines())

    result = set()
    visited, ancestor_files = set(), set()

    for file, info in previous_info.items():
        current_hash = info.get('commit_hash', '<unknown-commit-hash>')
        if current_hash not in hashes:
            result.add(file)
        else:
            visited.add(current_hash)
            ancestor_files.add(file)

    for h in visited:
        changed_files = subprocess.check_output(
            ['git', 'diff-tree', '--no-commit-id', '--name-only', '-r', h]).decode().splitlines()
        result |= set(
            file for file in changed_files if file not in ancestor_files)

    return list(result)


def files_filter(files: Iterable[str], patterns: tuple[str]) -> filter:
    return filter(lambda file: any(fnmatch.fnmatch(file, pattern) for pattern in patterns if not pattern.startswith('!')) and all(not fnmatch.fnmatch(file, pattern[1:]) for pattern in patterns if pattern.startswith('!')), files)


@with_logger
@with_timer
def files_dependencies(files: set[str], dependencies: dict[str, list[str]], **kwargs) -> set[str]:
    return files | set(dep for file in files for dep in dependencies.get(file, []))


@with_logger
@with_timer
# see https://en.wikipedia.org/wiki/Longest-processing-time-first_scheduling
def partition(files_info: dict[str, dict[str]], task_count: int, **kwargs) -> list[list[str]]:
    logger = kwargs.get('logger')
    if task_count <= 0:
        raise ValueError("task_count must be a positive integer")

    for k, v in files_info.items():
        if isinstance(v, str):
            logger.info(f"No previous info found")
            result = [[_k for _k, _ in files_info.items()][i::task_count]
                      for i in range(task_count)]
            for r in result:
                r.sort()
            return result

        if v['total_elapsed'] < 0:
            raise ValueError(
                f"File {k} has invalid total_elapsed {v['total_elapsed']}")
        if v['total_samples'] < 0:
            raise ValueError(
                f"File {k} has invalid total_samples {v['total_samples']}")
        v['prepare_elapsed'] = v['total_samples'] * (.4 if v['tag'].startswith(
            'problem libchk') else .2) if v['tag'].startswith('problem') else 0.

        files_info[k] = v

    groups = {}
    for path, info in files_info.items():
        groups.setdefault(info["tag"], []).append(
            (path, info["total_elapsed"], info["prepare_elapsed"]))

    tag_units = [(sum(r+p for _, r, p in items)-(len(items)-1) * items[0][2],
                  [p for p, _, _ in items]) for _, items in groups.items()]
    tag_units.sort(key=lambda x: x[0], reverse=True)

    heap = [(0.0, i) for i in range(task_count)]
    heapq.heapify(heap)

    partitions = [[] for _ in range(task_count)]
    part_load = [0.0] * task_count

    for weight, paths in tag_units:
        _, i = heapq.heappop(heap)
        partitions[i].extend(paths)
        part_load[i] += weight

        heapq.heappush(heap, (part_load[i], i))

    for p in partitions:
        p.sort()
    return partitions


@with_logger
@with_timer
def cpv_delegate(file_patterns: tuple[str], verify_files: str, merged_result: str, task_count: int, result_dir: str, **kwargs):
    logger = kwargs.get('logger')

    verify_files_info: dict = orjson.loads(
        open(verify_files, 'rb').read())['files']
    dependencies = {k: v['dependencies']
                    for k, v in verify_files_info.items()}

    try:
        previous_info: dict = orjson.loads(
            open(merged_result, 'rb').read())['files'] if merged_result else {}
    except FileNotFoundError:
        logger.warning(
            f"'{merged_result}' not found. Proceeding without previous info.")
        previous_info = {}

    file_lists: list[str] = list(files_filter(
        files_dependencies(
            set(files_filter(
                files_listing(previous_info),
                file_patterns)),
            dependencies),
        file_patterns))

    logger.info(f'{len(file_lists)} file(s) need to be verified')
    if not file_lists:
        return

    def _tag(v: dict[str]) -> str:
        match v['type']:
            case 'problem':
                return ' '.join(('problem',
                                 "aizu" if '.u-aizu.ac.jp/' in v['problem'] else
                                 "libchk" if '://judge.yosupo.jp/' in v['problem'] else
                                 "yuki" if '://yukicoder.me/' in v['problem'] else
                                 "",
                                 v["problem"]))
            case 'local':
                return f"{v['type']} {v['input']}"
            case 'command':
                return f"{v['type']} {v['compile'][-1]}"
            case _:
                raise ValueError(
                    f"Unknown verification type: {v['type']} for file with info: {v}")

    verifiable_files: list[str] = [
        file for file in file_lists
        if verify_files_info.get(file, {}).get('verification')
    ]
    skipped_files: list[str] = [
        file for file in file_lists
        if not verify_files_info.get(file, {}).get('verification')
    ]
    if skipped_files:
        logger.info(
            f'{len(skipped_files)} file(s) have missing or empty verification entries and will be skipped')
        logger.debug(
            '\n::group::Skipped files\n    ' + '\n    '.join(sorted(skipped_files)) + '\n::endgroup::')

    if not verifiable_files:
        logger.info('no verifiable files remain after filtering')
        return

    if previous_info:
        files_info = {}
        for k in verifiable_files:
            verifications = previous_info.get(k, {}).get('verifications', [])
            files_info[k] = {
                'tag': _tag(verify_files_info[k]['verification'][0]),
                'total_elapsed': sum(i.get('elapsed', 0.) for i in verifications if isinstance(i, dict)),
                'total_samples': len(verifications[0].get('testcases', [])) if verifications and isinstance(verifications[0], dict) else 0,
            }
    else:
        files_info = {
            k: _tag(verify_files_info[k]['verification'][0])
            for k in verifiable_files
        }

    tasklists = partition(files_info, task_count)
    os.makedirs(result_dir, exist_ok=True)
    for idx, task in enumerate(tasklists):
        with open(os.path.join(result_dir, f'{idx}.json'), 'wb') as f:
            f.write(orjson.dumps({
                'files': {file: verify_files_info[file] for file in task}
            }))

    logger.info('finished')


def _register_cpv_delegate(cli):
    @cli.command('delegate')
    @click.option('-f', '--file-pattern', type=str, help='File pattern to include/exclude, wildcards allowed, exclude patterns start with !. Files which mismatch all include patterns or match any exclude pattern are excluded', default='*')
    @click.option('-v', '--verify-files', type=click.Path(exists=True, dir_okay=False), help='Current verify_files.json', default='verify_files.json')
    @click.option('-m', '--merged-result', type=click.Path(dir_okay=False), help='Previous merged-result.json')
    @click.option('-t', '--task-count', type=int, help='verify tasks count', default=2)
    @click.option('-d', '--result-dir', type=click.Path(exists=False, file_okay=False), help='Directory for storing result files', default='.cp-lib/verify-list')
    def _cpv_delegate(file_pattern: str, verify_files: str, merged_result: str, task_count: int, result_dir: str):
        cpv_delegate(file_pattern.split(),
                     verify_files,
                     merged_result,
                     task_count,
                     result_dir)
