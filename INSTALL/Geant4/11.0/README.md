[![Docker images](https://img.shields.io/badge/docker-images-yellow.svg)](#docker-images)
[![Datasets installer](https://img.shields.io/badge/datasets-installer-blue.svg)](#datasets-installer)

## Docker images

This folder contains a [Dockerfile](Dockerfile) to install [Geant4][]-11.0 in the latest [Fedora][] [Docker][] [container][].

The 64-bit [Geant4][] libraries were pre-compiled with gcc 8.3.0 on CERN CentOS7 Linux. They were directly downloaded from the [Geant4][] [download][] page. Fortunately, they run just fine on [Fedora][] 35, which is a more up-to-date OS than CC7.

As the libraries were compiled already. The installation process only involves downloading and unpacking them, together with [Geant4][] [data files][download], which costs only ~ 10 min. Unfortunately, [Qt][] and [GDML][] were not enabled in the pre-compilation.

The [container](https://hub.docker.com/r/physino/geant4) can be generated using the following commands:

```sh
cd /path/to/gears/INSTALL/Geant4/11.0
docker build -t physino/geant4:11.0.2 .
docker push physino/geant4:11.0.2
```

It can be pulled from <https://hub.docker.com/r/physino/geant4> if [Docker][] is available in your system:

```sh
docker pull physino/geant4:11.0.2
```

[../../Dockerfile](../../Dockerfile) is used to include [GEARS][] in the container as a verification of the installation. It can be used the following way:

```sh
cd /path/to/gears/INSTALL
docker build -t physino/gears .
docker push physino/gears
```

The generated container can be pulled from <https://hub.docker.com/r/physino/gears>:

```sh
docker pull physino/gears
```

It can also be run directly with the following command in a Windows machine:

```sh
docker run -it physino/gears
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

On Linux that has [singularity][] or [apptainer][] installed, one can pull the image using the following commmands:

```sh
singularity pull docker://physino/gears
mv gears_latest.sif gears.sif
```

```sh
apptainer pull docker://physino/gears
mv gears_latest.sif gears.sif
```

The sif file can be directly used as an executable:
```sh
./gears.sif
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

## Datasets installer
[![YouTube](https://img.shields.io/badge/You-Tube-red.svg)](https://youtu.be/OIhNBPfaTm8)

[datasets.bat](datasets.bat) is a Windows [batch][] file used to download Geant4 data files and set corresponding environment variables automatically. Place it in a folder where you'd like to save Geant4 data files and double click it to run it.

[Geant4]: https://geant4.web.cern.ch
[Fedora]: https://getfedora.org
[Docker]: https://www.docker.com
[container]: https://www.docker.com/resources/what-container
[download]: https://geant4.web.cern.ch/support/download
[Qt]: https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#qt
[GDML]: https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomXML.html
[GEARS]: https://github.com/jintonic/gears
[batch]: https://en.wikipedia.org/wiki/Batch_file
[singularity]: https://en.wikipedia.org/wiki/Singularity_(software)
[apptainer]: https://apptainer.org
