"""CLI setup and command registration."""

import click
import coloredlogs

from libs.commands.doc import register_doc_command
from libs.commands.new import register_new_command
from libs.commands.test_usage import register_test_command
from libs.commands.fmt import register_fmt_command
from libs.commands.matrix import register_meta_command
from libs.commands.pack import register_pack_command


@click.group()
@click.option('-l', '--level', type=click.Choice(['CRITICAL', 'ERROR', 'WARNING', 'INFO', 'DEBUG']), help='log level',
              default='INFO')
def cli(level: str):
    coloredlogs.install(level=level,
                        fmt='%(asctime)s %(levelname)s %(programname)s::%(name)s [%(process)d] %(message)s',
                        field_styles={'asctime': {'color': 'green'},
                                      'hostname': {'color': 'red'},
                                      'levelname': {'bold': True, 'color': 'magenta'},
                                      'name': {'faint': True, 'color': 'blue'},
                                      'programname': {'bold': True, 'color': 'cyan'},
                                      'process': {'faint': True, 'color': 'green'},
                                      'username': {'color': 'yellow'}},
                        level_styles={'critical': {'bold': True, 'color': 'red'},
                                      'debug': {'color': 'cyan'},
                                      'error': {'color': 'red'},
                                      'info': {'bright': True, 'color': 'white'},
                                      'notice': {'color': 'magenta'},
                                      'spam': {'color': 'green', 'faint': True},
                                      'success': {'bold': True, 'color': 'green'},
                                      'verbose': {'color': 'blue'},
                                      'warning': {'bright': True, 'color': 'yellow'}})


# Register all commands
register_new_command(cli)
register_doc_command(cli)
register_test_command(cli)
register_fmt_command(cli)
register_meta_command(cli)
register_pack_command(cli)

if __name__ == '__main__':
    cli()
