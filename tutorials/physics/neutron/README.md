[![home](https://img.shields.io/badge/gears-home-blue?style=flat)](../../..)
[![tutorials](https://img.shields.io/badge/gears-tutorials-green?style=flat)](../..)
[![physics](https://img.shields.io/badge/tutorials-physics-red?style=flat)](..)

## Neutron interactions

Neutrons interact with matter mainly through the following processes:

- [Neutron capture][] (Geant4 name: **nCapture**, [GEARS process id](../../output#process-id): 4131)
- [Elastic scattering][] (Geant4 name: **hadElastic**, [GEARS process id](../../output#process-id): 4111)
- [Inelastic scattering][] (Geant4 name: **neutronInelastic**, [GEARS process id](../../output#process-id): 4121)
- Neutron induced [Fission][] (Geant4 name: **nFission**, [GEARS process id](../../output#process-id): 4141)

[Neutron capture]: https://www.glossary.oilfield.slb.com/en/Terms/n/neutron_capture.aspx
[Elastic scattering]: https://www.glossary.oilfield.slb.com/en/Terms/e/elastic_neutron_scattering.aspx
[Inelastic scattering]: https://www.glossary.oilfield.slb.com/en/Terms/i/inelastic_neutron_scattering.aspx
[Fission]: https://en.wikipedia.org/wiki/Nuclear_fission

### Gd(n,gamma)

The default HP (high precision) neutron model used in Geant4 does not handle Gd(n,gamma) correctly. This is described in detail in <https://indico.cern.ch/event/746466/contributions/3345714/>. An alternative model is called photon evaporation, which can be activated by setting up an environment variable:

```sh
export G4NEUTRONHP_USE_ONLY_PHOTONEVAPORATION=1
```

(Note that this will be replaced by a macro command in Geant4 version 11). The dataset used by this model is

```sh
export G4LEVELGAMMADATA=/path/to/Geant4/installtion/folder/share/Geant4-??.?.?/data/PhotonEvaporation?.?
```

Example simulation and analysis codes can be found in <https://github.com/jintonic/gears/tree/master/tutorials/physics/neutron/Gd>. As for Geant4.10.7, the simulated gamma-ray spectrum is not satisfactory compared to data described in <https://academic.oup.com/ptep/article/2020/4/043D02/5819518>.

### A comprehensive example

In [DT.mac](DT.mac), 14 MeV neutrons from a DT generator are shot to a concrete block defined in [concrete.tg](concrete.tg). Example analysis code:

```cpp
// check which interaction is dominant
root [] t->Draw("pro","pdg==2112 && pro>2000")
root [] gPad->SetLogy()
// neutrons all end up with being captured (pro==4131)
// draw the last point of a neutron track
root [] t->Draw("x","pdg==2112 && pro==4131")
// draw charges of generated particles
root [] t->Draw("q")
// draw isotopes involved
root [] t->Draw("pdg", "pdg>10000")
```

