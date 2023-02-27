#!/bin/sh

# use geant4.sh to avoid hard coding datasets' locaitons
. /usr/bin/geant4.sh

# ENV PS1="\u@Geant4:\w \$ " doesn't work together with ENTRYPOINT
# https://superuser.com/a/367280
export PS1="\[\e[0;32m\]\u@Geant4:\[\e[0;34m\]\w \[\e[0;31m\]\$\[\e[m\] "

exec "$@" # run cmd specified in Dockerfile or docker-compose.yml
