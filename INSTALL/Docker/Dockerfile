# According to https://geant4.org/download
# Geant4 (>=11.2) is pre-compiled on 64-bit AlmaLinux
FROM almalinux

# `which` is needed by `make`, `ncurses` provides tput
# `mesa-libGL` & `libXmu` are needed to compile geant4 applications
# `mesa-dri-drivers` is needed to run OpenGL.mac & TSG.mac
# `file`, `xdg-utils`, `vim` is used by https://github.com/dylanaraps/fff
RUN dnf install -y gcc-c++ which mesa-libGL libXmu file xdg-utils vim ncurses \
 && curl -LO https://github.com/dylanaraps/fff/raw/master/fff && chmod 755 fff && mv fff bin \
 && echo 'l(){ fff "$@"; cd "$(cat "${XDG_CACHE_HOME:=${HOME}/.cache}/fff/.fff_d")"; }' >> /root/.bashrc \
 && echo 'export EDITOR="vim"; alias ls="ls --color"; alias la="ls -a"' >> /root/.bashrc \ 
 && echo 'export FFF_FAV1=~/gears/INSTALL'>> /root/.bashrc \
 && echo 'export FFF_FAV2=~/gears/tutorials'>> /root/.bashrc \
 && echo 'export FFF_FAV4=~/gears/tutorials/physics'>> /root/.bashrc \
 && echo 'export FFF_FAV5=~/gears/tutorials/detector/visualization'>> /root/.bashrc \
 && echo 'export FFF_FAV6=~/gears/tutorials/sources'>> /root/.bashrc \
 && echo 'export FFF_FAV9=~/gears'>> /root/.bashrc \
 && dnf clean all && rm -fr /var/cache/*

# get pre-compiled geant4
RUN  curl -LO https://cern.ch/geant4-data/releases/lib4.11.2/Linux-g++11.3.1-Alma9.tar.gz \
  && tar xf Linux*.tar.gz && rm -r Linux*.tar.gz && mv Geant4*/lib64/cmake/Geant4 usr/lib64/cmake/ \
  && mv Geant4-*-Linux/bin/* usr/bin && mv Geant4-*-Linux/lib64/*.so* usr/lib64 \
  && mv Geant4-*-Linux/include/* usr/include && mv Geant4-*-Linux/share/* usr/share \
  && sed -i "s|build/jenkins/workspace/web/11.2.0/install/Geant4-11.2.0-Linux/share|root/gears/INSTALL|g" usr/bin/geant4-config \
  && rm -fr /Geant4-*-Linux

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
ENV PS1="\[\e[0;32m\]\u@Geant4:\[\e[0;34m\]\w \[\e[0;31m\]\$\[\e[m\] "
ENV TERM="xterm-256color"

# prefer user compiled gears over gears compiled here
ENV PATH=/root/gears:$PATH