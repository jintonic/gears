[![How to use containers](https://img.shields.io/badge/use-containers-yellow.svg)](#how-to-use-generated-container-images)
[![Datasets installer](https://img.shields.io/badge/datasets-installer-blue.svg)](#datasets-installer)

## Docker images

This folder contains a [Dockerfile](Dockerfile) to install [Geant4][]-11.0 in the latest [Fedora][] [Docker][] [container][].

The 64-bit [Geant4][] libraries were pre-compiled with gcc 8.3.0 on CERN CentOS7 Linux. They were directly downloaded from the [Geant4][] [download][] page. Fortunately, they run just fine on [Fedora][] 36, which is a more up-to-date OS than CC7.

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

[GEARS][] is included in this container as a verification of the [Geant4][] installation. As [GEARS][] may evolve more frequently than [Geant4][], [../../Dockerfile](../../Dockerfile) is used to update [GEARS][] in the [Geant4][] container. It can be used the following way:

```sh
cd /path/to/gears/INSTALL
docker build -t physino/gears .
docker push physino/gears
```

### How to use generated container images

The generated containers can be pulled from <https://hub.docker.com/r/physino>:

```sh
# pull latest Geant4 image with not-so-updated GEARS
docker pull physino/geant4
# pull latest Geant4 image with up-to-date GEARS
docker pull physino/gears
```

They can also be run directly with the following command in a Windows or a Mac that has [Docker][] installed:

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

One can also use [docker-compose](https://docs.docker.com/engine/reference/commandline/compose_run/) to get into an interactive shell of the container:

```sh
cd /path/to/gears
docker-compose run sh
root@Geant4-11.0.2:~/gears $
```

You can use this shell to install any package that you like. For example,

```sh
root@Geant4-11.0.2:~/gears $ dnf install glibc-langpack-en
```

## Apptainer/Singularity images

[../../gears.def](../../gears.def) can be used to generate [apptainer][]/[singularity][] images from the [Docker][] [GEARS][] image mentioned above using the following commands:

```sh
cd /path/to/gears/INSTALL
sudo apptainer build gears.sif gears.def
```

One must run the `build` command with `sudo`. If you don't have the privileg to run `sudo`, you can use the remote build option provided by [singularity][] to build the image in <https://cloud.sylabs.io>:

```sh
singularity build -r gears.sif gears.def
```

I sign and push the image to <https://cloud.sylabs.io/library/jintonic/geant4/gears> using the following commands:

```sh
singularity sign gears.sif
singularity push gears.sif library://jintonic/geant4/gears:latest
```

On a Linux machine that has [singularity][]/[apptainer][] installed, one can pull the image using the following commmands:

```sh
singularity pull library://jintonic/geant4/gears
```
or
```sh
apptainer pull library://jintonic/geant4/gears
```

Note that you may need to set the location of your [apptainer][] [remote][] library before `pull`:

```sh
apptainer remote add sylabs https://cloud.sylabs.io
apptainer remote use sylabs
apptainer remote list
```

The sif file can be directly used as an executable:
```sh
./gears.sif example.mac
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
[remote]: https://apptainer.org/docs/user/1.0/endpoint.html
