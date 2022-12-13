FROM fedora

# install packages needed to run HepRepFile viewer
RUN dnf install -y xauth java-1.8.0-openjdk && dnf clean all && rm -fr /var/cache/*

# install HepRepFile visualization tools
COPY v2x hv /usr/bin

RUN cd /usr/bin \
  && curl -LO http://www.slac.stanford.edu/~perl/HepRApp/HepRApp.jar \
  && curl -LO http://www.deem7.com/files/VrmlMerge-0.5beta.jar \
  && chmod 755 hv v2x

WORKDIR /root/gears

ENV PS1="\u@g4vis:\w \$ "
