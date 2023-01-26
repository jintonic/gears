# java-1.8.0-openjdk on centos8 is old enough to run HepRApp
FROM centos:centos8

# overwrite the maintainer of centos image
LABEL maintainer="Jing Liu"<jing.liu@usd.edu>

# https://yegorshytikov.medium.com/error-failed-to-download-metadata-for-repo-appstream-cannot-prepare-internal-mirrorlist-no-959768e5f8e5
RUN cd /etc/yum.repos.d/ && sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-* \
 && sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

# install packages needed to run HepRApp, python3 is needed to run a web server
RUN dnf install -y xauth java-1.8.0-openjdk python3 && dnf clean all \
 && rm -fr /var/cache/* /root/*.cfg /root/*.log

# install HepRepFile and VRML visualization tools
# HepRApp.jar needs to be downloaded manually from https://www.slac.stanford.edu/~perl/HepRApp/
# as the docker ip is blocked by slac
COPY HepRApp.jar VrmlMerge-0.5beta.jar hv v2x /usr/bin
COPY HepRApp.properties /root/.heprapprc
RUN cd /usr/bin && chmod 755 hv v2x

# overwrite the default working directory: /
WORKDIR /root
