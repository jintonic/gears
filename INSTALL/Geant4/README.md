[![Docker image](https://img.shields.io/badge/Docker-image-orange?style=flat)](https://hub.docker.com/r/physino/geant4)
[![Singularity image](https://img.shields.io/badge/Singularity-image-yellow?style=flat)](https://cloud.sylabs.io/library/jintonic/geant4/gears)

## Docker image

[Dockerfile](Dockerfile) in this folder is used to install the latest [Geant4][] in the latest [Fedora][] [Docker][] [container][].

The 64-bit [Geant4][] libraries were pre-compiled with gcc 8.3.0 on CERN CentOS7 (CC7) Linux. They were directly downloaded from the [Geant4][] [download][] page. Fortunately, they run just fine on the latest [Fedora][], which is a more up-to-date OS than CC7.

The [image][] can be generated using the following commands:

```sh
cd /path/to/gears/
docker-compose build g4
docker push physino/geant4:gears
```

[GEARS][] is included in `/usr/bin` in this [image][] as a verification of the [Geant4][] installation.

As the libraries were compiled already, the installation process only involves downloading and unpacking them, and only costs about 12 minutes, where, 10 minutes is used to download and unpack [Geant4][] [datasets][download]. Unfortunately, [Qt][] and [GDML][] were not enabled in the pre-compilation. Another image, <https://hub.docker.com/r/physino/g4vis>, is created with the [HepRApp][] viewer included to visualize detector geometries created using this [image][].

[Geant4]: https://geant4.web.cern.ch
[Fedora]: https://hub.docker.com/_/fedora
[Docker]: https://www.docker.com
[container]: https://www.docker.com/resources/what-container
[download]: https://geant4.web.cern.ch/support/download
[GEARS]: https://github.com/jintonic/gears
[image]: https://hub.docker.com/r/physino/geant4
[Qt]: https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#qt
[GDML]: https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomXML.html
[HepRApp]: https://www.slac.stanford.edu/~perl/HepRApp/

## Singularity image

[singularity.def](singularity.def) in this folder is used to generate [apptainer][]/[singularity][] images from the [GEARS][] [Docker][] [image][] mentioned above using the following commands:

```sh
cd /path/to/gears/INSTALL/Geant4
sudo singularity build gears.sif singularity.def
```

You must run the `build` command with `sudo`. If you don't have the privilege to run `sudo`, you can use the remote build option provided by [singularity][] to build the image in <https://cloud.sylabs.io>:

```sh
singularity build -r gears.sif singularity.def
```

I sign and push the image to <https://cloud.sylabs.io/library/jintonic/geant4/gears> using the following commands:

```sh
singularity sign gears.sif
singularity push gears.sif library://jintonic/geant4/gears:latest
```

On a Linux machine that has [singularity][]/[apptainer][] installed, you can pull the image using the following commands:

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

The `sif` file can be directly used as an executable:
```sh
./gears.sif example.mac


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

[singularity]: https://en.wikipedia.org/wiki/Singularity_(software)
[apptainer]: https://apptainer.org
[remote]: https://apptainer.org/docs/user/1.0/endpoint.html
