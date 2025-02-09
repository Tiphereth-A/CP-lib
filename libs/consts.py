import os.path

from libs.classes.config import Config
from libs.classes.config_tcgen import ConfigTCGen

CONTENTS_DIR: str = os.path.join('.', '_gen')
CONTENTS_CS: str = os.path.join(CONTENTS_DIR, 'contents_cheatsheet.tex')
CONTENTS_NB: str = os.path.join(CONTENTS_DIR, 'contents_notebook.tex')

CONFIG = Config(os.path.join('.', 'config.yml'))
CONFIG_TCGEN = ConfigTCGen(os.path.join('.', 'tcgen.yml'))

CLEAN_EXT_NAME: list[str] = ['.aux', '.bbl', '.blg', '.dvi', 'fdb_latexmk', '.fls',
                             '.log', '.nav', '.out', '.pyg', '.snm', '.synctex.gz', '.toc', '.vrb', '.xdv']
