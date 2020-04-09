[![home](https://img.shields.io/badge/gears-home-blue?style=flat)](../../..)
[![examples](https://img.shields.io/badge/gears-examples-green?style=flat)](../..)
[![physics](https://img.shields.io/badge/examples-physics-red?style=flat)](..)

In [DT.mac][], 14 MeV neutrons from a DT generator are shot to a concrete block defined in [concrete.tg][]. Example analysis code:

```cpp
// check which interaction is dominant
root [] t->Draw("pro","pdg==2112 && pro>2000")
root [] gPad->SetLogy()
// neutrons all end up with being captured (pro==4131)
// draw the last point of a neutron track
root [] t->Draw("x0","pdg==2112 && pro==4131")
// draw charges of generated particles
root [] t->Draw("q")
// draw isotopes involved
root [] t->Draw("pdg", "pdg>10000")
```

[DT.mac]:{{site.file}}/examples/physics/neutron/DT.mac
[concrete.tg]:{{site.file}}/examples/physics/neutron/concrete.tg
