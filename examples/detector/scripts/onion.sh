#!/bin/sh
output="onion.tg"

cat << END > $output
// default unit for length is mm
:volu skin100 ORB 100 G4_AIR
:color skin100 0.2 0.4 0.3

:rotm r000 0 0 0

END

r=95
while [ $r -ge 5 ]; do
  echo ":volu skin$r ORB $r G4_AIR" >> $output
  echo ":place skin$r 1 skin$((r+5)) r000 0 0 0" >> $output
  echo ":color skin$r 0.3 0.4 0.$r" >> $output
  r=$((r-5))
done
