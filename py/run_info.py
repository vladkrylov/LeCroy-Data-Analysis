import os
import numpy as n

import ROOT

class RunInfo(ROOT.TObject):
    def __init__(self):
        self.x = 1

    def TestWrite(self, root_filename=None):
        f = ROOT.TFile(root_filename, "recreate")
        t = ROOT.TTree("name_of_tree", "tree title")

        # create 1 dimensional float arrays (python's float datatype corresponds to c++ doubles)
        # as fill variables
        nm = n.zeros(1, dtype=float)
        u = n.zeros(1, dtype=float)
        
        # create the branches and assign the fill-variables to them
        t.Branch('normal', nm, 'normal/D')
        t.Branch('uniform', u, 'uniform/D')
        
        # create some random numbers, fill them into the fill varibles and call Fill()
        for i in xrange(100000):
            nm[0] = ROOT.gRandom.Gaus()
            u[0] = ROOT.gRandom.Uniform()
            t.Fill()
        
        # write the tree into the output file and close the file
        f.Write()
        f.Close()
        
        

if __name__ == "__main__":
    test = RunInfo()
    test.TestWrite("Test.root")
    test.Test2Write("Info.root")

