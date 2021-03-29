#!/bin/bash

# add gears directory to PATH
export GEARS="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
export PATH=$GEARS/examples/detector/visualization:$GEARS:$PATH

# add Geant4 libs to (DY)LD_LIBRARY_PATH
G4LIB=`geant4-config --libs | awk '{print $1}'`
G4LIB=${G4LIB#-L}
if [[ "$OSTYPE" == *"darwin"* ]]; then # Mac OSX
  if [[ ${G4LIB:0:10} != "/usr/local" ]]; then # not in /usr/local
    export DYLD_LIBRARY_PATH=$G4LIB:$DYLD_LIBRARY_PATH
  fi
else # Linux
  export LD_LIBRARY_PATH=$G4LIB:$LD_LIBRARY_PATH
fi

# print missing databases
while read line; do
  database=`echo $line | awk '{print $2}'`
  if [ $database = "NOTFOUND" ]; then echo $line; fi
done <<< "$(geant4-config --check-datasets)"

# set Geant4 database locations
while read line; do
  database=`echo $line | awk '{print $2}'`
  folder=`echo $line | awk '{print $3}'`
  export $database=$folder
done <<< "$(geant4-config --datasets)"
