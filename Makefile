# Check if geant4-config is available in your PATH.
# It should for a proper GEANT4 installation and configuration.
ifneq ($(OS), Windows_NT)
  ifeq (, $(shell which geant4-config))
    $(error "Cannot find geant4-config, please check your GEANT4 installation")
  endif
endif

# Setup flags used by the implicit make rule: %:%.cc
CXXFLAGS=$(shell geant4-config --cflags)
LDLIBS=$(shell geant4-config --libs)
# fix cxxflags for Geant4.10.7.0
CXXFLAGS+=$(shell geant4-config --cflags |awk '{print $$NF}'|sed 's|de/Geant4|de|')
CXXFLAGS+=-Wno-shadow

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

.PHONY: all clean hdf5 xml csv install

all: $(EXE)
	@echo --------------------------------------------------------
	@echo To install, please add the following line
	@echo `tput bold` source ${PWD}/gears.sh `tput sgr0`
	@printf "%s" "to `tput bold`~/.bashrc`tput sgr0` in Linux or "
	@echo `tput bold`~/.bash_profile`tput sgr0` in a Mac
	@echo \(or `tput bold`~/.zshrc`tput sgr0` if you use zsh instead of bash\)
	@echo --------------------------------------------------------
clean:
	$(RM) -r `cat .gitignore`
hdf5 xml csv:
	@printf "%s" "Creating g$@.cc for output in $@ format... "
	@sed 's/g4root/g4$@/' gears.cc > g$@.cc
	@echo done!
	@echo Please type `tput bold`make`tput sgr0` to compile g$@.cc
