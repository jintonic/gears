FROM fedora

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
RUN  dnf install -y which gcc-c++ mesa-libGL libXmu \
  && dnf clean all && rm -fr /var/cache/* \
  && curl -LO https://github.com/jintonic/gears/raw/master/gears.cc \
  && curl -LO https://github.com/jintonic/gears/raw/master/Makefile \
  && make && mv gears usr/bin && rm -f gears.cc Makefile

WORKDIR /root/gears

# avoid using ENV to hard code datasets' locaitons
COPY entrypoint.sh /bin/entrypoint.sh
RUN chmod 755 /bin/entrypoint.sh
ENTRYPOINT ["/bin/entrypoint.sh"]
