#include <G4String.hh>
#include <TFile.h>
#include <TTree.h>
#include <G4UImessenger.hh>
#include <G4Track.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIdirectory.hh>
#include <G4ParticleDefinition.hh>
const int MaxNhits=10000;
class Output:public G4UImessenger
{
  public:
    Output(): G4UImessenger()
    {
      fDir = new G4UIdirectory("/output/");
      fDir->SetGuidance("configure output");
      fFileCmd = new G4UIcmdWithAString("/output/setROOTfile",this);
      fFileCmd->SetGuidance("Set output ROOT file name.");
      fFileCmd->SetParameterName("fout",false);
      fFileCmd->AvailableForStates(G4State_PreInit);
    } 
    ~Output()
    { delete fFileCmd; delete fDir;};
    G4String fFileName;
    void SetNewValue(G4UIcommand* cmd, G4String value)
    { if (cmd==fFileCmd) fFileName = value; }
    void Open()
    {
      inidata();
      fFile=new TFile(fFileName.data(),"recreate","data");
      fTree=new TTree("atree","data");
      fTree->Branch("nd",nh,"nh/S");
      fTree->Branch("e",e,"e[nh]/D");
      fTree->Branch("t",t,"t[nh]/D");
      fTree->Branch("x",x,"x[nh]/D");
      fTree->Branch("y",y,"y[nh]/D");
      fTree->Branch("z",z,"z[nh]/D");
      fTree->Branch("did",did,"did[nh]/D");
      fTree->Branch("pid",pid,"pid[nh]/D");
    };
    void SetG4Track(G4Track *track){gt=track;};
    void WriteData()
    {
      did[nh]=(short)gt->GetNextVolume()->GetCopyNo();
      pid[nh]=gt->GetDefinition ()->GetPDGEncoding ();
      e[nh]=gt->GetTotalEnergy ();
      t[nh]=gt->GetGlobalTime();
      x[nh]=gt->GetPosition ().x();
      y[nh]=gt->GetPosition ().y();
      z[nh]=gt->GetPosition ().z();
      nh++;
    }
    void ClearData()
    {
      fTree->Fill();
      inidata();
    };
    void Close(){fFile->Close();};
    void inidata();
  private:
    G4UIcmdWithAString* fFileCmd;
    G4UIdirectory* fDir;
    TTree * fTree;
    TFile * fFile;
    G4Track * gt;
    short nh;
    short did[MaxNhits];
    int pid[MaxNhits];
    double e[MaxNhits];
    double t[MaxNhits];
    double x[MaxNhits];
    double y[MaxNhits];
    double z[MaxNhits];
};
void Output::inidata()
{
  for(int i=0;i<MaxNhits;i++)
  {
    e[i]=0;
    t[i]=0;
    x[i]=0;
    y[i]=0;
    z[i]=0;
    did[i]=0;
    pid[i]=0;
  }
}

#include <G4TransportationManager.hh>
#include <G4UIcmdWith3VectorAndUnit.hh>
#include <G4UniformMagField.hh>
#include <G4FieldManager.hh>
//______________________________________________________________________________
//
#include <G4tgrLineProcessor.hh>
#include <G4tgrVolumeMgr.hh>
#include <G4tgrFileReader.hh>
#include <G4tgbVolumeMgr.hh>
#include <G4tgbVolume.hh>
#include <G4OpticalSurface.hh>
#include <G4tgrMaterialSimple.hh>
struct LBS
{
  G4String name,v1,v2;
  G4OpticalSurface * ops;
  LBS * next;
}; 

class ExLineProcessor: public G4tgrLineProcessor{
  public:
    ~ExLineProcessor()
    {
      while(a)
      {
	LBS *b=a->next;
	delete a;
	a=b;
      }
    }
    G4bool ProcessLine(const std::vector< G4String > & wl );
    void setisa(bool a);
    bool getisa();
    LBS * getlbs();
    ExLineProcessor(){a=NULL;isa=false;};
    G4String gettarget(){return target;};
  private : 
    G4tgrVolumeMgr* mgr;
    G4String wl0;
    G4String target;
    bool isa;
    LBS * a;
};
#include <CLHEP/Units/SystemOfUnits.h>
#include <CLHEP/Units/PhysicalConstants.h>
#include <G4NistManager.hh>
#include <G4tgrUtils.hh>
G4MaterialPropertiesTable * CreateMaterialPropertiesTable(
    const std::vector< G4String > & wl,int k)
{
  G4MaterialPropertiesTable *properties = new G4MaterialPropertiesTable();
  for (size_t i=k;i<wl.size();i=i+1)
  {
    if (wl[i]=="const")
    {
      i++;
      properties -> AddConstProperty(wl[i], G4tgrUtils::GetDouble(wl[i+1]));
      i++;
    }
    else{
      G4String name = wl[i];
      G4int counter = G4UIcommand::ConvertToInt(wl[++i]);
      G4double *array1=new G4double[counter];
      G4double *array2=new G4double[counter];
      for (G4int j =0;j<counter;j++)
      {
	array1[j]=0;
	array2[j]=0;
      }
      for(G4int j =0;j<counter;j++)array1[j]=G4tgrUtils::GetDouble(wl[++i]);
      for(G4int j =0;j<counter;j++)array2[j]=G4tgrUtils::GetDouble(wl[++i]);
      properties->AddProperty(name,array1,array2,counter)->SetSpline(true);
      delete array1;
      delete array2;
    }
  }
  return properties;
}
void ExLineProcessor::setisa(bool q){isa=q;}
bool ExLineProcessor::getisa(){return isa;}
LBS * ExLineProcessor::getlbs(){return a;}
//add new tag "property"
//using: 
//:prop <new material name> <base material name> 
//      (if add a const property)const <new property name> <parameter>
//      (if not)<new name> <parameter array size> <two parameter array>
//multiple property acceptable
//
//new tag ":U"
//using: :U surfacename motherlogicalvolumname/firsttargetphysicalvolumename
//                      anothername propertyname
//      (if add a const property)const <new property name> <parameter>
//      (if not)<new name> <parameter array size> <two parameter array>
//multiple property acceptable

G4bool ExLineProcessor::ProcessLine(const std::vector< G4String > & wl)
{
  G4bool processed = G4tgrLineProcessor::ProcessLine( wl );
  if(processed) return true;

  G4String i0wl = wl[0];
  i0wl.toUpper();
  if(i0wl.substr(0,5) == ":PROP"  )
  {
    G4NistManager* man = G4NistManager::Instance();
    const G4Material *mid=(man -> FindOrBuildMaterial(wl[2]));
    G4Material *nmaterial=new G4Material(wl[1],mid->GetDensity(),
	mid,mid->GetState(),mid->GetTemperature(),mid->GetPressure());
    nmaterial->SetMaterialPropertiesTable(CreateMaterialPropertiesTable(wl,3));
    return true;
  } else if(i0wl == ":U" ) {
    setisa(true);
    LBS * b=new LBS;
    b->next=a;
    a=b;
    b->name=wl[1];
    b->v1=wl[2];
    b->v2=wl[3];
    b->ops= new G4OpticalSurface(wl[4]);
    b->ops->SetType(dielectric_dielectric);
    b->ops->SetModel(unified);
    b->ops->SetFinish(groundbackpainted);
    b->ops->SetSigmaAlpha(0.1);
    b->ops->SetMaterialPropertiesTable(CreateMaterialPropertiesTable(wl,5));
    return true;
  } else return false;
}
//-----------------------------------------------------------------------------
//tgb line processor replacement
#include <G4tgbDetectorBuilder.hh>
#include <G4LogicalBorderSurface.hh>
class ExTGRCDetectorBuilder : public G4tgbDetectorBuilder
{
  public :
    ~ExTGRCDetectorBuilder(){delete linepro;};
    const G4tgrVolume * ReadDetector();
    G4VPhysicalVolume * ConstructDetector(const G4tgrVolume* tgrVoltop);
  private :
    ExLineProcessor* linepro;
};
const G4tgrVolume * ExTGRCDetectorBuilder::ReadDetector()
{
  linepro = new ExLineProcessor;
  linepro ->setisa(false);
  G4tgrFileReader* tfr = G4tgrFileReader::GetInstance();
  tfr -> SetLineProcessor(linepro);
  tfr -> ReadFiles();
  G4tgrVolumeMgr* tgrVolmgr = G4tgrVolumeMgr::GetInstance();
  const G4tgrVolume* tgrVoltop = tgrVolmgr->GetTopVolume();
  return tgrVoltop;
}
//-----------------------------------------------------------------------------
void add(G4VPhysicalVolume* v1 , G4tgbVolumeMgr * tgbVolmgr, LBS * b)
{
  if(tgbVolmgr->GetTopPhysVol()->GetName()!=b->v2)
  {
    G4LogicalVolume * mom=tgbVolmgr->FindG4LogVol(b->v2.substr(0,
	  b->v2.find("/")));
    G4String target=b->v2.substr(b->v2.find("/")+1);
    for(int i=0;i<mom->GetNoDaughters();i++)
    {
      G4VPhysicalVolume * now=mom->GetDaughter(i);
      if (now->GetName()==target)
	new G4LogicalBorderSurface(b->name,v1,now,b->ops); 
    }
  }
  else 
      new G4LogicalBorderSurface(b->name,v1,tgbVolmgr->GetTopPhysVol(),b->ops);
}
//----------------------------------------------------------------------------
  G4VPhysicalVolume * 
ExTGRCDetectorBuilder::ConstructDetector( const G4tgrVolume* tgrVoltop )
{
  G4tgbVolumeMgr* tgbVolmgr = G4tgbVolumeMgr::GetInstance();
  tgbVolmgr->CopyVolumes();
  G4tgbVolume* tgbVoltop = tgbVolmgr->FindVolume( tgrVoltop->GetName() );
  tgbVoltop->ConstructG4Volumes( 0, (const G4LogicalVolume*)0 );
  G4VPhysicalVolume* physvol = tgbVolmgr->GetTopPhysVol();
#ifdef G4VERBOSE
  if( G4tgrMessenger::GetVerboseLevel() >= 1 )
  {
    G4cout << " G4tgbDetectorConstruction::ConstructDetector() - Volume: "
      << physvol->GetName() << G4endl;
  }
#endif
  if(!linepro->getisa())return physvol; 
  LBS * b=linepro->getlbs();
  while (b )
  {
    if(tgbVolmgr->GetTopPhysVol()->GetName()!=b->v1)
    {
      G4LogicalVolume *mom=tgbVolmgr->FindG4LogVol(b->v1.substr(0,
	    b->v1.find("/")));
      G4String target=b->v1.substr(b->v1.find("/")+1);
      for(int i=0;i<mom->GetNoDaughters();i++)
      {
	G4VPhysicalVolume * now=mom->GetDaughter(i);
	if (now->GetName()==target) add(now,tgbVolmgr,b);
      }
    }
    else  add(tgbVolmgr->GetTopPhysVol(),tgbVolmgr,b);
    b=b->next;
  }
  return physvol;
}
//------------------------------------------------------------------------------
#include <G4VUserDetectorConstruction.hh>
#include <G4tgrMessenger.hh>
class Detector : public G4VUserDetectorConstruction, public G4UImessenger
{
  public:
    Detector(): G4UImessenger()
    {  
      fFileCmd = new G4UIcmdWithAString("/geometry/textInput/file",this);
      fFileCmd->SetGuidance("Set input text file name.");
      fFileCmd->SetParameterName("fin",false);
      fFileCmd->AvailableForStates(G4State_PreInit);
    };
    Detector(const G4ThreeVector& value) : G4UImessenger()
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
    void SetNewValue(G4UIcommand* cmd, G4String value)
    {
      if (cmd==fSetCmd) {
	fField->SetFieldValue(fSetCmd->GetNew3VectorValue(value));
	fFieldManager->SetDetectorField(fField);
	fFieldManager->CreateChordFinder(fField);
	G4cout<<"Magnetic field is set to "<<value<<G4endl;
      }
      if (cmd==fFileCmd) FileName = value;
    };
    virtual ~Detector()
    { delete fDir; delete fSetCmd; delete fField; delete fFileCmd;}
    G4VPhysicalVolume* Construct();
    Output * out;
    G4String FileName;
  private:
    G4UIdirectory* fDir;
    G4UIcmdWith3VectorAndUnit* fSetCmd;
    G4UniformMagField* fField;
    G4FieldManager* fFieldManager;
    G4UIcmdWithAString* fFileCmd;
};
#include <G4LogicalVolume.hh>
#include <G4MaterialPropertiesTable.hh>
#include <G4Material.hh>
#include <G4tgrVolume.hh>
#include <G4tgrLineProcessor.hh>
G4VPhysicalVolume* Detector::Construct()
{
  G4tgbVolumeMgr* mgr = G4tgbVolumeMgr::GetInstance();
  mgr->AddTextFile(FileName);
  ExTGRCDetectorBuilder * gtb = new ExTGRCDetectorBuilder;
  mgr -> SetDetectorBuilder(gtb); 
  G4VPhysicalVolume * world = mgr->ReadAndConstructDetector();
  return world;
}
//______________________________________________________________________________
//

#include "G4VModularPhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"

class Physics: public G4VModularPhysicsList
{
  public:
    Physics() : G4VModularPhysicsList() {
      SetVerboseLevel(10);
      // modular physics lists are definded in g4 source/physics_lists
      RegisterPhysics(new G4DecayPhysics());
      RegisterPhysics(new G4RadioactiveDecayPhysics());
      RegisterPhysics(new G4EmStandardPhysics());
      RegisterPhysics(new G4OpticalPhysics());
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
#include <G4UserRunAction.hh>
class RunAction : public G4UserRunAction
{
  public:
    void BeginOfRunAction (const G4Run *aRun);
    void EndOfRunAction (const G4Run *aRun);
    Output * getout(){return out;};
    void setout(Output * o){out=o;};
  private:
    Output * out;
    double *e;
};
void RunAction::BeginOfRunAction(const G4Run * aRun){out->Open();}
void RunAction:: EndOfRunAction(const G4Run *aRun){ out->Close();}
//-----------------------------------------------------------------------------
#include <G4UserEventAction.hh>
class EventAction : public G4UserEventAction
{
  private:
    RunAction *u;
  public:
    void EndOfEventAction(const G4Event * anEvent);
    void setu(RunAction * r){u=r;};
};
void EventAction::EndOfEventAction(const G4Event * anEvent)
{u->getout()->ClearData();}
//-----------------------------------------------------------------------------
#include <G4UserTrackingAction.hh>
#include <G4ios.hh>
class TrackingAction : public G4UserTrackingAction
{
  public:
    void PostUserTrackingAction(const G4Track * );
    void setr(RunAction *u){ev=u;};
  private:
    G4String target;
    RunAction * ev;
};
void TrackingAction::PostUserTrackingAction(const G4Track * t)
{
  G4String tar;
  if(t->GetNextVolume())tar=t->GetNextVolume()->GetName();
  else tar="aaam";
  if(tar.substr(tar.length()-4)=="(S)")
  {
    ev->getout()->SetG4Track(t->GetStep()->GetTrack());
    ev->getout()->WriteData();
    t->GetStep()->GetTrack()->SetTrackStatus(G4TrackStatus::fStopAndKill);
  }
}
//-----------------------------------------------------------------------------
#include <G4RunManager.hh>
#include <QBBC.hh>
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>
#include <G4UImanager.hh> // needed for g4.10 and above

int main(int argc, char **argv)
{
  Output * out=new Output;
  Detector * d=new Detector();
  d->out=out; 
  G4RunManager* run = new G4RunManager;
  run->SetUserInitialization(d);
  run->SetUserInitialization(new Physics);
  run->SetUserAction(new Generator);
  RunAction *a=new RunAction();
  EventAction *b = new EventAction();
  TrackingAction *c =new TrackingAction();
  a->setout(out);
  b->setu(a);
  c->setr(a);
  run->SetUserAction(a);
  run->SetUserAction(b);
  run->SetUserAction(c);
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
  delete out;
  return 0;
}
