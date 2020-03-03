// ROOT script to visualize gears.gdml
{
  TGeoManager::Import("gears.gdml");
  gGeoManager->GetTopVolume()->Draw();
}
// -*- c++ -*-
// vim: set ft=cpp:
