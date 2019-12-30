// ROOT script to visualize hall.gdml
{
  TGeoManager::Import("hall.gdml");
  gGeoManager->GetTopVolume()->Draw();
}
// -*- c++ -*-
// vim: set ft=cpp:
