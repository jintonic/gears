/**
 * \file gears.C
 *
 * The only C++ file in this project.
 *
 * Everything is placed inside this file intentionally to simplify the
 * makefile.
 */
const int MaxNhit=20000; ///< Max number of hits that can be recorded
const int MaxNsrc=1000; ///< Max number of sources that can be handled
const int MaxNdet=100; ///< Max number of detectors that can be handled

#include <TFile.h>
#include <TTree.h>

#include <G4PrimaryVertex.hh>
#include <G4Track.hh>
#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithAString.hh>
/**
 * Save simulation results to a file.
 */
class Output: public G4UImessenger
{
   public:
      Output();
      ~Output() { delete fCmdFile; delete fDir; delete fFile; }

      void Open(); ///< Open output file and define data structure
      void Record(G4PrimaryVertex* vtx); ///< Record source info
      /**
       * Record track info.
       * Process types are defined in G4ProcessType.hh, sub types are defined
       * in G4HadronicProcessType.hh, G4DecayProcessType.hh,
       * G4EmProcessSubType.hh.  G4TransportationProcessType.hh,
       * G4FastSimulationProcessType.hh,
       */
      void Record(G4Track *track);
      void Write() { fTree->Fill(); Reset(); }
      void Close() { fFile->Write(); fFile->Close(); }

      void SetNewValue(G4UIcommand* cmd, G4String value) ///< for G4UI
      { if (cmd==fCmdFile) fFileName = value; }

      int nh; ///< number of hits
      int ns; ///< number of primary particles (source)
      int nd; ///< number of detectors (sensitive volumes)
      short det[MaxNhit]; ///< detector id
      int pid[MaxNhit]; ///< particle id
      int par[MaxNhit]; ///< parent id
      int trk[MaxNhit]; ///< track id
      int pro[MaxNhit]; ///< process id * 100 + sub-process id
      double e[MaxNhit]; ///< energy deposited [keV]
      double et[MaxNdet]; ///< total energy deposited in each detector [keV]
      double t[MaxNhit]; ///< time of hit [ns]
      double x[MaxNhit]; ///< x of hit [mm]
      double y[MaxNhit]; ///< y of hit [mm]
      double z[MaxNhit]; ///< z of hit [mm]
      double es[MaxNsrc]; ///< initial energy of primary particle [keV]
      double ts[MaxNsrc]; ///< time of primary particle emitted [ns]
      double xs[MaxNsrc]; ///< x of primary particle emitting point [mm]
      double ys[MaxNsrc]; ///< y of primary particle emitting point [mm]
      double zs[MaxNsrc]; ///< z of primary particle emitting point [mm]

   private:
      void Reset(); ///< Reset track record

      TTree* fTree;
      TFile* fFile;
      G4String fFileName; ///< output file name

      G4UIdirectory* fDir;
      G4UIcmdWithAString* fCmdFile;
};
//______________________________________________________________________________
//
Output::Output(): G4UImessenger()
{
   Reset(); // reset track record

   fDir = new G4UIdirectory("/output/");
   fDir->SetGuidance("Configure output");

   fCmdFile = new G4UIcmdWithAString("/output/file",this);
   fCmdFile->SetGuidance("Set output file name");
   fCmdFile->SetParameterName("output file name",false);
} 
//______________________________________________________________________________
//
void Output::Open()
{
   fFile=new TFile(fFileName.data(),"recreate","data");
   fTree=new TTree("t","simulated samples");

   fTree->Branch("nh",&nh,"nh/S");
   fTree->Branch("ns",&ns,"ns/S");
   fTree->Branch("nd",&nd,"nd/S");
   fTree->Branch("et",&et,"et/D");
   fTree->Branch("e",e,"e[nh]/D");
   fTree->Branch("t",t,"t[nh]/D");
   fTree->Branch("x",x,"x[nh]/D");
   fTree->Branch("y",y,"y[nh]/D");
   fTree->Branch("z",z,"z[nh]/D");
   fTree->Branch("det",det,"det[nh]/S");
   fTree->Branch("pid",pid,"pid[nh]/I");
   fTree->Branch("pro",&pro,"pro[nh]/I");
   fTree->Branch("par",par,"par[nh]/I");
   fTree->Branch("trk",trk,"trk[nh]/I");
   fTree->Branch("es",es,"es[ns]/D");
   fTree->Branch("ts",ts,"ts[ns]/D");
   fTree->Branch("xs",xs,"xs[ns]/D");
   fTree->Branch("ys",ys,"ys[ns]/D");
   fTree->Branch("zs",zs,"zs[ns]/D");
}
//______________________________________________________________________________
//
#include <G4PrimaryParticle.hh>
#include <CLHEP/Units/SystemOfUnits.h>
void Output::Record(G4PrimaryVertex* vtx)
{
   G4PrimaryParticle * particle = vtx->GetPrimary(0);
   while (particle) {
      xs[ns] = vtx->GetX0()/CLHEP::cm;
      ys[ns] = vtx->GetY0()/CLHEP::cm;
      zs[ns] = vtx->GetZ0()/CLHEP::cm;
      ts[ns] = vtx->GetT0()/CLHEP::ns;
      G4ThreeVector P = particle->GetMomentum()/CLHEP::keV;
      G4double M = particle->GetMass()/CLHEP::keV;
      if (P.mag() < M/100) es[ns] = P.mag2()/(2*M);
      else es[ns] = sqrt(P.mag2()+M*M)-M; // relativistic
      ns++;
      particle = particle->GetNext();
   }
}
//______________________________________________________________________________
//
#include <G4VProcess.hh>
void Output::Record(G4Track *track)
{
   if (nh>=MaxNhit) {
      G4cout<<"Output::Record: "
         <<"Total number of hits >= max capacity "<<MaxNhit<<G4endl;
      G4cout<<"Output::Record: Hit "<<nh<<" won't be recorded"<<G4endl;
   } else {
      det[nh]= track->GetVolume()->GetCopyNo();
      pid[nh]=track->GetDefinition()->GetPDGEncoding();
      e[nh]=track->GetStep()->GetTotalEnergyDeposit()/CLHEP::keV;
      t[nh]=track->GetGlobalTime()/CLHEP::ns;
      x[nh]=track->GetPosition().x()/CLHEP::mm;
      y[nh]=track->GetPosition().y()/CLHEP::mm;
      z[nh]=track->GetPosition().z()/CLHEP::mm;
      par[nh]=track->GetParentID();
      trk[nh]=track->GetTrackID();
      if (track->GetCreatorProcess()) 
         pro[nh]=track->GetCreatorProcess()->GetProcessType()*1000
            + track->GetCreatorProcess()->GetProcessSubType();
      et[det[nh]]+=e[nh];
      if (det[nh]>=nd) nd = det[nh]+1;
   }
   if(nh>=10000)track->SetTrackStatus(fKillTrackAndSecondaries);
   nh++;
}
//______________________________________________________________________________
//
void Output::Reset()
{
   for (int i=0; i<MaxNhit; i++) {
      e[i]=0; t[i]=0; x[i]=0; y[i]=0; z[i]=0;
      det[i]=0; pid[i]=0; par[i]=0; trk[i]=0;
   }
   for (int i=0;i<MaxNsrc;i++) {
      es[i]=0; ts[i]=0; xs[i]=0; ys[i]=0; zs[i]=0;
   }
   for (int i=0;i<MaxNdet;i++) et[i]=0;
   nh=0; ns=0; nd=0;
}
//______________________________________________________________________________
//
#include <G4tgrLineProcessor.hh>
#include <G4tgrVolumeMgr.hh>
#include <G4tgrFileReader.hh>
#include <G4tgrMaterialSimple.hh>

#include <G4tgbVolumeMgr.hh>
#include <G4tgbVolume.hh>

#include <G4OpticalSurface.hh>

struct SurfaceList // Link list of all G4LogicalBorderSurface
{
   G4String name,v1,v2; // name of the surface, volume 1 and volume 2
   G4OpticalSurface* optic;
   SurfaceList* next;
}; 

/**
 * Geant4 text geometry file line processor.
 */
class LineProcessor: public G4tgrLineProcessor
{
   public:
      LineProcessor(): Surface(0) {};
      ~LineProcessor();
      /*
       * Overwrite G4tgrLineProcessor::ProcessLine to add new tags.
       */
      G4bool ProcessLine(const std::vector<G4String> &words);

      SurfaceList* Surface;

   private:
      G4MaterialPropertiesTable* CreateMaterialPropertiesTable(
            const std::vector<G4String> &words, int idx);
};
//______________________________________________________________________________
//
LineProcessor::~LineProcessor()
{
   while(Surface) {
      SurfaceList *next=Surface->next;
      delete Surface;
      Surface=next;
   }
}
//______________________________________________________________________________
//
#include <G4NistManager.hh>
/**
 * New tag ":PROP" (multiple property acceptable)
 * :prop <original material> 
 *    <new property> const <value> or
 *    (before none const property) energy <arraysize> <energies array> 
 *    <new property> <property array>
 * 
 * new tag ":SURF" (multiple property acceptable)
 * :surf name [motherVol/]physVol1 [motherVol/]physVol2
 *    type <dielectric_dielectric|dielectric_metal>
 *    model <unified|..>
 *    finish < ..|..>
 *    SigmaAlpha < >
 *    property
 *    <new property> const <value> or
 *   (before none const property) energy <arraysize> <energies array> 
 *    <new property> <property array>
 */
G4bool LineProcessor::ProcessLine(const std::vector< G4String > &words)
{
   G4bool processed = G4tgrLineProcessor::ProcessLine(words);
   if (processed) return true;

   G4String firstWord = words[0];
   firstWord.toUpper();
   if (firstWord.substr(0,5)==":PROP") {
      G4NistManager* mgr = G4NistManager::Instance();
      mgr->FindOrBuildMaterial(words[1])->
         SetMaterialPropertiesTable(CreateMaterialPropertiesTable(words,2));
      return true;
   } else if (firstWord.substr(0,5)==":SURF") {
      SurfaceList *surf=new SurfaceList;
      surf->next=Surface;
      Surface=surf;
      surf->name=words[1];
      surf->v1=words[2];
      surf->v2=words[3];
      surf->optic = new G4OpticalSurface(words[1]);
      int i=4; 
      // loop over optical surface setup lines
      while(true) {
         if(words[i]=="property")break;
         else if(words[i]=="type") {
            if (words[i+1]=="dielectric_metal")
               surf->optic->SetType(dielectric_metal);
            else if(words[i+1]=="dielectric_dielectric")
               surf->optic->SetType(dielectric_dielectric);
            else if(words[i+1]=="firsov")
               surf->optic->SetType(firsov);
            else if(words[i+1]=="x_ray")
               surf->optic->SetType(x_ray);
         } else if(words[i]=="model") {
            if (words[i+1]=="glisur")
               surf->optic->SetModel(glisur);
            else if(words[i+1]=="unified")
               surf->optic->SetModel(unified);
         } else if(words[i]=="finish") {
            if(words[i+1]=="polished")
               surf->optic->SetFinish(polished);
            else if(words[i+1]=="polishedfrontpainted")
               surf->optic->SetFinish(polishedfrontpainted);
            else if(words[i+1]=="polishedbackpainted")
               surf->optic->SetFinish(polishedbackpainted);
            else if(words[i+1]=="ground")
               surf->optic->SetFinish(ground);
            else if(words[i+1]=="groundfrontpainted")
               surf->optic->SetFinish(groundfrontpainted);
            else if(words[i+1]=="groundbackpainted")
               surf->optic->SetFinish(groundbackpainted);
         } else if(words[i]=="sigmaalpha") 
            surf->optic->SetSigmaAlpha(G4UIcommand::ConvertToInt(words[i+1]));
         else G4cout<<"op surface tag not find"<<G4endl;
         i+=2;
      }
      i++;
      surf->optic->SetMaterialPropertiesTable(
            CreateMaterialPropertiesTable(words,i));
      return true;
   } else return false;
}
//______________________________________________________________________________
//
#include <G4tgrUtils.hh>

G4MaterialPropertiesTable* LineProcessor::CreateMaterialPropertiesTable(
      const std::vector<G4String> &words, int idx)
{
   bool en=false;
   int cnt=0;
   double *energies ;
   G4MaterialPropertiesTable *properties = new G4MaterialPropertiesTable();
   for (size_t i=idx; i<words.size(); i=i+1) {
      if (words[i+1]=="const") {
         properties->AddConstProperty(words[i], G4tgrUtils::GetDouble(words[i+2]));
         i+=2;
      } else if (words[i]=="energy"){
         en=true;
         cnt = G4UIcommand::ConvertToInt(words[++i]);
         energies= new double[cnt];
         for (int j=0; j<cnt; j++) {energies[j]=0;}
         for (int j=0; j<cnt; j++) { energies[j]=G4tgrUtils::GetDouble(words[++i]);}
      }else{
         if (!en){G4cout<<"no energies"<<G4endl;break;}
         G4String name = words[i];
         double *propVals = new double[cnt];
         for (int j=0; j<cnt; j++) { propVals[j]=0;}
         for (int j=0; j<cnt; j++) {propVals[j]=G4tgrUtils::GetDouble(words[++i]);}
         properties->AddProperty(name,energies,propVals,cnt)->SetSpline(true);
         delete [] propVals;
      }
   }
   delete [] energies;
   return properties;
}
//______________________________________________________________________________
//
#include <G4tgbDetectorBuilder.hh>
#include <G4LogicalBorderSurface.hh>

class TextDetectorBuilder : public G4tgbDetectorBuilder
{
   public :
      TextDetectorBuilder() { fLineProcessor = new LineProcessor(); }
      ~TextDetectorBuilder() { delete fLineProcessor; }
      const G4tgrVolume* ReadDetector(); ///< Read text geometry input
      G4VPhysicalVolume* ConstructDetector(const G4tgrVolume* topVol);

   private :
      LineProcessor* fLineProcessor;
      void AddSurface(G4VPhysicalVolume* v1, SurfaceList* surface);
};
//______________________________________________________________________________
//
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
// FIXME: may need reconsider the logic
void TextDetectorBuilder::AddSurface(G4VPhysicalVolume* v1, SurfaceList* surface)
{
   G4tgbVolumeMgr* mgr = G4tgbVolumeMgr::GetInstance();
   if(mgr->GetTopPhysVol()->GetName()!=surface->v2) {
      G4LogicalVolume *parent=mgr->FindG4LogVol(
            surface->v2.substr(0, surface->v2.find("/")) );
      G4String target=surface->v2.substr(surface->v2.find("/")+1);
      for (int i=0; i<parent->GetNoDaughters(); i++) {
         G4VPhysicalVolume * now=parent->GetDaughter(i);
         if (now->GetName()==target)
            new G4LogicalBorderSurface(surface->name,v1,now,surface->optic); 
      }
   } else 
      new G4LogicalBorderSurface(surface->name,v1,mgr->GetTopPhysVol(),surface->optic);
}
//______________________________________________________________________________
//
#include <G4tgrMessenger.hh>

G4VPhysicalVolume* TextDetectorBuilder::ConstructDetector(
      const G4tgrVolume* topVol)
{
   G4VPhysicalVolume *world = G4tgbDetectorBuilder::ConstructDetector(topVol);
   if(!fLineProcessor->Surface) return world; 

   SurfaceList* surface = fLineProcessor->Surface;
   G4tgbVolumeMgr* tgbVolmgr = G4tgbVolumeMgr::GetInstance();
   while (surface) {
      if(tgbVolmgr->GetTopPhysVol()->GetName()!=surface->v1) {
         G4LogicalVolume *parent=tgbVolmgr->FindG4LogVol(
               surface->v1.substr(0, surface->v1.find("/")) );
         G4String target=surface->v1.substr(surface->v1.find("/")+1);
         for (int i=0; i<parent->GetNoDaughters(); i++) {
            G4VPhysicalVolume * now=parent->GetDaughter(i);
            if (now->GetName()==target) AddSurface(now,surface);
         }
      } else
         AddSurface(world,surface);
      surface=surface->next;
   }
   return world;
}
//______________________________________________________________________________
//
#include <G4VUserDetectorConstruction.hh>
#include <G4TransportationManager.hh>
#include <G4UIcmdWith3VectorAndUnit.hh>
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
      { delete fDirField; delete fCmdSetM; delete fCmdSrc; delete fField; }
      G4VPhysicalVolume* Construct();
      void SetNewValue(G4UIcommand* cmd, G4String value);

   private:
      G4String fGeomSrcText;

      G4UIdirectory *fDirField;
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

   fDirField = new G4UIdirectory("/field/");
   fDirField->SetGuidance("Global uniform field UI commands");

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
#include "G4UIcmdWithABool.hh"
/**
 * Enable physics lists.
 * Physics lists have to be enabled when Geant4 is at PreInit state. All UI
 * commands defined here have to be put before /run/Initialize in a mac file.
 */
class Physics: public G4VModularPhysicsList, public G4UImessenger
{
   public:
      Physics();
      ~Physics() { delete fDir; delete fCmdElastic; delete fCmdInelastic; }
      void SetNewValue(G4UIcommand* cmd, G4String value);
   private:
      G4UIdirectory* fDir;
      G4UIcmdWithABool* fCmdElastic;
      G4UIcmdWithABool* fCmdInelastic;
};
//______________________________________________________________________________
//
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
Physics::Physics() : G4VModularPhysicsList(), G4UImessenger()
{
   fDir = new G4UIdirectory("/physics_lists/hadron/");
   fDir->SetGuidance("Configure hadronic physics lists");

   fCmdElastic=new G4UIcmdWithABool("/physics_lists/hadron/elasticOn",this);
   fCmdElastic->SetGuidance("Enable hadron elastic physics");
   fCmdElastic->SetParameterName("flag",true);
   fCmdElastic->SetDefaultValue(true);
   fCmdElastic->AvailableForStates(G4State_PreInit);

   fCmdInelastic=new G4UIcmdWithABool("/physics_lists/hadron/inelasticOn",this);
   fCmdInelastic->SetGuidance("Enable hadron inelastic physics");
   fCmdInelastic->SetParameterName("flag",true);
   fCmdInelastic->SetDefaultValue(true);
   fCmdInelastic->AvailableForStates(G4State_PreInit);

   RegisterPhysics(new G4DecayPhysics());
   RegisterPhysics(new G4RadioactiveDecayPhysics()); // weak force
   RegisterPhysics(new G4EmStandardPhysics());
   RegisterPhysics(new G4OpticalPhysics());
}
//______________________________________________________________________________
//
#include "G4HadronPhysicsFTFP_BERT_HP.hh" // won't work for Geant4 version<10
#include "G4HadronElasticPhysicsHP.hh"
void Physics::SetNewValue(G4UIcommand* cmd, G4String value)
{
   if (cmd==fCmdElastic) {
      if (fCmdElastic->GetNewBoolValue(value))
         RegisterPhysics(new G4HadronElasticPhysicsHP());
   } else {
      if (fCmdInelastic->GetNewBoolValue(value))
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
      RunAction(Output *out=0) : G4UserRunAction(), fOut(out) {};
      ~RunAction() {};
      void BeginOfRunAction (const G4Run* run);
      void EndOfRunAction (const G4Run* run);
   private:
      Output* fOut;
};
//______________________________________________________________________________
//
#include <G4Run.hh>
void RunAction::BeginOfRunAction (const G4Run* run)
{ 
   fOut->Open(); 
   G4cout<<run->GetNumberOfEventToBeProcessed()
      <<" events to be processed"<<G4endl;
}
//______________________________________________________________________________
//
void RunAction::EndOfRunAction (const G4Run* run)
{
   G4cout<<run->GetNumberOfEvent()<<" events simulated"<<G4endl;
   fOut->Write();
   fOut->Close();
}
//______________________________________________________________________________
//
#include <G4UserEventAction.hh>
#include "G4UIcmdWithAnInteger.hh"
class EventAction : public G4UserEventAction, public G4UImessenger
{
   public:
      EventAction(Output *out=0);
      ~EventAction() { delete fCmdReport; }
      void BeginOfEventAction(const G4Event* event);
      void EndOfEventAction(const G4Event* event);
      void SetNewValue(G4UIcommand* cmd, G4String value)
      { if (cmd==fCmdReport) fN2report=atoi(value); }
   private:
      Output* fOut;
      int fN2report;
      G4UIcmdWithAnInteger* fCmdReport;
};
//______________________________________________________________________________
//
EventAction::EventAction(Output *out)
   : G4UserEventAction(), G4UImessenger(), fOut(out), fN2report(1000)
{
   fCmdReport = new G4UIcmdWithAnInteger("/run/statusReport",this);
   fCmdReport->SetGuidance("enable status report after [number of events]");
   fCmdReport->SetParameterName("number of events",true);
   fCmdReport->SetDefaultValue(fN2report);
}
//______________________________________________________________________________
//
void EventAction::BeginOfEventAction(const G4Event* event)
{
   G4PrimaryVertex* vtx = event->GetPrimaryVertex(0);
   while (vtx) {
      fOut->Record(vtx);
      vtx = vtx->GetNext();
   }
}
//______________________________________________________________________________
//
void EventAction::EndOfEventAction(const G4Event* event)
{
   fOut->Write();
   int id=event->GetEventID();
   if (id%fN2report==0 && id!=0) G4cout<<id<<" events simulated"<<G4endl;
}
//______________________________________________________________________________
//
#include <G4UserSteppingAction.hh>
class SteppingAction : public G4UserSteppingAction
{
   public:
      SteppingAction(Output *out=0) : G4UserSteppingAction(), fOut(out) {};
      ~SteppingAction() {};
      void UserSteppingAction(const G4Step* step);
   private:
      Output* fOut;
};
//______________________________________________________________________________
//
void SteppingAction::UserSteppingAction(const G4Step* step)
{   
   G4String volume = step->GetPreStepPoint()->GetPhysicalVolume()->GetName();
   if (volume.length()<3) return;
   if (volume.substr(volume.length()-3)=="(S)") fOut->Record(step->GetTrack());
}
//______________________________________________________________________________
//
#include <G4RunManager.hh>
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>
#include <G4UImanager.hh> // needed for g4.10 and above
/**
 * \fn int main(int argc, char **argv)
 *
 * The main function that calls individual components.
 */
int main(int argc, char **argv)
{
   Output *out = new Output; // ROOT output

   G4RunManager* run = new G4RunManager;
   run->SetUserInitialization(new Detector);
   run->SetUserInitialization(new Physics);
   run->SetUserAction(new Generator);
   run->SetUserAction(new RunAction(out));
   run->SetUserAction(new EventAction(out));
   run->SetUserAction(new SteppingAction(out));

   G4VisManager* vis = new G4VisExecutive;
   //vis->SetVerboseLevel(0); // suppress list of vis engines
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
