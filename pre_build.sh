#!/bin/bash

rm -rf $1/generated/waveform_dict.*
make clean

rootcint $1/generated/waveform_dict.cxx -c $1/inc/Waveform.h $1/inc/Run.h

