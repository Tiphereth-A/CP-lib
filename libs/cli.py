"""CLI setup and command registration."""

import click
import coloredlogs

from libs.commands.clean import register_clean_command
from libs.commands.gen_nb import register_gen_nb_command
from libs.commands.gen_cs import register_gen_cs_command
from libs.commands.run_usage import register_run_usage_command
from libs.commands.compile import register_compile_command
from libs.commands.fmt import register_fmt_command
from libs.commands.new import register_new_command
from libs.commands.gentc import register_gentc_command


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
register_clean_command(cli)
register_gen_nb_command(cli)
register_gen_cs_command(cli)
register_run_usage_command(cli)
register_compile_command(cli)
register_fmt_command(cli)
register_new_command(cli)
register_gentc_command(cli)


if __name__ == '__main__':
    cli()
