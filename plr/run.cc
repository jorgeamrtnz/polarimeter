#include "run.hh"

MyRunAction::MyRunAction(G4String name)
 : G4UserRunAction(),
  fname(name)
{
for(G4int i = 1; i < 61; i++)
{
    // Stores hits for each layer
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	std::stringstream istr;
	istr << i;

		man->CreateNtuple("Hits"+istr.str(), "Hits"+istr.str());
		man->CreateNtupleIColumn("fEvent");
		man->CreateNtupleDColumn("fL"+istr.str()+"X");
		man->CreateNtupleDColumn("fL"+istr.str()+"Y");
		man->CreateNtupleDColumn("fL"+istr.str()+"Z");
		man->FinishNtuple(i-1);		
}
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    // Unique output name based on run
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	G4int runID = run->GetRunID();

	std::stringstream strRunID;
	strRunID << runID;

	man->OpenFile("output"+fname+".root");
}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->Write();
	man->CloseFile();
}
