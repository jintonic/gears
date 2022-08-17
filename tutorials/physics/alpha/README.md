[![home](https://img.shields.io/badge/gears-home-blue?style=flat)](../../..)
[![examples](https://img.shields.io/badge/gears-examples-green?style=flat)](../..)
[![physics](https://img.shields.io/badge/physics-processes-red?style=flat)](..)

## Alpha interactions

Alpha particles, or ions in general, are heavy (compared to elemental particles) electrically charged particles. According to Knoll's [Radiation Detection and Measurement](https://www.amazon.com/dp/0470131489), they interact with matter primarily through coulomb forces between their positive charge and the negative charge of the orbital electrons within the absorber atoms. Although interactions of the particle with nuclei (as in Rutherford scattering or alpha-particle-induced reactions) are also possible, such encounters occur only rarely and they are not normally significant in the response of radiation detectors.

Common interactions that can be assigned to an alpha in a physics list include:

- Multiple scattering (Geant4 name: msc, GEARS process id: 2010): an alpha changes its direction without ionizing other atoms.
- Ionization (Geant4 name: ionIoni, GEARS process id: 2002): an alpha changes its direction and creates secondary electrons. Energetic electrons are called delta-rays.
- Scintillation (Geant4 name: Scintillation, GEARS process id: 2022): in scintillating materials, an alpha track may end with this process.
- Elastic scattering against a nucleus (Geant4 name: hadElastic, GEARS process id: 4111): an alpha changes its direction by elastically scattering against a nucleus.
- Inelastic scattering against a nucleus (Geant4 name: alphaInelastic, GEARS process id: 4121): an alpha changes its direction and the scattered nucleus changes.

### Stopping power

The stopping power _S = -dE/dx_ is simply the energy loss in a unit track length. The [GEARS output](../../output#step-point) provides two variables to roughly calculate this: _de_ and _dl_. _de_ is the energy deposited in a step point. _dl_ is the corresponding step length.

```cpp
// draw dE/dx VS kinetic energy of alpha particles
root[] t->Draw("de/dl:k", "pdg==22")
```

An alternative simulation tool dedicated to ion interaction in matter is [SRIM](http://www.srim.org/). It may produce better results than Geant4 in some cases.

The [NIST stopping-power and range tables for helium ions](https://physics.nist.gov/PhysRefData/Star/Text/ASTAR.html) is a great resource to verify your Geant4 simulation of alpha particles.

### Bragg curve

The energy of an alpha particle decreases as it moves deeper and deeper into certain material. As it slows down, the surrounding electrons have more time to interact with it. Consequently, its _dE/dx_ goes up. However, when it becomes really slow, it can pick up electrons and get neutralized. Consequently, its _dE/dx_ quickly drops to zero. Such behavior can be shown clearly by the [Bragg curve](https://en.wikipedia.org/wiki/Bragg_peak):

<img src="https://upload.wikimedia.org/wikipedia/commons/d/df/Bragg_Curve_for_Alphas_in_Air.png" alt="Bragg curve" style="width:45%">
<img src="dedl.png" alt="simulated Bragg curve" style="width:50%">

Such a curve can be produced by

```sh
$ root air.root
root[] t->Draw("de/dl:l","trk==1 && de>15","colz")
```

`air.root` can be created by

```sh
$ gears BraggCurve.mac
```

In [BraggCurve.mac](BraggCurve.mac), 5.5 MeV alphas are shot to air. The simulated world is defined in [air.tg](air.tg)

### Range

The spatial distributions of MeV alphas in air can be draw with the following commands:

```cpp
$ root air.root
// draw tracks of the first 100 simulated alpha particles
root[] t->Draw("y:x","trk==1","l",100,0)
// display end points of alpha tracks
root[] t->Draw("y:z","trk==1")
```

<img src="alphaInAir.png" alt="alpha in air" style="width:50%">
<img src="endpoints.png" alt="end points of alpha tracks" style="width:40%">

One can see that there are often a group of hits very close to each other around the end points of alpha tracks. This is due to the large _dE/dx_ at low energies.

### Impact of physics list

In [range.mac](range.mac), 5.5 MeV alphas are shot to a CsI scintillation crystal instead of air. The simulated world is defined in [CsI.tg](CsI.tg). Without specifying a reference physics list (that is, to use the default one specified by GEARS, QGSP_BERT), all alpha particles deposit its full energy in just one step. The step lengths are all about 28 um. To do a detailed simulation, one needs to specify the maximal step length of alphas in CsI. This can be done manually using the macro command `/run/setCut 1 um` or to select a more suitable physics list:

```sh
# LBE: low background experiment (maximal step length: 1 um)
# LIV: Livermore data based EM models
# comment out the following line and run again to see the difference
/physics_lists/select LBE_LIV
```

Run `gears range.mac` with and without this line and draw the alpha hits distributions to see the difference.
