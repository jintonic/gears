[![YouTube](https://img.shields.io/badge/You-Tube-red?style=flat)](https://youtu.be/sgo-RPbDRcU)
[![optical processes](https://img.shields.io/badge/optical-processes-blue?style=flat)](../../physics#optical-processes)

The Polished finish defines the case where the surface is perfectly smooth. The simulation then considers the reflectivity and decides whether the optical photon is absorbed or whether a further calculation needs to be performed to determine whether the photon is reflected or refracted. If the photon is refracted, Snell's law is used to calculate how the refraction takes place.

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
  finish polished
  property photon_energies 2 2.5*eV 5.0*eV
           REFLECTIVITY      0      0
           TRANSMITTANCE     0      0

~~~

Initially, a random number is generated. If the random number is greater than the sum of REFLECTIVITY and TRANSMITTANCE, the photon is absorbed. If it is not greater than the sum but is greater than REFLECTIVITY alone, the photon is transmitted. If the random number is not greater than REFLECTIVITY, the usual scattering calculation is performed, which in this case would result in either refraction, calculated using Snell's law, or reflection.

Essentially, the following equation is used to calculate the probability of a photon being absorbed, transmitted, or undergoing the usual scattering calculation:

*R + A + T = 1*

Where R represents the reflectivity—the probability of the photon undergoing the usual scattering calculation, A represents the probability of absorption, and T represents the probability of transmittance. *Note - Transmittance in this case allows for photons to be transmitted without any change in direction or polarization*

Below are screenshots demonstrating different values for the various parameters. The green lines represent the trajectories of the photons. The volume with the blue outline represents the CsI crystal. Photons are emitted from a thin strip along the middle of the CsI crystal and directed into the black-bordered volume, which is the Teflon.

## Reflectivity = 0 and Transmittance = 0 

As mentioned earlier, a reflectivity value of 0 and a transmittance value of 0 mean that none of the photons are reflected or transmitted. Therefore, based on the random number mechanism previously described, the photon is determined to be absorbed. As shown in the image below, the photon emitted from the CsI is absorbed upon reaching the CsI–Teflon interface.

<img src="https://github.com/user-attachments/assets/b10cfb50-a935-4b22-8144-6cf04bf783ca" width="400"/>

## Reflectivity = 0 and Transmittance = 1 

In this case, all of the optical photons are transmitted through the interface without any reflection or absorption. The image shows photons simply crossing the CsI–Teflon boundary.

<img src="https://github.com/user-attachments/assets/be2f4bc1-d141-44fa-8e8b-5d47ecbce1bd" width="400"/>

## Reflectivity = 0.5 and Transmittance = 0.5

Using the random number mechanism mentioned above, the simulation first determines that no absorption occurs. Given a reflectivity of 0.5 and a transmittance of 0.5, approximately half of the photons are transmitted, as indicated by the trajectories that continue straight through, maintaining the angle of incidence. The remaining photons undergo the usual scattering calculation. In this case, the simulation determines whether the photons are refracted, calculated using Snell’s law, or reflected. The refracted photons can be identified by their altered trajectories, which show a greater angle of refraction compared to those that were simply transmitted. The photons that undergo specular reflection are reflected back into the CsI volume, as shown by the sharply angled green lines

<img src="https://github.com/user-attachments/assets/685215b0-34ad-40ee-a2e2-bd70e1382700" width="400"/>

## Reflectivity = 0.9 and Transmittance = 0.1

Using the random number mechanism mentioned above, the simulation first determines that no absorption occurs. Given a reflectivity of 0.9 and a transmittance of 0.1, only some of the photons are transmitted, as indicated by the trajectories that continue straight through, maintaining the angle of incidence. The remaining photons undergo the usual scattering calculation. In this case, the simulation determines whether the photons are refracted, calculated using Snell’s law, or reflected. The refracted photons can be identified by their altered trajectories, which show a greater angle of refraction compared to those that were simply transmitted. The photons that undergo specular reflection are reflected back into the CsI volume, as shown by the sharply angled green lines

<img src="https://github.com/user-attachments/assets/82ff9d2f-c584-493f-be21-80e17217632d" width="400"/>


## Reflectivity = 0.1 and Transmittance = 0.9

This configuration causes only some of the photons to undergo the usual scattering calculation, while most are transmitted straight through.


<img src="https://github.com/user-attachments/assets/51661495-d3ef-44bd-98eb-9e051c381ace" width="400"/>


## Reflectivity = 1 and Transmittance = 0

In this configuration, none of the photons are absorbed and none are transmitted. Each photon undergoes a calculation to determine whether it undergoes reflection or refraction based on Snell's law. The photons are fired at an incident angle to demonstrate that they can undergo either reflection or refraction.

<img src="https://github.com/user-attachments/assets/0af355ed-d273-4fa8-9a1e-2e136303e79b" width="400"/>



[GEARS]: http://physino.xyz/gears
[tg]: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomASCII.html
[Geant4]: http://geant4.cern.ch
[GDML]: https://gdml.web.cern.ch/GDML/
[G4OpBoundaryProcess]: http://www-geant4.kek.jp/lxr/source//processes/optical/include/G4OpBoundaryProcess.hh
[PostStepDoIt]: http://www.apc.univ-paris7.fr/~franco/g4doxy4.10/html/class_g4_op_boundary_process.html#a70a65cc5127a05680a0c4679f8300871
[G4LogicalBorderSurface]: http://www-geant4.kek.jp/lxr/source/geometry/volumes/include/G4LogicalBorderSurface.hh
