## Detector visualization
The [visualization chapter](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visualization.html) of the [Geant4 Book For Application Developers](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html) documents in detail how to visualize a detector using various tools.

### ASCIITree

The [ASCIITree](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#visualization-of-detector-geometry-tree) does not really visualize the detector geometry. Instead, it prints a hierarchical list of volumes in a detector on screen. If your geometry is simple, the only two commands you need in your macro is:

```
/vis/ASCIITree/verbose 13
/vis/drawTree
```

If your geometry is complicated, you can specify the volume to be printed following the instruction [here](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/AllResources/Control/UIcommands/_vis_ASCIITree_.html).

A [sample ASCIITree macro](https://github.com/jintonic/gears/blob/master/examples/detector/visualization/ASCIITree.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears ASCIITree.mac
```

### RayTracer

[RayTracer](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#raytracer) is included in any [Geant4][] installation, and can be used for geometries that other tools may fail to visualize. Detailed instructions on RayTracer related built-in commands can be found [here](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Control/AllResources/Control/UIcommands/_vis_rayTracer_.html)

A [sample RayTracer macro](https://github.com/jintonic/gears/blob/master/examples/detector/visualization/RayTracer.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears RayTracer.mac
```

It generates a `g4RayTracer.viewer-0_0000.jpeg` file in the same directory.

### OpenGL

[OpenGL](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#opengl) is included in most [Geant4][] installations. Detailed instructions on OpenGL related built-in commands can be found [here](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Control/AllResources/Control/UIcommands/_vis_ogl_.html)

A [sample OpenGL macro](https://github.com/jintonic/gears/blob/master/examples/detector/visualization/OpenGL.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears OpenGL.mac
```

It generates a `gears_0000.pdf` file in the same directory.

It can also be run in an [interactive session](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/GettingStarted/graphicalUserInterface.html).

Not that for Mac users, you may need to run

```sh
defaults write org.macosforge.xquartz.X11 enable_iglx -bool true
```

in a terminal to enable `iglx` for XQuartz if you encounter the following error message when running `gears OpenGL.mac`:

```
libGL error: No matching fbConfigs or visuals found
libGL error: failed to load driver: swrast
X Error ...
```

References:

- <https://www.hoffman2.idre.ucla.edu/access/x11_forwarding/#Mac_OS_X>
- <https://www.xquartz.org/releases/XQuartz-2.7.10.html>

### DAWNFILE

[DAWNFILE](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#dawn) is available in any [Geant4][] installation. It can be used to generate `g4_*.prim` files, which can be converted to an EPS file using an external program called [dawn](https://geant4.kek.jp/~tanaka/DAWN/About_DAWN.html).

A [sample DAWNFILE macro](https://github.com/jintonic/gears/blob/master/examples/detector/visualization/DAWN.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears DAWN.mac
```

### HepRepFile

[HepRepFile](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#heprepfile) is available in any [Geant4][] installation. It can be used to generate `G4Data*.heprep` files, which can be viewed using an external program called [HepRApp][] in wireframe mode, that is, no surface, only outlines.

A [sample HepRepFile macro](https://github.com/jintonic/gears/blob/master/examples/detector/visualization/HepRepFile.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears HepRepFile.mac
```

It generates `G4Data0.heprep` in the same directory. A shell script [hv](https://github.com/jintonic/gears/blob/master/examples/detector/visualization/hv) is shipped with [GEARS][]. Run it this way:

```sh
$ ./hv G4Data0.heprep
```

If this is the first time you run it, it will download a `HepRApp.jar` file from the Internet and run it the following way:

```sh
java -jar HepRApp.jar -opt HepRApp.properties -file G4Data0.heprep
```

[HepRApp.properties](https://github.com/jintonic/gears/blob/master/examples/detector/visualization/HepRApp.properties) is the configuration file for [HepRApp][]. It is also shipped with [GEARS][].

[HepRApp]: https://www.slac.stanford.edu/~perl/HepRApp/

### HepRepXML

[HepRepXML](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#heprepxml) is available in any [Geant4][] installation. It is used to generate binary HepRep (`.bheprep`) or XML HepRep (`.heprep`) file, which can be viewed using an external program called [JAS3][] with the [WIRED4][] plugin.

A [sample HepRepXML macro](https://github.com/jintonic/gears/blob/master/examples/detector/visualization/HepRepXML.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears HepRepXML.mac
```

It generates `scene-0.heprep.zip` in the same directory, which can be directly open using [WIRED4][] in [JAS3][].

[JAS3]: http://jas.freehep.org/jas3
[WIRED4]:http://wired.freehep.org/index.html

### VRML

[VRML][] is available in any [Geant4][] installation. It is used to generate files in VRML format, which can be viewed using an external program, such as [ORBISNAP][], [OpenVRML][], [view3dscene][], etc., or be converted to its succeeder [X3D][], which can be viewed directly in a modern web browser that supports WebGL.

A [sample VRML macro](https://github.com/jintonic/gears/blob/master/examples/detector/visualization/VRML.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears VRML.mac
```

It generates `g4_??.wrl` in the same directory.

A shell script [v2x][] is shipped in the same directory to convert the latest `g4_??.wrl` to `g4_??.x3d`, embed the latter to `g4_??.html` and run a simple http server using python3 in the current directory. Open <http://127.0.0.1/8888/g4_??.html> in a modern browser to see the result.

[VRML]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#vrml
[ORBISNAP]:https://www.orbisnap.com/download2.html
[OpenVRML]:https://sourceforge.net/projects/openvrml/
[view3dscene]:https://castle-engine.sourceforge.io/view3dscene.php
[X3D]:https://stackoverflow.com/questions/14849593/vrml-to-x3d-conversion
[v2x]:https://github.com/jintonic/gears/blob/master/examples/detector/visualization/v2x

## Detector construction
### Geometry
Instead of using geometry written in C++ as described in detail in the [Geant4 manual](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomSolids.html), [GEARS][] accepts two types of detector geometry descriptions in pure ASCII format as input:
- [Geant4][] [text geometry description][tg] (recommended)
- [GDML][] (provided for data analysis and visualization in other tools)
Their difference is similar to that between [markdown][md] and [HTML][]. The simpler [text geometry description][tg] provided by [Geant4][] is recommended to be used as [GEARS][]'s input given its simplicity and readability. For example, an experimental hall filled with air and of a dimension of 10 x 10 x 10 meters can be easily implemented using the following line:

~~~
:volume hall BOX 5*m 5*m 5*m G4_AIR
~~~

For more examples, please check `*.tg` files in the [examples/detector](https://github.com/jintonic/gears/blob/master/examples/detector) directory, such as [examples/detector/gears.tg](https://github.com/jintonic/gears/blob/master/examples/detector/gears.tg) and [example/detector/solids.tg](https://github.com/jintonic/gears/blob/master/examples/detector/solids.tg). The suffix of *.tg* indicates that they are [text geometry][tg] description files. A [Geant4][] macro command `/geometry/source` is added to load geometry files:

~~~sh
/geometry/source gears.tg
~~~

You can utilize [Boolean operation](boolean) or [shell scripts](scripts) to construct more complicated geometries.

Alternatively, you can read a [GDML][] file:

~~~sh
/geometry/source file.gdml
~~~

The command must be used before [/run/initialize][run], otherwise [GEARS][] will construct a simple experimental hall automatically to prevent crashing.

[GEARS][] provides the following command to export constructed detector geometry to a [GDML][] file:

~~~sh
/geometry/export output.gdml
~~~

This can only be used after the macro command [/run/initialize][run], which constructs the detector geometry before exporting. While the simpler [text geometry description][tg] can only be understood by [Geant4][], [GDML][] can be understood by many other tools. For example, [ROOT][] provides functions to read and visualize [GDML][] geometries. On the other hand, it is not that easy to write a valid [GDML][] file manually. This functionality is provided to enable the following usage:

~~~sh
 # describe the detector using simple text geometry description
 /geometry/source input.tg
 # construct the detector
 /run/intialize
 # export detector geometry as GDML for analysis/visualization in other tools
 /geometry/export output.gdml
~~~

You can find a concrete example in [example/detector/GDML](GDML).

#### Sensitive detector

Sensitive detectors are specified by simply add "(S)" at the end of their volume names. The copy numbers of their volumes must be continuous integers starting from 0.

### Material

The [NIST][] material table provided by [Geant4][] contains all elements (C, H, O, for example) and a lot of commonly used materials (start with "G4_"). One can run /material/nist/[listMaterials][] at any [Geant4][] state to print the list locally. These materials can be used directly in a [text geometry description][tg], for example

~~~
// use Geant4 elements, C and H to define TPB
:MIXT_BY_NATOMS TPB 1.079 2 C 28 H 22
// use NIST material G4_AIR to define vacuum
:mixt vacuum 1e-9 1 G4_AIR 1
~~~

### Optical properties of a material or a surface

There is no tag to define the optical properties of a material or a surface in the default [Geant4][] [text geometry description][tg]. The following two tags are added in [GEARS][] to enable definition of optical materials and surfaces using [Geant4][] [text geometry description][tg] syntax:

#### Define optical properties of a material

~~~
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
  photon_energies 2 2.034*eV, 3.025*eV, 4.136*eV
  RINDEX 1.34, 1.35, 1.36
  ABSLENGTH 1.0*meter, 1.1*meter, 1.2*meter
~~~

#### Define optical properties of a surface

First of all, there is no need to define a *surface* for polished interfaces between two media. As long as the two media have an index of refraction stored in their respective G4MaterialPropertiesTable, the [G4OpBoundaryProcess][]::[PostStepDoIt][] will handle the refraction and reflection correctly.

One can use the following syntax to define a [G4LogicalBorderSurface][] in case that there is a real need to specify the optical properties of the interface:

~~~
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

[GEARS]: http://physino.xyz/gears
[tg]: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomASCII.html
[Geant4]: http://geant4.cern.ch
[NIST]: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Appendix/materialNames.html
[run]: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Control/AllResources/Control/UIcommands/_run_.html
[listMaterials]: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Control/AllResources/Control/UIcommands/_material_nist_.html
[G4OpBoundaryProcess]: http://www-geant4.kek.jp/lxr/source//processes/optical/include/G4OpBoundaryProcess.hh
[PostStepDoIt]: http://www.apc.univ-paris7.fr/~franco/g4doxy4.10/html/class_g4_op_boundary_process.html#a70a65cc5127a05680a0c4679f8300871
[G4LogicalBorderSurface]: http://www-geant4.kek.jp/lxr/source/geometry/volumes/include/G4LogicalBorderSurface.hh
[GDML]: https://gdml.web.cern.ch/GDML/
[md]: https://en.wikipedia.org/wiki/Markdown
[HTML]: https://www.w3schools.com/html/
[ROOT]: https://root.cern.ch
