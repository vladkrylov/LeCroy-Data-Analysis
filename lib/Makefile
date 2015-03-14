name = Waveform.so

LDFLAGS = $(shell root-config --libs)

CPPFLAGS = $(shell root-config --cflags)
CPPFLAGS += -I../inc
CPPFLAGS += -I$(shell root-config --incdir)

PROJ_DIR = /home/vlad/Program_Files/Eclipse/g45work/LeetechDataAnalysis
LIB_DIR = $(PROJ_DIR)/lib

all: generate_dict obj
	g++ -shared $(CPPFLAGS) $(LDFLAGS) WaveformDict.o Waveform.o -o $(name)
	
generate_dict: clean
	rootcint WaveformDict.cpp -c ../inc/Waveform.h

obj:
	g++ $(CPPFLAGS) -c -fpic WaveformDict.cxx
	g++ $(CPPFLAGS) -c -fpic ../src/Waveform.cpp
	
clean:
	rm -rf $(name) *.o WaveformDict.* *gch
	
clean_obj:
	rm -rf *.o *gch	