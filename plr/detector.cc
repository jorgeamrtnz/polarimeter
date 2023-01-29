#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *R0hist)
{
	G4Track *track = aStep->GetTrack();
	const G4DynamicParticle* dynamicParticle = track->GetDynamicParticle();
	G4ParticleDefinition* particle = dynamicParticle->GetDefinition();
	G4String particleName = particle->GetParticleName();
	if (particleName == "geantino")
	
	{
		
		// Layer number
		const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
		G4int layerNo = touchable->GetCopyNumber();
		
		// Layer position
		G4VPhysicalVolume *physVol = touchable->GetVolume();
		G4ThreeVector posDetector = physVol->GetTranslation();
		
		// Photon position
		G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
		G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
		G4ThreeVector posPhoton = preStepPoint->GetPosition();
		
        // Storing to ROOT output file
		G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
		G4AnalysisManager *man = G4AnalysisManager::Instance();
		man->FillNtupleIColumn(0, evt);
		man->FillNtupleIColumn(layerNo-1, 0, evt);
		man->FillNtupleDColumn(layerNo-1, 1, posPhoton[0]);
		man->FillNtupleDColumn(layerNo-1, 2, posPhoton[1]);
		man->FillNtupleDColumn(layerNo-1, 3, posPhoton[2]);
		man->AddNtupleRow(layerNo-1);
	}
	return true;
}
