EXE = bin/croyana

CC = g++

SOURCES = main.cpp src/Waveform.cpp lib/WaveformDict.cpp
OBJECTS = $(SOURCES:.cpp=.o)

LDFLAGS =     $(shell root-config --libs)
CPPFLAGS = -c -Wall 
CPPFLAGS +=   $(shell root-config --cflags)
CPPFLAGS += -I$(shell root-config --incdir)
CPPFLAGS += -I./inc

all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	
.cpp.o:
	$(CC) $(CPPFLAGS) -o $@ $<
	
clean:
	rm -rf *.o $(EXE)	