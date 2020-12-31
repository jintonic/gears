[![home](https://img.shields.io/badge/gears-home-blue?style=flat)](../../..)
[![examples](https://img.shields.io/badge/gears-examples-green?style=flat)](../..)
[![physics](https://img.shields.io/badge/physics-processes-red?style=flat)](..)

## X-ray creation

The characteristic X-ray creation by ionizing particles in a material is demonstrated in [fluorescence.mac](fluorescence.mac), where 5.5 MeV alpha rays are shot to a thin Al foil defined in [foil.tg](foil.tg).Minimal macro commands needed to create characteristic X-ray are:

```sh
# working EM options: _LIV, _PEN, _EMY, _EMZ
/physics_lists/select LBE_LIV
# /process/em/ only exists with radioactive decay being enabled
/physics_lists/factory/addRadioactiveDecay
# PIXE must be used to enable the creation of characteristic X-rays
/process/em/pixe true
# /run/initialize must be called after the physics setups above
/run/initialize
```

For detailed tuning, please refer to Geant4 [node 1620][].

[node 1620]: https://geant4.web.cern.ch/node/1620
