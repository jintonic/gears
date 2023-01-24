# java-1.8.0-openjdk on centos8 is old enough to run HepRApp
FROM centos:centos8

# overwrite the maintainer of centos image
LABEL maintainer="Jing Liu"<jing.liu@usd.edu>

# https://yegorshytikov.medium.com/error-failed-to-download-metadata-for-repo-appstream-cannot-prepare-internal-mirrorlist-no-959768e5f8e5
RUN cd /etc/yum.repos.d/ && sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-* \
 && sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

# install packages needed to run HepRepFile viewer
RUN dnf install -y xauth java-1.8.0-openjdk && dnf clean all \
 && rm -fr /var/cache/* /root/*.cfg /root/*.log

# install HepRepFile visualization tools
# HepRApp.jar needs to be downloaded manually from https://www.slac.stanford.edu/~perl/HepRApp/
# as the docker ip is blocked by slac
COPY HepRApp.jar hv /usr/bin
COPY HepRApp.properties /root/.heprapprc
RUN cd /usr/bin && chmod 755 hv

# overwrite the default working directory: /
WORKDIR /root
