[![home](https://img.shields.io/badge/gears-home-blue?style=flat)](../../..)
[![examples](https://img.shields.io/badge/gears-examples-green?style=flat)](../..)
[![detector](https://img.shields.io/badge/examples-detector-orange?style=flat)](..)

## Boolean operation

Three [examples][] are provided here to demonstrate how to create a complex geometry using the [Boolean][] operation.

<img style="float:right; width:120px;" src="tophat.png"/>

### Tophat geometry

A tophat geometry is described in [tophat.tg](tophat.tg) which is visualized using [tophat.mac](tophat.mac):

```sh
$ gears tophat.mac
```

You need to install [dawn][] or [HepRApp][] to view the result.

[examples]:https://github.com/jintonic/gears/tree/master/examples/detector/boolean
[Boolean]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomSolids.html?highlight=boolean#solids-made-by-boolean-operations
[dawn]:https://geant4.kek.jp/~tanaka/DAWN/About_DAWN.html
[HepRApp]: https://www.slac.stanford.edu/~perl/HepRApp/

<img style="float:right; width:120px;" src="frame2.png"/>

### Frame geometry
[frame1.tg](frame1.tg) and [frame1.mac](frame1.mac) are created to demonstrate that [RayTracer][] always works to visualize geometries that other [visualization drivers][] cannot handle. [frame2.tg](frame2.tg) and [frame2.mac](frame2.mac) are created to demonstrate how to avoid creating a geometry that are problematic in visualization.

```sh
$ gears frame1.mac # can only be visualized by RayTracer
$ gears frame2.mac # can be visualized by any tool
```

[RayTracer]: ../#raytracer
[visualization drivers]: ..

### Hemispherical HPGe detector

Run the following command to produce four png files showing how to create a hemispherical Ge detector with holders using the [Boolean][] operation step by step:

~~~sh
$ ./cut.sh
~~~

One has to have the shell command *convert* available to generate the png files. Detailed settings and usage of DAWN are demonstrated in [cut.mac](cut.mac) and [cut.sh](cut.sh).

