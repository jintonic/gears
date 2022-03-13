FROM physino/geant4:11.0.1

RUN dnf update -y \
  && cd /gears && git pull && make && mv gears /usr/bin \
  && dnf clean all && rm -fr /var/cache/*

