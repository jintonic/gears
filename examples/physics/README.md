[![home](https://img.shields.io/badge/gears-home-magenta?style=flat)](../..)
[![examples](https://img.shields.io/badge/gears-examples-green?style=flat)](..)
[![alpha](https://img.shields.io/badge/alpha-interactions-blue?style=flat)](alpha)
[![beta](https://img.shields.io/badge/beta-interactions-yellow?style=flat)](beta)
[![gamma](https://img.shields.io/badge/gamma-interactions-cyan?style=flat)](gamma)
[![optical](https://img.shields.io/badge/optical-photons-red?style=flat)](#optical-processes)

## Terminology

1. [physics model][physics list]: what happens in a certain energy range
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

[Major categories of processes]({{site.g4doc}}/TrackingAndPhysics/physicsProcess.html) provided in [Geant4][] include:

- Electromagnitism (EM)
  - Standard processes (~1 keV to ~PeV)
  - Low energy processes (250 eV to ~PeV)
  - [Optical photon tracking](#optical-processes)
- Weak interaction
  - decay of subatomic particles
  - [radioactive decay of nuclei](radioactive-decay-processes)
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

### Radioactive decay processes
Radioactive decay processes can be enabled after a reference list is chosen:

```sh
 # choose a reference physics list
 /physics_lists/select QGSC_BERT_EMV
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

[grdm]:{{site.g4doc}}/Control/AllResources/Control/UIcommands/_grdm_.html

### Optical processes
Optical processes can be enabled after a reference list is chosen:

```sh
 # based on Geant4 example OpNovice2 (EMZ: option4 of EM)
 /physics_lists/select QGSC_BERT_EMZ
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

More built-in commands related to optical processes can be found [here]({{site.g4doc}}/Control/AllResources/Control/UIcommands/_process_optical_.html). Example usages can be found [here]({{site.g4doc}}/Examples/ExtendedCodes.html#optical-photons).

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
To [generate Cerenkov light]({{site.g4doc}}/TrackingAndPhysics/physicsProcess.html#generation-of-photons-in-processes-electromagnetic-xrays-cerenkov-effect), one HAS TO specify the refractive index of the material where the light is generated. In [GEARS][], this is [done in the detector geometry description file](../detector/optical).

At least two parameters need to be specified to [generate scintillation light]({{site.g4doc}}/TrackingAndPhysics/physicsProcess.html#generation-of-photons-in-processes-electromagnetic-xrays-scintillation): the light yield, i.e., the number of photons per unit energy deposition (SCINTILLATIONYIELD), and the variation of the number of generated photons (RESOLUTIONSCALE). The parameters need to be attached to the material that scintillates, they are hence [specified in the detector geometry description file](../detector/optical) as well.

The parameter, RAYLEIGH and ABSLENGTH, related to the transportation of [optical photons][] in a mertial also have to be [attached to the material](../detector/optical).

In an ideal optical interface, the transportation of [optical photons][] can be calculated [given the refractive indices of the matierials](../detector/optical) on both sides. To simulate more complicated interfaces, please see [here]({{site.g4doc}}/TrackingAndPhysics/physicsProcess.html#boundary-process).

#### Example macros

- [CsI3inWLS.tg]({{site.file}}/examples/detector/optical/CsI3inWLS.tg): it models a cylindrical [CsI][] crystal with a diameter of about 3 inches. It is wrapped in Teflon tape (painted with [TPB][]) on the side surface and coupled to two [PMT SiO2 windows][PMT] on its end surfaces.
- [CerenkovInPMTwindow.mac]({{site.file}}/examples/detector/optical/CerenkovInPMTwindow.mac): an electron is shot to a PMT window from the vacuum side, generating Cereknov light in the PMT silica window.
- [ScintillationInCsI.mac]({{site.file}}/examples/detector/optical/ScintillationInCsI.mac): a 6 keV gamma is emitted in the center of the CsI crystal generating scintillaiton light in the crystal.

[optical photons]: {{site.g4doc}}/TrackingAndPhysics/physicsProcess.html#optical-photon-processes
[CsI]:{{site.file}}/examples/detector/optical/CsI.tg
[TPB]:{{site.file}}/examples/detector/optical/TPB.tg
[PMT]:{{site.file}}/examples/detector/optical/SiO2.tg
