import os
import re
import sys
import getopt

import ROOT
from array import array

tree_name = 'T'

def process_plot(rootfiles=[], x_branch=None, y_branch=None):
    """"""
    n = len(rootfiles)
    if n == 0: return None
    
    g = ROOT.TGraph(n)
    x = []
    y = []
    
    for r in rootfiles:
        if not os.path.isfile(r):
            print "%s: cannot open file" % r
            return None 
        
        f = ROOT.TFile(r)
        t = f.Get(tree_name)
        
        vec = ROOT.std.vector('double')()
        
        t.SetBranchAddress(y_branch, vec)
        n = t.GetEntries()
        t.GetEntry(0)
#         print vec
#         for e in vec:
#             print e
#         hy = ROOT.TH1F()
        
#         b = t.GetBranch(y_branch)
#         for i in xrange(b.GetEntries()):
#             t.GetEntry(i)
#             hy.Fill(tmp)
        
        
#         hy.Draw()
#         hy.Print()
        
#         raw_input("wait for input to close canvas...")
        
        
if __name__ == "__main__":
    process_plot(rootfiles=["/home/vlad/Program_Files/Eclipse/g45work/LeetechDataAnalysis/test_data/ROOT_files/Run1.root"],
                 x_branch=None, 
                 y_branch="amplitude")
    