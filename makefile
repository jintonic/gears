FLAG=$(shell geant4-config --cflags) 
LIBS=$(shell geant4-config --libs)

GDML_ENABLED:=$(shell geant4-config --has-feature gdml)
ifeq ($(GDML_ENABLED),yes)
  ifndef XERCESROOT
  $(error XERCESROOT needs to be defined to enable GDML)
  endif
  FLAG+=-DhasGDML
  LIBS+=-L$(XERCESROOT)/lib -lxerces-c
endif

SRC=$(wildcard *.cc)
TGT=$(SRC:.cc=.exe)

.PHONY: all clean docs hdf5

all: $(TGT)

%.exe: %.cc
	$(CXX) $(FLAG) -o $@ $(LIBS) $^
clean:
	rm -f `cat .gitignore`
docs:
	doxygen Doxyfile
hdf5 xml csv:
	sed 's/g4root/g4$@/' gears.cc > g$@.cc
