#!/bin/sh

if [ $# -ne 2 ]; then 
  echo "usage: ./scatter.sh 1000"
  echo "since no number of simulations is specified, 100 is used by default"
  num=100; 
else 
  num=$1; 
fi

# get path to GEARS directory
src="${BASH_SOURCE[0]}"
while [ -h "$src" ] ; do src="$(readlink "$src")"; done
G="$(cd -P "$(dirname "$src")/../.." && pwd)"
echo $G

# tailor mac file for animation
M=animate.mac
sed -e 's|geom/|'$G'/geom/|' -e 's|mOn [0-9]*|mOn '$num'|' scatter.mac > $M

# run geant4 to create eps files
export DAWN_BATCH=1
export G4DAWNFILE_MAX_FILE_NUM=$num
$G/gears.exe $M

# convert eps to png
# eps cannot have transparent background, png can
# -transparent white: make white color transparent
# -trim: remove margins
for eps in `ls *.eps`; do
  CMD="convert -transparent white -trim $eps ${eps%.*}.png"
  echo $CMD
  $CMD
done

# create animation
# -delay 10/2: 4 seconds
# -delay 10: 10/100 seconds
# IE has a minimum speed of 6
# No browser honors a 0 delay
# -dispose None: keep previous png on canvas
CMD="convert -delay 8 -dispose None g4*.png merged.gif"
echo $CMD
$CMD

rm -f $M g4*.* .DAWN*
