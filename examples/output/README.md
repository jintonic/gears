## Output format
[GEARS][] utilizes [Geant4 analysis managers](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Analysis/managers.html) to provide 4 output formats: ROOT (default), HDF5, CSV, and XML. The output file format can be chosen using the following command:

~~~sh
$ make hdf5 # create ghdf5.cc from gears.cc
$ make # compile ghdf5.cc
~~~

The output file name can be chosen using macro command:

~~~
/analysis/setFileName output
~~~

No suffix is needed for the file name.

### ROOT

ROOT use TTree to save data. TTree have entry and branch to build their data structure. Each branch is a variable listed in [Track Points](#track-point), and each entry is a event. ROOT will compress the data, so it will cost less disk space. ROOT can load part of data, which can save time when it get large.

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

[GEARS]: http://physino.xyz/gears
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
