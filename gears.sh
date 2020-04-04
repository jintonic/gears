#!/bin/sh
if [ "$GEARS"X != X ]; then return; fi # only do it once

# add gears directory to PATH
export GEARS="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
export PATH=$GEARS:$PATH

# add Geant4 libs to LD_LIBRARY_PATH
G4INSTALL=`geant4-config --prefix`
G4LIB=$G$INSTALL/lib64
export LD_LIBRARY_PATH=$G4LIB:$LD_LIBRARY_PATH

# print missting databases
while read line; do
  database=`echo $line | awk '{print $2}'`
  if [ $database = "NOTFOUND" ]; then echo $line; fi
done <<< $(geant4-config --check-datasets)

# set Geant4 database locations
while read line; do
  database=`echo $line | awk '{print $2}'`
  folder=`echo $line | awk '{print $3}'`
  export $database=$folder
done <<< $(geant4-config --datasets)
