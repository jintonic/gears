#include <G4UImessenger.hh>
#include <G4UIcmdWithAString.hh>

class TextGeoInput : public G4UImessenger
{
   public:
      TextGeoInput();
      virtual ~TextGeoInput() { delete fFileCmd; }

      G4String FileName;
      void SetNewValue(G4UIcommand* cmd, G4String value)
      { if (cmd=fFileCmd) FileName = value; }

   private:
      G4UIcmdWithAString* fFileCmd;
};

TextGeoInput::TextGeoInput() : G4UImessenger()
{
   fFileCmd = new G4UIcmdWithAString("/geometry/textInput/file",this);
   fFileCmd->SetGuidance("Set input text file name.");
   fFileCmd->SetParameterName("fin",false);
}

//______________________________________________________________________________
//

#include <G4VUserDetectorConstruction.hh>
#include <G4tgbVolumeMgr.hh>
#include <G4tgrMessenger.hh>

class Detector : public G4VUserDetectorConstruction
{
   public:
      Detector();
      virtual ~Detector()
      { delete ftgrMessenger; delete fTextGeoInput; }

      G4VPhysicalVolume* Construct();

   private:
      G4tgrMessenger* ftgrMessenger;
      TextGeoInput* fTextGeoInput;
};

Detector::Detector() : G4VUserDetectorConstruction()
{ 
   ftgrMessenger = new G4tgrMessenger;
   fTextGeoInput = new TextGeoInput;
}

G4VPhysicalVolume* Detector::Construct()
{
  G4tgbVolumeMgr* mgr = G4tgbVolumeMgr::GetInstance();
  mgr->AddTextFile(fTextGeoInput->FileName);
  return mgr->ReadAndConstructDetector();
}

//______________________________________________________________________________
//

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4GeneralParticleSource.hh>

class Generator : public G4VUserPrimaryGeneratorAction
{
   public:
      Generator()
         : G4VUserPrimaryGeneratorAction(), fSource(0)
      { fSource = new G4GeneralParticleSource; }
      virtual ~Generator() { delete fSource; }

      virtual void GeneratePrimaries(G4Event* evt)
      { fSource->GeneratePrimaryVertex(evt); }

   private:
      G4GeneralParticleSource* fSource;
};

//______________________________________________________________________________
//

#include <G4RunManager.hh>
#include <QBBC.hh>
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>

int main(int argc, char **argv)
{
   G4RunManager* run = new G4RunManager;

   run->SetUserInitialization(new Detector);
   run->SetUserInitialization(new QBBC);
   run->SetUserAction(new Generator);

   G4VisManager* vis = new G4VisExecutive;
   vis->Initialize();

   if (argc!=1)  {
      G4String exe = "/control/execute ";
      G4String macro = argv[1];
      G4UImanager::GetUIpointer()->ApplyCommand(exe+macro);
   } else {
      G4UIExecutive *ui = new G4UIExecutive(argc,argv);
      ui->SessionStart();
      delete ui;
   }

   delete run;
   return 0;
}
