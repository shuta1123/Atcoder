import sys
from pathlib import Path

lib_dir = Path(sys.argv[1])
arg_list = ['-I ' + str(p.resolve()) for p in lib_dir.iterdir() if p.is_dir()]
print(' '.join(arg_list), end='')