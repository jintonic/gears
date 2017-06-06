#!/bin/sh
cat AmBe.mac |grep hist|awk '{print $2,$3}' > AmBe.dat
gnuplot AmBe.gnu
rm -f AmBe.dat
