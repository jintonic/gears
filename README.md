[![Doxygen](https://codedocs.xyz/jintonic/gears.svg)](https://codedocs.xyz/jintonic/gears/annotated.html)
[![License:MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Examples](https://img.shields.io/badge/gears-examples-blue?style=flat)](examples)
[![Get Started](https://img.shields.io/badge/get-started-orange?style=flat)](#getting-started)
[![Get Involved](https://img.shields.io/badge/get-involved-ff69b4?style=flat)](#how-to-contribute)

<a href="examples/detector/visualization/gearsX3D.html"><img style="float:right;width:120px;" src="examples/detector/visualization/gears.png"/></a>

[GEARS][] is a [Geant4][] [Example][] Application with [Rich features](#features) yet Small footprint. The entire C++ coding is minimized down to a single file with about 600 [SLOC][]. This is achieved mainly by utilizing [Geant4][] plain [text geometry description][tg], [built-in UI commands][TUI] (macros), and C++ inheritance. It is ideal for student training and fast implementation of small to medium-sized experiments.

[GEARS]: https://github.com/jintonic/gears
[Geant4]: http://geant4.cern.ch
[Example]:{{site.g4doc}}/Examples/examples.html
[tg]: {{site.g4doc}}/Detector/Geometry/geomASCII.html
[TUI]: {{site.g4doc}}/Control/commands.html
[SLOC]: https://en.wikipedia.org/wiki/Source_lines_of_code

## Features

* [Single small C++ file]({{site.file}}/gears.cc), easy to manage, fast to [compile](#compilation)(a few second on a regular PC)
* [Output in multiple data format](examples/output)
  * [ROOT](examples/output#root) TTree format (default, no [ROOT][] installation is needed)
    * Build-in data compression, well suitable for large data processing
    * Fast access to independent data members
    * Flat tree (no nested branches or arrays) with short leaf names
      * Easy to use in TTree::Draw
      * No need to load extra library to open
  * [HDF5][], universal data format, easy to read by different tools
  * CSV or XML, Human readable ASCII file, capable of dealing with multiple dimensional arrays
* [Record information of step 0](examples/output#record-information-of-step-0) (initStep)
  * This is not available from [G4UserSteppingAction][]
* [simple text][tg] or [GDML][] geometry I/O
  * Fast implementation of [detector geometry](examples/detector) without C++ programming
  * Create/Change geometry without re-compilation
  * Turn off data saving in a volume by assigning it a non-positive copy number
  * Turn any volume to a [sensitive detector](examples/detector#sensitive-detector) by adding "(S)" in its name
  * Assign optical properties in [Geant4][] plain [text geometry description][tg]
* Optional optical and hadronic [physics](examples/physics)
* Frequently used source spectra (AmBe, Am-241, etc.) in addition to [GPS][]
* [Doxygen documentation](https://codedocs.xyz/jintonic/gears/)
* Many [sample macros](examples) and [geometry descriptions](examples/detector) for feature demonstration

[ROOT]: https://root.cern.ch
[GPS]:{{site.g4doc}}/GettingStarted/generalParticleSource.html

## Getting started

### Prerequisites

* [Geant4][], version above 9 is requested due to the following inconvenience in version 9: <http://hypernews.slac.stanford.edu/HyperNews/geant4/get/hadronprocess/1242.html>.
* (Optional) [Xerces-C++](https://xerces.apache.org/xerces-c/), to use or export detector geometries in [GDML][] format.
* (Optional) [HDF5][], to save simulation results in [HDF5][] format.

### Get GEARS

You can download [GEARS][] as a `.tar.gz` or `.zip` file from its [homepage](http://physino.xyz/gears) or [GitHub page](https://github.com/jintonic/gears), and run the following to unzip it:

```sh
$ unzip gears-master.zip # if you downloaded the zip file
$ tar xfvz jintonic-gears-commitID.tar.gz # if you download the tar.gz file
$ mv jintonic-gears-commitID gears # rename the directory
```

If you know how to use [Git][], you can download the whole [GEARS repository from GitHub][GEARS]:

```sh
$ git clone https://github.com/jintonic/gears.git
```

This way, you can update your local copy from time to time using

```sh
$ cd /path/to/gears
$ git pull
```

Note that if you change some files in your local copy, the `git pull` command will fail since [Git][] does not want to overwrite your local modification with the updated [GEARS][]. To avoid this, please copy [example macros](examples) to somewhere outside of the `gears/` directory. You can then modify them as you like without worry.

### Compilation

[GEARS][] is shipped with a simple [makefile]({{site.file}}/makefile). Simply type `make` to compile [gears.cc]({{site.file}}/gears.cc) to generate a tiny executable `gears`:

```sh
$ cd /path/to/gears
$ make # compile gears.cc
$ export PATH=/path/to/gears:$PATH # so that you can use gears everywhere
$ export LD_LIBRARY_PATH=/path/to/geant4/libs:$LD_LIBRARY_PATH # for Linux
$ export DYLD_LIBRARY_PATH=/path/to/geant4/libs:$DYLD_LIBRARY_PATH # for MAC
$ gears # run gears
```

### User interface

[GEARS][] relies on [G4UIExecutive]({{site.g4doc}}/GettingStarted/graphicalUserInterface.html#how-to-select-interface-in-your-applications) to select a user interface (UI). Without any specific setup, [GEARS][] will try to run a graphic user interface (GUI) based on [Qt][]. If your [Geant4][] is not compiled with [Qt][] support, [GEARS][] will try to [use a command-line UI that behaves like a tcsh]({{site.g4doc}}/GettingStarted/graphicalUserInterface.html#g4uiterminal). Run the following command to check if your [Geant4][] is compiled with [Qt][]

```sh
$ geant4-config --help | grep qt
```

If the output is `qt[yes]`, then you should be able to use the [Qt][] based GUI. If you can't, please check if you set the environment variable `G4UI_USE_TCSH` somewhere:

```sh
$ env |grep G4UI
```

If yes, run `export G4UI_USE_QT=1` to overwrite the `G4UI_USE_TCSH` setting, and run `gears` again. It is optional to delete the latter, because if both variables are set, the latter will be ignored.

Now, if you want to go back to the command-line UI, you need to `unset G4UI_USE_QT` and keep the `G4UI_USE_TCSH` setting unchanged. `export G4UI_USE_QT=0` or `export G4UI_USE_QT=false` does not do what you intend to do. In fact, you can set `G4UI_USE_QT` to any value. It will take effect as long as it is not empty. The only way to completely get rid of it is to `unset` it.

If none of the environment variables is set, you can use `~/.g4session` to select your UI:

```sh
qt # the first line is for all Geant4 applications
gears tcsh # just for gears
```

### Session mode

Without any argument, `gears` will start an [interactive session]({{site.g4doc}}/GettingStarted/graphicalUserInterface.html). It accepts [commands]({{site.g4doc}}/Control/commands.html) you type in the UI.

You can also put a set of commands into a [macro](examples) file, which can be used as an argument of `gears`. For example,

```sh
$ cd gears/examples/detector/visualization
$ gears RayTracer.mac # run gears in batch mode
```

This way, `gears` will run in the batch mode. It executes commands in the macro file one by one, and quit once it finishes.

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

Two spaces instead of a tab are used to indent a line in [gears.cc]({{site.file}}/gears.cc) to insure a consistent appearance in different text editors, and to avoid wasting space in font of deeply nested code blocks. The following mode lines are added to the end of [gears.cc]({{site.file}}/gears.cc) to insure that in [Vim][] and [Emacs][]:

```cpp
// -*- C++; indent-tabs-mode:nil; tab-width:2 -*-
// vim: ft=cpp:ts=2:sts=2:sw=2:et
```

[Vim]: https://www.vim.org/
[Emacs]: https://www.gnu.org/software/emacs/

### To-do's

- examples
  - add an example to show how QE can be implemented
  - add an example to show how one can use uproot to load ROOT file
  - add examples to show how one can distribute source in a volume or surface
- new functions
  - time chopping of radioactive decay chain

[G4UserSteppingAction]:http://www-geant4.kek.jp/lxr/source/tracking/include/G4UserSteppingAction.hh
[GDML]: https://gdml.web.cern.ch/GDML/
[HDF5]: https://www.hdfgroup.org/downloads/hdf5/
[Qt]: https://doc.qt.io/
[Git]: https://en.wikipedia.org/wiki/Git
