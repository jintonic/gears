[![YouTube](https://img.shields.io/badge/You-Tube-red?style=flat)](https://youtu.be/sgo-RPbDRcU)
[![optical processes](https://img.shields.io/badge/optical-processes-blue?style=flat)](../../physics#optical-processes)

The finish PolishedFrontPainted represents a volume with a painted surface. The reflectivity 
𝑅 defines the probability that an optical photon is reflected by the painted surface. More specifically, it is defined as 1 minus the absorption coefficient. The optical photon may or may not be absorbed by the paint. The paint is modeled through surface properties. When not absorbed, the photon undergoes speculsar spike reflection. No refraction occurs.


## Naming convention for example files
r - Reflectivity
<br>
t - transmittance 
<br>
r0t0 - Reflectivity = 0, Trasmittance = 0
<br>
r05t05 - Reflectivity = 0.5 Transmittance = 0.5
## Example Parameters for r0t0.tg

~~~cpp

// optical properties of the surface between CsI & Teflon
:surf CsI2Teflon CsI:1 Teflon:2
  type dielectric_dielectric
  model unified	
  finish polishedfrontpainted
  property photon_energies 2 2.5*eV 5.0*eV
           REFLECTIVITY      0      0
           TRANSMITTANCE     0      0

~~~

Initially, a random number is generated. If the random number is greater than the sum of REFLECTIVITY and TRANSMITTANCE, the photon is absorbed. If it is not greater than the sum but is greater than REFLECTIVITY alone, the photon is transmitted. If the random number is not greater than REFLECTIVITY, the usual scattering calculation is performed, which in this case would be a specular spike reflection.

Below are screenshots demonstrating different values for the various parameters. The green lines represent the trajectories of the photons. The volume with the blue outline represents the CsI crystal. Photons are emitted from a thin strip along the middle of the CsI crystal and directed into the black-bordered volume, which is the Teflon.

## Relctivity = 0 and Transmittance = 0 

As mentioned earlier, a reflectivity value of 0 and a transmittance value of 0 mean that none of the photons are reflected or transmitted. Therefore, based on the random number mechanism previously described, the photon is determined to be absorbed. As shown in the image below, the photon emitted from the CsI is absorbed upon reaching the CsI–Teflon interface.

<img src="https://github.com/user-attachments/assets/a4d15050-51c9-4386-b79f-2acd6ef279de" width="400"/>

## Relctivity = 0 and Transmittance = 1 

In this case, all of the optical photons are transmitted through the interface without any reflection or absorption. The image shows photons freely crossing the CsI–Teflon boundary.

<img src="https://github.com/user-attachments/assets/24282ab8-aa50-4904-ad85-35be74f7a9ab" width="400"/>

## Relctivity = 0.5 and Transmittance = 0.5

With equal values of reflectivity and transmittance, each photon has a 50% chance of being reflected or transmitted. The image demonstrates both transmitted and reflected photon trajectories originating from the CsI surface. Recall that the reflection in this case is a specular spike reflection.

<img src="https://github.com/user-attachments/assets/c307e37c-f345-4c40-8d94-2049ed1caa79" width="400"/>

## Relctivity = 1 and Transmittance = 0

In this configuration, all photons are reflected at the interface. No transmission or absorption occurs, resulting in the specular spike reflection of photons.


<img src="https://github.com/user-attachments/assets/fe69e967-b2d7-4da9-845c-89dc7b8afb12" width="400"/>



[GEARS]: http://physino.xyz/gears
[tg]: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomASCII.html
[Geant4]: http://geant4.cern.ch
[GDML]: https://gdml.web.cern.ch/GDML/
[G4OpBoundaryProcess]: http://www-geant4.kek.jp/lxr/source//processes/optical/include/G4OpBoundaryProcess.hh
[PostStepDoIt]: http://www.apc.univ-paris7.fr/~franco/g4doxy4.10/html/class_g4_op_boundary_process.html#a70a65cc5127a05680a0c4679f8300871
[G4LogicalBorderSurface]: http://www-geant4.kek.jp/lxr/source/geometry/volumes/include/G4LogicalBorderSurface.hh
