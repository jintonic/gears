[![YouTube](https://img.shields.io/badge/You-Tube-red?style=flat)](https://youtu.be/sgo-RPbDRcU)
[![optical processes](https://img.shields.io/badge/optical-processes-blue?style=flat)](../../physics#optical-processes)


The ground finish describes a rough surface. The degree of roughness is defined by the sigma alpha parameter. The simulation determines, with respect to the reflectivity, whether the photon is absorbed or if the usual scattering calculation is performed. If the photon is not absorbed, a facet normal is sampled, and the photon is either refracted or reflected. If it is refracted, Snell's law is applied using the facet normal—that is, the angle alpha between the average surface normal and the facet normal is sampled. If reflection occurs instead, the photon undergoes one of the following: specular spike reflection, backscatter reflection, specular lobe reflection, or Lambertian reflection.

## Naming convention for example files
r - Reflectivity
<br>
t - transmittance 
<br>
sa - sigma alpha
<br>
sl - specularlobeconstant
<br>
back - backscatterconstant
<br>
spec - specularspikeconstant
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
  finish ground
  property photon_energies 2 2.5*eV 5.0*eV
           REFLECTIVITY      0      0
           TRANSMITTANCE     0      0

~~~

Initially, a random number is generated. If the random number is greater than the sum of REFLECTIVITY and TRANSMITTANCE, the photon is absorbed. If it is not greater than the sum but is greater than REFLECTIVITY alone, the photon is transmitted. If the random number is not greater than REFLECTIVITY, the usual scattering calculation is performed, which in this case would result in either Snell's law being used to calculate the photon trajectory after sampling the facet normal, or one of the four reflection types mentioned above.

The specular lobe constant defines the probability of reflection around the normal of a micro-facet. The specular spike constant  represents the probability of reflection about the average surface normal. The diffuse lobe constant corresponds to the probability of internal Lambertian reflection. Finally, the backscatter spike constant accounts for multiple reflections within a deep groove, ultimately resulting in exact backscattering. These four probabilities must sum to one, with the diffuse lobe constant automatically calculated by the simulation based on the other three user-defined values.

Below are screenshots demonstrating different values for the various parameters. The green lines represent the trajectories of the photons. The volume with the blue outline represents the CsI crystal. Photons are emitted from a thin strip along the middle of the CsI crystal and directed into the black-bordered volume, which is the Teflon.

## Relctivity = 0 and Transmittance = 0 

As mentioned earlier, a reflectivity value of 0 and a transmittance value of 0 mean that none of the photons are reflected or transmitted. Therefore, based on the random number mechanism previously described, the photon is determined to be absorbed. As shown in the image below, the photon emitted from the CsI is absorbed upon reaching the CsI–Teflon interface.

<img src="https://github.com/user-attachments/assets/955f0461-820c-431c-90d8-6da28ec162a8" width="400"/>

## Relctivity = 0 and Transmittance = 1 

In this case, all of the optical photons are transmitted through the interface without any reflection or absorption. The image shows photons simply crossing the CsI–Teflon boundary.

<img src="https://github.com/user-attachments/assets/8dfefd5f-7eec-42bb-a0c3-4dfe5aacfcd9" width="400"/>

## Relctivity = 0.5 and Transmittance = 0.5

UUsing the random number mechanism mentioned above, the simulation first determines that no absorption occurs. Given a reflectivity of 0.5 and a transmittance of 0.5, approximately half of the photons are transmitted, as indicated by the trajectories that continue straight through. The remaining photons undergo the usual scattering calculation. For some of these, the simulation uses Snell's law with respect to the facet normal to determine how they propagate further into the Teflon. Others undergo reflection. Some undergo specular spike reflection, while others experience one of the four different types such as Lambertian reflection.


<img src="https://github.com/user-attachments/assets/717e8d07-834b-47af-915d-07cb59ab2cf5" width="400"/>

## Relctivity = 1, sigma_alpha = 0, Transmittance = 0

In this configuration, none of the photons are absorbed, and none are transmitted. Each photon undergoes a calculation to determine whether it experiences one of the four types of reflection or whether Snell’s law is applied with respect to the facet normal. With a sigma alpha of 0, the surface is very flat and behaves much like a polished mirror. However, since four reflection types are possible, not all photons undergo specular spike reflection—some may be Lambertian. Therefore, the trajectories are not limited to straightforward refraction or specular spike reflection. Note that the photon is fired at an angle in the example below.

<img src="https://github.com/user-attachments/assets/3ed7db02-50bb-4907-9582-d7bdfdd7eac1" width="400"/>

## Relctivity = 1, sigma_alpha = 0, specularspikeconstant = 1

Much like the previous configuration, the photons are not absorbed. In this case, not only is sigma alpha set to 0 (so the surface behaves like a polished surface), but the specular spike constant is also set to 1, meaning none of the other three reflection types are possible when a reflection occurs. The photon is fired at an angle. As shown in the image below, either the facet normal is sampled, resulting in refraction, or a simple specular spike reflection takes place.

<img src="https://github.com/user-attachments/assets/e0ef3a44-f528-42eb-a7e1-07d14ebdae1c" width="400"/>

## Relctivity = 1, sigma_alpha = 30, Transmittance  = 0

In this configuration the sigma_alpha is set to 30 resulting in quite a rough surface. As shown below this results in the photon trajectories being quite varied. When the photon aproaches the CsI teflon Boundary eitehr the facetnormal is samolled or it undergoes one of the four reflection types. Given the roughness of teh surface the reflections are quite varied adn so are teh trajectories afeter the calculation using snell's Law.

<img src="https://github.com/user-attachments/assets/39c536a2-a8d2-4c3e-9a2a-f2eec144740a" width="400"/>

## Relctivity = 1, sigma_alpha = 30, Transmittance  = 0

In this configuration the sigma_alpha is set to 30 resulting in quite a rough surface. As shown below this results in the photon trajectories being quite varied. When the photon aproaches the CsI teflon Boundary eitehr the facetnormal is samolled or it undergoes one of the four reflection types. Given the roughness of teh surface the reflections are quite varied adn so are teh trajectories afeter the calculation using snell's Law.

<img src="https://github.com/user-attachments/assets/39c536a2-a8d2-4c3e-9a2a-f2eec144740a" width="400"/>

## Relctivity = 1, sigma_alpha = 0, Specularlobeconstant  = 1

In this configuration, sigma_alpha is set to 0, resulting in a flat surface. The specular lobe constant represents the reflection probability around the normal of a micro-facet. However, since sigma_alpha is 0, the micro-facets exhibit minimal variation in angle relative to the average surface normal. Therefore, the photon trajectories resemble those in the previous configuration with sigma_alpha set to 0 and the specularspikeconstant set to 1.



<img src="https://github.com/user-attachments/assets/2f7a40dc-ec68-4356-95be-67682d6c0cbc" width="400"/>


## Relctivity = 1, sigma_alpha = 0, Specularlobeconstant  = 0.1, specularspikeconstant = 0.1, backscatterconstant = 0.1

In this configuration, sigma_alpha is set to 0, resulting in a flat surface. The three reflection-type constants are each set to 0.1, so the probability of Lambertian reflection—calculated as 1 minus the sum of the other three reflection probabilities—is quite high. Therefore, if a reflection occurs, it will most likely be Lambertian, as shown in the image below.

<img src="https://github.com/user-attachments/assets/baad5976-0de0-47a3-9889-2fb980dffe65" width="400"/>

## Relctivity = 1, sigma_alpha = 0, backscatterconstant = 1

Much like the previous few configurations, this one also features sigma_alpha set to 0. The back‑scatter spike constant describes multiple reflections within a deep groove. However, since sigma_alpha is 0, the surface is flat, and such grooves do not form. Therefore, the photon trajectories show minimal variation in angle across different runs.
<img src="https://github.com/user-attachments/assets/105c4a4d-6b88-4abd-8756-9705f88cdeb9" width="400"/>



[GEARS]: http://physino.xyz/gears
[tg]: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomASCII.html
[Geant4]: http://geant4.cern.ch
[GDML]: https://gdml.web.cern.ch/GDML/
[G4OpBoundaryProcess]: http://www-geant4.kek.jp/lxr/source//processes/optical/include/G4OpBoundaryProcess.hh
[PostStepDoIt]: http://www.apc.univ-paris7.fr/~franco/g4doxy4.10/html/class_g4_op_boundary_process.html#a70a65cc5127a05680a0c4679f8300871
[G4LogicalBorderSurface]: http://www-geant4.kek.jp/lxr/source/geometry/volumes/include/G4LogicalBorderSurface.hh
