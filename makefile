# Check if geant4-config is available in your PATH.
# It should for a proper GEANT4 installation and configuration.
ifeq (, $(shell which geant4-config))
  $(error "Cannot find geant4-config, please check your GEANT4 installation")
endif

# Setup flags used by the implicit make rule: %:%.cc
CXXFLAGS=$(shell geant4-config --cflags)
LDLIBS=$(shell geant4-config --libs)

# In case that GDML and HDF5 libs are in user specified folders,
# add them in the LDLIBS flag.
ifneq ($(LD_LIBRARY_PATH),) # Linux
  LDLIBS+=$(shell echo "-L$(LD_LIBRARY_PATH)" | sed 's/:/ -L/g')
endif
ifneq ($(DYLD_LIBRARY_PATH),) # MacOS
  LDLIBS+=$(shell echo "-L$(DYLD_LIBRARY_PATH)" | sed 's/:/ -L/g')
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

.PHONY: all clean hdf5 xml csv

all: $(EXE)
	@echo -e "\nBefore you run an executable, please check if you have"
	@echo `geant4-config --libs |awk '{print $$1}'|sed 's/-L//'`
	@echo "in your LD_LIBRARY_PATH (Linux) or DYLD_LIBRARY_PATH (MacOS),"
	@echo and `pwd` in your PATH
clean:
	$(RM) `cat .gitignore`
hdf5 xml csv:
	@echo -n creating g$@.cc for output in $@ format...
	@sed 's/g4root/g4$@/' gears.cc > g$@.cc
	@echo done!
	@echo Type make to compile g$@.cc
