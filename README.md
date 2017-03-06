# gears - geant4 related simulation

It makes full use of Geant4 [plain-text geometry definition](http://geant4.web.cern.ch/geant4/collaboration/working_groups/geometry/docs/textgeom/textgeom.pdf) and [build-in macros](https://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/ForApplicationDeveloper/html/AllResources/Control/UIcommands/_.html) to reduce C++ coding and to enable fast implementation and debugging of new experiments.

# Get started

~~~shell
cd gears
make
cd macro/Rutherford/
./scatter.sh 100
~~~

# Physics

## Physics processes

Run `/process/list` after `/run/initialize`, and you will get

~~~
     Transportation,              Decay,   RadioactiveDecay,                msc
              hIoni,            ionIoni,             hBrems,          hPairProd
        CoulombScat,              eIoni,              eBrem,            annihil
               phot,              compt,               conv,             muIoni
            muBrems,         muPairProd,         hadElastic,   neutronInelastic
           nCapture,           nFission,    protonInelastic,       pi+Inelastic
       pi-Inelastic,     kaon+Inelastic,     kaon-Inelastic,    kaon0LInelastic
    kaon0SInelastic,    lambdaInelastic,anti-lambdaInelastic,    sigma-Inelastic
anti_sigma-Inelastic,    sigma+Inelastic,anti_sigma+Inelastic,       xi-Inelastic
  anti_xi-Inelastic,       xi0Inelastic,  anti_xi0Inelastic,    omega-Inelastic
anti_omega-Inelastic,anti_protonInelastic,anti_neutronInelastic,anti_deuteronInelastic
anti_tritonInelastic,  anti_He3Inelastic,anti_alphaInelastic
~~~

Now you can use, for example, `/process/inactivate nCapture` to disable neutron capture process in your simulation.

While optical processes can be toggled by the following commands:

~~~
/process/optical/processActivation Cerenkov true/false
/process/optical/processActivation Scintillation true/false
/process/optical/processActivation OpAbsorption true/false
/process/optical/processActivation OpRayleigh true/false
/process/optical/processActivation OpMieHG true/false
/process/optical/processActivation OpBoundary true/false
/process/optical/processActivation OpWLS true/false
~~~
