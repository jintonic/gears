# java-1.8.0-openjdk on centos8 is old enough to run HepRApp
FROM centos:centos8

# overwrite the maintainer of centos image
LABEL maintainer="Jing Liu"<jing.liu@usd.edu>

# https://yegorshytikov.medium.com/error-failed-to-download-metadata-for-repo-appstream-cannot-prepare-internal-mirrorlist-no-959768e5f8e5
RUN cd /etc/yum.repos.d/ && sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-* \
 && sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

# install packages needed to run HepRApp, python3 is needed to run a web server to display x3d
RUN dnf install -y xauth java-1.8.0-openjdk python3 && dnf clean all \
 && rm -fr /var/cache/* /root/*.cfg /root/*.log

# HepRApp.jar needs to be downloaded manually from https://www.slac.stanford.edu/~perl/HepRApp/
# as the docker ip is blocked by slac
COPY HepRApp.jar hv /usr/bin
COPY HepRApp.properties /root/.heprapprc

# build VRML web viewer
RUN mkdir /root/cgi-bin
COPY v2x /root/cgi-bin
COPY VrmlMerge-0.5beta.jar gears.png gears.x3d gearsX3D.html /root
# https://stackoverflow.com/a/68349357
RUN echo -e '<html style="padding: 10px;">\n\
<head><title>VRML Web Viewer</title></head>\n\
<body style="max-width: 800px; margin: auto;">\n\
<a href="gearsX3D.html"><img align="right" width="120px" src="gears.png"/></a>\n\
<h1>VRML visualization through X3D</h1>\n<ul>\n\
<li><a style="color:blue;" href="cgi-bin/v2x">Click here to scan *.wrl files</a></li>\n\
<li><a style="color:blue;" \
href="https://github.com/jintonic/gears/tree/master/tutorials/detector/visualization#vrml">Documentation</a></li>\n\
</ul>\n</body>\n</html>' > /root/index.html 

# overwrite the default working directory: /
WORKDIR /root
