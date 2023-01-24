# https://geant4.web.cern.ch/support/download
# Geant4 is pre-compiled using gcc 8.5.0 on CERN CentOS-Stream8, 64 bits
FROM centos:centos8

# https://yegorshytikov.medium.com/error-failed-to-download-metadata-for-repo-appstream-cannot-prepare-internal-mirrorlist-no-959768e5f8e5
RUN cd /etc/yum.repos.d/ && sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-* \
 && sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

# `which` is needed by `make`
# `mesa-libGL` & `libXmu` is needed to compile geant4 application
# `openssl` is needed to download geant4 datasets
RUN  dnf install -y gcc-c++ which mesa-libGL libXmu openssl make \
  && dnf clean all && rm -fr /var/cache/* /root/*.cfg /root/*.log

# Geant4 version
ARG v=11.1

# get pre-compiled geant4
RUN  curl -LO http://geant4-data.web.cern.ch/releases/lib_$v/Linux-g++8.5.0-CC8.tar.gz \
  && tar xfvz Linux-g++8.5.0-CC8.tar.gz && rm -r Linux-g++8.5.0-CC8.tar.gz \
  && mv Geant4-*-Linux/bin/* usr/bin && mv Geant4-*-Linux/lib64/*.so* usr/lib64 \
  && mv Geant4-*-Linux/include/* usr/include && mv Geant4-*-Linux/share/* usr/share \
  && sed -i "s|afs/cern.ch/user/g/gunter/l/releases/web/$v.0/install/Geant4-$v.0-Linux|usr|g" usr/bin/geant4.sh \
  && sed -i "s|afs/cern.ch/user/g/gunter/l/releases/web/$v.0/install/Geant4-$v.0-Linux|usr|g" usr/bin/geant4-config \
  && rm -fr /Geant4-*-Linux /root/*.cfg /root/*.log

# download geant4 datasets
RUN geant4-config --install-datasets

# compile GEARS
RUN cd usr/bin \
  && curl -LO https://github.com/jintonic/gears/raw/master/gears.cc \
  && curl -LO https://github.com/jintonic/gears/raw/master/Makefile \
  && make && rm -f gears.cc Makefile

WORKDIR root/gears

# avoid using ENV to hard code datasets' locations
COPY entrypoint.sh /bin/entrypoint.sh
RUN chmod 755 /bin/entrypoint.sh
ENTRYPOINT ["/bin/entrypoint.sh"]
