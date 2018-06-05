[GEARS][] is a [Geant4][] Example Application with Rich features yet Small footprint. The entire C++ coding is minimized down to a single file with about 600 [SLOC][]. This is achieved mainly by utilizing [Geant4][] plain [text geometry description][tg], [build-in UI commands][TUI] (macros), and C++ inheritance. It is ideal for student training and fast implementation of small to medium-sized experiments.

# Features

* Single small C++ file
  * Easy code browsing
  * Easy management and compiling
* Fast compilation
  * a few second on a regular PC
* [Output in JSON data format](#json) (default)
  * Universal data format, easy to read by different tools
  * Human readable ASCII file
  * Capable of dealing with multiple dimensional arrays
* [Output](#output) in [ROOT](#root) TTree format (optional)
  * Build-in data compression, well suitable for large data processing
  * Fast access to independent data members
  * Flat tree (no nested branches or arrays)
    * Easy to use in TTree::Draw
    * No need to load extra library to open
* [Record information of step 0](#record-information-of-step-0) (initStep)
  * This is not available from G4UserSteppingAction
* Create/Change geometry without re-compilation
* Turn any volume to a sensitive detector by adding "(S)" in its name
* Assign optical properties in [Geant4][] plain [text geometry description][tg]
* Optional optical and hadronic physics
* Periodic status report in a long run
* Frequently used source spectra (AmBe, Am-241, etc.)
* [Doxygen documentation](http://www.physino.xyz/gears/)

# Prerequisites

* [ROOT][] for recording simulation results
* [Geant4][], version above 9 is requested due to the following inconvenience in version 9: http://hypernews.slac.stanford.edu/HyperNews/geant4/get/hadronprocess/1242.html?inline=-1

# Get started

~~~shell
git clone https://github.com/jintonic/gears.git
cd gears
make
cd macro/Rutherford/
./scatter.sh 100
~~~

# Detector

## Geometry
[Geant4][] provides a simple way to describe the geometry of a detector in a plain text file. For example, the following line in such a file defines an experimental hall filled with air, the dimension of which is 20 x 20 x 30 meters:

~~~
:volume hall BOX 10*m 10*m 10*m G4_AIR
~~~

More examples can be found in the [geom/](geom/) directory, such as [geom/hall.tg](geom/hall.tg). Files in this directory have a suffix of *.tg*, indicating that they are [text geometry][tg] description files. A [Geant4][] macro command is added to load [one of the geometry files](geom/Rutherford/foil.tg):

~~~
/geometry/source geom/Rutherford/foil.tg
~~~

The command must be used before [/run/initialize][run], otherwise [Geant4][] does not have a detector to initialize.

## Material

The [NIST][] material table provided by Geant4 contains a lot of commonly used materials. One can run /material/nist/[listMaterials][] at any Geant4 state to print the list locally. These materials can be used directly in a [text geometry description][tg], for example

~~~
// use NIST material G4_AIR to define vacuum
:mixt vacuum 1e-9 1 G4_AIR 1
~~~

## Optical properties of a material or a surface

There is no tag to define the optical properties of a material or a surface in the default [Geant4][] [text geometry description][tg]. The following two tags are added in [GEARS][] to enable definition of optical materials and surfaces using [Geant4][] [text geometry description][tg] syntax:

### Define optical properties of a material

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

### Define optical properties of a surface

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

## Sensitive detector

Sensitive detectors are specified by simply add "(S)" at the end of their volume names. The copy numbers of their volumes must be continuous integers starting from 0.

# Physics

## Physics list

Since it requires a lot of knowledge to set up a correct physics list, [Geant4][] provides some pre-packaged physics lists. Three are enabled by default in [GEARS][]:

- G4DecayPhysics, it defines particle decays. It defines more particles than G4EmStandardPhysics does, so it has to be enabled before optional hadronic physics, otherwise the later will complain about missing particle definitions.
- G4RadioactiveDecayPhysics, it defines nuclear decays.
- G4EmStandardPhysics, it has to be defined after G4RadioactiveDecayPhysics, otherwise nuclei cannot get their energy state information and won't decay. No [Geant4][] documentation warns it.

Three optional lists (G4OpticalPhysics, G4HadronElasticPhysicsHP, G4HadronPhysicsFTFP_BERT_HP) can be enabled using [Geant4][] macros:

~~~
  # has to be called before /run/initialize
  /physics_lists/enable Optical
  /physics_lists/enable HadronElastic
  /physics_lists/enable HadronInelastic
~~~

### Physics processes

Run `/process/list` after `/run/initialize`, and you will get

~~~
     Transportation,              Decay,   RadioactiveDecay,                msc
              hIoni,            ionIoni,             hBrems,          hPairProd
        CoulombScat,              eIoni,              eBrem,            annihil
               phot,              compt,               conv,             muIoni
            muBrems,         muPairProd,         hadElastic,   neutronInelastic
           nCapture,           nFission,    protonInelastic,       pi+Inelastic
       pi-Inelastic,     kaon+Inelastic,     kaon-Inelastic,    kaon0LInelastic
    kaon0SInelastic,    lambdaInelastic,anti-lambdaInelastic,   sigma-Inelastic
anti_sigma-Inelastic,    sigma+Inelastic,anti_sigma+Inelastic,     xi-Inelastic
  anti_xi-Inelastic,       xi0Inelastic,  anti_xi0Inelastic,    omega-Inelastic
anti_omega-Inelastic,anti_protonInelastic,anti_neutronInelastic,anti_deuteronInelastic
anti_tritonInelastic,  anti_He3Inelastic,anti_alphaInelastic
~~~

Now you can use, for example, `/process/inactivate nCapture` to disable neutron capture process in your simulation. And you can use, for example, `/process/setVerbose 20 RadioactiveDecay` to change the verbosity of the radioactive decay process.

Individual optical processes can be toggled by the following commands:

~~~
/process/optical/processActivation Cerenkov true/false
/process/optical/processActivation Scintillation true/false
/process/optical/processActivation OpAbsorption true/false
/process/optical/processActivation OpRayleigh true/false
/process/optical/processActivation OpMieHG true/false
/process/optical/processActivation OpBoundary true/false
/process/optical/processActivation OpWLS true/false
~~~

Detailed control of radioactive decay is provided by the /[grdm]/ command, for example,

~~~
/grdm/deselectVolume chamber # disabled radioactive decay in volume "chamber"
/grdm/nucleusLimits 1 80 # enabled radioactive decay only when z in [1, 80]
~~~

# Output

## Track point

A track point is a concept introduced in [GEARS][]. It is a point where a track is generated or changed. It records the following information:

* Track id (`trk` in short)
* Step number, starting from 0  (`stp` in short)
* Detector volume copy number (`det` in short)
* [Process id](#process-id) (`pro` in short)
* [Particle id](#particle-id) (`pid` in short)
* Parent id (`mom` in short)
* Energy deposited [keV] (`e` in short)
* Kinetic energy of the track [keV] (`k` in short)
* global time [ns] (`t` in short)
* x [mm]
* y [mm]
* z [mm]

## Process id

The physics process generating each track point is saved in a variable `pro[n]`, where `n` is the index of the track point. It equals to (process type) * 1000 + (sub type). The Process types are defined in G4ProcessType.hh, sub types are defined in G4HadronicProcessType.hh, G4DecayProcessType.hh, G4EmProcessSubType.hh,  G4TransportationProcessType.hh, G4FastSimulationProcessType.hh, G4OpProcessSubType.hh, etc. They can be found at http://www-geant4.kek.jp/lxr/find?string=Type.hh

## Particle id

The type of particle related to a track point is saved in a variable `pdg[n]`. It is the same as the `PDG encoding` of the particle. A Google search will give more information about it.

## Record information of step 0

One cannot get access to step 0 (initStep printed on screen if `/tracking/verbose` is set to be more than 0) through [G4UserSteppingAction][], which only provides access to step 1 and afterwards. However, step 0 contains some very important information that is constantly requested by the user. For example, the energy of a gamma ray from a radioactive decay is only available from step 0. Such information can be easily displayed using the following ROOT command with the Output ROOT tree, `t`:

~~~cpp
  // draw kinetic energy, "k", of a gamma (pdg==22)
  // created by radioactive decay process (pro==6210)
  t->Draw("k","pro==6210 && pdg==22")
~~~

This is achieved by using [G4SteppingVerbose][] instead of [G4UserSteppingAction][] for data recording. The former provides a function called [TrackingStarted][]() to print verbose information about step 0 on screen if `/tracking/verbose` is set to be more than 0. It also provides a function called [StepInfo][]() to print verbose information about steps after step 0 on screen if `/tracking/verbose` is more than 0. [G4SteppingVerbose][]::[StepInfo][]() is called right before [G4UserSteppingAction][]::[UserSteppingAction][]([G4Step][]*) is called in [G4SteppingManager][]::[Stepping][](), it hence can be used to fully replace the functionality of [G4UserSteppingAction][]::[UserSteppingAction][]([G4Step][]*).

In fact, [G4UserSteppingAction][]::[UserSteppingAction][]([G4Step][]*) is not used at all in [GEARS][]. The Output class inherits [TrackingStarted][]() and [StepInfo][]() from [G4SteppingVerbose][] to record data from all steps. There is another advantage of using [G4SteppingVerbose][] instead of [G4UserSteppingAction][] for recording, that is, [G4SteppingVerbose][] is provided as a globally available singleton, which can be easily accessed at different places in the codes using:

~~~cpp
  G4VSteppingVerbose::GetInstance()
~~~

This is used in [G4UserRunAction][] to open and close a TFile, in [G4UserEventAction][] to fill a TTree.

The catch is that functions in [G4SteppingVerbose][] will not be called in [G4SteppingManager][] unless `/tracking/verbose` is set, which will print too much information on screen for a long run. This is solved in EventAction::BeginOfEventAction by turning on tracking verbose all the time so that all functions in [G4SteppingVerbose][] will be called, while at the same time, turning on [G4SteppingVerbose][] local verbose flag [Silent][] to run them in silent mode.

## Output format
Gears provides two output formats: JSON and ROOT. The output file name and format can be chosen using macro command:

~~~
/run/output file.json (or file.root)
~~~

The format is determined by the surfix of the output file name.

### JSON 
Since the amount of data which gears might generate can be huge, we suggest install the [ROOT](#root) library and use .root format to store data to increase the preforance of data processing. If users do not want to use .root format, JSON format is avilable as default.
 
All events are store as a JSON object array. Each event is an object and contains all information listed in [Track Point](#track-point), for example:

~~~
[
{
   "n":2,
   "trk":[1,1],
   "stp":[0,1],
   "det":[0,0],
   "pro":[-1,1091],
   "pdg":[22,22],
   "mom":[0,0],
   "e":[0,0],
   "k":[4438.84,4438.84],
   "t":[0,0.258763],
   "x":[-1.99299,65.9771],
   "y":[-8.12482,-45.244],
   "z":[-225,-229.486] 
},
{
   "n":3,
   "trk":[1,1,2],
   "stp":[0,1,3],
   "det":[0,0,2],
   "pro":[-1,1091,2000],
   "pdg":[22,22,22],
   "mom":[0,0,0],
   "e":[0,0,0],
   "k":[4438.84,4438.84,4438.84],
   "t":[0,0.258763,1],
   "x":[-1.99299,65.9771,23],
   "y":[-8.12482,-45.244,-70],
   "z":[-225,-229.486,-233] 
}
]
~~~

where things inside of a pair of {} is the information of an event, "n" is the number of [Track Points](#track-point) in each event.

### ROOT

ROOT use TTree to save data. TTree have entry and branch to build their data structure. Each branch is a variable listed in [Track Points](#track-point), and each entry is a event. ROOT will compress the data, so it will cost less disk space. ROOT can load part of data, which can save time when it get large.

# Coding convention

## G4cout VS std::cout

`G4cout` and `G4endl` is preferred over `std:cout` and `std:endl` because the former handle the output in [Geant4][] GUI correctly, while the later can only output to terminal.

[GEARS]: https://github.com/jintonic/gears
[tg]: http://geant4.web.cern.ch/geant4/collaboration/working_groups/geometry/docs/textgeom/textgeom.pdf
[TUI]: http://geant4.cern.ch/G4UsersDocuments/UsersGuides/ForApplicationDeveloper/html/Control/UIcommands/_.html
[SLOC]: https://en.wikipedia.org/wiki/Source_lines_of_code
[ROOT]: https://root.cern.ch
[Geant4]: http://geant4.cern.ch
[NIST]: http://geant4.web.cern.ch/geant4/workAreaUserDocKA/Backup/Docbook_UsersGuides_beta/ForApplicationDeveloper/html/apas08.html
[run]: http://geant4.cern.ch/G4UsersDocuments/UsersGuides/ForApplicationDeveloper/html/Control/UIcommands/_run_.html
[listMaterials]: https://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/ForApplicationDeveloper/html/AllResources/Control/UIcommands/_material_nist_.html
[G4OpBoundaryProcess]: http://www-geant4.kek.jp/lxr/source//processes/optical/include/G4OpBoundaryProcess.hh
[G4LogicalBorderSurface]: http://www-geant4.kek.jp/lxr/source/geometry/volumes/include/G4LogicalBorderSurface.hh
[grdm]:http://geant4.cern.ch/UserDocumentation/UsersGuides/ForApplicationDeveloper/html/AllResources/Control/UIcommands/_grdm_.html
[G4Track]: http://www-geant4.kek.jp/lxr/source/track/include/G4Track.hh
[G4Step]: http://www-geant4.kek.jp/lxr/source/track/include/G4Step.hh
[G4UserSteppingAction]:http://www-geant4.kek.jp/lxr/source/tracking/include/G4UserSteppingAction.hh
[UserSteppingAction]:http://www-geant4.kek.jp/lxr/source/tracking/include/G4UserSteppingAction.hh
[G4SteppingVerbose]: http://www-geant4.kek.jp/lxr/source/tracking/include/G4SteppingVerbose.hh
[G4SteppingManager]: http://www-geant4.kek.jp/lxr/source/tracking/include/G4SteppingManager.hh
[G4UserRunAction]: http://www-geant4.kek.jp/lxr/source/run/include/G4UserRunAction.hh
[G4UserEventAction]: http://www-geant4.kek.jp/lxr/source/event/include/G4UserEventAction.hh
[Silent]: http://www-geant4.kek.jp/lxr/source/tracking/src/G4VSteppingVerbose.cc#L50
[Stepping]: http://www-geant4.kek.jp/lxr/source/tracking/src/G4SteppingManager.cc#L116
[StepInfo]: http://www-geant4.kek.jp/lxr/source/tracking/src/G4SteppingManager.cc#L228
[TrackingStarted]: http://www-geant4.kek.jp/lxr/source/tracking/src/G4SteppingManager.cc#L360
