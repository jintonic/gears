[![jintonic/geant4/gears](https://img.shields.io/badge/geant4-gears-blue?style=flat)](https://cloud.sylabs.io/library/jintonic/geant4/gears)

The [GEARS][] [Apptainer][]/[Singularity][] image can be pulled from [sylabs][]:

```sh
singularity pull gears.sif library://jintonic/geant4/gears
```

or

```sh
apptainer pull library://jintonic/geant4/gears
```

Note that you may need to set the location of your [Apptainer][] [remote][] library before `pull`:

```sh
apptainer remote add sylabs https://cloud.sylabs.io
apptainer remote use sylabs
apptainer remote list
```

The `sif` file can be directly used as an executable:
```sh
./gears.sif example.mac
```

## For developer

[gears.def](gears.def) in this folder is used to generate the [Apptainer][]/[Singularity][] images from the [GEARS Docker image](../Docker) using the following commands:

```sh
cd gears/INSTALL/Apptainer
sudo singularity build gears.sif gears.def
```

You must run the `build` command with `sudo`. If you don't have the privilege to run `sudo`, you can use the remote build option provided by [Singularity][] to build the image in <https://cloud.sylabs.io>:

```sh
singularity build -r gears.sif gears.def
```

I sign and push the image to <https://cloud.sylabs.io/library/jintonic/geant4/gears> using the following commands:

```sh
singularity sign gears.sif
singularity push gears.sif library://jintonic/geant4/gears:latest
```

[GEARS]: https://github.com/jintonic/gears
[Apptainer]: https://apptainer.org
[Singularity]: https://en.wikipedia.org/wiki/Singularity_(software)
[sylabs]: https://cloud.sylabs.io/library/jintonic/geant4/gears
[remote]: https://apptainer.org/docs/user/1.0/endpoint.html

