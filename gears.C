#include <G4UImessenger.hh>
#include <G4UIcmdWithAString.hh>

class TextGeoInput : public G4UImessenger
{
   public:
      TextGeoInput();
      ~TextGeoInput() { delete fFileCmd; }

      G4String FileName;
      void SetNewValue(G4UIcommand* cmd, G4String value)
      { if (cmd==fFileCmd) FileName = value; }

   private:
      G4UIcmdWithAString* fFileCmd;
};

TextGeoInput::TextGeoInput() : G4UImessenger()
{
   fFileCmd = new G4UIcmdWithAString("/geometry/textInput/file",this);
   fFileCmd->SetGuidance("Set input text file name.");
   fFileCmd->SetParameterName("fin",false);
   fFileCmd->AvailableForStates(G4State_PreInit);
}

//______________________________________________________________________________
//

#include <G4UIdirectory.hh>
#include <G4UIcmdWith3VectorAndUnit.hh>
#include <G4UniformMagField.hh>
#include <G4FieldManager.hh>

class MagneticField : public G4UImessenger
{
   public:
      MagneticField(const G4ThreeVector& value = G4ThreeVector());
      ~MagneticField() { delete fDir; delete fSetCmd; delete fField; }

      void SetNewValue(G4UIcommand* cmd, G4String value)
      {
         if (cmd==fSetCmd) {
            fField->SetFieldValue(fSetCmd->GetNew3VectorValue(value));
            fFieldManager->SetDetectorField(fField);
            fFieldManager->CreateChordFinder(fField);
            G4cout<<"Magnetic field is set to "<<value<<G4endl;
         }
      }

   private:
      G4UIdirectory* fDir;
      G4UIcmdWith3VectorAndUnit* fSetCmd;
      G4UniformMagField* fField;
      G4FieldManager* fFieldManager;
};

#include <G4TransportationManager.hh>

MagneticField::MagneticField(const G4ThreeVector& value) : G4UImessenger()
{
   fDir = new G4UIdirectory("/field/");
   fDir->SetGuidance("Global uniform field UI commands");

   fSetCmd = new G4UIcmdWith3VectorAndUnit("/field/setM",this);
   fSetCmd->SetGuidance("Set uniform magnetic field value.");
   fSetCmd->SetParameterName("Bx", "By", "Bz", false);
   fSetCmd->SetUnitCategory("Magnetic flux density");
   fSetCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

   fFieldManager = 
      G4TransportationManager::GetTransportationManager()->GetFieldManager();
   fField = new G4UniformMagField(value);
   fFieldManager->SetDetectorField(fField);
   fFieldManager->CreateChordFinder(fField);
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
      { delete ftgrMessenger; delete fTextGeoInput; delete fMagneticField; }

      G4VPhysicalVolume* Construct();

   private:
      MagneticField* fMagneticField;
      G4tgrMessenger* ftgrMessenger;
      TextGeoInput* fTextGeoInput;
};

Detector::Detector() : G4VUserDetectorConstruction()
{ 
   ftgrMessenger = new G4tgrMessenger;
   fTextGeoInput = new TextGeoInput;
   fMagneticField = new MagneticField;
}

G4VPhysicalVolume* Detector::Construct()
{
   G4tgbVolumeMgr* mgr = G4tgbVolumeMgr::GetInstance();
   mgr->AddTextFile(fTextGeoInput->FileName);
   return mgr->ReadAndConstructDetector();
}

//______________________________________________________________________________
//

#include "G4VModularPhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"

class Physics: public G4VModularPhysicsList
{
   public:
      Physics() : G4VModularPhysicsList() {
         SetVerboseLevel(10);
         RegisterPhysics(new G4DecayPhysics());
         RegisterPhysics(new G4RadioactiveDecayPhysics());
         RegisterPhysics(new G4EmStandardPhysics());
      }
      virtual ~Physics() {};
};

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
#include <G4UImanager.hh> // needed for g4.10 and above

int main(int argc, char **argv)
{
   G4RunManager* run = new G4RunManager;

   run->SetUserInitialization(new Detector);
   run->SetUserInitialization(new Physics);
   run->SetUserAction(new Generator);

   G4VisManager* vis = new G4VisExecutive;
   vis->SetVerboseLevel(0);
   vis->Initialize();

   if (argc!=1)  {
      G4String exe = "/control/execute ";
      G4String macro = argv[1];
      G4UImanager::GetUIpointer()->ApplyCommand(exe+macro);
   } else {
      // check available UI automatically in the order of Qt, tsch, Xm
      G4UIExecutive *ui = new G4UIExecutive(argc,argv);
      ui->SessionStart();
      delete ui;
   }

   delete vis;
   delete run;
   return 0;
}
