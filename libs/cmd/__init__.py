from libs.cmd.doc import _register_doc
from libs.cmd.new import _register_new
from libs.cmd.verify import _register_verify
from libs.cmd.fmt import _register_fmt
from libs.cmd.meta import _register_meta
from libs.cmd.pack import _register_pack


def register_all_commands(cli):
    _register_doc(cli)
    _register_new(cli)
    _register_verify(cli)
    _register_fmt(cli)
    _register_meta(cli)
    _register_pack(cli)


__all__ = ['register_all_commands']
