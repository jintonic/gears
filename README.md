> **Note**
> The latest [GEARS][] require [Geant4.11](https://geant4.web.cern.ch/support/download). If you are still using [Geant4.10](https://geant4.web.cern.ch/support/download_archive?page=1), please download [v1.5.1](https://github.com/jintonic/gears/releases/tag/v1.5.1) of [GEARS][] from the [Release](https://github.com/jintonic/gears/releases) page.

[![Get GEARS](https://img.shields.io/badge/Get-GEARS-orange?style=flat)](INSTALL)
[![Tutorials](https://img.shields.io/badge/Use-GEARS-blue?style=flat)](tutorials)
[![YouTube](https://img.shields.io/badge/You-Tube-red?style=flat)](https://www.youtube.com/@physino)
[![Doxygen](https://codedocs.xyz/jintonic/gears.svg)](https://codedocs.xyz/jintonic/gears/annotated.html)
[![Get Involved](https://img.shields.io/badge/Get-involved-ff69b4?style=flat)](#how-to-contribute)

<a href="http://physino.xyz/gears/tutorials/detector/visualization/gearsX3D.html"><img align="right" width="120px" src="tutorials/detector/visualization/gears.png"/></a>

[GEARS][] is a [Geant4][] [Example][] Application with [Rich features](#features) yet Small footprint. The entire C++ coding is minimized down to a single file with about 550 [SLOC][]. This is achieved mainly by utilizing [Geant4][] plain [text geometry description][tg], [built-in UI commands][TUI] (macros), and C++ inheritance. It is ideal for student training and fast implementation of small to medium-sized experiments.

[GEARS]: https://github.com/jintonic/gears
[Geant4]: http://geant4.cern.ch
[Example]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Examples/examples.html
[tg]: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomASCII.html
[TUI]: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Control/commands.html
[SLOC]: https://en.wikipedia.org/wiki/Source_lines_of_code

## Features

* [Single small C++ file](gears.cc), easy to manage, fast to [compile](INSTALL#compile-gears) (a few second on a regular PC)
* [Easy switching between well maintained Geant4 reference physics lists without recompilation](tutorials/physics)
  * [Individual processes can be turned on/off without recompilation](tutorials/physics#physics-processes)
  * [Fast implementation of optical properties without recompilation](tutorials/physics#optical-properties-of-materials-and-surfaces)
  * [Optional radioactive decay simulation](tutorials/physics#radioactive-decay) with the possibility to [save the parent and daughter decays into different events if the later happens after a user specified time interval](tutorials/physics#split-decay-chain)
* [Frequently used source spectra (AmBe, Am-241, etc.)](tutorials/sources#common-sources) in addition to [GPS](tutorials/sources)
* [Output in multiple data format](tutorials/output)
  * [ROOT](tutorials/output#root) TTree format (default, no [ROOT][] installation is needed)
    * Build-in data compression, well suitable for large data processing
    * Fast access to independent data members
    * Flat tree (no nested branches or arrays) with short leaf names
      * Easy to use in [TTree][]::[Draw][]
      * No need to load extra library to open
      * Can be easily analyzed in [Python][] through [Uproot][]
  * [HDF5][], universal data format, easy to read by different tools
  * CSV or XML, Human readable ASCII file, capable of dealing with multiple dimensional arrays
* [Record information of step 0](tutorials/output#record-information-of-step-0) (initStep), which is not available through [G4UserSteppingAction][]
* [simple text][tg] or [GDML][] geometry I/O
  * [Fast implementation of detector geometry](tutorials/detector) without C++ programming
  * Create/Change geometry without re-compilation
  * Turn off data saving in a volume by assigning it a non-positive copy number
  * Turn any volume to a [sensitive detector](tutorials/detector#sensitive-volume) by adding "(S)" in its name
  * [Assign optical properties in Geant4 plain text geometry description](tutorials/detector/optical), which is not available in the official [Geant4][] release
  * [Syntax highlighting of the simple text geometry description files](tutorials/detector/syntax) in [Emacs](tutorials/detector/syntax#emacs), [Vim](tutorials/detector/syntax#vim), [Micro](tutorials/detector/syntax#micro), and [Sublime Text](tutorials/detector/syntax#sublime-text)
* [Creating 3D mesh to record and visualize physical variables in it without any change of the C++ code](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Detector/commandScore.html)
* [Doxygen documentation](https://codedocs.xyz/jintonic/gears/)
* Many simple [tutorials](tutorials) to demonstrate the usage of [Geant4][]

[ROOT]: https://root.cern.ch
[GPS]: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/GettingStarted/generalParticleSource.html
[TTree]: https://root.cern/manual/trees
[Draw]: https://root.cern.ch/doc/master/classTTree.html#a73450649dc6e54b5b94516c468523e45
[Python]: https://www.python.org/
[Uproot]: https://pypi.org/project/uproot
[G4UserSteppingAction]:http://www-geant4.kek.jp/lxr/source/tracking/include/G4UserSteppingAction.hh
[GDML]: https://gdml.web.cern.ch/GDML/
[HDF5]: https://www.hdfgroup.org/downloads/hdf5/

## How to contribute

Please [fork GEARS on GitHub](https://help.github.com/en/github/getting-started-with-github/fork-a-repo). Run the following to get a local copy of the forked repository and link it to the [original GEARS repository][GEARS]:

```sh
$ git clone git@github.com:yourGitHubAccount/gears.git # get forked repository
$ git remote add upstream git@github.com:jintonic/gears.git # link to original repository
$ git remote -v # run a check
```

Run the following to keep your local repository updated with the [original GEARS repository][GEARS]:

```sh
$ git fetch upstream # updates are saved in a new branch upstream/master
$ git merge upstream/master # merge 2 branches: upstream/master and master
```

If the merge is successful, run `git push` to update your forked GEARS repository on GitHub.

You can initiate a [pull request on GitHub](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/about-pull-requests) if you'd like to have your update being absorbed in [the original GEARS repository][GEARS].

### Coding convention

#### G4cout VS std::cout

`G4cout` and `G4endl` is preferred over `std:cout` and `std:endl` because the former handle the output in [Geant4][] GUI correctly, while the later can only output to terminal.

#### Indentation

Two spaces instead of a tab are used to indent a line in [gears.cc](gears.cc) to insure a consistent appearance in different text editors, and to avoid wasting space in front of deeply nested code blocks. The following mode lines are added to the end of [gears.cc](gears.cc) to insure that in [Vim][] and [Emacs][]:

```cpp
// -*- C++; indent-tabs-mode:nil; tab-width:2 -*-
// vim: ft=cpp:ts=2:sts=2:sw=2:et
```

[Vim]: https://www.vim.org/
[Emacs]: https://www.gnu.org/software/emacs/

### To-do's

- tutorials
  - add tutorials to show how one can distribute source in a volume or surface
