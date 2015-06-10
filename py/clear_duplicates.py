import os
from sys import argv
from clear_run_duplicates import clear_run_duplicates

def is_run(dir_name):
    if 'Run' in dir_name:
        return True
    else:
        return False

# data_path = "/run/media/vlad/00789D9D789D91D0/Leetech/RawData/Beamtime4_16.04.2015/17.04.2015"
# save_dir = "WaveformsListFiles"
data_path = os.path.abspath(argv[1])
save_dir = os.path.abspath(argv[2])
if not os.path.exists(save_dir):
    os.makedirs(save_dir)
channel = int(argv[3])

run_dirs = [d for d in os.listdir(data_path) if os.path.isdir(os.path.join(data_path, d)) and is_run(d)]

prefix = 'C%d_FBLM_' % channel
suffix = '_00000.txt'

for d in run_dirs:
    run_dir = os.path.join(data_path, d, "Waveforms")
    out_file = os.path.join(save_dir, "%s.txt" % d)
    clear_run_duplicates(run_dir, out_file, prefix, suffix)
    
    print d

