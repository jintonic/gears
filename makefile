FLAG=$(shell geant4-config --cflags) 
LIBS=$(shell geant4-config --libs) -L/share/apps/xerces-c/lib

ROOTAVAILABLE:=$(shell command -v root-config 2> /dev/null)
ifdef ROOTAVAILABLE
  ROOTCONFIG = root-config
  ROOTCFLAGS:= $(shell $(ROOTCONFIG) --cflags)
  ROOTLIBS  := $(shell $(ROOTCONFIG) --libs)
  LIBS+=$(ROOTLIBS)
  FLAG+=$(ROOTCFLAGS) -DhasROOT
endif

SRC=$(wildcard *.C)
TGT=$(SRC:.C=.exe)

.PHONY: all clean docs

all: $(TGT)

%.exe: %.C
	$(CXX) $(FLAG) $^ -o $@     $(LIBS) -lxerces-c 

clean:
	rm -f `cat .gitignore`

docs:
	doxygen Doxyfile
