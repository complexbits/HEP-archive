CPP=KCC
LD=KCC
SPECIALFLAGS=--thread_safe --exceptions
ROOTCFLAGS=$(shell root-config --cflags)
ROOTLIBS=$(shell root-config --libs)

CFLAGS = $(SPECIALFLAGS) -I- -I./
LFLAGS = $(SPECIALFLAGS) 

RCXX=$(CFLAGS) $(ROOTCFLAGS)
RLXX=$(LFLAGS) $(ROOTLIBS)

all: ramp

ramp: ReadSAMinfo.o

ReadSAMinfo.o : ReadSAMinfo.cpp
	$(CPP) $(RCXX) -c ReadSAMinfo.cpp

RecoGen.o: RecoGen.cpp
	$(CPP) $(RCXX) -c RecoGen.cpp
RecoGen: RecoGen.o ReadSAMinfo.o
	$(LD) RecoGen.o ReadSAMinfo.o $(RLXX) -o RecoGen

clean:
	rm -rf ti_files
	rm -f *~ *.o
	rm -f RecoGen

