[![home](https://img.shields.io/badge/gears-home-blue?style=flat)](../..)
[![examples](https://img.shields.io/badge/gears-examples-green?style=flat)](..)

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

[Geant4]: http://geant4.cern.ch
[GEARS]: http://physino.xyz/gears
[grdm]:http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Control/AllResources/Control/UIcommands/_grdm_.html
