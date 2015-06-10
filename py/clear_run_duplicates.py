from filecmp import cmp
import os
from sys import argv

def find_neighbour(filename, prefix, suffix):
    f_path, f = os.path.split(filename)
    if f.startswith(prefix) and f.endswith(suffix):
        idx = int(f[len(prefix):-len(suffix)])
        if idx == 1:
            return 'first'
        prev_name = ''.join([prefix, str(idx-1), suffix])
        return os.path.join(f_path, prev_name)
    else:
        return None

# if len(argv) < 3:
#     raise Exception("""
# ###################################
# Path to waveforms and output file 
# name must be specified as an input 
# parameters
# ###################################""")

# data_path = os.path.abspath(argv[1])
# out_file = os.path.abspath(argv[2])
# prefix = 'C3_FBLM_'
# suffix = '_00000.txt'

def clear_run_duplicates(data_path, out_file, prefix, suffix):
    all_files = os.listdir(data_path)
    distinct_files = []
       
    for f in all_files:
        full_f = os.path.join(data_path, f)
        prev = find_neighbour(full_f, prefix, suffix)
        if (prev == 'first') or (prev and not cmp(prev, full_f)):
             distinct_files.append(full_f)
     
    with open(out_file, 'w') as tmp:
            tmp.write('\n'.join(sorted(distinct_files)))


