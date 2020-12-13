[![home](https://img.shields.io/badge/gears-home-blue?style=flat)](../../..)
[![examples](https://img.shields.io/badge/gears-examples-green?style=flat)](../..)
[![physics](https://img.shields.io/badge/examples-physics-red?style=flat)](..)

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

