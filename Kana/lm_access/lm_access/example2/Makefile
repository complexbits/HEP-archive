CPP=gcc
LD=gcc
SPECIALFLAGS= --exceptions
ROOTCFLAGS=$(shell root-config --cflags)
ROOTLIBS=$(shell root-config --libs)

CFLAGS = $(SPECIALFLAGS) -I- -I../
LFLAGS = $(SPECIALFLAGS) -L$(SRT_PRIVATE_CONTEXT)/lib/$(SRT_SUBDIR)/ -llm_access -lz

RCXX=$(CFLAGS) $(ROOTCFLAGS)
RLXX=$(LFLAGS) $(ROOTLIBS)

all: examples

examples:  example_parentage



example_parentage.o: example_parentage.cpp
	$(CPP) $(RCXX) -c example_parentage.cpp
example_parentage: example_parentage.o
	$(LD) example_parentage.o $(RLXX) -o example_parentage


clean:
	rm -rf ti_files
	rm -f *~ *.o
	rm -f  example_parentage

