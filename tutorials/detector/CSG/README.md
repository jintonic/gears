This folder contains demos of all CSG solids that can be handled by Geant4 text geometry description. A shape, sphere for example, is defined in [sphere.tg](sphere.tg). To visualize it, please run

```sh
G4VIS_DEFAULT_DRIVER=HepRepFile gears sphere.mac
```

The environment variable `G4VIS_DEFAULT_DRIVER` can be used to select a visualization driver other than the default one.

