FROM fedora

# overwrite the maintainer of fedora image
LABEL maintainer="Jing Liu"<jing.liu@usd.edu>

# install packages needed to run HepRepFile viewer
RUN dnf install -y xauth java-1.8.0-openjdk && dnf clean all \
 && rm -fr /var/cache/* root/*.log root/*.cfg

# install HepRepFile visualization tools
COPY v2x hv /usr/bin

RUN cd /usr/bin \
  && curl -LO http://www.slac.stanford.edu/~perl/HepRApp/HepRApp.jar \
  && curl -LO http://www.deem7.com/files/VrmlMerge-0.5beta.jar \
  && chmod 755 hv v2x

# overwrite the default working directory: /
WORKDIR /root

# enable colorful shell prompt
ENV PS1="\e[0;32m\u@g4vis:\e[0;34m\w \e[0;31m\$\e[m "
ENV TERM="xterm-256color"
