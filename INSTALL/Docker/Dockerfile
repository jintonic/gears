# https://hub.docker.com/r/physino/geant4
from physino/geant4:minimal

# compile GEARS
RUN cd /usr/bin \
  && curl -LO https://github.com/jintonic/gears/raw/master/gears.cc \
  && curl -LO https://github.com/jintonic/gears/raw/master/Makefile \
  && make && rm -f gears.cc Makefile

# install tmux, git, java, micro, lf, uproot, visidata, mpld3
run dnf install -y tmux git python3-pip java-1.8.0-openjdk-headless \
 && cd /usr/local/bin && curl https://getmic.ro/r | bash \
 && curl -LO https://github.com/gokcehan/lf/releases/download/r31/lf-linux-amd64.tar.gz \
 && tar xf *.gz && rm -f *.gz && dnf clean all && rm -fr /var/cache/* \
 && pip install uproot visidata mpld3 && rm -fr /root/.cache

# set up environment
copy tmux.conf /etc/
copy config /root/.config
copy v2x /usr/bin
# tmux uses $PS1 defined in .bashrc to show its prompt
run cd /etc && sed -i 's/"ls -Alh"/lf/' bashrc \
 && echo 'export PS1="\[\e[0;32m\]\u@AlmaLinux:\[\e[0;34m\]\w \[\e[0;31m\]\$\[\e[m\] "' >> bashrc \ 
 && echo 'alias t="tmux -u"' >> bashrc \
 && echo 'alias ta="t attach"' >> bashrc \
 && echo 'options.disp_canvas_charset = " +"' >> /root/.visidatarc \
 && echo 'You are using /bin/sh' >> /root/.profile \
 && echo 'Type "tmux -u a↵" for a better UI' >> /root/.profile \
 && cd /usr/bin \
 && curl -LO https://github.com/jintonic/gears/raw/master/tutorials/detector/visualization/VrmlMerge-0.5beta.jar \
 && cd /usr/share \
 && curl -LO https://raw.githubusercontent.com/jintonic/gears/master/tutorials/detector/visualization/gearsX3D.html

# lf started by tmux uses vi without the following line
env EDITOR=micro

volume /geant4
expose 8000

# https://askubuntu.com/a/746846
# https://kodekloud.com/blog/keep-docker-container-running
cmd python3 -u -m http.server -b 0.0.0.0 --cgi
