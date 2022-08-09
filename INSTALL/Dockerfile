FROM physino/geant4:minimal

RUN dnf update -y \
  && dnf install -y freewrl java-1.8.0-openjdk xerces-c-devel qt5-qt3d-devel \
    python3-h5py python3-pandas python3-matplotlib-qt5 boost-openmpi-python3-devel \
    root root-gdml root-fftw root-roofit root-notebook root-minuit2 root-graf3d-x3d \
  && dnf clean all && rm -fr /var/cache/* && pip install uproot awkward \
  && cd /gears && git pull && make && mv gears /usr/bin \
  && cp examples/detector/visualization/{hv,v2x} /usr/bin \
  && cd /usr/bin && wget http://www.deem7.com/files/VrmlMerge-0.5beta.jar \
  && wget http://www.slac.stanford.edu/~perl/HepRApp/HepRApp.jar \
  && wget http://cern.ch/geant4-data/releases/geant4-v11.0.2.tar.gz \
  && tar xfvz geant4-v11.0.2.tar.gz \
  && cd geant4-v11.0.2 && mkdir build && cd build \
  && cmake -DGEANT4_INSTALL_DATA=OFF -DGEANT4_USE_GDML=ON -DGEANT4_USE_PYTHON=ON -DGEANT4_USE_QT=ON -DGEANT4_USE_RAYTRACER_X11=ON -DGEANT4_BUILD_TLS_MODEL=global-dynamic ..
