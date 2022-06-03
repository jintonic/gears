This folder contains a [Dockerfile](Dockerfile) to install [Geant4][]-11.0.1 in the latest [Fedora][] [Docker][] [container][].

The 64-bit [Geant4][] libraries were pre-compiled with gcc 8.3.0 on CERN CentOS7 Linux. They were directly downloaded from the [Geant4][] [download][] page. Fortunately, they run just fine on [Fedora][] 35, which is a more up-to-date OS than CC7.

As the libraries were compiled already. The installation process only involves downloading and unpacking them, together with [Geant4][] [data files][download], which costs only ~ 10 min. Unfortunately, [Qt][] and [GDML][] were not enabled in the pre-compilation.

The [container](https://hub.docker.com/r/physino/geant4) can be generated using the following commands:

```sh
cd /path/to/gears/INSTALL/Geant4/11.0.1
docker build -t physino/geant4:11.0.1 .
docker push physino/geant4:11.0.1
```

It can be pulled from <https://hub.docker.com/r/physino/geant4> if [Docker][] is available in your system:

```sh
docker pull physino/geant4:11.0.1
```

[GEARS][] is included in the container as a verification of the installation. It can be run with the following command:

```sh
docker run -it physino/geant4:11.0.1


          ################################
          !!! G4Backtrace is activated !!!
          ################################


**************************************************************
 Geant4 version Name: geant4-11-00-patch-01 [MT]   (8-March-2022)
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
