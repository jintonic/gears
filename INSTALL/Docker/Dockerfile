# https://geant4.web.cern.ch/download
# Geant4 is pre-compiled using gcc 8.5.0 on CERN CentOS-Stream8, 64 bits
FROM centos:centos8

# https://yegorshytikov.medium.com/error-failed-to-download-metadata-for-repo-appstream-cannot-prepare-internal-mirrorlist-no-959768e5f8e5
RUN cd /etc/yum.repos.d/ && sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-* \
 && sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

# `which` is needed by `make`
# `mesa-libGL` & `libXmu` is needed to compile geant4 application
# `openssl` is needed to download geant4 datasets
# `file`, `xdg-utils`, `vim` is used by https://github.com/dylanaraps/fff
RUN dnf install -y gcc-c++ which make mesa-libGL libXmu openssl file xdg-utils vim \
 && curl -LO https://github.com/dylanaraps/fff/raw/master/fff && chmod 755 fff && mv fff bin \
 && echo 'l(){ fff "$@"; cd "$(cat "${XDG_CACHE_HOME:=${HOME}/.cache}/fff/.fff_d")"; }' >> /root/.bashrc \
 && echo 'export EDITOR="vim"; alias ls="ls --color"; alias la="ls -a"' >> /root/.bashrc \ 
 && dnf clean all && rm -fr /var/cache/* /root/*.cfg /root/*.log /root/.*cshrc

# Geant4 version
ARG v=11.1.1

# get pre-compiled geant4
RUN  curl -LO https://cern.ch/geant4-data/releases/lib4.11.1.p01/Linux-g++8.5.0-CC8.tar.gz \
  && tar xfvz Linux-g++8.5.0-CC8.tar.gz && rm -r Linux-g++8.5.0-CC8.tar.gz \
  && mv Geant4-*-Linux/bin/* usr/bin && mv Geant4-*-Linux/lib64/*.so* usr/lib64 \
  && mv Geant4-*-Linux/include/* usr/include && mv Geant4-*-Linux/share/* usr/share \
  && sed -i "s|afs/cern.ch/user/g/gunter/l/releases/web/$v/install/Geant4-$v-Linux/share|root/gears/INSTALL|g" usr/bin/geant4-config \
  && rm -fr /Geant4-*-Linux /root/*.cfg /root/*.log

# compile GEARS
RUN cd usr/bin \
  && curl -LO https://github.com/jintonic/gears/raw/master/gears.cc \
  && curl -LO https://github.com/jintonic/gears/raw/master/Makefile \
  && make && rm -f gears.cc Makefile

WORKDIR /root/gears

# use datasets saved in the mapped host folder
ENV GEANT4_DATA_DIR=/root/gears/INSTALL/Geant4/data
# if datasets are missing in the host folder, run
#     geant4-config --install-datasets
# in the container to install them

# enable colorful shell prompt
# https://superuser.com/a/367280
ENV PS1="\[\e[0;32m\]\u@Geant4-$v:\[\e[0;34m\]\w \[\e[0;31m\]\$\[\e[m\] "
ENV TERM="xterm-256color"
