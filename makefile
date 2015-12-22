FLAG=$(shell geant4-config --cflags)
LIBS=$(shell geant4-config --libs)

SRC=$(wildcard *.C)
TGT=$(SRC:.C=.exe)

.PHONY: all clean

all: $(TGT)

%.exe: %.C
	g++ $(FLAG) $(LIBS) $^ -o $@

clean:
	rm -f `cat .gitignore`
