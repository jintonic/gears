# gears - geant4 related simulation

It makes full use of Geant4 [plain-text geometry definition](http://geant4.web.cern.ch/geant4/collaboration/working_groups/geometry/docs/textgeom/textgeom.pdf) and [build-in macros](https://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/ForApplicationDeveloper/html/AllResources/Control/UIcommands/_.html) to reduce C++ coding and to enable fast implementation and debugging of new experiments.

# Get started

~~~shell
cd gears
make
./macro/Rutherford/scatter.sh 100
~~~
