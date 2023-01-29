#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
	RegisterPhysics (new G4EmStandardPhysics());
	RegisterPhysics (new G4OpticalPhysics());
	RegisterPhysics (new G4StepLimiterPhysics());
	
	G4PhysListFactory factory;
	G4VModularPhysicsList* physlist = factory.GetReferencePhysList("FTFP_BERT_LIV");
	physlist->RegisterPhysics(new G4StepLimiterPhysics());
	G4RunManager::GetRunManager()->SetUserInitialization(physlist);
	physlist->SetCuts();
}

MyPhysicsList::~MyPhysicsList()
{}
