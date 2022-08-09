[![docker hub](https://img.shields.io/badge/docker-hub-yellow.svg)](https://hub.docker.com/r/physino/geant4)

This folder contains a [Dockerfile](Dockerfile) to install the latest [Geant4][] in the latest [Fedora][] [Docker][] [container][].

The 64-bit [Geant4][] libraries were pre-compiled with gcc 8.3.0 on CERN CentOS7 (CC7) Linux. They were directly downloaded from the [Geant4][] [download][] page. Fortunately, they run just fine on the latest [Fedora][], which is a more up-to-date OS than CC7.

As the libraries were compiled already, the installation process only involves downloading and unpacking them, together with [Geant4][] [data files][download], which costs only ~ 10 min. Unfortunately, [Qt][] and [GDML][] were not enabled in the pre-compilation.

The [container](https://hub.docker.com/r/physino/geant4) can be generated using the following commands:

```sh
docker build -t physino/geant4:minimal .
docker push physino/geant4:minimal
```

It can be pulled from <https://hub.docker.com/r/physino/geant4> if [Docker][] is available in your system:

```sh
docker pull physino/geant4:minimal
```

[GEARS][] is included in this container as a verification of the [Geant4][] installation. As [GEARS][] may evolve more frequently than [Geant4][], [../../Dockerfile](../../Dockerfile) is used to update [GEARS][] in the [Geant4][] container. It can be used the following way:

[Geant4]: https://geant4.web.cern.ch
[Fedora]: https://getfedora.org
[Docker]: https://www.docker.com
[container]: https://www.docker.com/resources/what-container
[download]: https://geant4.web.cern.ch/support/download
[Qt]: https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#qt
[GDML]: https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomXML.html
[GEARS]: https://github.com/jintonic/gears
