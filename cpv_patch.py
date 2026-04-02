#!/usr/bin/python3
# -*- coding: utf-8 -*-

from libs import cli, register_cpv_patch_commands


register_cpv_patch_commands(cli)

if __name__ == '__main__':
    cli()
