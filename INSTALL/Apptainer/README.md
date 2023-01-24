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

[GEARS]: https://github.com/jintonic/gears
[Apptainer]: https://apptainer.org
[Singularity]: https://en.wikipedia.org/wiki/Singularity_(software)
[sylabs]: https://cloud.sylabs.io/library/jintonic/geant4/gears
[remote]: https://apptainer.org/docs/user/1.0/endpoint.html
