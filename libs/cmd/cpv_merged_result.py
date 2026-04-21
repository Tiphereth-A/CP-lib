import orjson
import subprocess
import click

from datetime import datetime, timedelta, timezone
from libs.decorator import with_logger, with_timer


@with_logger
@with_timer
def cpv_merged_result(merged_result: str, **kwargs):
    logger = kwargs.get('logger')

    def _to_utc_timestamp(iso_time: str) -> float:
        dt = datetime.fromisoformat(iso_time)
        return (dt.replace(tzinfo=timezone.utc) if dt.tzinfo is None else dt.astimezone(timezone.utc)).timestamp()

    with open(merged_result, 'rb') as f:
        data: dict[str, dict] = orjson.loads(f.read())

    history = [(h, _to_utc_timestamp(t))
               for h, t in (l.split('\t') for l in subprocess.check_output(
                   ['git', 'log', '--since', (datetime.now() - timedelta(days=15)).isoformat(), '--format=%H%x09%cI']).decode().splitlines())]
    history.sort(key=lambda x: x[1], reverse=True)

    for file, info in data['files'].items():
        data['files'][file]['commit_hash'] = next(
            (h for h, t in history if t <= max(
                (_to_utc_timestamp(v['last_execution_time']) for v in info.get('verifications', [])), default=0.)),
            '<outdated-or-invalid>')

    with open(merged_result, 'wb') as f:
        f.write(orjson.dumps(data))

    logger.info('finished')


def _register_cpv_merged_result(cli):
    @cli.command('merged-result')
    @click.option('-m', '--merged-result', type=click.Path(exists=True, dir_okay=False), default='merged-result.json')
    def _cpv_merged_result(merged_result: str):
        cpv_merged_result(merged_result)
