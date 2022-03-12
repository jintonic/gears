FROM fedora:latest

RUN dnf update -y \
  && dnf install -y langpacks-en glibc-langpack-en binutils cmake gcc-c++ git gitk tig \
  && mesa-libGL-devel libAfterImage-devel libX11-devel libXmu-devel libXext-devel libXft-devel libXpm-devel \
  && gsl-devel expat-devel libtiff-devel libxml2-devel lz4-devel openjpeg-devel openssl openssl-devel \
  && make ncurses-libs numpy python3-root root wget vim emacs screen tmux vifm w3m sc ImageMagick \
  && wget http://geant4-data.web.cern.ch/releases/lib_11.0.1/Linux-g++8.3.0-CC7.tar.gz \
  && tar xfvz Linux-g++8.3.0-CC7.tar.gz && rm -r Linux-g++8.3.0-CC7.tar.gz \
  && mv Geant4-11.0.1-Linux/bin/* usr/bin && mv Geant4-11.0.1-Linux/lib64/* usr/lib64 \
  && mv Geant4-11.0.1-Linux/include/* usr/include && mv Geant4-11.0.1-Linux/share/* usr/share \
  && rm -fr Geant4-11.0.1-Linux \
  && sed -i 's|afs/cern.ch/user/g/gunter/l/releases/web/11.0.1/install/Geant4-11.0.1-Linux|usr|g' usr/bin/geant4.sh \
  && sed -i 's|afs/cern.ch/user/g/gunter/l/releases/web/11.0.1/install/Geant4-11.0.1-Linux|usr|g' usr/bin/geant4-config \
  && usr/bin/geant4-config --install-datasets \
  && source usr/bin/geant4.sh \
  && git clone https://github.com/jintonic/gears.git \
  && cd gears && make && mv gears /usr/bin

ENV PS1="\u@\H:\w \$ "
ENV LANG=en_US.UTF-8
ENV G4NEUTRONHPDATA="/usr/share/Geant4-11.0.1/data/G4NDL4.6"
ENV G4LEDATA="/usr/share/Geant4-11.0.1/data/G4EMLOW8.0"
ENV G4LEVELGAMMADATA="/usr/share/Geant4-11.0.1/data/PhotonEvaporation5.7"
ENV G4RADIOACTIVEDATA="/usr/share/Geant4-11.0.1/data/RadioactiveDecay5.6"
ENV G4PARTICLEXSDATA="/usr/share/Geant4-11.0.1/data/G4PARTICLEXS4.0"
ENV G4PIIDATA="/usr/share/Geant4-11.0.1/data/G4PII1.3"
ENV G4REALSURFACEDATA="/usr/share/Geant4-11.0.1/data/RealSurface2.2"
ENV G4SAIDXSDATA="/usr/share/Geant4-11.0.1/data/G4SAIDDATA2.0"
ENV G4ABLADATA="/usr/share/Geant4-11.0.1/data/G4ABLA3.1"
ENV G4INCLDATA="/usr/share/Geant4-11.0.1/data/G4INCL1.0"
ENV G4ENSDFSTATEDATA="/usr/share/Geant4-11.0.1/data/G4ENSDFSTATE2.3"
ENV G4NEUTRONHP_USE_ONLY_PHOTONEVAPORATION=1

WORKDIR /root/gears
CMD ["gears"]
