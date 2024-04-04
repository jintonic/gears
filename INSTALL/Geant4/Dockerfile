from physino/geant4:sshd

# https://wiki.almalinux.org/repos/Extras.html
run dnf install -y epel-release && dnf config-manager --set-enabled crb \
 && curl -LO https://github.com/kasmtech/KasmVNC/releases/download/v1.3.1/kasmvncserver_oracle_9_1.3.1_x86_64.rpm \
 && dnf localinstall -y kasmvncserver*.rpm && rm -f kasmvncserver*.rpm \
 && dnf clean all && rm -fr /var/cache/*

run dnf install -y openbox xterm && dnf clean all && rm -fr /var/cache/*

run usermod -a -G kasmvnc-cert root && mkdir -p /root/.vnc \
 && touch /root/.vnc/.de-was-selected \
 && echo -e 'geant4\ngeant4\n' | vncpasswd -u root -w -r \
 && echo 'xsetroot -solid "#538cc6"' > /root/.vnc/xstartup \
 && echo 'st' >> /root/.vnc/xstartup \
 && chmod 755 /root/.vnc/xstartup \
 && mkdir -p /root/.config/openbox \
 && echo -e '<?xml version="1.0" encoding="UTF-8"?>\n\
<openbox_menu>\n\
<menu id="root-menu" label="Openbox 3">\n\
  <item label="Terminal">\n\
    <action name="Execute">\n\
       <command>xterm -fg white -bg black -fs=12</command>\n\
    </action>\n\
  </item>\n\
  <item label="Reconfigure">\n\
    <action name="Reconfigure" />\n\
  </item>\n\
  <item label="Exit">\n\
    <action name="Exit">\n\
      <prompt>yes</prompt>\n\
    </action>\n\
  </item>\n\
</menu>\n\
</openbox_menu>' > /root/.config/openbox/menu.xml \
 && echo -e 'network:\n  ssl:\n    require_ssl: false\n' > /root/.vnc/kasmvnc.yaml

# 8443 + display number
expose 8444
# container exits immediately without "tail"
cmd vncserver && tail -f ~/.vnc/*.log
