FLAG=$(shell geant4-config --cflags) 
LIBS=$(shell geant4-config --libs)

GDML_ENABLED:=$(shell geant4-config --has-feature gdml)
ifeq ($(GDML_ENABLED),yes)
  FLAG+=-DhasGDML
  LIBS+=-lxerces-c
endif

SRC=$(wildcard *.cc)
TGT=$(SRC:.cc=.exe)

.PHONY: all clean docs

all: $(TGT)

%.exe: %.cc
	$(CXX) $(FLAG) $^ -o $@ $(LIBS)

clean:
	rm -f `cat .gitignore`

docs:
	doxygen Doxyfile
