[![YouTube](https://img.shields.io/badge/You-Tube-red?style=flat)](https://youtu.be/ySOIkUnT3rw)
[![ASCIITree](https://img.shields.io/badge/ASCII-Tree-blue?style=flat)](#asciitree)
[![RayTracer](https://img.shields.io/badge/Ray-Tracer-green?style=flat)](#raytracer)
[![VRML](https://img.shields.io/badge/VRML-orange?style=flat)](#vrml)
[![HepRepFile](https://img.shields.io/badge/HepRep-File-yellow?style=flat)](#heprepfile)
[![ToolsSG](https://img.shields.io/badge/Tools-SG-red?style=flat)](#tsg)
[![DAWNFILE](https://img.shields.io/badge/DAWN-FILE-cyan?style=flat)](#dawnfile)
[![OpenGL](https://img.shields.io/badge/Open-GL-magenta?style=flat)](#opengl)

## Visualization of detector geometry

The [visualization chapter](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visualization.html) of the [Geant4 Book For Application Developers](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html) documents in detail how to visualize a detector using various tools.

### ASCIITree

The [ASCIITree][] visualization driver does not really visualize anything. Instead, it prints a hierarchical list of volumes in a detector in a terminal. If your geometry is simple, the only two commands you need in your macro is:

```
/vis/ASCIITree/verbose 13
/vis/drawTree
```

If your geometry is complicated, you can specify the volume to be printed following the instruction [here](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/AllResources/Control/UIcommands/_vis_ASCIITree_.html).

A [sample ASCIITree macro](ASCIITree.mac) is shipped with [GEARS][]. Try it out this way in Linux or macOS:

```sh
$ cd /path/to/gears
$ cd tutorials/detector/visualization
$ gears ASCIITree.mac
```
Follow [this instruction][UI] to try it out in Windows.

[ASCIITree]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#visualization-of-detector-geometry-tree

### RayTracer

The [RayTracer][] visualization driver is included in any [Geant4][] installation, and can be used for geometries that other tools may fail to visualize. Detailed instructions on [RayTracer][] related built-in commands can be found [here](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Control/AllResources/Control/UIcommands/_vis_rayTracer_.html).

A [sample RayTracer macro](RayTracer.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd tutorials/detector/visualization
$ gears RayTracer.mac
```

It generates a `g4RayTracer.viewer-0_0000.jpeg` file in the same directory. Note that the working principle of RayTracer is to shoot many rays (360000 by default) through the detector geometry and draw their intersecting points to reveal the geometry surfaces. Because of this, it takes more time than other methods to finish. It cannot be used to show particle trajectories, the world geometry, nor any cross section. Its advantage is to show complex geometry that other visualization method may fail.

### VRML

The [VRML][] visualization driver is available in any [Geant4][] installation. It is used to generate files in VRML format, which can be viewed using an external program, such as [ORBISNAP][], [FreeWRL][] (handy for MacOS), [OpenVRML][], [view3dscene][] (only for Linux and Windows), [3D builder](https://www.microsoft.com/en-us/p/3d-builder/9wzdncrfj3t6) (default Windows 10 App),  etc., or be converted to its succeeder [X3D][], which can be viewed directly in a modern web browser that supports WebGL.

A [sample VRML macro](VRML.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd tutorials/detector/visualization
$ gears VRML.mac
```

It generates `g4_??.wrl` in the same directory.

A shell script [v2x][] is shipped in the same directory to convert the latest `g4_??.wrl` to `g4_??.x3d`, embed the latter to `g4_??.html` and run a simple http server using python3 in the current directory. Open <http://127.0.0.1:8000/g4_??.html> in a modern browser to see the result.

The last service defined in [gears/docker-compose.yml](../../../docker-compose.yml) `x3d` serves a website in a Docker container to visualize `g4_??.html`.

### HepRepFile

[![Docker image](https://img.shields.io/badge/Docker-image-blue?style=flat)](https://hub.docker.com/r/physino/heprapp)
[![Apptainer image](https://img.shields.io/badge/Apptainer-image-red?style=flat)](https://cloud.sylabs.io/library/jintonic/geant4/vis)

The [HepRepFile][] visualization driver is available in any [Geant4][] installation. It can be used to generate `G4Data*.heprep` files, which can be viewed using an external program called [HepRApp][] in wireframe mode, that is, no surface, only outlines, which sounds primitive, but is one of the best ways to troubleshoot a complicated geometry.

A [sample HepRepFile macro](HepRepFile.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd tutorials/detector/visualization
$ gears HepRepFile.mac
```

It generates `G4Data0.heprep` in the same directory. A shell script [hv](hv) is shipped with [GEARS][] to run [HepRApp][]. Use it this way:

```sh
$ ./hv G4Data0.heprep
```

If this is the first time you run it, it will download a `HepRApp.jar` file from the Internet and run it the following way:

```sh
java -jar HepRApp.jar -opt HepRApp.properties -file G4Data0.heprep
```

In case of Windows, please download [HepRApp.jar](http://www.slac.stanford.edu/~perl/HepRApp/HepRApp.jar) and double click on it in a file browser to launch it instead of usimng the command above.

Unfortunately, `HepRApp.jar` can only be run on java version 1.8 (or 8 in short). To use the [HepRApp][] viewer, you may need to install two versions of java and switch to the older one if needed. This can be done, but the detailed procedure changes with the OS. In case of Windows, simply download java 8 from <https://www.java.com/en/download>. In case of modern MacOS or Linux distributions, there is no tested working procedure. A Docker image <https://hub.docker.com/r/physino/heprapp> is create to solve this problem. It can be used in the following way:

1. download and run [Docker][] Desktop
2. for Mac and Windows users: run an [X11][] server ([XQuartz][] for Mac, [MobaXterm][] for Windows)
3. for Mac and Linux users: run `xhost +` in a terminal
4. download [GEARS][], and then

```sh
cd /path/to/gears
docker-compose run heprapp
```

The [HepRApp][] window should pop up on your desktop.

[Dockerfile](Dockerfile) shows how the [Docker][] image is created. [HepRApp.def](HepRApp.def) shows how the [Apptainer][] image is created.

[HepRApp.properties](HepRApp.properties) is the configuration file for [HepRApp][]. It is also shipped with [GEARS][].

In [HepRApp][] browser, "beam view" is to look at -z direction, "top view" is to look at -y direction, and "side view" is to look at +x direction.

### TSG

[ToolsSG](https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#toolssg) is available in [Geant4][] version >= 11.1. It can be used with X11 or Qt.

A [sample ToolsSG  macro](TSG.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd tutorials/detector/visualization
$ gears
$ /control/execute TSG.mac
```

### DAWNFILE

[DAWNFILE](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#dawn) is available in any [Geant4][] installation. It can be used to generate `g4_*.prim` files, which can be converted to an EPS file using an external program called [dawn](https://geant4.kek.jp/~tanaka/DAWN/About_DAWN.html).

A [sample DAWNFILE macro](DAWN.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd tutorials/detector/visualization
$ gears DAWN.mac
```

### OpenGL

[OpenGL][] is included in most [Geant4][] installations. Detailed instructions on OpenGL related built-in commands can be found [here](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Control/AllResources/Control/UIcommands/_vis_ogl_.html)

A [sample OpenGL macro](OpenGL.mac) is shipped with [GEARS][]. Try it out this way:

```sh
$ cd /path/to/gears
$ cd tutorials/detector/visualization
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


## Visualization of particle trajectories

Most of the visualization methods can be used to visualize not only the detector geometry but also particle trajectories passing through it. This is enabled using the following command

```
/vis/scene/add/trajectories
```

> **Note**
> This may slow down your visualization program or enlarge its output file if many particles are created in a simulation.

The scene will be cleared after each event. In case of [HepRepFile](#heprepfile), ten `G4Data*.heprep` files will be created if you run `/run/beamOn 10`, each contains the scene of one event. If you want to overlap the results from multiple events in one scene, use

```
/vis/scene/add/trajectories
# accumulate trajectories from 10 events
/vis/scene/endOfEventAction accumulate 10
```

Only one `G4Data01.heprep` will be created in this case if you use [HepRepFile](#heprepfile).

More information can be saved with trajectories with the following syntax:

```
/vis/scene/add/trajectories rich
```

By default, green tracks are neutral particles, e.g. gamma-rays; red tracks are negatively charged particles, e.g. electrons; blue tracks are positively charged particles, e.g. protons. But these default settings can be changed, for example,

```
/vis/modeling/trajectories/create/drawByParticleID
/vis/modeling/trajectories/drawByParticleID-0/set e- blue
```

There are also ways to hide trajectories based on particle type:

```
/vis/filtering/trajectories/create/particleFilter
# draw only gamma-rays
/vis/filtering/trajectories/particleFilter-0/add gamma
# draw everything except for gamma-rays
/vis/filtering/trajectories/particleFileter-0/invert true
```

## Visualization of axes, date, text, etc.

You can add more objects to a scene:

```
# Add x (red), y (green), z (blue) axes in the middle of the scene
/vis/scene/add/axes
# add date to the corner of the scene
/vis/scene/add/date
# add text to the scene
/vis/scene/add/text 2 3 4 m 12 0 0 hello
```

For more information please check the [manual of /vis/scene/add/](https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Control/AllResources/Control/UIcommands/_vis_scene_add_.html).

[OpenGL]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#opengl
[UI]:../../../INSTALL/#user-interface
[RayTracer]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#raytracer
[Qt]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/GettingStarted/graphicalUserInterface.html#g4uixm-g4uiqt-and-g4uiwin32-classes
[tcsh]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/GettingStarted/graphicalUserInterface.html#g4uiterminal
[HepRepFile]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#heprepfile
[GEARS]: http://physino.xyz/gears
[Geant4]: http://geant4.cern.ch
[VRML]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Visualization/visdrivers.html#vrml
[ORBISNAP]:https://www.orbisnap.com/download2.html
[OpenVRML]:https://sourceforge.net/projects/openvrml
[FreeWRL]: http://freewrl.sourceforge.net/download.html
[view3dscene]:https://castle-engine.sourceforge.io/view3dscene.php
[X3D]:https://stackoverflow.com/questions/14849593/vrml-to-x3d-conversion
[v2x]:https://github.com/jintonic/gears/blob/master/tutorials/detector/visualization/v2x
[HepRApp]: https://www.slac.stanford.edu/~perl/HepRApp
[XQuartz]: https://www.xquartz.org
[Docker]: https://docker.com
[MobaXterm]: https://mobaxterm.mobatek.net
[X11]: https://en.wikipedia.org/wiki/X_Window_System
[Apptainer]: https://apptainer.org
[Singularity]: https://github.com/apptainer/singularity#singularity
