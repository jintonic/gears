[![Compile gears](https://img.shields.io/badge/Compile-GEARS-yellow?style=flat)](#compile-gears)
[![Install gears](https://img.shields.io/badge/Install-GEARS-brown?style=flat)](#install-gears)
[![Install Geant4](https://img.shields.io/badge/Install-Geant4-magenta?style=flat)](Geant4)
[![Install ROOT](https://img.shields.io/badge/Install-ROOT-pink?style=flat)](ROOT)
[![Docker image](https://img.shields.io/badge/Docker-image-green?style=flat)](Docker)
[![Apptainer image](https://img.shields.io/badge/Apptainer-image-blue?style=flat)](Apptainer)

[GEARS][] can run in three major operating systems: [Windows](#compile-gears-in-windows), [macOS](#compile-gears-in-macos), and [Linux](#compile-gears-in-linux). It depends on [Geant4][]. If you don't have [Geant4][] installed yet in your system, please [install Geant4](Geant4) first. However, if you have [Docker][] installed on Windows, MacOS, Linux, or [Apptainer][]/[Singularity][] installed on Linux, you can run [GEARS][] in a [container][] where [Geant4][] has been installed, which can save you a lot of hassle. Please check the [Docker/](Docker) and [Apptainer/](Apptainer) folders for detailed instruction if you are interested in using containerized [GEARS][].

[GEARS]: https://github.com/jintonic/gears
[Geant4]: http://geant4.cern.ch
[Docker]: https://www.docker.com
[Singularity]: https://en.wikipedia.org/wiki/Singularity_(software)
[Apptainer]: https://apptainer.org
[container]: https://www.docker.com/resources/what-container

## Get GEARS
### Get GEARS in Windows
[GEARS][] can be downloaded as a `.zip` file from its [homepage](http://physino.xyz/gears) or [GitHub](https://github.com/jintonic/gears). Unpack it and that's it, you've got [GEARS][].

If you know how to use [Git][], you can download the whole [GEARS repository from GitHub][GEARS] using either [GitHub Desktop](https://desktop.github.com/) or [Visual Studio][]. If you use [Visual Studio][], read [Compile GEARS with Visual Studio](VisualStudio) for detailed instruction.

[Visual Studio]: https://visualstudio.microsoft.com

### Get GEARS in macOS or Linux
[GEARS][] can be downloaded as a `.tar.gz` or `.zip` file from its [homepage](http://physino.xyz/gears) or [GitHub](https://github.com/jintonic/gears). Run the following commands in your terminal to unzip it:

```sh
$ unzip gears-master.zip # if you downloaded the zip file
$ tar xfvz jintonic-gears-commitID.tar.gz # if you download the tar.gz file
$ mv jintonic-gears-commitID gears # rename the directory
```

If you know how to use [Git][], you can download the whole [GEARS repository from GitHub][GEARS]:

```sh
$ git clone https://github.com/jintonic/gears
```

This way, you can update your local copy from time to time using

```sh
$ cd /path/to/gears
$ git pull
```

Note that if you change some files in your local working copy, the `git pull` command will fail since [Git][] does not want to overwrite your local modification with the updated [GEARS][]. To avoid this, please copy [example macros](tutorials) to somewhere outside of the `gears/` directory. You can then modify them as you like without worry. An easy way to check if there is any local change that may block `git pull` is:

```sh
$ git status # show modified files
$ git diff a/changed/local/file # show what are changed
$ git checkout -- a/changed/local/file # discard the local change
$ git pull # get latest gears
```
[Git]: https://en.wikipedia.org/wiki/Git

## Compile GEARS

Two compilation systems are provide for [GEARS][]. One is [CMake][]. This mechanism is provided to insure that [GEARS][] can be compiled across platforms. You can find a [CMakeLists.txt](../CMakeLists.txt) file in the [GEARS][] folder, which can be detected automatically by [CMake][] in all platforms or [Visual Studio][] in Windows. The other method is to directly use a [Makefile](../Makefile) shipped with [GEARS][], which simplifies the compilation in Linux and macOS significantly.

[CMake]: https://cmake.org/

### Compile GEARS in Windows

Please download [Visual Studio][] Community Edition installer. Run it. Choose to install a workload called "Desktop development with C++". It is about 2 GB and takes a long time to download and install. When you open VS the first time, choose "Visual C++" as your "Development Settings".

The compilation of GEARS can be done [solely with Visual Studio](VisualStudio). However, the process would become much easier if we [use CMake before using Visual Studio](CMake).

### Compile GEARS in Linux
[GEARS][] is shipped with a simple [Makefile](../Makefile). Simply type `make` to compile [gears.cc](../gears.cc) to generate a tiny executable `gears` in the GEARS directory:

```sh
$ cd /path/to/gears
$ make # compile gears.cc to generate executable: gears
```

### Compile GEARS in macOS

You need to have the [commandline tools for developers](https://osxdaily.com/2014/02/12/install-command-line-tools-mac-os-x/) installed before you can compile [GEARS][] in macOS. The command to install that is:

```sh
$ xcode-select --install
```

After this, the procedure is the same as [that in Linux](#compile-gears-in-linux).

## Install GEARS

### Install GEARS in Windows

If you compiled [GEARS][] using [CMake][] and then [Visual Studio][], you don't have to do anything extra, `gears.exe` has been installed automatically for you. If you only used [Visual Studio][] to compile [GEARS][], please follow the instruction [here](VisualStudio). 

### Install GEARS in macOS or Linux

After the compilation, the following message will be shown in your terminal:

```sh
$ cd /path/to/gears
$ make # compile gears.cc to generate executable: gears
 --------------------------------------------------------
 To install, please add the following line
    source /path/to/gears/gears.sh
 to ~/.bashrc in Linux or ~/.bash_profile in a Mac
 (or ~/.zshrc if you use zsh instead of bash)
 --------------------------------------------------------
```

Follow this instruction, open a new terminal when you are done, and you should be able to use the `gears` command in a new terminal now.

For Mac users, you need to use `~/.bash_profile` instead of `~/.bashrc`. Please check [this article](https://scriptingosx.com/2017/04/about-bash_profile-and-bashrc-on-macos/) for explanation. Alternatively, you can add `source ~/.bashrc` in your `~/.bash_profile` and still add `source /path/to/gears/gears.sh` to `~/.bashrc`.

If you use `zsh` instead of `bash`, use `~/.zshrc` instead of `~/.bashrc` or `~/.bash_profile`.

[GDML]: https://gdml.web.cern.ch/GDML/
[HDF5]: https://www.hdfgroup.org/downloads/hdf5/

