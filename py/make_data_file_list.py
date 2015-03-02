import ROOT
import os
import re
import sys
import inspect
import getopt

from subprocess import call

# global parameters
temp_dir = '../'

def get_py_dir():
    """Returns full path to this file"""
    return os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))

def get_proj_dir():
    """Returns full path to project.
    It is assumed that this file was placed in project_dir/py directory"""
    return os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))

if __name__ == "__main__":
    print get_py_dir()
    
    