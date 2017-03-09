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
      ~Output() { delete fCmd; delete fDir; delete fFile; }

      void Open(); ///< Open output file and define data structure
      void Record(G4PrimaryVertex* vtx); ///< Record source info
      /**
       * Record track info.
       * Process types are defined in G4ProcessType.hh, sub types are defined
       * in G4HadronicProcessType.hh, G4DecayProcessType.hh,
       * G4EmProcessSubType.hh.  G4TransportationProcessType.hh,
       * G4FastSimulationProcessType.hh, G4OpProcessSubType.hh, etc. They can
       * be found at http://www-geant4.kek.jp/lxr/find?string=Type.hh
       */
      void Record(G4Track *track);
      void Write() { fTree->Fill(); Reset(); }
      void Close() { fFile->Write(); fFile->Close(); }

      void SetNewValue(G4UIcommand* cmd, G4String value) ///< for G4UI
      { if (cmd==fCmd) fFileName = value; }

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
      G4UIcmdWithAString* fCmd;
};
//______________________________________________________________________________
//
Output::Output(): G4UImessenger()
{
   Reset(); // reset track record

   fDir = new G4UIdirectory("/output/");
   fDir->SetGuidance("Configure output");

   fCmd = new G4UIcmdWithAString("/output/file",this);
   fCmd->SetGuidance("Set output file name");
   fCmd->SetParameterName("output file name",false);
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
   G4OpticalSurface* optic;
   BorderSurface* next;
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

      BorderSurface* Border;

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
class TextDetectorBuilder : public G4tgbDetectorBuilder
{
   public :
      TextDetectorBuilder() { fLineProcessor = new LineProcessor(); }
      ~TextDetectorBuilder() { delete fLineProcessor; }
      const G4tgrVolume* ReadDetector(); ///< Read text geometry input
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
      G4VPhysicalVolume* Construct();
      void SetNewValue(G4UIcommand* cmd, G4String value);

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
      void SetNewValue(G4UIcommand* cmd, G4String value);
   private:
      G4UIcmdWithAString* fCmd;
};
//______________________________________________________________________________
//
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
Physics::Physics() : G4VModularPhysicsList(), G4UImessenger()
{
   fCmd = new G4UIcmdWithAString("/physics_lists/enable",this);
   fCmd->SetGuidance("Enable a certain physics list");
   fCmd->SetParameterName("name of a physics list", false);
   fCmd->SetCandidates("RadioactiveDecay Optical HadronElastic HadronInelastic");
   fCmd->AvailableForStates(G4State_PreInit);

   RegisterPhysics(new G4EmStandardPhysics());
   // has to be loaded to define some particles for hadron processes:
   RegisterPhysics(new G4DecayPhysics()); // muon, pion, kaon etc.
}
//______________________________________________________________________________
//
#include "G4OpticalPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh" // won't work for Geant4 version<10
void Physics::SetNewValue(G4UIcommand* cmd, G4String value)
{
   if (cmd==fCmd) {
      if (value=="RadioactiveDecay") // alpha, beta, gamma, etc.
         RegisterPhysics(new G4RadioactiveDecayPhysics());
      else if (value=="Optical")
         RegisterPhysics(new G4OpticalPhysics());
      else if (value=="HadronElasticHP")
         RegisterPhysics(new G4HadronElasticPhysicsHP());
      else if (value=="FTFP_BERT_HP") // for low energy neutrons
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
      ~EventAction() { delete fCmd; }
      void BeginOfEventAction(const G4Event* event);
      void EndOfEventAction(const G4Event* event);
      void SetNewValue(G4UIcommand* cmd, G4String value)
      { if (cmd==fCmd) fN2report=atoi(value); }
   private:
      Output* fOut;
      int fN2report;
      G4UIcmdWithAnInteger* fCmd;
};
//______________________________________________________________________________
//
EventAction::EventAction(Output *out)
   : G4UserEventAction(), G4UImessenger(), fOut(out), fN2report(1000)
{
   fCmd = new G4UIcmdWithAnInteger("/run/statusReport",this);
   fCmd->SetGuidance("enable status report after [number of events]");
   fCmd->SetParameterName("number of events",true);
   fCmd->SetDefaultValue(fN2report);
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
