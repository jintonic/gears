[![home](https://img.shields.io/badge/gears-home-blue?style=flat)](../../..)
[![examples](https://img.shields.io/badge/gears-examples-green?style=flat)](../..)
[![detector](https://img.shields.io/badge/examples-detector-orange?style=flat)](..)

## Visualization of detector geometry

The [visualization chapter]({{site.g4doc}}/Visualization/visualization.html) of the [Geant4 Book For Application Developers]({{site.g4doc}}) documents in detail how to visualize a detector using various tools.

### ASCIITree

The [ASCIITree][]) does not really visualize the detector geometry. Instead, it prints a hierarchical list of volumes in a detector on screen. If your geometry is simple, the only two commands you need in your macro is:

```
/vis/ASCIITree/verbose 13
/vis/drawTree
```

If your geometry is complicated, you can specify the volume to be printed following the instruction [here]({{site.g4doc}}/Visualization/AllResources/Control/UIcommands/_vis_ASCIITree_.html).

A [sample ASCIITree macro]({{site.file}}/examples/detector/visualization/ASCIITree.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears ASCIITree.mac
```
[ASCIITree]:{{site.g4doc}}/Visualization/visdrivers.html#visualization-of-detector-geometry-tree

### RayTracer

[RayTracer]({{site.g4doc}}/Visualization/visdrivers.html#raytracer) is included in any [Geant4][] installation, and can be used for geometries that other tools may fail to visualize. Detailed instructions on RayTracer related built-in commands can be found [here]({{site.g4doc}}/Control/AllResources/Control/UIcommands/_vis_rayTracer_.html)

A [sample RayTracer macro]({{site.file}}/examples/detector/visualization/RayTracer.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears RayTracer.mac
```

It generates a `g4RayTracer.viewer-0_0000.jpeg` file in the same directory.

### OpenGL

[OpenGL][] is included in most [Geant4][] installations. Detailed instructions on OpenGL related built-in commands can be found [here]({{site.g4doc}}/Control/AllResources/Control/UIcommands/_vis_ogl_.html)

A [sample OpenGL macro]({{site.file}}/examples/detector/visualization/OpenGL.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears OpenGL.mac
```

It generates a `gears_????.pdf` file in the same directory.

Note that even if you run it in batch mode, the [Geant4][] [UI][] session must be set to [Qt][] instead of [tcsh][]. Otherwise [OpenGL][] won't work. It can also be run in the [interactive mode]({{site.g4doc}}/GettingStarted/graphicalUserInterface.html), where you can use your mouse to rotate the visualized geometry.

For Mac users, you may need to run

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

[OpenGL]:{{site.g4doc}}/Visualization/visdrivers.html#opengl
[UI]:../../../#user-interface
[Qt]:{{site.g4doc}}/GettingStarted/graphicalUserInterface.html#g4uixm-g4uiqt-and-g4uiwin32-classes
[tcsh]:{{site.g4doc}}/GettingStarted/graphicalUserInterface.html#g4uiterminal

### DAWNFILE

[DAWNFILE]({{site.g4doc}}/Visualization/visdrivers.html#dawn) is available in any [Geant4][] installation. It can be used to generate `g4_*.prim` files, which can be converted to an EPS file using an external program called [dawn](https://geant4.kek.jp/~tanaka/DAWN/About_DAWN.html).

A [sample DAWNFILE macro]({{site.file}}/examples/detector/visualization/DAWN.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears DAWN.mac
```

### HepRepFile

[HepRepFile]({{site.g4doc}}/Visualization/visdrivers.html#heprepfile) is available in any [Geant4][] installation. It can be used to generate `G4Data*.heprep` files, which can be viewed using an external program called [HepRApp][] in wireframe mode, that is, no surface, only outlines.

A [sample HepRepFile macro]({{site.file}}/examples/detector/visualization/HepRepFile.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears HepRepFile.mac
```

It generates `G4Data0.heprep` in the same directory. A shell script [hv]({{site.file}}/examples/detector/visualization/hv) is shipped with [GEARS][]. Run it this way:

```sh
$ ./hv G4Data0.heprep
```

If this is the first time you run it, it will download a `HepRApp.jar` file from the Internet and run it the following way:

```sh
java -jar HepRApp.jar -opt HepRApp.properties -file G4Data0.heprep
```

[HepRApp.properties]({{site.file}}/examples/detector/visualization/HepRApp.properties) is the configuration file for [HepRApp][]. It is also shipped with [GEARS][].

[HepRApp]: https://www.slac.stanford.edu/~perl/HepRApp/

### HepRepXML

[HepRepXML]({{site.g4doc}}/Visualization/visdrivers.html#heprepxml) is available in any [Geant4][] installation. It is used to generate binary HepRep (`.bheprep`) or XML HepRep (`.heprep`) file, which can be viewed using an external program called [JAS3][] with the [WIRED4][] plugin.

A [sample HepRepXML macro]({{site.file}}/examples/detector/visualization/HepRepXML.mac) is shipped with [GEARS][]. Try it out this way:

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

A [sample VRML macro]({{site.file}}/examples/detector/visualization/VRML.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears VRML.mac
```

It generates `g4_??.wrl` in the same directory.

A shell script [v2x][] is shipped in the same directory to convert the latest `g4_??.wrl` to `g4_??.x3d`, embed the latter to `g4_??.html` and run a simple http server using python3 in the current directory. Open <http://127.0.0.1/8888/g4_??.html> in a modern browser to see the result.

[GEARS]: http://physino.xyz/gears
[Geant4]: http://geant4.cern.ch
[VRML]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#vrml
[ORBISNAP]:https://www.orbisnap.com/download2.html
[OpenVRML]:https://sourceforge.net/projects/openvrml/
[view3dscene]:https://castle-engine.sourceforge.io/view3dscene.php
[X3D]:https://stackoverflow.com/questions/14849593/vrml-to-x3d-conversion
[v2x]:https://github.com/jintonic/gears/blob/master/examples/detector/visualization/v2x
