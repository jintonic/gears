#!/bin/sh
# usage: ./cut.sh

# https://stackoverflow.com/questions/592620/how-can-i-check-if-a-program-exists-from-a-bash-script
type gears >/dev/null 2>&1 || { echo >&2 "Can't find gears, abort."; exit 1; }

# run geant4
export DAWN_BATCH=1
M=cut.mac
for step in 0 1 2 3; do
  sed 's|0.tg|'$step'.tg|' $M > $step.mac
  gears $step.mac 2>cut.log
  err=`sed -n '/corrapted/p' cut.log`
  if [ -n "$err" ]; then 
    echo $err; read -p "Press any key to continue..."
  fi
  rm -f $step.mac cut.log
done

# avoid drawing lines in dawn
cat > .DAWN_1.history << EOF
61.3125
45
0
0
0
3.55271e-15
-10.8239
fd0.866025
3
0.001
0
1
1
1
0.5
0.5
0.5
19
71
-0.1
-0.1
-0.1
3
70
0.1
0
1
1
NONE
1
0
EOF

unset DAWN_BATCH # .DAWN_1.history wont' be read in batch mode
for step in 0 1 2 3; do dawn -d g4_*$step.prim; done

# eps cannot have transparent background, png can
# -transparent white: make white color transparent
# -trim: remove margins
for eps in `ls *.eps`; do
  CMD="convert -transparent white -trim $eps ${eps%.*}.png"
  echo $CMD
  $CMD
done

if [ -f g4_*3.png ]; then
  rm -f *.prim *.eps .DAWN*
fi
