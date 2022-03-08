[![home](https://img.shields.io/badge/gears-home-blue?style=flat)](../../..)
[![examples](https://img.shields.io/badge/gears-examples-green?style=flat)](../..)
[![detector](https://img.shields.io/badge/detector-construction-orange?style=flat)](..)
[![optical processes](https://img.shields.io/badge/optical-processes-red?style=flat)](../../physics#optical-processes)

One can hard code the optical properties of a material or a surface in C++, which requires recompiling of the source code. [GDML][] can also be used, but with some limitation (for example, [properties cannot be assigned to existing NIST materials pre-defined in Geant4](https://geant4-forum.web.cern.ch/t/adding-optical-properties-to-built-in-g4-materials-using-gdml/340/4)). Worse, there is no way to define optical properties in the default [Geant4][] [text geometry description][tg].

The following two tags are added in [GEARS][] to enable definition of optical materials and surfaces using [Geant4][] [text geometry description][tg] syntax. **NOTE** that they need to be placed at the end of a _.tg_ file to avoid interrupting the processing of known tags by [Geant4][] before [GEARS][] processes the added ones.

More than 40% of the ~550 lines of C++ code in [gears.cc](../../../gears.cc) is used to implement this new feature. If it is absorbed in future [Geant4][] releases, [gears.cc](../../../gears.cc) can become a lot smaller.

## Define optical properties of a material

~~~cpp
//:prop <material>
//  <wavelength-independent_property> <value>
:prop pureCsIat77K
  SCINTILLATIONYIELD 100./keV
  RESOLUTIONSCALE 2.
  FASTTIMECONSTANT 1.*ns
  SLOWTIMECONSTANT 1.*us
  YIELDRATIO 0.8

//:prop <material> photon_energies <int(array size)> <energy array>
//  <wavelength-dependent_property> <property values>
:prop pureCsIat77K
  photon_energies 2 2.034*eV 3.025*eV 4.136*eV
  RINDEX 1.34 1.35 1.36
  ABSLENGTH 1.0*meter 1.1*meter 1.2*meter
~~~

## Define optical properties of a surface

First of all, there is no need to define a *surface* for polished interfaces between two media. As long as the two media have an index of refraction stored in their respective G4MaterialPropertiesTable, the [G4OpBoundaryProcess][]::[PostStepDoIt][] will handle the refraction and reflection correctly.

One can use the following syntax to define a [G4LogicalBorderSurface][] in case that there is a real need to specify the optical properties of the interface:

~~~cpp
//:surf v12v2 v1:copyNo1 v2:copyNo2
:surf CsI2Teflon CsI:1 Teflon:1
  type dielectric_dielectric
  model unified
  finish ground
  sigma_alpha 0.1
  property photon_energies 2 2.5*eV 5.0*eV
    REFLECTIVITY 0.9 0.9
//property must be the last setting due to the current coding method
~~~

Note that physics volumes from the same logical volume created by the text geometry processor share the same name as their logical volume. Since [G4LogicalBorderSurface][] requires pointers to the two physical volumes beside, a unique copy number has to be attached to the volume name to uniquely identify the physics volume.

Please read [the Geant4 manual](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/TrackingAndPhysics/physicsProcess.html#boundary-process) if you would like to learn more about the optical interface models in Geant4.

You can also run example macros in the [surface/](surface/) directory to understand the difference between different surfaces.

[GEARS]: http://physino.xyz/gears
[tg]: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomASCII.html
[Geant4]: http://geant4.cern.ch
[GDML]: https://gdml.web.cern.ch/GDML/
[G4OpBoundaryProcess]: http://www-geant4.kek.jp/lxr/source//processes/optical/include/G4OpBoundaryProcess.hh
[PostStepDoIt]: http://www.apc.univ-paris7.fr/~franco/g4doxy4.10/html/class_g4_op_boundary_process.html#a70a65cc5127a05680a0c4679f8300871
[G4LogicalBorderSurface]: http://www-geant4.kek.jp/lxr/source/geometry/volumes/include/G4LogicalBorderSurface.hh
