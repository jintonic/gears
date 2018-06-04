FLAG=$(shell geant4-config --cflags)
LIBS=$(shell geant4-config --libs)

#ifeq ( root-config , 0 )
ROOTCHECK := $(shell command -v 1root-config 2> /dev/null )

ROOTCONFIG = root-config
ROOTCFLAGS:= $(shell $(ROOTCONFIG) --cflags)
ROOTLIBS  := $(shell $(ROOTCONFIG) --libs)
LIBS += $(ROOTLIBS)
FLAG+= $(ROOTCFLAGS)

SRC=$(wildcard *.C)
TGT=$(SRC:.C=.exe)

.PHONY: all clean docs

all: $(TGT)
ifdef ROOTCHECK
hasROOT=yes
endif
%.exe: %.C
	$(CXX) $(FLAG) $^ -DhasROOT -o $@ $(LIBS)

clean:
	rm -f `cat .gitignore`

docs:
	doxygen Doxyfile
