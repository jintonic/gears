[![Geant4 image](https://img.shields.io/badge/Geant4-image-blue.svg)](https://hub.docker.com/r/geant4/geant4)
[![Dockerfile](https://img.shields.io/badge/Docker-file-red.svg)](Dockerfile)

This folder contains a [Dockerfile](Dockerfile) to demonstrate the possibility of compiling [Geant4][] in the latest [Fedora][] [Docker][] [container][] with [Qt][] and [GDML][] enabled. It is not used to generate any image because there is already an official image of [Geant4][] on Docker hub: <https://hub.docker.com/r/geant4/geant4>, which has even more features enabled. For people who want to experience the full power of [Geant4][], please use the official image. The second service listed in [gears/docker-compose.yml](../../../docker-compose.yml) demonstrates the usage of the official image:

```sh
cd /path/to/gears
# pull and run https://hub.docker.com/r/geant4/geant4
docker-compose run geant4
# compile gears
root@8704najvr:~/gears $ mkdir build
root@8704najvr:~/gears $ cd build
root@8704najvr:~/gears/build $ ccmake ..
root@8704najvr:~/gears/build $ make
# run gears
root@8704najvr:~/gears/build $ gears
```

> **Warning**
> The official [Geant4][] image is huge due to its rich feature. Be prepared for a looong downloading time.

If you only need the basic functionality of [Geant4][], please try the much smaller [GEARS][] [Docker][] image: <https://hub.docker.com/r/physino/gears>. For more information about the [GEARS][] image, please check [../../Docker/](../../Docker).

[Geant4]: https://geant4.web.cern.ch
[Fedora]: https://getfedora.org
[Docker]: https://www.docker.com
[container]: https://www.docker.com/resources/what-container
[Qt]: https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#qt
[GDML]: https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomXML.html
[GEARS]: https://github.com/jintonic/gears
