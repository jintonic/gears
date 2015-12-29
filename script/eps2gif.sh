#!/bin/sh
# usage: ./eps2gif.sh /path/to/g4.mac 1000
G=$HOME/gears
M=animate.mac
sed -e 's|geo/|'$G'/geo/|' -e '/accum/d' -e 's|mOn [0-9]*|mOn '$2'|' $1 > $M

export DAWN_BATCH=1
export G4DAWNFILE_MAX_FILE_NUM=$2
$G/gears.exe $M

# -delay 10/2: 4 seconds
# -delay 10: 10/100 seconds
# IE has a minimum speed of 6
# No browser honors a 0 delay
convert -delay 20 -dispose None g4*.eps merged.gif

rm -f $M g4*.prim .DAWN*
