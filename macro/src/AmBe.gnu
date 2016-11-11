#!/usr/bin/gnuplot -persist
set terminal png giant
set output 'AmBe.png'

set lmargin -1
set bmargin -1
set rmargin -1
set tmargin -1

set title "AmBe neutron source energy spectrum"
set ylabel "Intensity [Arbitury unit]"
set xlabel "Neutron energy [MeV]"
set key reverse 
plot "AmBe.dat" using 1:2 title "Digitized data from Fig.5 in NIMA 366 (1995) 340" with line

set output # important! close output file
