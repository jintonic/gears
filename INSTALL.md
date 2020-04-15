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

## Install pre-compiled ROOT in MacOS

Download pre-compiled ROOT for MacOS from <https://root.cern.ch/downloading-root>. If you download the `.pkg` version, simply double click on the file to install it to `/Applications/` directory and then add the following to your `~/.bash_profile`:

```sh
export ROOTSYS=/Applications/root_v6.20.04
export PATH=$ROOTSYS/bin:$PATH
export DYLD_LIBRARY_PATH=$ROOTSYS/lib:$DYLD_LIBRARY_PATH
```

