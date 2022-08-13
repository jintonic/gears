[![docker hub](https://img.shields.io/badge/docker-hub-blue.svg)](https://hub.docker.com/r/physino/geant4)

This folder contains a [Dockerfile](Dockerfile) to install the latest [Geant4][] in the latest [Fedora][] [Docker][] [container][].

The 64-bit [Geant4][] libraries were pre-compiled with gcc 8.3.0 on CERN CentOS7 (CC7) Linux. They were directly downloaded from the [Geant4][] [download][] page. Fortunately, they run just fine on the latest [Fedora][], which is a more up-to-date OS than CC7.

As the libraries were compiled already, the installation process only involves downloading and unpacking them, which costs only ~ 3 min. Unfortunately, [Qt][] and [GDML][] were not enabled in the pre-compilation.

The [container](https://hub.docker.com/r/physino/geant4) can be generated using the following commands:

```sh
docker build -t physino/geant4 .
docker push physino/geant4
```

It can be used in the following way:

```sh
cd /path/to/gears
docker-compose run --rm sh
root@Geant4.11.0.2:~/gears $
```

**Note** that the [Geant4][] [datasets][download] are not included in the container to keep its size minimal. However, they can be easily downloaded through the container into the `gears/INSTALL/Geant4/data/` folder in the host computer:

```sh
root@Geant4.11.0.2:~/gears $ geant4-config --install-datasets
root@Geant4.11.0.2:~/gears $ ls INSTALL/Geant4/data
root@Geant4.11.0.2:~/gears $ gears


          ################################
          !!! G4Backtrace is activated !!!
          ################################


**************************************************************
 Geant4 version Name: geant4-11-00-patch-02 [MT]   (25-May-2022)
                       Copyright : Geant4 Collaboration
                      References : NIM A 506 (2003), 250-303
                                 : IEEE-TNS 53 (2006), 270-278
                                 : NIM A 835 (2016), 186-225
                             WWW : http://geant4.org/
**************************************************************

Available UI session types: [ tcsh, csh ]
PreInit>
```

[Geant4]: https://geant4.web.cern.ch
[Fedora]: https://getfedora.org
[Docker]: https://www.docker.com
[container]: https://www.docker.com/resources/what-container
[download]: https://geant4.web.cern.ch/support/download
[Qt]: https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#qt
[GDML]: https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomXML.html
[GEARS]: https://github.com/jintonic/gears
