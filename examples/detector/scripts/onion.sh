#!/bin/sh
output="onion.tg"
echo -n "Creating $output... "

cat << END > $output
// default unit for length is mm
:volu skin50 ORB 50 G4_AIR
:color skin50 0.5 0 0.5

:rotm r000 0 0 0

END

r=45
while [ $r -ge 5 ]; do
  echo ":volu skin$r ORB $r G4_AIR" >> $output
  echo ":place skin$r 1 skin$((r+5)) r000 0 0 0" >> $output
  echo ":color skin$r 0.3 0 0.$r" >> $output
  r=$((r-5))
done
echo Done.
