[![Docker image](https://img.shields.io/badge/Docker-image-blue.svg)](https://hub.docker.com/r/physino/gears)
[![Dockerfile](https://img.shields.io/badge/Docker-file-red.svg)](Dockerfile)
[![For developer](https://img.shields.io/badge/For-developer-red.svg)](#for-developer)

This folder contains a [Dockerfile](Dockerfile) to generate the [Docker][] image <https://hub.docker.com/r/physino/gears>, which contains [GEARS][] compiled with the latest 64-bit [Geant4][] libraries pre-compiled with gcc 8.5.0 on CERN CentOS8 (CC8) Linux. They are directly downloaded from the [Geant4][] [download][] page.

As the libraries were compiled already, the image generation process only involves downloading and unpacking them, which costs only ~ 3 min. Unfortunately, [Qt][] and [GDML][] were not enabled in the pre-compiled [Geant4][] libraries.

The [container][] image can be pulled from <https://hub.docker.com/r/physino/gears> and run locally using [docker-compose][] in the following way:

```sh
# docker-compose.yml is located in /path/to/gears
cd /path/to/gears
# use docker-compose to run gears
# --rm (optional) is used to delete the container after each use
# if the image physino/gears doesn't exist locally,
# it will be pulled from https://hub.docker.com/r/physino/gears
docker-compose run --rm gears
# the command prompt will change to the following,
# where you can run gears
root@Geant4.11.1:~/gears $
```

> **Note**
> The [Geant4][] [datasets][download] are not included in the [container][] to keep its size minimal. However, they can be easily downloaded through the [container][] into the [gears/INSTALL/Geant4/data/](../Geant4/data) folder in the host computer:

```sh
root@Geant4-11.1.1:~/gears $ geant4-config --install-datasets
root@Geant4-11.1.1:~/gears $ ls INSTALL/Geant4/data
root@Geant4-11.1.1:~/gears $ gears
**************************************************************
 Geant4 version Name: geant4-11-01-patch-01 [MT]   (10-February-2023)
                       Copyright : Geant4 Collaboration
                      References : NIM A 506 (2003), 250-303
                                 : IEEE-TNS 53 (2006), 270-278
                                 : NIM A 835 (2016), 186-225
                             WWW : http://geant4.org/
**************************************************************

Available UI session types: [ tcsh, csh ]
PreInit>
```

Another image, <https://hub.docker.com/r/physino/heprapp>, is created with the [HepRApp][] viewer included to visualize detector geometries created using <https://hub.docker.com/r/physino/gears>.

## For developer

### Generate the image

The [container][] image <https://hub.docker.com/r/physino/gears> can be generated in two ways:

1. use `docker build`:

```sh
cd gears/INSTALL/Docker
docker build -t physino/gears .
docker push physino/gears
```

2. use `docker-compose`:

```sh
cd gears
docker-compose build gears
docker-compose push gears
```

### Update the image
`docker-compose run --rm gears` provides an interactive bash, where one can install any package that she likes. For example,

```sh
root@Geant4:~/gears $ dnf install glibc-langpack-en
```

One can also use it to update [GEARS][] in the image if [gears.cc](../../gears.cc) is modified:

```sh
root@Geant4:~/gears $ make
root@Geant4:~/gears $ mv gears /usr/bin
root@Geant4:~/gears $ exit
# list all containers
docker ps -a
CONTAINER ID  IMAGE                 COMMAND  CREATED         STATUS                     PORTS  NAMES
53614a6b7563  physino/gears:latest  "bash"   3 minutes ago   Exited (0) 14 seconds ago         eloquent_napier
# commit the updated container into image physino/gears
docker commit 53614a6b7563 physino/gears
# push the image to docker hub
docker push physino/gears
```

[Geant4]: https://geant4.web.cern.ch
[Docker]: https://www.docker.com
[container]: https://www.docker.com/resources/what-container
[download]: https://geant4.web.cern.ch/support/download
[Qt]: https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#qt
[GDML]: https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomXML.html
[GEARS]: https://github.com/jintonic/gears
[docker-compose]: https://docs.docker.com/compose
[HepRApp]: https://www.slac.stanford.edu/~perl/HepRApp/
