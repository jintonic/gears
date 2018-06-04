FLAG=$(shell geant4-config --cflags)
LIBS=$(shell geant4-config --libs)

#ifeq ( root-config , 0 )
ROOTCHECK := $(shell command -v root-config 2> /dev/null )

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
FLAG+= -DhasROOT
endif
%.exe: %.C
	$(CXX) $(FLAG) $^ -o $@ $(LIBS)

clean:
	rm -f `cat .gitignore`

docs:
	doxygen Doxyfile
