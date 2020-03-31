[![home](https://img.shields.io/badge/gears-home-blue?style=flat)](../..)
[![examples](https://img.shields.io/badge/gears-examples-green?style=flat)](..)
[![common sources](https://img.shields.io/badge/common-sources-red?style=flat)](#common-sources)

[GEARS][] uses the [Geant4][] [general particle source][gps] to generate the [primary particles][], from which a [Geant4][] simulation starts (see [this plot](../output#step-point) to understand the general concept). The up-to-date examples of [gps][] are shipped together with the [Geant4][] source code in the folder:

- [geant4/examples/extended/eventgenerator/exgps/macros]({{site.g4git}}/../examples/extended/eventgenerator/exgps/macros)

An [outdated webpage](http://hurel.hanyang.ac.kr/Geant4/Geant4_GPS/reat.space.qinetiq.com/gps/examples/examples.html) shows most of the examples contained in the folder above. In addition, it also shows resulted distribution plots, which are very helpful to understand the real effects of the [gps][] macro commands.

[Geant4][] also provide a much simpler particle source ([particle gun]({{site.g4doc}}/Control/AllResources/Control/UIcommands/_gun_.html)), which is less powerful, but covers some basic user cases.

[GEARS]: http://physino.xyz/gears
[Geant4]: http://geant4.cern.ch
[gps]:{{site.g4doc}}/GettingStarted/generalParticleSource.html
[primary particles]: {{site.g4doc}}/Fundamentals/eventGenerator.html

## GPS macros

An ASCII version of the manual of [gps][] macros is available [here]({{site.xyz}}/examples/sources/gps.txt).

### Source in a volume

```sh
/gps/pos/confine physics_volume_name
```

### Source on a surface

```sh
# on a plane
/gps/pos/type Plane
# <shape> can be Circle, Annulus, Ellipse, Square, Rectangle
/gps/pos/shape <shape>

# on the surface of a volume
/gps/pos/type Surface
# <shape> can be Sphere, Ellipsoid, Cylinder, EllipticCylinder, Para
/gps/pos/shape <shape>
```

## Common sources

### Am241

Am241 is a complicated source. It is an alpha, X-ray and gamma emitter at the same time. A mac file is inclued [here]({{site.file}}/examples/sources/Am241.mac) to demonstrate the definition of multiple particles from a source.

### AmBe

The alpha partiles emitted from Am241 can be used to bonbust Be and generate neutrons up to about 12 MeV. The measured neutron energy spectrum can be found in the literature. A mac file is included [here]({{site.file}}/examples/sources/AmBe/AmBe.mac) to demonstrate how to generate neutrons based on an energy spectrum.

### Ar39

Ar39 is a beta emitter. It is a common background for examples ulitize liquid argon as detecting material. Its measured beta spectrum is implemented in [this mac file]({{site.file}}/examples/sources/Ar39.mac).

### Co57

Co57 is a common low-energy calibration source. It emits a few x and gamma-rays as shown in [this mac file]({{site.file}}/examples/sources/Co57.mac).

### Fe55

Fe55 is an other commonly used low-energy calibration source. It emits a few x-rays around 6 keV as shown in [this mac file]({{site.file}}/examples/sources/Fe55.mac).
