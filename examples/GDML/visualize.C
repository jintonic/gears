{
  TGeoManager::Import("hall.gdml");
  gGeoManager->GetTopVolume()->Draw();
}
