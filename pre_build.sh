#!/bin/bash

make clean

cd $1/lib
make
make clean_obj
cd ..


#cp $1/lib/Waveform.so $ROOTSYS/lib/root/Waveform.so
#rootcint $1/generated/waveform_dict.cxx -c $1/inc/Waveform.h

