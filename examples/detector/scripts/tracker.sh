#!/bin/sh
output="tracker.tg"
echo -n "Creating $output... "

cat << EOC > $output
:volu world BOX 10*cm 10*cm 10*cm G4_Galactic
:vis world OFF

:rotm r000 0 0 0

:volu tracker BOX 1*micrometer 9*cm 9*cm G4_Galactic
EOC

id=1
while [ $id -le 81 ]; do
  x=$((id*2-82))*mm
  echo ":place tracker $id world r000 $x 0 0" >> $output
  echo ":color tracker 0.3 0.4 0.3" >> $output
  id=$((id+1))
done

echo Done.
