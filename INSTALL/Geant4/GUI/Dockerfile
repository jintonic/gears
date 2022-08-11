FROM fedora

ARG v=v11.0.2

# install packages needed to compile and run Geant4 GUI
RUN dnf install -y freewrl java-1.8.0-openjdk expat-devel \
  xerces-c-devel qt5-qt3d-devel libXmu-devel mesa-libGL-devel \
  && dnf clean all && rm -fr /var/cache/*

# compile Geant4
RUN curl -LO http://cern.ch/geant4-data/releases/geant4-$v.tar.gz \
  && tar xfvz geant4-$v.tar.gz && cd geant4-$v && mkdir build && cd build \
  && cmake -DGEANT4_USE_GDML=ON -DGEANT4_USE_QT=ON \
  -DGEANT4_USE_OPENGL_X11=ON -DGEANT4_USE_RAYTRACER_X11=ON \
  -DGEANT4_INSTALL_EXAMPLES=OFF -DGEANT4_INSTALL_PACKAGE_CACHE=OFF \
  -DGEANT4_INSTALL_DATA=OFF -DGEANT4_INSTALL_DATADIR=/root/gears/INSTALL/Geant4 \
  -DCMAKE_INSTALL_PREFIX=/usr .. && make install && cd / && rm -fr geant4-$v*

# compile GEARS
RUN  curl -LO https://github.com/jintonic/gears/raw/master/gears.cc \
  && curl -LO https://github.com/jintonic/gears/raw/master/Makefile \
  && make && mv gears /usr/bin && rm -f gears.cc Makefile

# install HepRepFile visualization tools
RUN cd /usr/bin \
  && curl -LO https://github.com/jintonic/gears/raw/master/examples/detector/visualization/hv \
  && curl -LO https://github.com/jintonic/gears/raw/master/examples/detector/visualization/v2x \
  && curl -LO http://www.slac.stanford.edu/~perl/HepRApp/HepRApp.jar \
  && curl -LO http://www.deem7.com/files/VrmlMerge-0.5beta.jar

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
