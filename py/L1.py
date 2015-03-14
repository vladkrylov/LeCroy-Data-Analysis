import os
import re
import sys
import getopt

from subprocess import call

from make_data_file_list import save_file_list, get_tmp_dir, get_proj_dir
# from run_info import add_run_info

if __name__ == "__main__":
    experiment_dir = None
    baseline_run_id = 21
    
    rootfile_base = 'Run'
#     rootfile_pat = re.compile(".*(%s\d+).*" % rootfile_base)
#     exe = os.path.join(get_proj_dir(), "Debug/LeetechDataAnalysis")
    exe = os.path.join(get_proj_dir(), "bin/croyana")
    temp_list_file = os.path.join(get_tmp_dir(), "data_files.txt")
    
    opts, args = getopt.getopt(sys.argv[1:], 'd:', [])
    for o, a in opts:
        if o == '-d':
            if not os.path.isdir(a):
                print "Wrong path to experiment data specified"
            else:
                experiment_dir = os.path.abspath(a)
                
    rootfiles_dir = os.path.join(experiment_dir, "ROOT_files")
    if not os.path.isdir(rootfiles_dir):
        os.mkdir(rootfiles_dir)
    
    run_dirs = [d for d in os.listdir(experiment_dir) if rootfile_base in d]
    
    for d in run_dirs:
        save_file_list(data_dir=os.path.join(experiment_dir, d), out_filename=temp_list_file)
        
        out_rootfile = os.path.join(rootfiles_dir, "%s.root" % d)
        call([exe, temp_list_file, out_rootfile])
        
#         add_run_info(out_rootfile)
        
        
        