#!/usr/bin/gnuplot -persist
set lmargin -1
set bmargin -1
set rmargin -1
set tmargin -1

set title "Ar39 beta source energy spectrum"
set ylabel "Normalized intensity"
set xlabel "beta energy [KeV]"
set key reverse 

set terminal png giant
set output 'Ar39.png'
plot "Ar39.dat" 

set terminal postscript eps "Times" 32
set output 'Ar39.eps'
set notitle
set size 1.8, 0.8
replot

set output # important! close output file
