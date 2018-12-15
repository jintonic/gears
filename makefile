FLAG=$(shell geant4-config --cflags) 
LIBS=$(shell geant4-config --libs)
# check if GDML is enabled in GEANT4
GDML_ENABLED:=$(shell geant4-config --has-feature gdml)
ifeq ($(GDML_ENABLED),yes)
  FLAG+=-DhasGDML
  ifndef XERCESROOT
    LIBS+=-lxerces-c
  else
    LIBS+=-L$(XERCESROOT)/lib -lxerces-c
  endif
endif

SRC=$(wildcard *.cc)
TGT=$(SRC:.cc=.exe)

.PHONY: all clean docs hdf5 xml csv

all: $(TGT)

%.exe: %.cc
ifeq ($(GDML_ENABLED),yes)
	@echo compile $^ with libxerces-c to enable GDML
ifndef XERCESROOT
	@echo export XERCESROOT=/path/to/your/xerces-c only if $(CXX) cannot find libxerces-c
endif
endif
	$(CXX) $(FLAG) -o $@ $(LIBS) $^
clean:
	rm -f `cat .gitignore`
docs:
	doxygen Doxyfile
hdf5 xml csv:
	@echo -n creating g$@.cc for output in $@ format...
	@sed 's/g4root/g4$@/' gears.cc > g$@.cc
	@echo done!
	@echo please type `make` to compile g$@.cc
