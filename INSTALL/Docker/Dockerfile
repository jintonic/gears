# https://hub.docker.com/r/physino/geant4
from physino/geant4:minimal

# compile GEARS
RUN cd /usr/bin \
  && curl -LO https://github.com/jintonic/gears/raw/master/gears.cc \
  && curl -LO https://github.com/jintonic/gears/raw/master/Makefile \
  && make && rm -f gears.cc Makefile

# install command-line tools: tmux, git, lf, micro, asciigraph, sc-im
# byacc and ncurses-devel are needed for compiling sc-im
run dnf install -y byacc ncurses-devel tmux git \
 && cd /usr/local/bin && curl https://getmic.ro/r | bash \
 && curl -LO https://github.com/gokcehan/lf/releases/download/r31/lf-linux-amd64.tar.gz \
 && tar xf *.gz && rm -f *.gz \
 && curl -LO https://github.com/andmarti1424/sc-im/archive/refs/tags/v0.8.3.tar.gz \
 && tar xf *.gz && cd sc*/src && make && make install && cd ../.. && rm -fr *0.8* \
 && curl -LO https://github.com/guptarohit/asciigraph/releases/download/v0.6.0/asciigraph_0.6.0_Linux_x86_64.tar.gz \
 && tar xf *.gz && rm -f *.gz LICENSE *.md \
 && dnf clean all && rm -fr /var/cache/*

# set up environment
copy tmux.conf /root/.tmux.conf
copy config /root/.config
# tmux uses $PS1 defined in .bashrc to show its prompt
run cd /root && rm -f .*cshrc && sed -i 's/"ls -Alh"/lf/' .bashrc \
 && echo 'export PS1="\[\e[0;32m\]\u@Geant4:\[\e[0;34m\]\w \[\e[0;31m\]\$\[\e[m\] "' >> .bashrc \ 
 && echo 'alias t="tmux -u"' >> .bashrc \
 && echo 'alias ta="t attach"' >> .bashrc \
 && echo 'alias a="asciigraph -h 15 -w 60"' >> .bashrc \
 && echo 'alias s=sc-im' >> .bashrc
# lf started by tmux uses vi without the following line
env EDITOR=micro

# https://askubuntu.com/a/746846
# https://kodekloud.com/blog/keep-docker-container-running
cmd tmux -u new -d lf && sleep infinity
