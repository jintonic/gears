FROM fedora:latest

ARG v=11.0.2

# get pre-compiled geant4
RUN  curl -LO http://geant4-data.web.cern.ch/releases/lib_$v/Linux-g++8.3.0-CC7.tar.gz \
  && tar xfvz Linux-g++8.3.0-CC7.tar.gz && rm -r Linux-g++8.3.0-CC7.tar.gz \
  && mv Geant4-$v-Linux/bin/* usr/bin && mv Geant4-$v-Linux/lib64/* usr/lib64 \
  && mv Geant4-$v-Linux/include/* usr/include && mv Geant4-$v-Linux/share/* usr/share \
  && sed -i "s|afs/cern.ch/user/g/gunter/l/releases/web/$v/install/Geant4-$v-Linux/share/Geant4-$v|root/gears/INSTALL/Geant4|g" usr/bin/geant4.sh \
  && sed -i "s|afs/cern.ch/user/g/gunter/l/releases/web/$v/install/Geant4-$v-Linux/share/Geant4-$v|root/gears/INSTALL/Geant4|g" usr/bin/geant4-config \
  && rm -fr /Geant4-$v-Linux

# compile GEARS
RUN  dnf install -y which ncurses gcc-c++ mesa-libGL-devel libXmu-devel expat-devel \
  && dnf clean all && rm -fr /var/cache/*
RUN  curl -LO https://github.com/jintonic/gears/raw/master/gears.cc \
  && curl -LO https://github.com/jintonic/gears/raw/master/Makefile \
  && make && mv gears usr/bin && rm -f gears.cc Makefile

ENV PS1="\u@Geant4.$v:\w \$ "
ENV G4NEUTRONHPDATA="/root/gears/INSTALL/Geant4/data/G4NDL4.6"
ENV G4LEDATA="/root/gears/INSTALL/Geant4/data/G4EMLOW8.0"
ENV G4LEVELGAMMADATA="/root/gears/INSTALL/Geant4/data/PhotonEvaporation5.7"
ENV G4RADIOACTIVEDATA="/root/gears/INSTALL/Geant4/data/RadioactiveDecay5.6"
ENV G4PARTICLEXSDATA="/root/gears/INSTALL/Geant4/data/G4PARTICLEXS4.0"
ENV G4PIIDATA="/root/gears/INSTALL/Geant4/data/G4PII1.3"
ENV G4REALSURFACEDATA="/root/gears/INSTALL/Geant4/data/RealSurface2.2"
ENV G4SAIDXSDATA="/root/gears/INSTALL/Geant4/data/G4SAIDDATA2.0"
ENV G4ABLADATA="/root/gears/INSTALL/Geant4/data/G4ABLA3.1"
ENV G4INCLDATA="/root/gears/INSTALL/Geant4/data/G4INCL1.0"
ENV G4ENSDFSTATEDATA="/root/gears/INSTALL/Geant4/data/G4ENSDFSTATE2.3"
ENV G4TENDLDATA="/root/gears/INSTALL/Geant4/data/G4TENDL1.4"

WORKDIR /root/gears
CMD ["gears"]
