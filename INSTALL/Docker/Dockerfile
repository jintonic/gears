# According to https://geant4.org/download
# Geant4 (>=11.2) is pre-compiled on 64-bit AlmaLinux
from physino/geant4:minimal

# compile GEARS
RUN cd /usr/bin \
  && curl -LO https://github.com/jintonic/gears/raw/master/gears.cc \
  && curl -LO https://github.com/jintonic/gears/raw/master/Makefile \
  && make && rm -f gears.cc Makefile

# install command-line tools
# `file`, `xdg-utils` are used by https://github.com/dylanaraps/fff
run dnf install -y file xdg-utils tmux git \
 && cd /usr/local/bin && curl https://getmic.ro/r | bash \
 && curl -LO https://github.com/dylanaraps/fff/raw/master/fff && chmod 755 fff \
 && dnf clean all && rm -fr /var/cache/*

# set up environment
run mkdir -p /root/.config/micro \
 && echo 'export EDITOR=micro' >> /root/.bashrc \ 
 && echo -e '{\n "colorscheme": "solarized"\n}' >> /root/.config/micro/settings.json \ 
 && echo -e 'f() {\n  fff "$@"' >> /root/.bashrc \
 && echo '  cd "$(cat "${XDG_CACHE_HOME:=${HOME}/.cache}/fff/.fff_d")"' >> /root/.bashrc \
 && echo '}' >> /root/.bashrc \
 && echo 'export FFF_FAV3=~/mingle' >> /root/.bashrc \
 && echo 'export FFF_FAV9=~/gears' >> /root/.bashrc \
 && echo 'export FFF_COL2=6' >> /root/.bashrc \
 && echo 'alias t=tmux' >> /root/.bashrc \
 && echo 'set -g mouse on' >> /root/.tmux.conf \
 && echo 'set-option -g status-position top' >> /root/.tmux.conf \
 && echo 'set-option -g status-right "[physino/geant4]"' >> /root/.tmux.conf \
 && echo 'setw -g window-status-current-style bg=black,fg=white' >> /root/.tmux.conf

