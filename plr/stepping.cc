#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
	fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
    // Layer number before step
	const G4VTouchable *touchablepre = step->GetPreStepPoint()->GetTouchable();
	G4int layerNoPre = touchablepre->GetCopyNumber();
    
	// Layer number after step
	const G4VTouchable *touchablepst = step->GetPostStepPoint()->GetTouchable();
	G4int layerNoPst = touchablepst->GetCopyNumber();
	
	// Particle name
	G4Track *track = step->GetTrack();
	const G4DynamicParticle* dynamicParticle = track->GetDynamicParticle();
	G4ParticleDefinition* particle = dynamicParticle->GetDefinition();
	G4String particleName = particle->GetParticleName();
	
	fEventAction->AddName(particleName, layerNoPre);
	fEventAction->AddlayerNum(particleName, layerNoPre);
}
