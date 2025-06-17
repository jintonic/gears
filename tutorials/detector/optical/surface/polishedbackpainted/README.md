[![YouTube](https://img.shields.io/badge/You-Tube-red?style=flat)](https://youtu.be/sgo-RPbDRcU)
[![optical processes](https://img.shields.io/badge/optical-processes-blue?style=flat)](../../physics#optical-processes)

PolishedBackPainted describes the situation when a volume features a painted surface with a gap between the volume and the paint. Reflectivity defines the probability of reflection by the paint. The refractive index for the volume-paint gap can be defined as a surface parameter. The sigma value refers to the degree of roughness of the volume surface. Geant4 documentation describes it more aptly as the roughness of the crystal–air gap interface.

Snell's law is applied after sampling the facet normals with respect to the sigma alpha parameter. The photon then enters the crystal–air gap if refracted, and if reflected, one of four things can happen: specular spike reflection, specular lobe reflection, backscatter, or Lambertian reflection.

It is important that once the optical photon reaches the paint, it undergoes specular spike reflection—this is the "polished" part of the name PolishedBackPainted. The paint is defined by the surface parameters.

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
rin - Rindex; more specifically, the refractive index fo the crystal-air gap
<br>
r05t05 - Reflectivity = 0.5 Transmittance = 0.5
## Example Parameters for r0t0.tg

~~~cpp

// optical properties of the surface between CsI & Teflon
:surf CsI2Teflon CsI:1 Teflon:2
  type dielectric_dielectric
  model unified	
  finish polishedbackpainted
  property photon_energies 2 2.5*eV 5.0*eV
           REFLECTIVITY      0      0
           RINDEX            0      0

~~~

Below is an image illustrating what occurs at the crystal–air interface (J. Nilsson et al.). Notice how altering the sigma alpha brings about changes in the facet normal of the crystal volume. The gap between the reflective paint/wrapping (the line at the top of the image) and the crystal/volume surface (featured at the bottom) corresponds to the RINDEX surface parameters described in the example optical properties section above. Note that the reflection off the paint/wrapping is a specular spike reflection.

<img src="https://github.com/user-attachments/assets/d9bc7810-8df6-4ef0-950f-5c28f2d31257" width="400"/>


As for the different types of reflections that are possible off the facet normals, the following occurs:
The specular lobe constant defines the probability of reflection around the normal of a micro-facet. The specular spike constant represents the probability of reflection about the average surface normal. The diffuse lobe constant corresponds to the probability of internal Lambertian reflection. Finally, the backscatter spike constant accounts for multiple reflections within a deep groove, ultimately resulting in exact backscattering.

Below are screenshots demonstrating different values for the various parameters. The green lines represent the trajectories of the photons. The volume with the blue outline represents the CsI crystal.

## Reflectivity = 0 sigma_alpha = 0 

Reflectivity in this case corresponds to the probability of reflection off the wrapper/paint. Recall, however, that the photon must first pass through the crystal/volume, interact with the crystal–air interface, traverse the crystal–air gap, and only then confront the wrapper/paint. Note that the sigma alpha of 0 yields a smooth crystal surface.

Therefore, note that some of the trajectories are not simply specular spike reflections. Some photons, before traversing the gap and reaching the paint, reflect off the crystal boundary itself and undergo Lambertian reflection.<img src="https://github.com/user-attachments/assets/2a78dd47-ce7f-42d8-ba23-212469e3eb3d" width="400"/>

## Reflectivity = 0 sigma_alpha = 0 Specularspikeconstant = 1

In this case, the configuration is quite similar to the previous one, with a sigma alpha of 0. However, setting the specular spike constant to 1 ensures that if a reflection is to occur off the crystal boundary, the photon undergoes specular spike reflection. It can now be seen that the photons are either absorbed by the paint or undergo a specular spike reflection off the crystal boundary.

<img src="https://github.com/user-attachments/assets/cdc857ca-5991-4a20-bfa1-74f2bd02c53e" width="400"/>

## Reflectivity = 0 sigma_alpha = 0 Backscatterconstant = 1
This configuration simply features all reflected photons undergoing backscattering. The photons can either make it through to the paint and get absorbed or undergo backscattering, as shown by all the backscattered photon trajectories below.


<img src="https://github.com/user-attachments/assets/f5ba0896-c8a9-4495-8d4b-a915357c0c8a" width="400"/>

## Reflectivity = 1, sigma_alpha = 0, Rindex = 0.9

In this configuration, none of the photons are absorbed. Each photon undergoes a calculation to determine its trajectory: traveling through the volume, reaching the crystal–air gap interface, entering the gap, and then confronting the wrapper/paint.

The photon may undergo one of the four aforementioned types of reflection off the crystal boundary, as displayed by the various diverging trajectories. Alternatively, it may pass through to the air gap—courtesy of a calculation using Snell's law—undergo specular spike reflection off the paint, interact with the crystal–air gap interface again (using Snell's law), and make its way back into the volume.

Recall again that Rindex refers to the index of refraction of the crystal–air gap.

<img src="https://github.com/user-attachments/assets/643713da-eaeb-4f9e-ac09-001fb14d6f03" width="400"/>

## Reflectivity = 1, sigma_alpha = 0, Rindex = 2

This configuration is quite similar to the previous one, with only the index of refraction of the crystal–air gap altered. However, notice that now the photon trajectories don't showcase photons undergoing one of the four different types of reflection, but rather those that traverse through to the reflective paint, undergo specular spike reflection, and refract back into the volume itself. This configuration mostly shows the changes that the Rindex of the crystal–air gap can bring forth.

<img src="https://github.com/user-attachments/assets/b8c5fbfa-a38f-4efe-8342-f63419abe80f" width="400"/>

## Reflectivity = 1, sigma_alpha = 0, specularspikeconstant = 1, rindex = 0.9

In this case, the photon traverses the volume at an angle and undergoes a specular spike reflection off the crystal boundary.

<img src="https://github.com/user-attachments/assets/4ac08679-a7e5-42da-b660-386503089430" width="400"/>



## Reflectivity = 1, sigma_alpha = 30, rindex = 0.9 

This configuration features the optical photon trajectories given a rough crystal boundary, as indicated by a sigma value of 30.

<img src="https://github.com/user-attachments/assets/6b992c39-5e44-439b-8de7-3f7de3a2cacf" width="400"/>



[GEARS]: http://physino.xyz/gears
[tg]: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomASCII.html
[Geant4]: http://geant4.cern.ch
[GDML]: https://gdml.web.cern.ch/GDML/
[G4OpBoundaryProcess]: http://www-geant4.kek.jp/lxr/source//processes/optical/include/G4OpBoundaryProcess.hh
[PostStepDoIt]: http://www.apc.univ-paris7.fr/~franco/g4doxy4.10/html/class_g4_op_boundary_process.html#a70a65cc5127a05680a0c4679f8300871
[G4LogicalBorderSurface]: http://www-geant4.kek.jp/lxr/source/geometry/volumes/include/G4LogicalBorderSurface.hh
