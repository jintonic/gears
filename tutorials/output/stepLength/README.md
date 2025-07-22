A new macro command

```
/tracking/setStepLimit logical_volume_name length
```

is added in [GEARS] to specify the maximal step length in the unit of mm in volume "logical_volume_name".

According to [Geant4 Physics Reference Manual](https://geant4.web.cern.ch/documentation/dev/prm_html/PhysicsReferenceManual/generalities/particletransport/occurence.html), the next step size of a particle is the smallest among all possible interactions. For each interaction, a step size is randomly sampled using the mean free path of the interaction or by various step limitations established by different Geant4 components.

One can force Geant4 to create a step point by manually adding a volume boundary. Geant4 creates a step point on the boundary. One can also specify some [User Limits](https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/TrackingAndPhysics/userLimits.html), one of them is the maximal step length. In this case, one must register G4StepLimiterPhysics in the physics list as shown in the official example [B2].

User limits can ony be applied to individual logical volumes, they don't propagate to daughter volumes.

A step length limit only applies to charged particles, not neutral particles.

[B2]: https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Examples/BasicCodes.html#example-b2