#!/bin/sh
# usage: ./eps2gif.sh /path/to/g4.mac 1000

# tailor mac file for animation
G=$HOME/gears
M=animate.mac
sed -e 's|geo/|'$G'/geo/|' -e 's|mOn [0-9]*|mOn '$2'|' $1 > $M

# run geant4 to create eps files
export DAWN_BATCH=1
export G4DAWNFILE_MAX_FILE_NUM=$2
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
