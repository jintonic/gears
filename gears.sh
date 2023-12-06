#!/bin/bash

# add gears directory to PATH
export GEARS="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
export PATH=$GEARS/tutorials/detector/visualization:$GEARS:$PATH

# print missing databases
while read line; do
  database=`echo $line | awk '{print $2}'`
  if [ $database = "NOTFOUND" ]; then echo $line; fi
done <<< "$(geant4-config --check-datasets)"

