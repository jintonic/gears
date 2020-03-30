[![home](https://img.shields.io/badge/gears-home-blue?style=flat)](../..)
[![examples](https://img.shields.io/badge/gears-examples-green?style=flat)](..)
[![Step point](https://img.shields.io/badge/step-point-red?style=flat)](#step-point)
[![Detected energy](https://img.shields.io/badge/total-energy-magenta?style=flat)](#total-energy)
[![Data analysis](https://img.shields.io/badge/data-analysis-orange?style=flat)](#data-analysis)

[GEARS][] uses the [Geant4][] [general particle source][gps] to generate the [primary particle][], from which a [Geant4][] simulation starts (see [this plot](../output#step-point) to understand the general concept). The up-to-date examples of [gps][] are shipped together with the [Geant4][] source code in the folder:

[geant4/examples/extended/eventgenerator/exgps/macros]({{site.g4git}}/examples/extended/eventgenerator/exgps/macros)

An [outdated webpage](http://hurel.hanyang.ac.kr/Geant4/Geant4_GPS/reat.space.qinetiq.com/gps/examples/examples.html) shows most of the examples contained in the folder above. In addition, it also shows resulted distribution plots, which are very helpful to understand the real effects of the [gps][] macro commands.

[gps]:{{site.g4doc}}/GettingStarted/generalParticleSource.html
[Geant4]: http://geant4.cern.ch
