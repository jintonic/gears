# Windows 10

## Install pre-compiled Geant4 in Windows

Download pre-compiled Geant4 in Windows 10 from <https://geant4.web.cern.ch/support/download>. When you double click it to install it, Windows will pop a window "Windows protected your PC". Select "More info" and then "Run anyway".

![winSys](/assets/winSys.png)
![winEnv](/assets/winEnv.png)

## Compile GEARS
### Install visual studio

Download Visual Studio Community Edition installer. Run it. Choose to install a workload called "Desktop development with C++". It is about 2 GB and takes a long time to download and install. When you open VS the first time, choose "Visual C++" as your "Development Settings". And then "Clone and checkout code":

![vsstart](/assets/vsstart.png)
![vsrepos](/assets/vsrepos.png)
![vsconfig](/assets/vsconfig.png)
![vsvscmakesetting](/assets/vsvscmakesetting.png)
![vsvscmakermdebug](/assets/vsvscmakermdebug.png)
![vssavecmakejson](/assets/vssavecmakejson.png)
![vsselectgears](/assets/vsselectgears.png)
![vsrungears](/assets/vsrungears.png)
![vsdebuggears](/assets/vsdebuggears.png)

# macOS

## Install pre-compiled Geant4 in MacOS

You can download the pre-compiled Geant4 libraries for the MacOS [here](https://geant4.web.cern.ch/support/download). By default, it will be saved to `~/Downloads`.

```sh
$ cd ~/Downloads/Geant4-10.6.1-Darwin/bin
# change location of geant4 databases
$ sed -i.bak 's|/Users/gcosmo/Software/release/install|'${HOME}'/Downloads/Geant4-10.6.1-Darwin|g' geant4-config
$ ./geant4-config --install-datasets
```

By default, MacOS does not allow you to run Geant4 libraries in `~/Downloads/Geant4-10.6.1-Darwin/lib`. You have to follow the instruction [here](https://github.com/Jackett/Jackett/issues/5589) to make the exception:

```sh
$ cd ~/Downloads/Geant4-10.6.1-Darwin/lib
$ xattr -p com.apple.quarantine libG4run.dylib
0081;5e968234;Firefox;29504EDE-15EA-4CF5-A750-6B0AEB8CF5ED
# copy the output and change the first 4 letters from 0081 to 00c1:
$ xattr -w com.apple.quarantine "00c1;5e968234;Firefox;29504EDE-15EA-4CF5-A750-6B0AEB8CF5ED" libG3*.dylib
$ xattr -w com.apple.quarantine "00c1;5e968234;Firefox;29504EDE-15EA-4CF5-A750-6B0AEB8CF5ED" libG4*.dylib
```

Add the following to `~/.bash_profile`:

```sh
export G4SYSTEM=Darwin-clang
export G4INSTALL=~/Downloads/Geant4-10.6.1-Darwin
export PATH=$G4INSTALL/bin:$PATH
export DYLD_LIBRARY_PATH=$G4INSTALL/lib:$DYLD_LIBRARY_PATH
# source gears/gears.sh to export Geant4 database locations
source /path/to/gears/gears.sh
```

If you encounter problems to load some shared libraries when you run a Geant4 executable, for example, `libXmu.6.dylib`, check its location in `libG4OpenGL.dylib` using:

```sh
# print shared libraries used in a library file
$ otool -L libG4OpenGL.dylib
libG4OpenGL.dylib:
...
/opt/X11/lib/libXext.6.dylib (compatibility version 11.0.0, current version 11.0.0)
/opt/local/lib/libXmu.6.dylib (compatibility version 9.0.0, current version 9.0.0)
/opt/X11/lib/libGL.1.dylib (compatibility version 4.0.0, current version 4.0.0)
...
```

and then use the following trick to solve the problem:

```sh
# make a link in the location appeared in the library file
$ mkdir /opt/local/lib
$ cd /opt/local/lib
$ ln -sf /opt/X11/lib/libXmu.6.dylib
```

## Install pre-compiled ROOT in MacOS

Download pre-compiled ROOT for MacOS from <https://root.cern.ch/downloading-root>. If you download the `.pkg` version, simply double click on the file to install it to `/Applications/` directory and then add the following to your `~/.bash_profile`:

```sh
export ROOTSYS=/Applications/root_v6.20.04
export PATH=$ROOTSYS/bin:$PATH
export DYLD_LIBRARY_PATH=$ROOTSYS/lib:$DYLD_LIBRARY_PATH
```

