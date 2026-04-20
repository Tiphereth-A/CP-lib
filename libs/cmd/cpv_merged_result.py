import datetime
import orjson
import subprocess
import click

from libs.decorator import with_logger, with_timer


@with_logger
@with_timer
def cpv_merged_result(merged_result: str, type: str, **kwargs):
    def set_commit_hash_if_absent(data: dict[str, dict[str]]) -> dict[str, dict[str]]:
        current_hash = subprocess.check_output(
            ['git', 'rev-parse', 'HEAD']).decode().strip()

        for file, result in data['files'].items():
            if 'commit_hash' not in result:
                result['commit_hash'] = current_hash
                data['files'][file] = result
        return data

    # https://github.com/competitive-verifier/competitive-verifier/blob/a0dda3a00396a083f66780b2f00ff277ad032733/src/competitive_verifier/verify/verifier.py#L361
    # seems CPV consider rejudge or not based on timestamp, which is invalid for `commit --amend`
    def reset_last_execution_time(data: dict[str, dict[str]]) -> dict[str, dict[str]]:
        for file, result in data['files'].items():
            for idx, v in enumerate(result['verifications']):
                v['last_execution_time'] = datetime.datetime.fromtimestamp(
                    0, tz=datetime.datetime.now(datetime.timezone.utc).astimezone().tzinfo)
                result['verifications'][idx] = v
            data['files'][file] = result
        return data

    logger = kwargs.get('logger')

    with open(merged_result, 'rb') as f:
        data = orjson.loads(f.read())
    data = locals()[type](data)
    with open(merged_result, 'wb') as f:
        f.write(orjson.dumps(data))

    logger.info('finished')


def _register_cpv_merged_result(cli):
    @cli.command('merged-result')
    @click.option('-m', '--merged-result', type=click.Path(exists=True, dir_okay=False), default='merged-result.json')
    @click.option('-t', '--type', type=click.Choice(('set_commit_hash_if_absent', 'reset_last_execution_time')), prompt='patch type')
    def _cpv_merged_result(merged_result: str, type: str):
        cpv_merged_result(merged_result, type)
