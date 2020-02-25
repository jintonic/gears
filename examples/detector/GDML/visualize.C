// ROOT script to visualize hall.gdml
{
  TGeoManager::Import("gears.gdml");
  gGeoManager->GetTopVolume()->Draw();
}
// -*- c++ -*-
// vim: set ft=cpp:
