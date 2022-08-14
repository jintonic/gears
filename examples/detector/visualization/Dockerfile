FROM fedora

# install packages needed to run HepRepFile viewer
RUN dnf install -y java-1.8.0-openjdk && dnf clean all && rm -fr /var/cache/*

# install HepRepFile visualization tools
COPY ../../../examples/detector/visualization/v2x \
     ../../../examples/detector/visualization/hv /usr/bin

RUN cd /usr/bin \
  && curl -LO http://www.slac.stanford.edu/~perl/HepRApp/HepRApp.jar \
  && curl -LO http://www.deem7.com/files/VrmlMerge-0.5beta.jar \
  && chmod 755 hv v2x

WORKDIR /root/gears
EXPOSE 8888
ENV PS1="\u@g4vis:\w \$ "
CMD bash
