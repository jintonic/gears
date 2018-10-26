#!/usr/bin/gnuplot -persist
set lmargin -1
set bmargin -1
set rmargin -1
set tmargin -1

set title "AmBe neutron source energy spectrum"
set ylabel "Normalized intensity"
set xlabel "Neutron energy [MeV]"
set key reverse 

set terminal png giant
set output 'AmBe.png'
plot "AmBe.dat" using 1:2 title "Digitized data from Fig.5 in NIMA 366 (1995) 340" with line

set terminal postscript eps "Times" 32
set output 'AmBe.eps'
set notitle
set size 1.8, 0.8
replot

set output # important! close output file
