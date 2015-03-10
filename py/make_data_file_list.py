import os
import re
import sys
import inspect
import getopt

from subprocess import call

# global parameters

def get_py_dir():
    """Returns full path to this file"""
    return os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))

def get_proj_dir():
    """Returns full path to project.
    It is assumed that this file was placed in project_dir/py directory"""
    return os.path.dirname(get_py_dir())

def get_tmp_dir():
    """Returns full path to directory with temporal files
    project_dir/tmp
    Creates it if it does not exists"""
    tmp = '%s/tmp' % get_proj_dir()
    
    if not os.path.exists(tmp):
        os.makedirs(tmp)
    return tmp

def get_channel_number():
    pass

def save_file_list(data_dir=None, 
                   out_filename="data_files.txt", 
                   patt="C\d+_FBLM_\d+_00000\.txt", 
                   number_of_channels=1):
    """Looks for files in data_dir and its subfolders and
    writes all filenames that matches to patt in tmp_dir/out_filename text file"""
    pat = re.compile(patt)
    if not data_dir:
        data_dir = os.getcwd()
    
    data_files_list = [];
    for path, subdirs, files in os.walk(data_dir):
        data_files_list.extend([os.path.join(path, name) for name in files if pat.match(name)]) 
            
    with open(os.path.join(get_tmp_dir(), "data_files.txt"), 'w') as tmp:
        tmp.write('\n'.join(data_files_list))
 
       
if __name__ == "__main__":
    pat = re.compile("C[2]_FBLM_\d+_00000\.txt")
    
    data_dir = None
    number_of_channels = 1;
    
    opts, args = getopt.getopt(sys.argv[1:], 'd:noc:', [])
    for o, a in opts:
        if o == '-d':
            if not os.path.exists(a) or not os.path.isdir(a):
                print "Wrong path to data specified"
                print "The full path must be specified as an argument"
            else:
                data_dir = a
        elif o == '-noc':
            number_of_channels = a
    
    print number_of_channels, type(number_of_channels)
#     save_file_list(data_dir=data_dir, patt=pat, number_of_channels=1)



