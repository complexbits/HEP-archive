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

examples:  example_tick example_xsec test_stage3 example_prescale



example_tick.o: example_tick.cpp
	$(CPP) $(RCXX) -c example_tick.cpp
example_tick: example_tick.o
	$(LD) example_tick.o $(RLXX) -o example_tick

example_prescale.o: example_prescale.cpp
	$(CPP) $(RCXX) -c example_prescale.cpp
example_prescale: example_prescale.o
	$(LD) example_prescale.o $(RLXX) -o example_prescale

example_xsec.o: example_xsec.cpp
	$(CPP) $(RCXX) -c example_xsec.cpp
example_xsec: example_xsec.o
	$(LD) example_xsec.o $(RLXX) -o example_xsec

test_stage3.o: test_stage3.cpp
	$(CPP) $(RCXX) -c test_stage3.cpp
test_stage3: test_stage3.o
	$(LD) test_stage3.o $(RLXX) -o test_stage3

clean:
	rm -rf ti_files
	rm -f *~ *.o
	rm -f  example_tick example_xsec test_stage3 example_prescale



