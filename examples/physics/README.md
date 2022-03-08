[![home](https://img.shields.io/badge/gears-home-magenta?style=flat)](../..)
[![examples](https://img.shields.io/badge/gears-examples-green?style=flat)](..)
[![alpha](https://img.shields.io/badge/alpha-interactions-blue?style=flat)](alpha)
[![beta](https://img.shields.io/badge/beta-interactions-yellow?style=flat)](beta)
[![gamma](https://img.shields.io/badge/gamma-interactions-cyan?style=flat)](gamma)
[![neutron](https://img.shields.io/badge/neutron-interactions-brown?style=flat)](neutron)
[![optical](https://img.shields.io/badge/optical-photons-red?style=flat)](#optical-processes)
[![decay](https://img.shields.io/badge/radioactive-decay-orange?style=flat)](#radioactive-decay)
[![X-ray](https://img.shields.io/badge/X--ray-creation-green?style=flat)](X-ray)

## Terminology

1. [physics model][physics list]: what happens in a certain energy range
2. [physics process][physics list]: model + cross section (how often it happens)
3. [physics list][]: a list of processes for common particles
4. [modular lists][]: lists of processes that can be used as building blocks to construct a more complex list
5. [pre-packaged lists][]: official [modular lists][] shipped with [Geant4][]
6. [reference lists][]: a subset of the [pre-packaged lists][] that are well-maintained and tested
7. [factory][]: a [Geant4][] class that can be used to call [pre-packaged lists][] by their names

[physics list]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/UserActions/mandatoryActions.html#physics-lists
[modular lists]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/UserActions/mandatoryActions.html#building-physics-list-from-physics-builders
[pre-packaged lists]:https://gitlab.cern.ch/geant4/geant4/tree/master/source/physics_lists/lists/include
[reference lists]: https://geant4.web.cern.ch/node/155
[factory]:https://geant4.kek.jp/lxr/source/physics_lists/lists/src/G4PhysListFactory.cc#L79

[Geant4]: http://geant4.cern.ch

## How to choose a physics list

[GEARS][] uses [G4PhysListFactory.cc][factory] to allow the user to select one from the [pre-packaged lists][] by its name:

```sh
  # select a pre-packaged physics list. For example,
  # LBE: low background experiment
  # LIV: EM model based on Livermore data
  /physics_lists/select LBE_LIV
  # initialize physics based on the list
  /run/initialize
  # dump the lists on screen
  /run/beamOn
```

The available names are listed in [G4PhysListFactory.cc][factory]. The naming scheme is introduced on page 24 in this [tutorial][]. A guidance on how to choose a proper physics list is also available in the [tutorial][].

[GEARS]: http://physino.xyz/gears
[tutorial]:https://www.slac.stanford.edu/xorg/geant4/SLACTutorial14/Physics1.pdf

## Physics processes

[Major categories of processes](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/TrackingAndPhysics/physicsProcess.html) provided in [Geant4][] include:

- Electromagnitism (EM)
  - Standard processes (~1 keV to ~PeV)
  - Low energy processes (250 eV to ~PeV)
  - [Optical photon tracking](#optical-processes)
- Weak interaction
  - decay of subatomic particles
  - [radioactive decay of nuclei](radioactive-decay)
- Hadronic physics
  - pure strong interaction (0 to ~TeV)
  - electro- and gamma-nuclear (10 MeV to ~TeV)
- Parameterized physics (not from first principles) for fast simulation
- Transportation (change from one volume to another)

A unique [process id](../output#process-id) is assigned to each process in a [GEARS][] [output](../output#process-id).

Run `/process/list` after `/run/initialize`, you will get something like this:

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

### Radioactive decay
Radioactive decay processes can be enabled after a reference list is chosen:

```sh
 # choose a reference physics list
 /physics_lists/select QGSP_BERT_EMV
 # cmd below becomes available only when the cmd above is used
 /physics_lists/factory/addRadioactiveDecay
 # must be run after the cmds above
 /run/initialize

 /process/list Decay
   Decay    RadioactiveDecay
```

Detailed control of radioactive decay is provided by the /[grdm][]/ command, for example,

~~~sh
/grdm/deselectVolume chamber # disabled radioactive decay in volume "chamber"
/grdm/nucleusLimits 1 80 # enabled radioactive decay only when z in [1, 80]
~~~

[grdm]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Control/AllResources/Control/UIcommands/_grdm_.html

Here is an example to create [Pb210][] on the surface of a cylindrical CsI detector:

```sh
 /gps/particle ion
 /gps/ion 82 210
 # default energy is 1 MeV, must be set to zero to let it decay at rest
 /gps/energy 0

 /gps/pos/type Surface
 /gps/pos/shape Cylinder
 /gps/radius 7 cm
 /gps/halfz 2.5 cm
```

[Pb210]:https://storage.googleapis.com/groundai-web-prod/media%2Fusers%2Fuser_92756%2Fproject_309275%2Fimages%2F210Pbdecaychain.png

#### Split decay chain
Some [isotope][]s in a radioactive [decay chain][] have long [half live][]s. They decay long after the first decay on top of the chain. However, [Geant4][] simulate the whole chain in one event. It is the user's task to split different decays in the chain to different events based on the times when they happen.

[isotope]:https://en.wikipedia.org/wiki/Isotope
[decay chain]:https://en.wikipedia.org/wiki/Decay_chain
[half live]: https://en.wikipedia.org/wiki/Half-life

[GEARS][] provides a macro command `/grdm/setTimeWindow` for you to split the chain based on a time window specified by you:

```sh
 # choose a reference physics list
 /physics_lists/select QGSP_BERT_EMV
 # cmd below becomes available only when the cmd above is used
 /physics_lists/factory/addRadioactiveDecay
 # must be run after the commands above
 /run/initialize

 # If a decay that happens 1 second after its previous one,
 # it is saved to another event in the output n-tuple
 # The command can be run before or after /run/initialize,
 # but only becomes available after radioactive decay is enabled
 /grdm/setTimeWindow 1 s

 # a time window <= 0 will disable splitting:
 # /grdm/setTimeWindow 0
 # show detailed instruction of this command:
 help /grdm/setTimeWindow

 # turn on tracking and event verbose
 # to understand Geant4 tracking and stacking processes
 /tracking/verbose 2
 /event/verbose 2
 # record output to check the splitting result
 /analysis/setFileName output
 # simulate just one or a few events to check result
 /run/beamOn 1
```

Example macro and detector definition files can be found in [GEARS][][/examples/physics/decay](decay) folder. The following is an example analysis code to show the recorded events in ROOT:

```cpp
root [] t->Scan("pdg:trk:pid:stp:dt/1e9:t/1e9","","colsize=10 precision=10")
```

For people who want to understand how this is done, please check the [GEARS doxygen page of StakingAction](https://codedocs.xyz/jintonic/gears/classStackingAction.html) and the following [Geant4][] help pages:

- <http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Fundamentals/event.html#stacking-mechanism>
- <http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/UserActions/optionalActions.html?highlight=stack#g4userstackingaction>

For the impatient, new particles created after the specified time window in a decay process will be tagged as `fWaiting` in `G4UserStackingAction::ClassifyNewTrack()`. This postpones the tracking of them after the call of `G4UserStackingAction::NewStage()`. One can then save and reset the current event in the `NewStage()` function so that the postponed tracks will be saved in a separate event.

#### Stop decay chain
If the half life of a daughter nucleus is longer than a measurement duration, there is no need to simulate its decay anymore. In this case, instead of splitting its decay to another event, we should simply stop its radioactive decay completely. This is done using a Geant4 macro command `/grdm/nucleusLimits`, for example,

```sh
# enable radioactive decay physics
/physics_lists/select QGSP_BERT
/physics_lists/factory/addRadioactiveDecay

/run/initialize

# start with the alpha decay of Am-241
/gps/particle ion
/gps/ion 95 241
/gps/energy 0
# since Np-237, the daughter of Am-241, is not in the following range,
# it will not alpha-decay into its daughter nucleus in this simulation.
# The simulation will stop when Np-237 decays into its ground state.
/grdm/nucleusLimits 241 241 95 95
```

### Optical processes
Optical processes can be enabled after a reference list is chosen:

```sh
 # based on Geant4 example OpNovice2 (EMZ: option4 of EM)
 /physics_lists/select QGSP_BERT_EMZ
 # cmd below becomes available only when the cmd above is used
 /physics_lists/factory/addOptical
 # must be run after the cmds above
 /run/initialize

 /process/list Electromagnetic
   phot,              compt,               conv,                msc
   eIoni,              eBrem,        CoulombScat,            annihil
   muIoni,            muBrems,         muPairProd,              hIoni
   hBrems,          hPairProd,            ionIoni,           Cerenkov
   Scintillation

 /process/list Optical
   OpAbsorption,   OpRayleigh,            OpMieHG,         OpBoundary
   OpWLS
```

Individual optical processes can be toggled by the following commands:

~~~sh
/process/optical/processActivation Cerenkov true/false
/process/optical/processActivation Scintillation true/false
/process/optical/processActivation OpAbsorption true/false
/process/optical/processActivation OpRayleigh true/false
/process/optical/processActivation OpMieHG true/false
/process/optical/processActivation OpBoundary true/false
/process/optical/processActivation OpWLS true/false
~~~

More built-in commands related to optical processes can be found [here](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Control/AllResources/Control/UIcommands/_process_optical_.html). Example usages can be found [here](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Examples/ExtendedCodes.html#optical-photons).

It is useful to categorize the processes the following way:

- Production of [optical photons][]:
  - [Cerenkov radiation](https://en.wikipedia.org/wiki/Cherenkov_radiation)
  - [Scintillaiton](https://en.wikipedia.org/wiki/Scintillation_(physics))
- Transportation of [optical photons][] inside certain material:
  - Absorption (OpAbsorption)
  - Scattering: [Rayleigh scattering](https://en.wikipedia.org/wiki/Rayleigh_scattering) (OpRayleigh), and [Mie scattering](https://en.wikipedia.org/wiki/Mie_scattering) (OpMieHG), etc.
  - Wavelength shifting (OpWLS)
- Transportation of [optical photons][] on the boundary of two materials:
  - Reflection, refraction and transmission (OpBoundary)

It is also important to understand that [optical photons][] are treated differently from gamma and x-rays in [Geant4][], since completely different physics processes are assigned to them.

#### Optical properties of materials and surfaces
To [generate Cerenkov light](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/TrackingAndPhysics/physicsProcess.html#generation-of-photons-in-processes-electromagnetic-xrays-cerenkov-effect), one HAS TO specify the refractive index of the material where the light is generated. In [GEARS][], this is [done in the detector geometry description file](../detector/optical).

At least two parameters need to be specified to [generate scintillation light](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/TrackingAndPhysics/physicsProcess.html#generation-of-photons-in-processes-electromagnetic-xrays-scintillation): the light yield, i.e., the number of photons per unit energy deposition (SCINTILLATIONYIELD), and the variation of the number of generated photons (RESOLUTIONSCALE). The parameters need to be attached to the material that scintillates, they are hence [specified in the detector geometry description file](../detector/optical) as well.

The parameter, RAYLEIGH and ABSLENGTH, related to the transportation of [optical photons][] in a mertial also have to be [attached to the material](../detector/optical).

In an ideal optical interface, the transportation of [optical photons][] can be calculated [given the refractive indices of the matierials](../detector/optical) on both sides. To simulate more complicated interfaces, please see [here](../detector/optical#define-optical-properties-of-a-surface).

#### Example macros

- [CsI3inWLS.tg](../detector/optical/CsI3inWLS.tg): it models a cylindrical [CsI][] crystal with a diameter of about 3 inches. It is wrapped in Teflon tape (painted with [TPB][]) on the side surface and coupled to two [PMT SiO2 windows][PMT] on its end surfaces.
- [CerenkovInPMTwindow.mac](../detector/optical/CerenkovInPMTwindow.mac): an electron is shot to a PMT window from the vacuum side, generating Cereknov light in the PMT silica window.
- [ScintillationInCsI.mac](../detector/optical/ScintillationInCsI.mac): a 6 keV gamma is emitted in the center of the CsI crystal generating scintillaiton light in the crystal.
- [groundFrontPainted.mac](../detector/optical/surface/groundFrontPainted.mac) and [CsI2Teflon.tg](../detector/optical/surface/CsI2Teflon.tg): optical photons shot to an unpolished surface between a CsI crystal and PTFE reflector without an air gap in between.

[optical photons]: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/TrackingAndPhysics/physicsProcess.html#optical-photon-processes
[CsI]:../detector/optical/CsI.tg
[TPB]:../detector/optical/TPB.tg
[PMT]:../detector/optical/SiO2.tg
