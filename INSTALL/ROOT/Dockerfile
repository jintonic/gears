FROM fedora

RUN dnf update -y && dnf install -y root \
  && dnf clean all && rm -fr /var/cache/*

WORKDIR /root/gears

ENV PS1="\u@fedora:\w \$ "
