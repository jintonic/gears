#!/usr/bin/gnuplot -persist
# draw refractive index (n) of CsI
# https://refractiveindex.info/?shelf=main&book=CsI&page=Rodney

# n(wavelength[um])
nVSw(x) = sqrt(1 \
      +0.34617251/(1-(0.0229567/x)**2) \
      +1.0080886/(1-(0.1466/x)**2) \
      +0.28551800/(1-(0.1810/x)**2) \
      +0.39743178/(1-(0.2120/x)**2) \
      +3.3605359/(1-(161.0/x)**2) \
      )

# n(energy[eV])
nVSe(x) = sqrt(1 \
      +0.34617251/(1-(0.0229567/h/c*x)**2) \
      +1.0080886/(1-(0.1466/h/c*x)**2) \
      +0.28551800/(1-(0.1810/h/c*x)**2) \
      +0.39743178/(1-(0.2120/h/c*x)**2) \
      +3.3605359/(1-(161.0/h/c*x)**2) \
      )
h=4.135667662e-15 # [eV*s]
c=2.99792458e14 # [um/s]

# plot settings
set xlabel "photon wavelength [um]"
set x2label "photon energy [eV]" # set top axis label
set ylabel "n, refractive index of CsI"
set xrange [0.25:50]
set x2range [0.0248:4.18]
set x2tics # turn on x2(top axis) tics
set xtics nomirror # turn off x tics mirrored on top
set grid x2 y

# plot to a png file
set terminal png giant
set output 'CsI.png'
plot nVSw(x) axes x1y1 title "n(wavelength)",\
        nVSe(x) axes x2y1 title "n(energy)"
set output # close terminal
