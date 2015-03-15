#!/bin/bash


cd lib
make
cd ..

make
python py/L1.py -d test_data/

root -l load.cxx -l test_data/ROOT_files/Run10.root

#cp $1/lib/Waveform.so $ROOTSYS/lib/root/Waveform.so
#rootcint $1/generated/waveform_dict.cxx -c $1/inc/Waveform.h

