/**
 * \file gears.C
 *
 * The only C++ file in this project.
 *
 * Everything is placed in one file intentionally to simplify management.
 */
const int MaxNpnt=20000; ///< Max number of track points that can be recorded
const int MaxNdet=100; ///< Max number of detectors that can be handled
#include <TFile.h>
#include <TTree.h>
#include <G4SteppingVerbose.hh>
#include <G4UImessenger.hh>
#include <G4UIcmdWithAString.hh>
/**
 * Output simulation results to screen or a file.
 */
class Output : public G4SteppingVerbose, public G4UImessenger
{
   public:
      Output();
      ~Output() { delete fCmd; }
      void TrackingStarted(); ///< Infomation of step 0 (initStep)
      void StepInfo()
      { G4SteppingVerbose::StepInfo(); Record(); } ///< Infomation of step > 0 
      void Reset(); ///< Reset record variables
      void SetNewValue(G4UIcommand* cmd, G4String value); ///< for G4UI

      short n; ///< Number of track points
      short trk[MaxNpnt]; ///< track id
      short stp[MaxNpnt]; ///< step number
      short det[MaxNpnt]; ///< detector volume copy number
      short pro[MaxNpnt]; ///< process id * 100 + sub-process id
      int pdg[MaxNpnt]; ///< particle PDG encoding
      int mom[MaxNpnt]; ///< parent particle's PDG encoding
      double e[MaxNpnt]; ///< energy deposited [keV]
      double k[MaxNpnt]; ///< kinetic energy of the track [keV]
      double t[MaxNpnt]; ///< time [ns]
      double x[MaxNpnt]; ///< x [mm]
      double y[MaxNpnt]; ///< y [mm]
      double z[MaxNpnt]; ///< z [mm]

      short nd; ///< Number of detectors
      double ed[MaxNdet]; ///< Total energy deposited in each detector [keV]

      TFile* File; ///< ROOT output file
      TTree* Tree; ///< ROOT tree to save output

   private:
      void Record(); ///< Record simulated data
      G4UIcmdWithAString* fCmd; ///< UI command to set output file name
};
//______________________________________________________________________________
//
Output::Output(): G4SteppingVerbose(), G4UImessenger(), File(0), Tree(0)
{
   fCmd = new G4UIcmdWithAString("/run/output",this);
   fCmd->SetGuidance("Set output file name");
   fCmd->SetParameterName("output file name",false);
}
//______________________________________________________________________________
//
void Output::TrackingStarted()
{
   // print to screen
   G4SteppingVerbose::TrackingStarted(); // fulfill its designed functionality
   // save to file
   if(n>=MaxNpnt) {
      G4cout<<"Number of records >= "<<MaxNpnt<<", stop recording."<<G4endl;
      fTrack->SetTrackStatus(fKillTrackAndSecondaries);
      return;
   }
   Record();
}
//______________________________________________________________________________
//
void Output::Record()
{
   if (Silent==1) CopyState(); // point fTrack, fStep, etc. to right places
   trk[n] = fTrack->GetTrackID();
   stp[n] = fTrack->GetCurrentStepNumber();
   det[n] = fTrack->GetVolume()->GetCopyNo();
   pdg[n] = fTrack->GetDefinition()->GetPDGEncoding();
   mom[n] = fTrack->GetParentID();
   if (stp[n]==0) {
      if (mom[n]!=0)
         pro[n] = fTrack->GetCreatorProcess()->GetProcessType()*1000
            + fTrack->GetCreatorProcess()->GetProcessSubType();
   } else {
      const G4VProcess *p = fStep->GetPostStepPoint()->GetProcessDefinedStep();
      pro[n] = p->GetProcessType()*1000 + p->GetProcessSubType();
   }
   e[n] = fStep->GetTotalEnergyDeposit()/CLHEP::keV;
   k[n] = fTrack->GetKineticEnergy()/CLHEP::keV;
   t[n] = fTrack->GetGlobalTime()/CLHEP::ns;
   x[n] = fTrack->GetPosition().x()/CLHEP::mm;
   y[n] = fTrack->GetPosition().y()/CLHEP::mm;
   z[n] = fTrack->GetPosition().z()/CLHEP::mm;
   if (e[n]>0 && fTrack->GetVolume()->GetName().contains("(S)")) {
      ed[det[n]]+=e[n];
      if (det[n]>=nd) nd=det[n]+1;
   }
   n++;
}
//______________________________________________________________________________
//
void Output::Reset()
{
   n=nd=0;
   for (int i=0; i<MaxNpnt; i++) {
      trk[i]=stp[i]=det[i]=pro[i]=pdg[i]=mom[i]=-1;
      e[i]=k[i]=t[i]=x[i]=y[i]=z[i]=0.;
   }
   for (int i=0; i<MaxNdet; i++) ed[i]=0;
}
//______________________________________________________________________________
//
void Output::SetNewValue(G4UIcommand* cmd, G4String value)
{
   if (cmd==fCmd && File==0) {
      File = new TFile(value.data(),"recreate");
      Tree = new TTree("t","simulated samples");
      Tree->Branch("n",&n,"n/S");
      Tree->Branch("trk",trk,"trk[n]/S");
      Tree->Branch("stp",stp,"stp[n]/S");
      Tree->Branch("det",det,"det[n]/S");
      Tree->Branch("pro",pro,"pro[n]/S");
      Tree->Branch("pdg",pdg,"pdg[n]/I");
      Tree->Branch("mom",mom,"mom[n]/I");
      Tree->Branch("e",e,"e[n]/D");
      Tree->Branch("k",k,"k[n]/D");
      Tree->Branch("t",t,"t[n]/D");
      Tree->Branch("x",x,"x[n]/D");
      Tree->Branch("y",y,"y[n]/D");
      Tree->Branch("z",z,"z[n]/D");
      Tree->Branch("nd",&nd,"nd/S");
      Tree->Branch("ed",ed,"ed[nd]/D");
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
   public:
      LineProcessor(): G4tgrLineProcessor(), Border(0) {};
      ~LineProcessor();
      /**
       * Overwrite G4tgrLineProcessor::ProcessLine to add new tags.
       * Two new tags are added: ":PROP" and ":SURF".
       */
      G4bool ProcessLine(const std::vector<G4String> &words);

      BorderSurface* Border; ///< pointer to a BorderSurface object

   private:
      G4MaterialPropertiesTable* CreateMaterialPropertiesTable(
            const std::vector<G4String> &words, size_t idxOfWords);
};
//______________________________________________________________________________
//
LineProcessor::~LineProcessor()
{
   while (Border) { // the G4OpticalSurface should be taken care by Geant4
      BorderSurface *next=Border->next;
      delete Border;
      Border=next;
   }
}
//______________________________________________________________________________
//
#include <G4NistManager.hh>
G4bool LineProcessor::ProcessLine(const std::vector<G4String> &words)
{
   // process default text geometry tags
   G4bool processed = G4tgrLineProcessor::ProcessLine(words);
   if (processed) return true;

   // process added tags
   G4String tag = words[0];
   tag.toLower();
   if (tag.substr(0,5)==":prop") {
      G4NistManager* mgr = G4NistManager::Instance();
      G4cout<<"Set optical properties of "<<words[1]<<":"<<G4endl;
      mgr->FindOrBuildMaterial(words[1])
         ->SetMaterialPropertiesTable(CreateMaterialPropertiesTable(words,2));
      return true;
   } else if (tag.substr(0,5)==":surf") {
      BorderSurface *bdr = new BorderSurface;
      bdr->next=Border;
      Border=bdr;
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
            else G4cout<<"Unknown surface type "<<value<<", ignored!"<<G4endl;
         } else if(setting=="model") {
            if (value=="glisur") bdr->optic->SetModel(glisur);
            else if(value=="unified") bdr->optic->SetModel(unified);
            else G4cout<<"Unknown surface model "<<value<<", ignored!"<<G4endl;
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
               G4cout<<"Unknown surface finish "<<value<<", ignored!"<<G4endl;
         } else if(setting=="sigma_alpha") {
            bdr->optic->SetSigmaAlpha(G4UIcommand::ConvertToInt(value));
         } else
            G4cout<<"Unknown surface setting "<<setting<<", ignored!"<<G4endl;
         i+=2;
      }
      if (i<words.size()) { // break while loop because of "property"
         G4cout<<"Set optical properties of "<<bdr->name<<":"<<G4endl;
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
      const std::vector<G4String> &words, size_t idxOfWords)
{
   bool photonEnergyUnDefined=true;
   int cnt=0; // number of photon energy values
   double *energies; // photon energy values
   G4MaterialPropertiesTable *table = new G4MaterialPropertiesTable();
   for (size_t i=idxOfWords; i<words.size(); i++) {
      G4String property = words[i]; property.toUpper();
      if (property=="SCINTILLATIONYIELD" || property=="RESOLUTIONSCALE"
            || property=="FASTTIMECONSTANT" || property=="SLOWTIMECONSTANT"
            || property=="YIELDRATIO" || property=="WLSTIMECONSTANT") {
         table->AddConstProperty(property, G4tgrUtils::GetDouble(words[i+1]));
         G4cout<<property<<"="<<words[i+1]<<G4endl;
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
            G4cout<<"photon energies undefined, "
               <<"ignore all wavelength-dependent properties!"<<G4endl;
            break;
         }
         double *values = new double[cnt];
         for (int j=0; j<cnt; j++) 
            values[j]=G4tgrUtils::GetDouble(words[i+1+j]);
         G4cout<<property<<"="<<values[0]<<", "<<values[1]<<"..."<<G4endl;
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
      TextDetectorBuilder() { fLineProcessor = new LineProcessor(); }
      ~TextDetectorBuilder() { delete fLineProcessor; }
      const G4tgrVolume* ReadDetector(); ///< Read text geometry input
      /**
       * Construct detector based on text geometry description.
       */
      G4VPhysicalVolume* ConstructDetector(const G4tgrVolume* topVol);

   private :
      LineProcessor* fLineProcessor;
};
//______________________________________________________________________________
//
#include <G4tgrVolumeMgr.hh>
#include <G4tgrFileReader.hh>
#include <G4tgbVolumeMgr.hh>
const G4tgrVolume * TextDetectorBuilder::ReadDetector()
{
   G4tgrFileReader* fileReader = G4tgrFileReader::GetInstance();
   fileReader->SetLineProcessor(fLineProcessor);
   fileReader->ReadFiles();
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
      // search for phyiscs volumes on the sides of the border
      G4VPhysicalVolume *v1=0, *v2=0;
      for (int i=0; i<m1->GetNoDaughters(); i++) {
         v1 = m1->GetDaughter(i);
         if (v1->GetCopyNo()==copyNo1) break;
      }
      for (int i=0; i<m2->GetNoDaughters(); i++) {
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
#include <G4VUserDetectorConstruction.hh>
#include <G4TransportationManager.hh>
#include <G4UIcmdWith3VectorAndUnit.hh>
#include <G4UIdirectory.hh>
#include <G4UniformMagField.hh>
#include <G4FieldManager.hh>
/**
 * Construct detector geometry.
 *
 * This uses Geant4 text geometry to construct a detector: 
 * http://geant4.cern.ch/geant4/collaboration/working_groups/geometry/docs/textgeom/textgeom.pdf
 *
 * It won't work together with HP neutron simulation if Geant4 version is lower
 * than 10 because of this bug:
 * http://hypernews.slac.stanford.edu/HyperNews/geant4/get/hadronprocess/1242.html?inline=-1
 */
class Detector : public G4VUserDetectorConstruction, public G4UImessenger
{
   public:
      Detector();
      ~Detector()
      { delete fDir; delete fCmdSetM; delete fCmdSrc; delete fField; }
      G4VPhysicalVolume* Construct(); ///< Construct detector
      void SetNewValue(G4UIcommand* cmd, G4String value); ///< for G4UI

   private:
      G4String fGeomSrcText;

      G4UIdirectory *fDir;
      G4UIcmdWith3VectorAndUnit* fCmdSetM;
      G4UIcmdWithAString* fCmdSrc;
      G4UniformMagField* fField;
};
//______________________________________________________________________________
//
Detector::Detector(): G4UImessenger()
{
   fCmdSrc = new G4UIcmdWithAString("/geometry/source",this);
   fCmdSrc->SetGuidance("Set geometry source file name");
   fCmdSrc->SetParameterName("text geometry input",false);
   fCmdSrc->AvailableForStates(G4State_PreInit);

   fDir = new G4UIdirectory("/field/");
   fDir->SetGuidance("Global uniform field UI commands");

   fCmdSetM = new G4UIcmdWith3VectorAndUnit("/field/setM",this);
   fCmdSetM->SetGuidance("Set uniform magnetic field value.");
   fCmdSetM->SetParameterName("Bx", "By", "Bz", false);
   fCmdSetM->SetUnitCategory("Magnetic flux density");

   fField = new G4UniformMagField(0,0,0);
}
//______________________________________________________________________________
//
void Detector::SetNewValue(G4UIcommand* cmd, G4String value)
{
   if (cmd==fCmdSetM) {
      fField->SetFieldValue(fCmdSetM->GetNew3VectorValue(value));
      G4FieldManager* mgr = 
         G4TransportationManager::GetTransportationManager()->GetFieldManager();
      mgr->SetDetectorField(fField);
      mgr->CreateChordFinder(fField);
      G4cout<<"Magnetic field is set to "<<value<<G4endl;
   } else if (cmd==fCmdSrc) fGeomSrcText = value;
}
//______________________________________________________________________________
//
G4VPhysicalVolume* Detector::Construct()
{
   G4tgbVolumeMgr* mgr = G4tgbVolumeMgr::GetInstance();
   mgr->AddTextFile(fGeomSrcText);
   TextDetectorBuilder * gtb = new TextDetectorBuilder;
   mgr->SetDetectorBuilder(gtb); 
   G4VPhysicalVolume* world = mgr->ReadAndConstructDetector();
   return world;
}
//______________________________________________________________________________
//
#include "G4VModularPhysicsList.hh"
/**
 * Enable physics lists.
 * Physics lists have to be enabled when Geant4 is at PreInit state. All UI
 * commands defined here have to be put before /run/Initialize in a mac file.
 */
class Physics: public G4VModularPhysicsList, public G4UImessenger
{
   public:
      Physics();
      ~Physics() { delete fCmd; }
      void SetNewValue(G4UIcommand* cmd, G4String value); ///< for G4UI
   private:
      G4UIcmdWithAString* fCmd;
};
//______________________________________________________________________________
//
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
Physics::Physics() : G4VModularPhysicsList(), G4UImessenger()
{
   fCmd = new G4UIcmdWithAString("/physics_lists/enable",this);
   fCmd->SetGuidance("Enable a certain physics list");
   fCmd->SetParameterName("name of a physics list", false);
   fCmd->SetCandidates("Optical HadronElastic HadronInelastic");
   fCmd->AvailableForStates(G4State_PreInit);

   RegisterPhysics(new G4DecayPhysics()); // defined many particles
   RegisterPhysics(new G4RadioactiveDecayPhysics());
   RegisterPhysics(new G4EmStandardPhysics()); // must be after RadioactiveDecay
}
//______________________________________________________________________________
//
#include "G4OpticalPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh" // won't work for Geant4 version<10
void Physics::SetNewValue(G4UIcommand* cmd, G4String value)
{
   if (cmd==fCmd) {
      if (value=="Optical") RegisterPhysics(new G4OpticalPhysics());
      else if (value=="HadronElastic")
         RegisterPhysics(new G4HadronElasticPhysicsHP());
      else if (value=="HadronInelastic")
         RegisterPhysics(new G4HadronPhysicsFTFP_BERT_HP());
   }
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
   public:
      Generator()
         : G4VUserPrimaryGeneratorAction(), fSource(0)
      { fSource = new G4GeneralParticleSource; }
      virtual ~Generator() { delete fSource; }
      virtual void GeneratePrimaries(G4Event* evt)
      { fSource->GeneratePrimaryVertex(evt); } ///< add sources to an event
   private:
      G4GeneralParticleSource* fSource;
};
//______________________________________________________________________________
//
#include <G4UserRunAction.hh>
/**
 * Book keeping before and after a run.
 */
class RunAction : public G4UserRunAction
{
   public:
      RunAction() : G4UserRunAction() {};
      void BeginOfRunAction (const G4Run* run);///< Print # of evts
      void EndOfRunAction (const G4Run* run); ///< Close output file
};
//______________________________________________________________________________
//
#include <G4Run.hh>
void RunAction::BeginOfRunAction (const G4Run* run)
{ 
   G4cout<<run->GetNumberOfEventToBeProcessed()
      <<" events to be processed"<<G4endl;
}
//______________________________________________________________________________
//
void RunAction::EndOfRunAction (const G4Run* run)
{
   G4cout<<"In total, "<<run->GetNumberOfEvent()<<" events simulated"<<G4endl;
   Output *o = (Output*) G4VSteppingVerbose::GetInstance();
   o->File->Write("", TObject::kOverwrite);
   o->File->Close();
}
//______________________________________________________________________________
//
#include <G4UserEventAction.hh>
#include "G4UIcmdWithAnInteger.hh"
/**
 * Book keeping before and after an event.
 */
class EventAction : public G4UserEventAction, public G4UImessenger
{
   public:
      EventAction();
      ~EventAction() { delete fCmd; }
      void BeginOfEventAction(const G4Event*); ///< Prepare for recording
      void EndOfEventAction(const G4Event* event); ///< Fill tree
      void SetNewValue(G4UIcommand* cmd, G4String value)
      { if (cmd==fCmd) fN2report=atoi(value); } ///< for G4UI
   private:
      int fN2report;///< Number of events to report
      G4UIcmdWithAnInteger* fCmd;
};
//______________________________________________________________________________
//
EventAction::EventAction()
   : G4UserEventAction(), G4UImessenger(), fN2report(1000)
{
   fCmd = new G4UIcmdWithAnInteger("/run/statusReport",this);
   fCmd->SetGuidance("enable status report after [number of events]");
   fCmd->SetParameterName("number of events",true);
   fCmd->SetDefaultValue(fN2report);
}
//______________________________________________________________________________
//
#include <G4EventManager.hh>
void EventAction::BeginOfEventAction(const G4Event*)
{
   // turn on the use of G4SteppingVerbose for recording, but silently
   if (fpEventManager->GetTrackingManager()->GetVerboseLevel()==0) {
      fpEventManager->GetTrackingManager()->SetVerboseLevel(1);
      G4VSteppingVerbose::GetInstance()->SetSilent(1);
   }
   // reset Output member variables for new record
   ((Output*) G4VSteppingVerbose::GetInstance())->Reset(); 
}
//______________________________________________________________________________
//
void EventAction::EndOfEventAction(const G4Event* event)
{
   Output *o = (Output*) G4VSteppingVerbose::GetInstance();
   o->Tree->Fill();
   int id=event->GetEventID()+1;
   if (id%fN2report==0) G4cout<<id<<" events simulated"<<G4endl;
}
//______________________________________________________________________________
//
#include <G4RunManager.hh>
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
   // initialize necessary components for simulation
   G4RunManager* run = new G4RunManager;
   run->SetUserInitialization(new Detector);
   run->SetUserInitialization(new Physics);
   run->SetUserAction(new Generator);
   run->SetUserAction(new RunAction);
   run->SetUserAction(new EventAction);
   // enable visualization of detector and tracks
   G4VisManager* vis = new G4VisExecutive;
   //vis->SetVerboseLevel(0); // suppress list of vis engines
   vis->Initialize();
   // run simulation
   if (argc!=1)  { // run from command line
      G4String exe = "/control/execute ";
      G4String macro = argv[1];
      G4UImanager::GetUIpointer()->ApplyCommand(exe+macro);
   } else { // run with an UI
      // check available UI automatically in the order of Qt, tsch, Xm
      G4UIExecutive *ui = new G4UIExecutive(argc,argv);
      ui->SessionStart();
      delete ui;
   }
   // clean up
   delete vis;
   delete run;
   return 0;
}
