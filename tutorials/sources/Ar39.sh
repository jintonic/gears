#!/bin/sh
cat Ar39.mac |grep "hist/point" |awk '{print $2,$3}' > Ar39.dat
gnuplot Ar39.gnu
rm -f Ar39.dat
