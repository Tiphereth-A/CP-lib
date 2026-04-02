from libs.cmd.doc import _register_doc
from libs.cmd.new import _register_new
from libs.cmd.verify import _register_verify
from libs.cmd.fmt import _register_fmt
from libs.cmd.meta import _register_meta
from libs.cmd.pack import _register_pack

from libs.cmd.patch_cpvdoc import _register_patch_cpvdoc


def register_main_commands(cli):
    _register_doc(cli)
    _register_new(cli)
    _register_verify(cli)
    _register_fmt(cli)
    _register_meta(cli)
    _register_pack(cli)


def register_cpv_patch_commands(cli):
    _register_patch_cpvdoc(cli)


__all__ = ['register_main_commands', 'register_cpv_patch_commands']
