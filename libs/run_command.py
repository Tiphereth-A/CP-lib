import subprocess
import time
from queue import Queue
from threading import Thread
from typing import Any, Callable, Iterable
from libs.decorator import with_logger, with_timer


@with_logger
@with_timer
def run_command(command: Callable[[Any], list[str]], thread_limit: int, params: Iterable, **kwargs) -> list:
    logger = kwargs.get('logger')

    params_queue = Queue()
    for p in params:
        params_queue.put_nowait(p)
    failed_params: Queue = Queue()

    def single_process(thread_id: int):
        while True:
            param=params_queue.get()
            if param is None:
                return
            logger.debug(f'Thread #{thread_id}: Param {param}')
            try:
                result = subprocess.run(
                    command(param),
                    capture_output=True,
                    text=True,
                    encoding='utf8'
                )
                if result.stdout or result.stderr:
                    msg = f"param: {param}\n"
                    if result.stdout:
                        msg += f"    stdout:\n{result.stdout}\n"
                    if result.stderr:
                        msg += f"    stderr:\n{result.stderr}\n"
                    logger.info(msg.rstrip())
                if result.returncode:
                    raise subprocess.CalledProcessError(
                        result.returncode, result.args)
            except subprocess.CalledProcessError:
                failed_params.put(param)

    def heartbeat():
        while True:
            sz=params_queue.qsize()
            logger.debug(f"Heartbeat: {sz} params left")
            if not sz:
                return
            time.sleep(30)

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
