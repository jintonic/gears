FLAG=$(shell geant4-config --cflags) 
LIBS=$(shell geant4-config --libs)
ifneq ($(LD_LIBRARY_PATH),) # linux
  LIBS+=$(shell echo "-L$(LD_LIBRARY_PATH)" | sed 's/:/ -L/g')
endif
ifneq ($(DYLD_LIBRARY_PATH),) # mac
  LIBS+=$(shell echo "-L$(DYLD_LIBRARY_PATH)" | sed 's/:/ -L/g')
endif

ifeq ($(shell geant4-config --has-feature gdml),yes)
  FLAG+=-DhasGDML
  LIBS+=-lxerces-c
endif
ifeq ($(shell geant4-config --has-feature hdf5),yes)
  LIBS+=-lhdf5
endif

SRC=$(wildcard *.cc)
TGT=$(SRC:.cc=.exe)

.PHONY: all clean docs hdf5 xml csv

all: $(TGT)

%.exe: %.cc
	$(CXX) $(FLAG) $^ $(LIBS) -o $@
clean:
	rm -f `cat .gitignore`
docs:
	doxygen Doxyfile
hdf5 xml csv:
	@echo -n creating g$@.cc for output in $@ format...
	@sed 's/g4root/g4$@/' gears.cc > g$@.cc
	@echo done!
	@echo compiling g$@.cc
	make
