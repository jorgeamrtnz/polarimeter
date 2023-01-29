#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv)
{
    // Refreshes seed every run
	CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
	G4long seed = time(NULL);
	CLHEP::HepRandom::setTheSeed(seed);
    
    // Sets up environment
    G4RunManager *runManager = new G4RunManager();
	runManager->SetUserInitialization(new MyDetectorConstruction());
	runManager->SetUserInitialization(new MyPhysicsList());
	
    // Creates name for ROOT output file
	G4String name;
	if (argc == 3) {
		name=argv[2];
	}
	else name="jorge";
    runManager->SetUserInitialization(new MyActionInitialization(name));
    
    // Initializes run
    runManager->Initialize();
    
    // Runs macro if not running with visualization
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    G4UIExecutive *ui = 0;
    if (argc == 1)
    {
        ui = new G4UIExecutive(argc, argv);
    }
    
	if(ui)
	{
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
	}
	else
	{
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	}
    
	return 0;
}
