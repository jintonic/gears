#!/bin/sh

# use geant4.sh to avoid hard coding datasets' locaitons
. /usr/bin/geant4.sh

# ENV PS1="\u@Geant4:\w \$ " doesn't work together with ENTRYPOINT
export PS1="\u@Geant4:\w \$ "

exec "$@" # run cmd specified in Dockerfile or docker-compose.yml
