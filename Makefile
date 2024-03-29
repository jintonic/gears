# Check if geant4-config is available in your PATH.
# It should for a proper GEANT4 installation and configuration.
ifneq ($(OS), Windows_NT)
  ifeq (, $(shell which geant4-config))
    $(error "Cannot find geant4-config, please check your GEANT4 installation")
  endif
endif

# Setup flags used by the implicit make rule: %:%.cc
CXXFLAGS=$(shell geant4-config --cflags) -fPIC
LDLIBS=$(shell geant4-config --libs)
# fix LDLIBS for Geant4.11.1.0
ifeq (11.1.0, $(shell geant4-config --version))
  LDLIBS+=-lG4ToolsSG
endif
# imbed Geant4 lib path to rpath on MacOS
# https://stackoverflow.com/a/12099167/1801749
# https://stackoverflow.com/a/6638539/1801749
ifeq (Darwin, $(shell uname -s))
  LDLIBS+="-Wl,-rpath,$(shell geant4-config --prefix)/lib"
endif

# In case that Xerces-c and HDF5 libs are in LD_LIBRARY_PATH
# add them in the LDLIBS flag. (Fixme: macOS doesn't use LD_LIBRARY_PATH)
ifneq ($(LD_LIBRARY_PATH),)
  LDLIBS+=$(shell echo "-L$(LD_LIBRARY_PATH)" | sed 's/:/ -L/g')
endif

# Enable GDML and HDF5 if they are enabled in GEANT4
ifeq ($(shell geant4-config --has-feature gdml),yes)
  CXXFLAGS+=-DhasGDML
  LDLIBS+=-lxerces-c
endif
ifeq ($(shell geant4-config --has-feature hdf5),yes)
  LDLIBS+=-lhdf5
endif

SRC=$(wildcard *.cc) # a list of all C++ source files
EXE=$(SRC:.cc=) # a list of all executables

.PHONY: all clean

all: $(EXE)
	@echo --------------------------------------------------------
	@echo To install, simply move `tput bold`gears`tput sgr0` to a desired folder
	@echo --------------------------------------------------------
clean:
	$(RM) -r `cat .gitignore`
