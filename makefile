FLAG=$(shell geant4-config --cflags)
LIBS=$(shell geant4-config --libs)

ROOTCONFIG = root-config
ROOTCFLAGS:= $(shell $(ROOTCONFIG) --cflags)
ROOTLIBS  := $(shell $(ROOTCONFIG) --libs)
LIBS += $(ROOTLIBS)
FLAG+= $(ROOTCFLAGS)

SRC=$(wildcard *.C)
TGT=$(SRC:.C=.exe)

.PHONY: all clean docs

all: $(TGT)

%.exe: %.C
	g++ $(FLAG) $(LIBS) $^ -o $@

clean:
	rm -f `cat .gitignore`

docs:
	doxygen Doxyfile
