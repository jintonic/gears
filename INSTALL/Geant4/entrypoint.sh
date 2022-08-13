#!/bin/sh

# use geant4.sh to avoid hard coding datasets' locaitons
. /usr/bin/geant4.sh

# ENV PS1="\u@Geant4:\w \$ " doesn't work together with ENTRYPOINT
export PS1="\u@Geant4:\w \$ "

if [ ! -d /root/gears/INSTALL/Geant4/data/G4ENSDFSTATE* ]; then
  geant4-config --install-datasets
fi

exec "$@" # run cmd specified in Dockerfile or docker-compose.yml
