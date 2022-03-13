FROM fedora:latest

ARG v=11.0.1

RUN dnf update -y \
  && dnf install -y git wget which openssl cmake gcc-c++ mesa-libGL-devel libXmu-devel expat-devel \
  && wget http://geant4-data.web.cern.ch/releases/lib_$v/Linux-g++8.3.0-CC7.tar.gz \
  && tar xfvz Linux-g++8.3.0-CC7.tar.gz && rm -r Linux-g++8.3.0-CC7.tar.gz \
  && mv Geant4-$v-Linux/bin/* usr/bin && mv Geant4-$v-Linux/lib64/* usr/lib64 \
  && mv Geant4-$v-Linux/include/* usr/include && mv Geant4-$v-Linux/share/* usr/share \
  && sed -i "s|afs/cern.ch/user/g/gunter/l/releases/web/11.0.1/install/Geant4-$v-Linux|usr|g" usr/bin/geant4.sh \
  && sed -i "s|afs/cern.ch/user/g/gunter/l/releases/web/11.0.1/install/Geant4-$v-Linux|usr|g" usr/bin/geant4-config \
  && usr/bin/geant4-config --install-datasets && source usr/bin/geant4.sh \
  && git clone https://github.com/jintonic/gears.git && cd gears && make && mv gears /usr/bin \
  && dnf clean all && rm -fr /var/cache/* /Geant4-$v-Linux

ENV PS1="\u@\H:\w \$ "
ENV G4NEUTRONHPDATA="/usr/share/Geant4-$v/data/G4NDL4.6"
ENV G4LEDATA="/usr/share/Geant4-$v/data/G4EMLOW8.0"
ENV G4LEVELGAMMADATA="/usr/share/Geant4-$v/data/PhotonEvaporation5.7"
ENV G4RADIOACTIVEDATA="/usr/share/Geant4-$v/data/RadioactiveDecay5.6"
ENV G4PARTICLEXSDATA="/usr/share/Geant4-$v/data/G4PARTICLEXS4.0"
ENV G4PIIDATA="/usr/share/Geant4-$v/data/G4PII1.3"
ENV G4REALSURFACEDATA="/usr/share/Geant4-$v/data/RealSurface2.2"
ENV G4SAIDXSDATA="/usr/share/Geant4-$v/data/G4SAIDDATA2.0"
ENV G4ABLADATA="/usr/share/Geant4-$v/data/G4ABLA3.1"
ENV G4INCLDATA="/usr/share/Geant4-$v/data/G4INCL1.0"
ENV G4ENSDFSTATEDATA="/usr/share/Geant4-$v/data/G4ENSDFSTATE2.3"

WORKDIR /root/gears
CMD ["gears"]
