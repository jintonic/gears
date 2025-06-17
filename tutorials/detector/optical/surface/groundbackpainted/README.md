[![YouTube](https://img.shields.io/badge/You-Tube-red?style=flat)](https://youtu.be/sgo-RPbDRcU)
[![optical processes](https://img.shields.io/badge/optical-processes-blue?style=flat)](../../physics#optical-processes)

Groundbackpainted describes the situation when a volume features a painted surface with a gap between the volume and the paint. Reflectivity defines the probability of reflection by the paint. The refractive index for the volume-paint gap can be defined as a surface parameter. The sigma value refers to the degree of roughness of the volume surface. Geant4 documentation describes it more aptly as the roughness of the crystal–air gap interface.

Snell's law is applied after sampling the facet normals with respect to the sigma alpha parameter. The photon then enters the crystal–air gap if refracted, and if instead it is reflected off of the facetnormal, one of four things can happen: specular spike reflection, specular lobe reflection, backscatter, or Lambertian reflection.

Unlike PolishedBackPainted, it is important to note that once the optical photon reaches the paint, it undergoes Lambertian reflection—this is the "ground" part of the name GroundBackPainted. The paint is defined by the surface parameters

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
  finish groundbackpainted
  property photon_energies 2 2.5*eV 5.0*eV
           REFLECTIVITY      0      0
           RINDEX            0      0

~~~

Below is an image illustrating what occurs at the crystal–air interface (J. Nilsson et al.). Notice how altering the sigma alpha brings about changes in the facet normal of the crystal volume. The gap between the paint/wrapping (the line at the top of the image) and the crystal/volume surface (featured at the bottom) corresponds to the RINDEX surface parameters described in the example optical properties section above. Note that the reflection off the paint/wrapping is a Lambertian reflection.

<img src="https://github.com/user-attachments/assets/5a2d6ed6-e712-4fcf-98db-ee9d14dbca64" width="400"/>


As for the different types of reflections that are possible off the facet normals, the following occurs:
The specular lobe constant defines the probability of reflection around the normal of a micro-facet. The specular spike constant represents the probability of reflection about the average surface normal. The diffuse lobe constant corresponds to the probability of internal Lambertian reflection. Finally, the backscatter spike constant accounts for multiple reflections within a deep groove, ultimately resulting in exact backscattering.

Below are screenshots demonstrating different values for the various parameters. The green lines represent the trajectories of the photons. The volume with the blue outline represents the CsI crystal.

## Reflectivity = 0 sigma_alpha = 0 

Reflectivity in this case corresponds to the probability of reflection off the wrapper/paint. Recall, however, that the photon must first pass through the crystal/volume, interact with the crystal–air interface, traverse the crystal–air gap, and only then confront the wrapper/paint. Note that the sigma alpha of 0 yields a smooth crystal surface.

Therefore, some photons, before traversing the gap and reaching the paint, reflect off the crystal boundary itself and undergo Lambertian reflection.<img src="https://github.com/user-attachments/assets/0f00d663-9498-40d2-a625-e558410aeb30" width="400"/>

## Reflectivity = 0 sigma_alpha = 0 Specularspikeconstant = 1

In this case, the configuration is quite similar to the previous one, with a sigma alpha of 0. However, setting the specular spike constant to 1 ensures that if a reflection is to occur off the crystal boundary, the photon undergoes specular spike reflection. It can now be seen that the photons are either absorbed by the paint or undergo a specular spike reflection off the crystal boundary.

<img src="https://github.com/user-attachments/assets/47f43f47-1015-4e5c-90eb-31a89dcd9fc5" width="400"/>

## Reflectivity = 0 sigma_alpha = 0 Backscatterconstant = 1
This configuration simply features all reflected photons undergoing backscattering. The photons can either make it through to the paint and get absorbed or undergo backscattering, as shown by all the backscattered photon trajectories below.


<img src="https://github.com/user-attachments/assets/96e81e23-6e04-4533-88ac-276efadd43ef" width="400"/>

## Reflectivity = 1, sigma_alpha = 0, Rindex = 0.9

In this configuration, none of the photons are absorbed. Each photon undergoes a calculation to determine its trajectory: traveling through the volume, reaching the crystal–air gap interface, entering the gap, and then confronting the wrapper/paint.

The photon may undergo one of the four aforementioned types of reflection off the crystal boundary, as displayed by the various diverging trajectories. Alternatively, it may pass through to the air gap—courtesy of a calculation using Snell's law—undergo Lambertian reflection off the paint, interact with the crystal–air gap interface again (using Snell's law), and make its way back into the volume. Note how the trajectories are slightly more spread out in comparison to the PolishedBackPainted configuration due to the diffusive reflection off the "ground" paint.

Recall again that Rindex refers to the index of refraction of the crystal–air gap.

<img src="https://github.com/user-attachments/assets/c5066790-7eab-476d-af25-36e8b058e231" width="400"/>

## Reflectivity = 1, sigma_alpha = 0, specularspikeconstant = 1, rindex = 2.0

In this case, the photon traverses the volume at an angle and, if reflected off the crystal boundary, undergoes specular spike reflection. However, if it instead passes through the crystal–air gap and reaches the paint, it undergoes Lambertian reflection off the paint and then travels back through the crystal–air gap into the volume.

It can therefore be seen how the trajectories differ from the same configuration with the PolishedBackPainted finish. These differences arise because the reflection off the paint in this case is not a specular spike reflection, but rather a Lambertian reflection.

<img src="https://github.com/user-attachments/assets/45d2d0da-315b-4808-8bff-b32baa5177ae" width="400"/>

## Reflectivity = 1, sigma_alpha = 0, specularspikeconstant = 1, rindex = 0.9
This configuration is quite similar to the previous one, with only the index of refraction of the crystal–air gap altered. However, notice that now the photon trajectories don't showcase photons undergoing one of the four different types of reflection, but rather those that traverse through to the reflective paint, undergo specular spike reflection, and refract back into the volume itself. This configuration mostly shows the changes that the Rindex of the crystal–air gap can bring forth.

<img src="https://github.com/user-attachments/assets/18349257-8e03-4f88-83c5-dac95514808c" width="400"/>

## Reflectivity = 1, sigma_alpha = 30, rindex = 0.9 

This configuration features the optical photon trajectories given a rough crystal boundary, as indicated by a sigma value of 5.

<img src="https://github.com/user-attachments/assets/fd2d5107-8ba1-465a-9070-2eb70b250ee0" width="400"/>



[GEARS]: http://physino.xyz/gears
[tg]: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomASCII.html
[Geant4]: http://geant4.cern.ch
[GDML]: https://gdml.web.cern.ch/GDML/
[G4OpBoundaryProcess]: http://www-geant4.kek.jp/lxr/source//processes/optical/include/G4OpBoundaryProcess.hh
[PostStepDoIt]: http://www.apc.univ-paris7.fr/~franco/g4doxy4.10/html/class_g4_op_boundary_process.html#a70a65cc5127a05680a0c4679f8300871
[G4LogicalBorderSurface]: http://www-geant4.kek.jp/lxr/source/geometry/volumes/include/G4LogicalBorderSurface.hh
