#!/usr/bin/python3
# -*- coding: utf-8 -*-

from libs import cli, register_main_commands

register_main_commands(cli)

if __name__ == '__main__':
    cli()
