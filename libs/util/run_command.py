import subprocess
import time
from queue import Queue
from threading import Thread
from typing import Any, Callable, Iterable
from libs.decorator import with_logger, with_timer


@with_logger
@with_timer
def run_command(command: Callable[[Any], tuple[list[str], dict]], params: Iterable, thread_limit: int, time_limit: float | None = None, **kwargs) -> list:
    logger = kwargs.get('logger')

    params_queue = Queue()
    for p in params:
        params_queue.put_nowait(p)
    failed_params: Queue = Queue()

    def single_process(thread_id: int):
        while True:
            if params_queue.empty():
                return
            param = params_queue.get()
            if param is None:
                return
            try:
                cmd, extra_args = command(param)
                post_run = extra_args.pop('post_run', None)
                hide_stdout = extra_args.pop('hide_stdout', False)
                extra_args = extra_args.get('subprocess_args', {})
                if time_limit is not None:
                    extra_args.setdefault('timeout', time_limit)

                logger.debug(
                    f'Thread #{thread_id}: cmd:{cmd!r}, Param {param!r}, extra_args: {extra_args!r}')

                result = subprocess.run(
                    cmd,
                    capture_output=True,
                    text=True,
                    encoding='utf8',
                    **extra_args
                )
                if (not hide_stdout and result.stdout) or result.stderr:
                    msg = f"cmd:{cmd!r}\n    param: {param!r}\n"
                    if not hide_stdout and result.stdout:
                        msg += f"    stdout:\n{result.stdout}\n"
                    if result.stderr:
                        msg += f"    stderr:\n{result.stderr}\n"
                    logger.info(msg.rstrip())
                if result.returncode:
                    raise subprocess.CalledProcessError(
                        result.returncode, result.args)
                if post_run:
                    post_run(result)
            except subprocess.TimeoutExpired:
                logger.error(
                    f'cmd:{cmd!r}\n    param: {param!r}\n    timeout expired')
                failed_params.put((cmd, param))
            except subprocess.CalledProcessError as e:
                logger.error(
                    f'cmd:{cmd!r}\n    param: {param!r}\n    {e.output}')
                failed_params.put((cmd, param))
            except Exception as e:
                logger.error(
                    f'cmd:{cmd!r}\n    param: {param!r}\n    unexpected error: {e}')
                failed_params.put((cmd, param))

    def heartbeat():
        while True:
            sz = params_queue.qsize()
            logger.debug(f"Heartbeat: {sz} params left")
            if not sz:
                return
            time.sleep(1)

    threads = [
        Thread(
            target=single_process,
            args=(i,),
            name=str(i)
        )
        for i in range(thread_limit)
    ]
    threads.append(
        Thread(
            target=heartbeat,
            name='heartbeat'
        )
    )

    for thread in threads:
        thread.start()
    for thread in threads:
        thread.join()
    return list(failed_params.queue)
