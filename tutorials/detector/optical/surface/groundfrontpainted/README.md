[![YouTube](https://img.shields.io/badge/You-Tube-red?style=flat)](https://youtu.be/sgo-RPbDRcU)
[![optical processes](https://img.shields.io/badge/optical-processes-blue?style=flat)](../../physics#optical-processes)

The finish GroundFrontPainted represents a volume with a painted surface. The reflectivity 
𝑅 defines the probability that an optical photon is reflected by the painted surface. More specifically, it is defined as 1 minus the absorption coefficient. The optical photon may or may not be absorbed by the paint. The paint is modeled through surface properties. When not absorbed, the photon undergoes Lambertian reflection. No refraction occurs.


## Naming convention for example files
r - Reflectivity
<br>
t - transmittance 
<br>

## Example Parameters for r0t0.tg

~~~cpp

// optical properties of the surface between CsI & Teflon
:surf CsI2Teflon CsI:1 Teflon:2
  type dielectric_dielectric
  model unified	
  finish groundfrontpainted
  property photon_energies 2 2.5*eV 5.0*eV
           REFLECTIVITY      0      0
           TRANSMITTANCE     0      0

~~~

Initially, a random number is generated. If the random number is greater than the sum of REFLECTIVITY and TRANSMITTANCE, the photon is absorbed. If the random number is not greater than the sum but is greater than REFLECTIVITY alone, the photon is transmitted. If the random number is not greater than REFLECTIVITY, the usual scattering calculation is performed.

Below are screenshots demonstrating different view configurations:

### r0t0  
![r0t0](https://github.com/user-attachments/assets/5fd1ddb5-a69b-4a81-8b4b-797dbfec878e)

### r0t1  
![r01](https://github.com/user-attachments/assets/8b43542b-8da5-4da0-98ac-531a4b42a866)

### r05t05  
![r05t05](https://github.com/user-attachments/assets/a95ea882-0cdb-4ce8-b239-b1f475b0f1a9)

### r1t0  
![r10](https://github.com/user-attachments/assets/edfb7c23-392d-4267-b6e1-ae4bfd1b90b9)


[GEARS]: http://physino.xyz/gears
[tg]: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomASCII.html
[Geant4]: http://geant4.cern.ch
[GDML]: https://gdml.web.cern.ch/GDML/
[G4OpBoundaryProcess]: http://www-geant4.kek.jp/lxr/source//processes/optical/include/G4OpBoundaryProcess.hh
[PostStepDoIt]: http://www.apc.univ-paris7.fr/~franco/g4doxy4.10/html/class_g4_op_boundary_process.html#a70a65cc5127a05680a0c4679f8300871
[G4LogicalBorderSurface]: http://www-geant4.kek.jp/lxr/source/geometry/volumes/include/G4LogicalBorderSurface.hh
