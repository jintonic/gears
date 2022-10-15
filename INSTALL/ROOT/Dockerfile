FROM fedora

RUN dnf update -y && dnf install -y root \
  && dnf clean all && rm -fr /var/cache/* root/*.log root/*.cfg


WORKDIR /root/gears

ENV PS1="\u@fedora:\w \$ "
