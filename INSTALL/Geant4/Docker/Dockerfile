FROM fedora

ARG v=v11.0.3

# install packages needed to compile and run Geant4 GUI
RUN dnf install -y openssl freewrl java-1.8.0-openjdk expat-devel \
  xerces-c-devel qt5-qt3d-devel libXmu-devel mesa-libGL-devel \
  && dnf clean all && rm -fr /var/cache/*

# compile Geant4 with Qt, GDML, X11 and download datasets
RUN curl -LO http://cern.ch/geant4-data/releases/geant4-$v.tar.gz \
  && tar xfvz geant4-$v.tar.gz && cd geant4-$v && mkdir build && cd build \
  && cmake -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_GDML=ON -DGEANT4_USE_QT=ON \
  -DGEANT4_USE_OPENGL_X11=ON -DGEANT4_USE_RAYTRACER_X11=ON \
  -DGEANT4_INSTALL_EXAMPLES=OFF -DGEANT4_INSTALL_PACKAGE_CACHE=OFF \
  -DCMAKE_INSTALL_PREFIX=/usr .. && make install && cd / && rm -fr geant4-$v*

# compile GEARS
RUN  curl -LO https://github.com/jintonic/gears/raw/master/gears.cc \
  && curl -LO https://github.com/jintonic/gears/raw/master/Makefile \
  && make && mv gears /usr/bin && rm -f gears.cc Makefile

# install HepRepFile visualization tools
RUN cd /usr/bin \
  && curl -LO https://github.com/jintonic/gears/raw/master/tutorials/detector/visualization/hv \
  && curl -LO https://github.com/jintonic/gears/raw/master/tutorials/detector/visualization/v2x \
  && curl -LO http://www.slac.stanford.edu/~perl/HepRApp/HepRApp.jar \
  && curl -LO http://www.deem7.com/files/VrmlMerge-0.5beta.jar \
  && chmod 755 hv v2x

WORKDIR /root/gears

# avoid using ENV to hard code datasets' locaitons
COPY entrypoint.sh /bin/entrypoint.sh
RUN chmod 755 /bin/entrypoint.sh
ENTRYPOINT ["/bin/entrypoint.sh"]
