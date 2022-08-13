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
# openssl is for geant4-config --install-datasets, which is for make
RUN  dnf install -y openssl which ncurses gcc-c++ mesa-libGL-devel libXmu-devel expat-devel \
  && dnf clean all && rm -fr /var/cache/*
RUN  curl -LO https://github.com/jintonic/gears/raw/master/gears.cc \
  && curl -LO https://github.com/jintonic/gears/raw/master/Makefile \
  && make && mv gears usr/bin && rm -f gears.cc Makefile

ENV PS1="\u@Geant4.$v:\w \$ "
ENTRYPOINT ["cd /usr/bin && source geant4.sh"]

WORKDIR /root/gears
CMD ["gears"]
