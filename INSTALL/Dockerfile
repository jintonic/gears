FROM fedora:latest

LABEL maintainer.name="Jing LIU"
LABEL maintainer.email="jintonic@physino.xyz"

RUN dnf update -y \
  && dnf install -y binutils cmake gcc-c++ git gsl-devel libAfterImage-devel libX11-devel libXmu-devel libXext-devel libXft-devel libXpm-devel expat-devel libtiff-devel libxml2-devel lz4-devel make ncurses-libs numpy openjpeg-devel openssl openssl-devel python3-root root wget vim screen tmux vifm w3m sc ImageMagick gitk tig emacs \
  && wget http://geant4-data.web.cern.ch/releases/lib_11.0.1/Linux-g++8.3.0-CC7.tar.gz \
  && tar xfvz Linux-g++8.3.0-CC7.tar.gz \
  && sed -i 's|/afs/cern.ch/user/g/gunter/l/releases/web/11.0.1/install|/root|g' Geant4-11.0.1-Linux/bin/geant4.sh \
  && sed -i 's|/afs/cern.ch/user/g/gunter/l/releases/web/11.0.1/install|/root|g' Geant4-11.0.1-Linux/bin/geant4-config \
  && Geant4-11.0.1-Linux/bin/geant4-config --install-datasets \
  && git clone https://github.com/jintonic/gears.git \
  && cd gears && make && mv gears /usr/bin

CMD ["gears"]
