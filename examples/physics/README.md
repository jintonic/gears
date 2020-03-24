[![home](https://img.shields.io/badge/gears-home-blue?style=flat)](../..)
[![examples](https://img.shields.io/badge/gears-examples-green?style=flat)](..)

## Terminology

1. [physics model][physics list]: what generates what
2. [physics process][physics list]: model + cross section (how often it happens)
3. [physics list][]: a list of processes for common particles
4. [modular lists][]: lists of processes that can be used as building blocks to construct a more complex list
5. [pre-packaged lists][]: official [modular lists][] shipped with [Geant4][]
6. [reference lists][]: a subset of the [pre-packaged lists][] that are well-maintained and tested
7. [factory][]: a [Geant4][] class that can be used to call [pre-packaged lists][] by their names

[physics list]:{{site.g4doc}}/UserActions/mandatoryActions.html#physics-lists
[modular lists]:{{site.g4doc}}/UserActions/mandatoryActions.html#building-physics-list-from-physics-builders
[pre-packaged lists]: {{site.g4git}}/physics_lists/lists/include
[reference lists]: https://geant4.web.cern.ch/node/155
[factory]:https://geant4.kek.jp/lxr/source/physics_lists/lists/src/G4PhysListFactory.cc#L79

## How to choose a physics list

[GEARS][] uses [G4PhysListFactory.cc][factory] to allow one to select one from [pre-packaged lists][] by its name:

```sh
# select an example physics list
# LBE: low background experiment
# LIV: EM model based on Livermore data
/physics_lists/select LBE_LIV
# dump the lists on screen
/process/verbose 1
# initialize physics based on the list
/run/initialize
```

The available names are listed in [G4PhysListFactory.cc][factory]. The naming scheme is introduced on page 24 in this [tutorial][]. A guidance on how to choose a proper physics list is also available in the [tutorial][].

[tutorial]:https://www.slac.stanford.edu/xorg/geant4/SLACTutorial14/Physics1.pdf

## Physics processes

[Major categories of processes]({{site.g4doc}}/TrackingAndPhysics/physicsProcess.html) provided in [Geant4][] include:

- Electromagnitism (EM)
  - Standard processes (~1 keV to ~PeV)
  - Low energy processes (250 eV to ~PeV)
  - Optical photon tracking
- Weak interaction
  - decay of subatomic particles
  - radioactive decay of nuclei
- Hadronic physics
  - pure strong interaction (0 to ~TeV)
  - electro- and gamma-nuclear (10 MeV to ~TeV)
- Parameterized physics (not from first principles) for fast simulation
- Transportation (change from one volume to another)

A unique [process id](../output#process-id) is assigned to each process in a [GEARS][] [output](../output).

Run `/process/list` after `/run/initialize`, and you will get something like this:

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

### Optical processes
Optical processes can be enabled after a reference list is chosen:

```sh
/physics_lists/select QGSC_BERT_EMV
# cmd below becomes available only after the cmd above is executed
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
  OpAbsorption,         OpRayleigh,            OpMieHG,         OpBoundary
  OpWLS

```

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

### Radioactive decay processes
Radioactive decay processes can be enabled after a reference list is chosen:

```sh
/physics_lists/select QGSC_BERT_EMV
# cmd below becomes available only after the cmd above is executed
/physics_lists/factory/addRadioactiveDecay
# must be run after the cmds above
/run/initialize

/process/list Decay
  Decay 	RadioactiveDecay
```
Detailed control of radioactive decay is provided by the /[grdm][]/ command, for example,

~~~
/grdm/deselectVolume chamber # disabled radioactive decay in volume "chamber"
/grdm/nucleusLimits 1 80 # enabled radioactive decay only when z in [1, 80]
~~~

[Geant4]: http://geant4.cern.ch
[GEARS]: http://physino.xyz/gears
[grdm]:{{site.g4doc}}/Control/AllResources/Control/UIcommands/_grdm_.html
