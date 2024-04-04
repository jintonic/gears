# https://hub.docker.com/r/physino/geant4
from physino/geant4:minimal

# compile GEARS
RUN cd /usr/bin \
  && curl -LO https://github.com/jintonic/gears/raw/master/gears.cc \
  && curl -LO https://github.com/jintonic/gears/raw/master/Makefile \
  && make && rm -f gears.cc Makefile

# install command-line tools: tmux, git, lf, micro, uproot, visidata, mpld3
run dnf install -y tmux git python3-pip \
 && cd /usr/local/bin && curl https://getmic.ro/r | bash \
 && curl -LO https://github.com/gokcehan/lf/releases/download/r31/lf-linux-amd64.tar.gz \
 && tar xf *.gz && rm -f *.gz && dnf clean all && rm -fr /var/cache/* \
 && pip install uproot visidata mpld3 && rm -fr /root/.cache

# set up environment
copy tmux.conf /etc/
copy config /root/.config
# tmux uses $PS1 defined in .bashrc to show its prompt
run cd /etc && sed -i 's/"ls -Alh"/lf/' bashrc \
 && echo 'export PS1="\[\e[0;32m\]\u@AlmaLinux:\[\e[0;34m\]\w \[\e[0;31m\]\$\[\e[m\] "' >> bashrc \ 
 && echo 'alias t="tmux -u"' >> bashrc \
 && echo 'alias ta="t attach"' >> bashrc \
 && echo 'You are using /bin/sh' >> profile \
 && echo 'Type "tmux -u a↵" for a better UI' >> profile

# lf started by tmux uses vi without the following line
env EDITOR=micro

volume /geant4/data
expose 8000
expose 8888

# https://askubuntu.com/a/746846
# https://kodekloud.com/blog/keep-docker-container-running
cmd tmux -u new -d lf && tail -12f /usr/README
