/**
 * \mainpage notitle
 * Homepage: <http://physino.xyz/gears>
 */
#include <vector>
using namespace std;
#include <g4root.hh>
#include <G4SteppingVerbose.hh>
#include <G4SteppingManager.hh>
/**
 * Output simulation results to screen or a file.
 */
class Output : public G4SteppingVerbose
{
  protected:
    void Record(); ///< Record simulated data
  public:
    Output(); ///< Create analysis manager to handle output
    ~Output() { delete G4AnalysisManager::Instance(); }
    void TrackingStarted() { G4SteppingVerbose::TrackingStarted();
      Record(); } ///< Information of step 0 (initStep)
    void StepInfo() { G4SteppingVerbose::StepInfo();
      Record(); } ///< Information of steps>0 
    void Reset() { trk.clear(); stp.clear(); vlm.clear(); pro.clear();
      pdg.clear(); pid.clear(); xx.clear(); yy.clear(); zz.clear(); dt.clear();
      de.clear(); dl.clear(); l.clear(); x.clear(); y.clear(); z.clear();
      t.clear(); k.clear(); p.clear(); q.clear(); et.clear(); }
    void SetSteppingVerbose(int level) { fManager->SetVerboseLevel(level); }
    int GetSteppingVerbose() { return fManager->GetverboseLevel(); }

    vector<int> trk;   ///< track ID
    vector<int> stp;   ///< step number
    vector<int> vlm;   ///< volume copy number
    vector<int> pro;   ///< process ID * 100 + sub-process ID
    vector<int> pdg;   ///< PDG encoding
    vector<int> pid;   ///< parent particle's PDG encoding
    vector<double> xx; ///< x [mm] (origin: center of local volume)
    vector<double> yy; ///< y [mm] (origin: center of local volume)
    vector<double> zz; ///< z [mm] (origin: center of local volume)
    vector<double> dt; ///< time elapsed from previous step point [ns]
    vector<double> de; ///< energy deposited [keV]
    vector<double> dl; ///< step length [mm]
    vector<double> l;  ///< length of track till this point [mm]
    vector<double> x;  ///< x [mm] (origin: center of the world)
    vector<double> y;  ///< y [mm] (origin: center of the world)
    vector<double> z;  ///< z [mm] (origin: center of the world)
    vector<double> t;  ///< time elapsed from the beginning of an event [ns]
    vector<double> k;  ///< kinetic energy [keV]
    vector<double> p;  ///< momentum [keV]
    vector<double> q;  ///< charge [elementary charge]
    vector<double> et; ///< Total energy deposited in a volume [keV]
};
//______________________________________________________________________________
//
Output::Output(): G4SteppingVerbose()
{
  auto manager = G4AnalysisManager::Instance();
  manager->CreateNtuple("t", "Geant4 step points");
  manager->CreateNtupleIColumn("n"); // total number of recorded hits
  manager->CreateNtupleIColumn("m"); // max copy number of sensitive volume
  manager->CreateNtupleIColumn("trk", trk);
  manager->CreateNtupleIColumn("stp", stp);
  manager->CreateNtupleIColumn("vlm", vlm);
  manager->CreateNtupleIColumn("pro", pro);
  manager->CreateNtupleIColumn("pdg", pdg);
  manager->CreateNtupleIColumn("pid", pid);
  manager->CreateNtupleDColumn("xx", xx);
  manager->CreateNtupleDColumn("yy", yy);
  manager->CreateNtupleDColumn("zz", zz);
  manager->CreateNtupleDColumn("dt", dt);
  manager->CreateNtupleDColumn("de", de);
  manager->CreateNtupleDColumn("dl", dl);
  manager->CreateNtupleDColumn("l", l);
  manager->CreateNtupleDColumn("x", x);
  manager->CreateNtupleDColumn("y", y);
  manager->CreateNtupleDColumn("z", z);
  manager->CreateNtupleDColumn("t", t);
  manager->CreateNtupleDColumn("k", k);
  manager->CreateNtupleDColumn("p", p);
  manager->CreateNtupleDColumn("q", q);
  manager->CreateNtupleDColumn("et", et);
  manager->FinishNtuple();
}
//______________________________________________________________________________
//
#include <G4NavigationHistory.hh>
void Output::Record()
{
  if (GetSilent()==1) // CopyState() won't be called in G4SteppingVerbose
    CopyState(); // point fTrack, fStep, etc. to right places

  G4TouchableHandle handle = fStep->GetPreStepPoint()->GetTouchableHandle();
  int copyNo=handle->GetReplicaNumber();
  if (copyNo<=0) return; //skip uninteresting volumes (copy No. of world == 0)
  if (trk.size()>=10000) {
    G4cout<<"GEARS: # of step points >=10000. Recording stopped."<<G4endl;
    fTrack->SetTrackStatus(fKillTrackAndSecondaries);
    return;
  }

  trk.push_back(fTrack->GetTrackID());
  stp.push_back(fTrack->GetCurrentStepNumber());
  vlm.push_back(copyNo);
  pdg.push_back(fTrack->GetDefinition()->GetPDGEncoding());
  pid.push_back(fTrack->GetParentID());
  if (stp.back()==0) { // step zero
    if (pid.back()!=0) // not primary particle
      pro.push_back(fTrack->GetCreatorProcess()->GetProcessType()*1000
          + fTrack->GetCreatorProcess()->GetProcessSubType());
    else pro.push_back(1000); // primary particle
  } else {
    const G4VProcess *pr = fStep->GetPostStepPoint()->GetProcessDefinedStep();
    if (pr) pro.push_back(pr->GetProcessType()*1000 + pr->GetProcessSubType());
    else pro.push_back(900); // not sure why pr can be zero
  }

  k.push_back(fTrack->GetKineticEnergy()/CLHEP::keV);
  p.push_back(fTrack->GetMomentum().mag()/CLHEP::keV);
  q.push_back(fStep->GetPostStepPoint()->GetCharge());
  l.push_back(fTrack->GetTrackLength()/CLHEP::mm);

  de.push_back(fStep->GetTotalEnergyDeposit()/CLHEP::keV);
  dl.push_back(fTrack->GetStepLength()/CLHEP::mm);

  t.push_back(fTrack->GetGlobalTime()/CLHEP::ns);
  x.push_back(fTrack->GetPosition().x()/CLHEP::mm);
  y.push_back(fTrack->GetPosition().y()/CLHEP::mm);
  z.push_back(fTrack->GetPosition().z()/CLHEP::mm);

  G4ThreeVector pos = handle->GetHistory()->GetTopTransform()
    .TransformPoint(fStep->GetPostStepPoint()->GetPosition());
  xx.push_back(pos.x()/CLHEP::mm);
  yy.push_back(pos.y()/CLHEP::mm);
  zz.push_back(pos.z()/CLHEP::mm);
  dt.push_back(fTrack->GetLocalTime()/CLHEP::ns);

  if (de.back()>0 && handle->GetVolume()->GetName().contains("(S)")) {
    if (et.size()<(unsigned int)copyNo+1) et.resize((unsigned int)copyNo+1);
    et[copyNo]+=de.back(); et[0]+=de.back();
  }
}
//______________________________________________________________________________
//
#include <G4OpticalSurface.hh>
/**
 * A link list of G4LogicalBorderSurface.
 * It is used to save information provided by the :surf tag in the text
 * geometry description, for constructing a G4LogicalBorderSurface later.
 */
struct BorderSurface
{
  G4String name; ///< name of the surface
  G4String v1;   ///< name of volume 1
  G4String v2;   ///< name of volume 2
  G4OpticalSurface* optic; ///< point to G4OpticalSurface object
  BorderSurface* next; ///< link to next border surface
}; 
//______________________________________________________________________________
//
#include <G4tgrLineProcessor.hh>
/**
 * Extension to default text geometry file line processor.
 */
class LineProcessor: public G4tgrLineProcessor
{
  private:
    G4MaterialPropertiesTable* CreateMaterialPropertiesTable(
        const vector<G4String> &words, size_t idxOfWords);
  public:
    LineProcessor(): G4tgrLineProcessor(), Border(0) {};
    ~LineProcessor() {
      while (Border) { // deleting G4OpticalSurface is done in Geant4
        BorderSurface *next=Border->next;
        delete Border;
        Border=next;
      }
    }
    /**
     * Overwrite G4tgrLineProcessor::ProcessLine to add new tags.
     *
     * Two new tags are added: ":PROP" and ":SURF" (case insensitive):
     * - ":prop" is used to add optical properties to a material
     * - ":surf" is used to define an optical surface
     *
     * The function is called for each new line.  Be sure to insert an
     * end-of-line character by typing <Enter> at the end of the last line,
     * otherwise, the last line will not be processed.
     */
    G4bool ProcessLine(const vector<G4String> &words);
    BorderSurface* Border; ///< pointer to a BorderSurface object
};
//______________________________________________________________________________
//
#include <G4NistManager.hh>
#include <G4tgbMaterialMgr.hh>
#include <G4UImessenger.hh>
G4bool LineProcessor::ProcessLine(const vector<G4String> &words)
{
  // process default text geometry tags
  G4bool processed = G4tgrLineProcessor::ProcessLine(words);
  if (processed) return true; // no new tags involved

  // process added tags: prop & surf
  G4String tag = words[0];
  tag.toLower(); // to lower cases
  if (tag.substr(0,5)==":prop") { // set optical properties of a material
    G4NistManager *mgr = G4NistManager::Instance(); mgr->SetVerbose(2);
    G4Material *m = mgr->FindOrBuildMaterial(words[1]);
    if (m==NULL) // if not in NIST, then build in tgb
      m=G4tgbMaterialMgr::GetInstance()->FindOrBuildG4Material(words[1]);
    G4cout<<"GEARS: Set optical properties of "<<words[1]<<":"<<G4endl;
    m->SetMaterialPropertiesTable(CreateMaterialPropertiesTable(words,2));
    return true;
  } else if (tag.substr(0,5)==":surf") { // define an optical surface
    BorderSurface *bdr = new BorderSurface;
    bdr->next=Border; // save current border pointer
    Border=bdr; // overwrite current border pointer
    bdr->name=words[1];
    bdr->v1=words[2];
    bdr->v2=words[3];
    bdr->optic = new G4OpticalSurface(words[1]);
    size_t i=4; 
    // loop over optical surface setup lines
    while (i<words.size()) {
      G4String setting = words[i], value = words[i+1];
      setting.toLower(); value.toLower();
      if (setting=="property") {
        i++;
        break;
      } else if(setting=="type") {
        if (value=="dielectric_metal")
          bdr->optic->SetType(dielectric_metal);
        else if(value=="dielectric_dielectric")
          bdr->optic->SetType(dielectric_dielectric);
        else if(value=="firsov") bdr->optic->SetType(firsov);
        else if(value=="x_ray") bdr->optic->SetType(x_ray);
        else G4cout<<"GERAS: Ignore unknown surface type "<<value<<G4endl;
      } else if(setting=="model") {
        if (value=="glisur") bdr->optic->SetModel(glisur);
        else if(value=="unified") bdr->optic->SetModel(unified);
        else G4cout<<"GERAS: Ignore unknown surface model "<<value<<G4endl;
      } else if(setting=="finish") {
        if(value=="polished") bdr->optic->SetFinish(polished);
        else if(value=="polishedfrontpainted")
          bdr->optic->SetFinish(polishedfrontpainted);
        else if(value=="polishedbackpainted")
          bdr->optic->SetFinish(polishedbackpainted);
        else if(value=="ground") bdr->optic->SetFinish(ground);
        else if(value=="groundfrontpainted")
          bdr->optic->SetFinish(groundfrontpainted);
        else if(value=="groundbackpainted")
          bdr->optic->SetFinish(groundbackpainted);
        else
          G4cout<<"GERAS: Ignore unknown surface finish "<<value<<G4endl;
      } else if(setting=="sigma_alpha") {
        bdr->optic->SetSigmaAlpha(G4UIcommand::ConvertToInt(value));
      } else
        G4cout<<"GERAS: Ignore unknown surface setting "<<value<<G4endl;
      i+=2;
    }
    if (i<words.size()) { // break while loop because of "property"
      G4cout<<"GEARS: Set optical properties of "<<bdr->name<<":"<<G4endl;
      bdr->optic->SetMaterialPropertiesTable(
          CreateMaterialPropertiesTable(words,i));
    }
    return true;
  } else
    return false;
}
//______________________________________________________________________________
//
#include <G4tgrUtils.hh>
G4MaterialPropertiesTable* LineProcessor::CreateMaterialPropertiesTable(
    const vector<G4String> &words, size_t idxOfWords)
{
  bool photonEnergyUnDefined=true;
  int cnt=0; // number of photon energy values
  double *energies=NULL; // photon energy values
  G4MaterialPropertiesTable *table = new G4MaterialPropertiesTable();
  for (size_t i=idxOfWords; i<words.size(); i++) {
    G4String property = words[i]; property.toUpper();
    if (property.contains("SCINTILLATIONYIELD") || property=="RESOLUTIONSCALE"
        || property.contains("FASTTIMECONSTANT") || property=="YIELDRATIO") {
      table->AddConstProperty(property, G4tgrUtils::GetDouble(words[i+1]));
      G4cout<<"GEARS: "<<property<<"="<<words[i+1]<<G4endl;
      i++; // property value has been used
    } else if (property.substr(0,12)=="PHOTON_ENERG") {
      photonEnergyUnDefined=false;
      cnt = G4UIcommand::ConvertToInt(words[i+1]); // get array size
      energies = new double[cnt]; // create energy array
      for (int j=0; j<cnt; j++)
        energies[j]=G4tgrUtils::GetDouble(words[i+2+j]);
      i=i+1+cnt; // array has been used
    } else { // wavelength-dependent properties
      if (photonEnergyUnDefined) {
        G4cout<<"GEARS: photon energies undefined, "
          <<"ignore all wavelength-dependent properties!"<<G4endl;
        break;
      }
      double *values = new double[cnt];
      for (int j=0; j<cnt; j++) 
        values[j]=G4tgrUtils::GetDouble(words[i+1+j]);
      G4cout<<"GEARS: "<<property<<"="<<values[0]<<", "
        <<values[1]<<"..."<<G4endl;
      table->AddProperty(property, energies, values, cnt);
      delete[] values;
      i=i+cnt;
    }
  }
  delete[] energies;
  return table;
}
//______________________________________________________________________________
//
#include <G4tgbDetectorBuilder.hh>
/**
 * Construct detector based on text geometry description.
 */
class TextDetectorBuilder : public G4tgbDetectorBuilder
{
  public :
    TextDetectorBuilder() :
      G4tgbDetectorBuilder() { fLineProcessor = new LineProcessor(); }
    ~TextDetectorBuilder() { delete fLineProcessor; }
    const G4tgrVolume* ReadDetector(); ///< Read text geometry input
    /**
     * Construct detector based on text geometry description.
     */
    G4VPhysicalVolume* ConstructDetector(const G4tgrVolume* topVol);

  private :
    LineProcessor* fLineProcessor; ///< Process individual lines in a tg file
};
//______________________________________________________________________________
//
#include <G4tgrVolumeMgr.hh>
#include <G4tgrFileReader.hh>
#include <G4tgbVolumeMgr.hh>
const G4tgrVolume* TextDetectorBuilder::ReadDetector()
{
  G4tgrFileReader* reader = G4tgrFileReader::GetInstance();
  reader->SetLineProcessor(fLineProcessor);
  reader->ReadFiles();
  G4tgrVolumeMgr* mgr = G4tgrVolumeMgr::GetInstance();
  const G4tgrVolume* world = mgr->GetTopVolume();
  return world;
}
//______________________________________________________________________________
//
#include <G4LogicalBorderSurface.hh>
G4VPhysicalVolume* TextDetectorBuilder::ConstructDetector(
    const G4tgrVolume* topVol)
{
  G4VPhysicalVolume *world = G4tgbDetectorBuilder::ConstructDetector(topVol);

  G4tgbVolumeMgr* tgbVolmgr = G4tgbVolumeMgr::GetInstance();
  BorderSurface* border = fLineProcessor->Border;
  while (border) {
    G4String physV1 = border->v1.substr(0,border->v1.find(":"));
    G4String physV2 = border->v2.substr(0,border->v2.find(":"));
    int copyNo1 = atoi(border->v1.substr(border->v1.find(":")+1).data());
    int copyNo2 = atoi(border->v2.substr(border->v2.find(":")+1).data());
    G4LogicalVolume *m1=tgbVolmgr->FindG4PhysVol(physV1)->GetMotherLogical();
    G4LogicalVolume *m2=tgbVolmgr->FindG4PhysVol(physV2)->GetMotherLogical();
    // search for physics volumes on the sides of the border
    G4VPhysicalVolume *v1=0, *v2=0;
    for (int i=0; i<(int)m1->GetNoDaughters(); i++) {
      v1 = m1->GetDaughter(i);
      if (v1->GetCopyNo()==copyNo1) break;
    }
    for (int i=0; i<(int)m2->GetNoDaughters(); i++) {
      v2 = m2->GetDaughter(i);
      if (v2->GetCopyNo()==copyNo2) break;
    }
    if (v1 && v2) {
      new G4LogicalBorderSurface(border->name,v1,v2,border->optic);
      G4cout<<"Border surface "<<border->name<<" in between "
        <<physV1<<":"<<copyNo1<<" and "<<physV2<<":"<<copyNo2
        <<" added"<<G4endl;
    }
    border=border->next;
  }
  return world;
}
//______________________________________________________________________________
//
#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWith3VectorAndUnit.hh>
#include <G4VUserDetectorConstruction.hh>
/**
 * Construct detector geometry.
 *
 * This uses two types of instructions to construct a detector: 
 *
 * - [Geant4 text geometry](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomASCII.html)
 * - [GDML](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomXML.html)
 *
 * It won't work together with HP neutron simulation if Geant4 version is lower
 * than 10 because of this bug:
 * http://hypernews.slac.stanford.edu/HyperNews/geant4/get/hadronprocess/1242.html?inline=-1
 */
class Detector : public G4VUserDetectorConstruction, public G4UImessenger
{
  public:
    Detector();
    ~Detector() { delete fCmdSetB; delete fCmdSrc; delete fCmdOut; }
    G4VPhysicalVolume* Construct(); ///< called at /run/initialize
    void SetNewValue(G4UIcommand* cmd, G4String value); ///< for G4UI

  private:
    G4UIcmdWith3VectorAndUnit* fCmdSetB; ///< /field/setB
    G4UIcmdWithAString* fCmdSrc; ///< /geometry/source
    G4UIcmdWithAString* fCmdOut; ///< /geometry/export
    G4VPhysicalVolume * fWorld;
};
//______________________________________________________________________________
//
Detector::Detector(): G4VUserDetectorConstruction(), G4UImessenger(), fWorld(0)
{
#ifdef hasGDML
  fCmdOut = new G4UIcmdWithAString("/geometry/export",this);
  fCmdOut->SetGuidance("Export geometry gdml file name");
  fCmdOut->SetParameterName("gdml geometry output",false);
  fCmdOut->AvailableForStates(G4State_Idle);
#else
  fCmdOut=0;
#endif

  fCmdSrc = new G4UIcmdWithAString("/geometry/source",this);
  fCmdSrc->SetGuidance("Set geometry source file name");
  fCmdSrc->SetParameterName("text geometry input",false);
  fCmdSrc->AvailableForStates(G4State_PreInit);

  fCmdSetB = new G4UIcmdWith3VectorAndUnit("/geometry/SetB",this);
  fCmdSetB->SetGuidance("Set uniform magnetic field value.");
  fCmdSetB->SetParameterName("Bx", "By", "Bz", false);
  fCmdSetB->SetUnitCategory("Magnetic flux density");
}
//______________________________________________________________________________
//
#include <G4FieldManager.hh>
#include <G4UniformMagField.hh>
#include <G4TransportationManager.hh>
#ifdef hasGDML
#include "G4GDMLParser.hh"
#endif
void Detector::SetNewValue(G4UIcommand* cmd, G4String value)
{
  if (cmd==fCmdSetB) {
    G4UniformMagField* field = new G4UniformMagField(0,0,0);
    field->SetFieldValue(fCmdSetB->GetNew3VectorValue(value));
    G4FieldManager* mgr = 
      G4TransportationManager::GetTransportationManager()->GetFieldManager();
    mgr->SetDetectorField(field);
    mgr->CreateChordFinder(field);
    G4cout<<"GEARS: Magnetic field is set to "<<value<<G4endl;
#ifdef hasGDML
  } else if(cmd==fCmdOut) {
    G4GDMLParser paser;
    paser.Write(value,fWorld);
#endif
  } else { // cmd==fCmdSrc
    if (value.substr(value.length()-4)!="gdml") { // text geometry input
      G4tgbVolumeMgr* mgr = G4tgbVolumeMgr::GetInstance();
      mgr->AddTextFile(value);
      TextDetectorBuilder * tgb = new TextDetectorBuilder;
      mgr->SetDetectorBuilder(tgb); 
      fWorld = mgr->ReadAndConstructDetector();
#ifdef hasGDML
    } else { // GDML input
      G4GDMLParser parser;
      parser.Read(value);
      fWorld=parser.GetWorldVolume();
#endif
    }
  }
}
//______________________________________________________________________________
//
#include "G4Box.hh"
#include "G4PVPlacement.hh"
G4VPhysicalVolume* Detector::Construct()
{
  if (fWorld==NULL) {
    G4cout<<"GEARS: no detector specified, set to a 10x10x10 m^3 box."<<G4endl;
    G4Box* box = new G4Box("hall", 5*CLHEP::m, 5*CLHEP::m, 5*CLHEP::m);
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *vacuum = nist->FindOrBuildMaterial("G4_Galactic");
    G4LogicalVolume *v = new G4LogicalVolume(box, vacuum, "hall");
    fWorld = new G4PVPlacement(0, G4ThreeVector(), v, "hall", 0, 0, 0);
  }
  return fWorld;
}
//______________________________________________________________________________
//
#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4GeneralParticleSource.hh>
/**
 * Call Geant4 General Particle Source to generate particles.
 */
class Generator : public G4VUserPrimaryGeneratorAction
{
  private:
    G4GeneralParticleSource* fSource;
  public:
    Generator()
      : G4VUserPrimaryGeneratorAction(), fSource(0)
    { fSource = new G4GeneralParticleSource; }
    virtual ~Generator() { delete fSource; }
    virtual void GeneratePrimaries(G4Event* evt)
    { fSource->GeneratePrimaryVertex(evt); } ///< add sources to an event
};
//______________________________________________________________________________
//
#include <G4UserRunAction.hh>
#include <G4Run.hh>
/**
 * Book keeping before and after a run.
 */
class RunAction : public G4UserRunAction
{
  public:
    void BeginOfRunAction (const G4Run*) { 
      auto a = G4AnalysisManager::Instance(); if (a->GetFileName()=="") return; 
      a->OpenFile();
      Output* o = ((Output*) G4VSteppingVerbose::GetInstance()); 
      if (o->GetSteppingVerbose()==0) { // in case of /tracking/verbose 0
        o->SetSilent(1); // avoid screen dump
        o->SetSteppingVerbose(1);//enable calling StepInfo() in G4SteppingManager
      }
    } ///< enable output if output file name is not empty
    void EndOfRunAction (const G4Run*) {
      auto a = G4AnalysisManager::Instance();
      if (a->GetFileName()!="") { a->Write(); a->CloseFile(); }
    }  ///< Close output file
};
//______________________________________________________________________________
//
void SaveAndResetEvent()
{
  auto a = G4AnalysisManager::Instance();
  Output* o = ((Output*) G4VSteppingVerbose::GetInstance()); 
  if (a->GetFileName()!="" && o->stp.size()!=0) {
    a->FillNtupleIColumn(0,o->stp.size());
    a->FillNtupleIColumn(1,o->et.size()-1);
    a->AddNtupleRow();
  } // save n-tuple if it is not empty and output file name is specified
  o->Reset(); // reset Output member variables for new record
} ///< save and then reset an event
//______________________________________________________________________________
//
#include <G4UserEventAction.hh>
/**
 * Book keeping before and after an event.
 */
class EventAction : public G4UserEventAction
{ public: void EndOfEventAction(const G4Event*) { SaveAndResetEvent(); } };
//______________________________________________________________________________
//
#include <G4UserStackingAction.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
/**
 * Split a radioactive decay chain to different events based on a time window.
 */
class StackingAction : public G4UserStackingAction, public G4UImessenger
{
  private:
    double fT0; ///< reference time for splitting decay chain
    double fTimeWindow; ///< time window to split a decay chain
    G4UIcmdWithADoubleAndUnit *fCmdT; ///< UI cmd to set time window
  public:
    StackingAction() : G4UserStackingAction(), G4UImessenger(),
    fT0(0), fTimeWindow(0), fCmdT(0) {
      fCmdT = new G4UIcmdWithADoubleAndUnit("/grdm/setTimeWindow", this);
      fCmdT->SetGuidance("Time window to split a radioactive decay chain.");
      fCmdT->SetGuidance("If a daughter nucleus appears after the window,");
      fCmdT->SetGuidance("it is saved in a new entry in the output ntuple.");
      fCmdT->SetGuidance("---Set it to <=0 to disable the splitting---");
      fCmdT->SetParameterName("time window",false,true);
      fCmdT->SetDefaultUnit("s");
      fCmdT->AvailableForStates(G4State_PreInit, G4State_Idle);
    } ///< created macro /grdm/setTimeWindow
    ~StackingAction() { delete fCmdT; }
    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track *trk) { 
      if (fTimeWindow<=0) return fUrgent; // no need to split
      if (trk->GetGlobalTime()>fT0+fTimeWindow) return fWaiting; // split
      else return fUrgent; // too fast to be split
    } ///< send a daughter particle to waiting stack if it appears too late
    void NewStage() { // called after processing urgent trk, before waiting trk
      if (fTimeWindow<=0) return; // do nothing if no time window is specified
      Output* o = ((Output*) G4VSteppingVerbose::GetInstance()); 
      fT0 = o->t.back(); // update the reference time to the latest decay time
      SaveAndResetEvent(); // end an event manually
    } ///< save and reset output before processing waiting tracks
    void SetNewValue(G4UIcommand* cmd, G4String value)
    { if (cmd!=fCmdT) return; fTimeWindow = fCmdT->GetNewDoubleValue(value); }
};
//______________________________________________________________________________
//
#include <G4RunManager.hh>
#include <G4StateManager.hh>
#include <G4PhysListFactory.hh>
/**
 * Place to put all building blocks together.
 */
class RunManager : public G4RunManager, public G4UImessenger
{
  private:
    G4PhysListFactory* fFactory; ///< tool to construct a ref. list by its name
    G4UIcmdWithAString* fCmdPhys; ///< macro cmd to select a physics list
  public:
    RunManager() : G4RunManager(), G4UImessenger(), fFactory(0) {
      SetUserInitialization(new Detector); // needed for /run/initialize
      fCmdPhys = new G4UIcmdWithAString("/physics_lists/select",this);
      fCmdPhys->SetGuidance("Select a physics list");
      fCmdPhys->SetGuidance("Candidates are specified in G4PhysListFactory.cc");
      fCmdPhys->SetParameterName("name of a physics list", false);
      fCmdPhys->AvailableForStates(G4State_PreInit);
    }
    ~RunManager() { delete fCmdPhys; delete fFactory; }

    void SetNewValue(G4UIcommand* cmd, G4String value) {
      if (cmd!=fCmdPhys || fFactory) return;
      fFactory = new G4PhysListFactory;
      if (fFactory->IsReferencePhysList(value)==false) {
        G4cout<<"GEARS: no physics list \""<<value
          <<"\", set to \"QGSP_BERT\""<<G4endl;
        value = "QGSP_BERT"; // default
      }
      SetUserInitialization(fFactory->GetReferencePhysList(value));
    } ///< for UI

    void InitializePhysics() {
      if (fFactory==NULL) { // no /physics_lists/select is used
        fFactory = new G4PhysListFactory;
        G4StateManager::GetStateManager()->SetNewState(G4State_PreInit);
        // has to be called in PreInit state:
        SetUserInitialization(fFactory->GetReferencePhysList("QGSP_BERT"));
      }
      G4RunManager::InitializePhysics(); // call the original function
      // has to be called after physics initialization
      SetUserAction(new Generator);
      SetUserAction(new RunAction);
      SetUserAction(new EventAction);
      SetUserAction(new StackingAction);
    } ///< set physics list if it is not specified explicitly
};
//______________________________________________________________________________
//
#include <G4ScoringManager.hh>
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>
#include <G4UImanager.hh> // needed for g4.10 and above
/**
 * The main function that calls individual components.
 */
int main(int argc, char **argv)
{
  // inherit G4SteppingVerbose instead of G4UserSteppingAction to record data
  G4VSteppingVerbose::SetInstance(new Output); // must be before run manager
  RunManager* run = new RunManager; // customized run control
  G4ScoringManager::GetScoringManager(); // enable built-in scoring cmds
  G4VisManager* vis = new G4VisExecutive("quiet"); // visualization
  vis->Initialize();
  // select mode of execution
  if (argc!=1)  { // batch mode
    G4String cmd = "/control/execute ";
    G4UImanager::GetUIpointer()->ApplyCommand(cmd+argv[1]);
  } else { // interactive mode
    // check available UI automatically in the order of Qt, tsch, Xm
    G4UIExecutive *ui = new G4UIExecutive(argc,argv);
    ui->SessionStart();
    delete ui;
  }
  // clean up
  delete vis; delete run;
  return 0;
}
// -*- C++; indent-tabs-mode:nil; tab-width:2 -*-
// vim: ft=cpp:ts=2:sts=2:sw=2:et
