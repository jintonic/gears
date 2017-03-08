[GEARS][] is a [Geant4][] Example Application that is made Really Simple by utilizing [Geant4][] plain [text geometry description][tg] and [build-in UI commands][TUI] (macros) to reduce C++ coding down to a single file (less than 600 [SLOC][]). It is ideal for student training and fast implementation of small experiments.

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

~~~
//:surf name [motherVol/]physVol1 [motherVol/]physVol2
//  type <dielectric_dielectric|dielectric_metal|firsov|x_ray>
//  model <unified|glisur>
//  finish <polished|ground|...>
//  sigma_alpha <float>
//  property
//    <wavelength-independent_property> <value>
//    photon_energies <int(array size)> <energy array>
//    <wavelength-dependent_property> <property values>
:surf reflector CsI PTFE
  type dielectric_dielectric
  model unified
  finish polished
  sigma_alpha 0.1
  property photon_energies 2 2.038*eV, 4.144*eV
    REFLECTIVITY 0.3, 0.5
    EFFICIENCY 0.8, 0.1
~~~

## Sensitive detector

Sensitive detectors are specified by simply add "(S)" at the end of their volume names. The copy numbers of their volumes must be continuous integers starting from 0.

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
    kaon0SInelastic,    lambdaInelastic,anti-lambdaInelastic,   sigma-Inelastic
anti_sigma-Inelastic,    sigma+Inelastic,anti_sigma+Inelastic,     xi-Inelastic
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

[GEARS]: https://github.com/jintonic/gears
[tg]: http://geant4.web.cern.ch/geant4/collaboration/working_groups/geometry/docs/textgeom/textgeom.pdf
[TUI]: http://geant4.cern.ch/G4UsersDocuments/UsersGuides/ForApplicationDeveloper/html/Control/UIcommands/_.html
[SLOC]: https://en.wikipedia.org/wiki/Source_lines_of_code
[ROOT]: https://root.cern.ch
[Geant4]: http://geant4.cern.ch
[NIST]: http://geant4.web.cern.ch/geant4/workAreaUserDocKA/Backup/Docbook_UsersGuides_beta/ForApplicationDeveloper/html/apas08.html
[run]: http://geant4.cern.ch/G4UsersDocuments/UsersGuides/ForApplicationDeveloper/html/Control/UIcommands/_run_.html
[listMaterials]: https://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/ForApplicationDeveloper/html/AllResources/Control/UIcommands/_material_nist_.html
