[![home](https://img.shields.io/badge/gears-home-blue?style=flat)](../../..)
[![examples](https://img.shields.io/badge/gears-examples-green?style=flat)](../..)
[![detector](https://img.shields.io/badge/examples-detector-orange?style=flat)](..)

## Visualization of detector geometry

The [visualization chapter](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visualization.html) of the [Geant4 Book For Application Developers](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html) documents in detail how to visualize a detector using various tools.

### ASCIITree

The [ASCIITree][] does not really visualize the detector geometry. Instead, it prints a hierarchical list of volumes in a detector on screen. If your geometry is simple, the only two commands you need in your macro is:

```
/vis/ASCIITree/verbose 13
/vis/drawTree
```

If your geometry is complicated, you can specify the volume to be printed following the instruction [here](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/AllResources/Control/UIcommands/_vis_ASCIITree_.html).

A [sample ASCIITree macro](ASCIITree.mac) is shipped with [GEARS][]. Try it out this way in Linux or macOS:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears ASCIITree.mac
```
Follow [this instruction](/gears/install/#user-interface) to try it out in Windows.

[ASCIITree]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#visualization-of-detector-geometry-tree

### RayTracer

[RayTracer](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#raytracer) is included in any [Geant4][] installation, and can be used for geometries that other tools may fail to visualize. Detailed instructions on RayTracer related built-in commands can be found [here](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Control/AllResources/Control/UIcommands/_vis_rayTracer_.html).

A [sample RayTracer macro](RayTracer.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears RayTracer.mac
```

It generates a `g4RayTracer.viewer-0_0000.jpeg` file in the same directory.

### VRML

[VRML][] is available in any [Geant4][] installation. It is used to generate files in VRML format, which can be viewed using an external program, such as [ORBISNAP][], [FreeWRL][], [OpenVRML][], [view3dscene][], [3D builder](https://www.microsoft.com/en-us/p/3d-builder/9wzdncrfj3t6) (default Windows 10 App),  etc., or be converted to its succeeder [X3D][], which can be viewed directly in a modern web browser that supports WebGL.

A [sample VRML macro](VRML.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears VRML.mac
```

It generates `g4_??.wrl` in the same directory.

A shell script [v2x][] is shipped in the same directory to convert the latest `g4_??.wrl` to `g4_??.x3d`, embed the latter to `g4_??.html` and run a simple http server using python3 in the current directory. Open <http://127.0.0.1/8888/g4_??.html> in a modern browser to see the result.

### HepRepFile

[HepRepFile](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#heprepfile) is available in any [Geant4][] installation. It can be used to generate `G4Data*.heprep` files, which can be viewed using an external program called [HepRApp][] in wireframe mode, that is, no surface, only outlines.

A [sample HepRepFile macro](HepRepFile.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears HepRepFile.mac
```

It generates `G4Data0.heprep` in the same directory. A shell script [hv](hv) is shipped with [GEARS][]. Run it this way:

```sh
$ ./hv G4Data0.heprep
```

If this is the first time you run it, it will download a `HepRApp.jar` file from the Internet and run it the following way:

```sh
java -jar HepRApp.jar -opt HepRApp.properties -file G4Data0.heprep
```

Unfortunately, `HepRApp.jar` can only be run on java version less or equal to 1.8, while current java version is 14 (as of 2020). To use the HepRApp viewer, you need to install two versions of java and switch to the older one if needed. This can be done, but the detailed procedure changes with the OS. In case of a Mac, one can follow [this link](https://stackoverflow.com/questions/24342886/how-to-install-java-8-on-mac) to install java 1.8 and [this link](https://stackoverflow.com/questions/21964709/how-to-set-or-change-the-default-java-jdk-version-on-os-x) to switch in between different versions of java. In case of Ubuntu, please refer to [this link](https://docs.datastax.com/en/jdk-install/doc/jdk-install/installOpenJdkDeb.html). In case of Windows, simply download jdk8 from the [oracle website](https://www.oracle.com/java/technologies/javase/javase-jdk8-downloads.html).

[HepRApp.properties](HepRApp.properties) is the configuration file for [HepRApp][]. It is also shipped with [GEARS][].

[HepRApp]: https://www.slac.stanford.edu/~perl/HepRApp/

### HepRepXML

[HepRepXML](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#heprepxml) is available in any [Geant4][] installation. It is used to generate binary HepRep (`.bheprep`) or XML HepRep (`.heprep`) file, which can be viewed using an external program called [JAS3][] with the [WIRED4][] plugin.

A [sample HepRepXML macro](HepRepXML.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears HepRepXML.mac
```

It generates `scene-0.heprep.zip` in the same directory, which can be directly open using [WIRED4][] in [JAS3][].

[JAS3]: http://jas.freehep.org/jas3
[WIRED4]:http://wired.freehep.org/index.html

### DAWNFILE

[DAWNFILE](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#dawn) is available in any [Geant4][] installation. It can be used to generate `g4_*.prim` files, which can be converted to an EPS file using an external program called [dawn](https://geant4.kek.jp/~tanaka/DAWN/About_DAWN.html).

A [sample DAWNFILE macro](DAWN.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears DAWN.mac
```

### OpenGL

[OpenGL][] is included in most [Geant4][] installations. Detailed instructions on OpenGL related built-in commands can be found [here](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Control/AllResources/Control/UIcommands/_vis_ogl_.html)

A [sample OpenGL macro](OpenGL.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd examples/detector/visualization
$ gears OpenGL.mac
```

It generates a `gears_????.pdf` file in the same directory.

Note that even if you run it in batch mode, the [Geant4][] [UI][] session must be set to [Qt][] instead of [tcsh][]. Otherwise [OpenGL][] won't work. It can also be run in the [interactive mode](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/GettingStarted/graphicalUserInterface.html), where you can use your mouse to rotate the visualized geometry.

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

[OpenGL]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#opengl
[UI]:../../../#user-interface
[Qt]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/GettingStarted/graphicalUserInterface.html#g4uixm-g4uiqt-and-g4uiwin32-classes
[tcsh]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/GettingStarted/graphicalUserInterface.html#g4uiterminal

[GEARS]: http://physino.xyz/gears
[Geant4]: http://geant4.cern.ch
[VRML]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#vrml
[ORBISNAP]:https://www.orbisnap.com/download2.html
[OpenVRML]:https://sourceforge.net/projects/openvrml/
[FreeWRL]: https://sourceforge.net/projects/freewrl/
[view3dscene]:https://castle-engine.sourceforge.io/view3dscene.php
[X3D]:https://stackoverflow.com/questions/14849593/vrml-to-x3d-conversion
[v2x]:https://github.com/jintonic/gears/blob/master/examples/detector/visualization/v2x
