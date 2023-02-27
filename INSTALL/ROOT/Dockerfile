# fedora has ROOT in its package repo, ubuntu doesn't
FROM fedora

# overwrite the maintainer of fedora image
LABEL maintainer="Jing Liu"<jing.liu@usd.edu>

# https://hub.docker.com/r/fedora/container-best-practices/dockerfile
RUN dnf update -y && dnf clean all

RUN dnf install -y root root-gui-webdisplay \
  && dnf clean all && rm -fr /var/cache/* root/*.log root/*.cfg

# overwrite the default working directory: /
WORKDIR /root/

# enable colorful shell prompt
# https://superuser.com/a/367280
ENV PS1="\[\e[0;32m\]\u@fedora:\[\e[0;34m\]\w \[\e[0;31m\]\$\[\e[m\] "
ENV TERM="xterm-256color"

