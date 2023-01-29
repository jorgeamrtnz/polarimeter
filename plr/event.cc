#include "event.hh"
#include "run.hh"
#include <iostream>
#include <vector>
MyEventAction::MyEventAction(MyRunAction*)
{
	layersHit = {};
	converted = false;
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
    // Starting state of variables for each event
	layersHit = {};
	converted = false;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
    // Checks which layers were hit
	G4bool contains = true;
	for (G4int i = 53; i < 61; i++)
	{
		if (!(std::find(layersHit.begin(), layersHit.end(), i) != layersHit.end()))
		{
			contains = false;
		}
	}
	
    // Keep events that satisfy conditions
	if (contains)
		
	{
		G4EventManager::GetEventManager()->KeepTheCurrentEvent();
	}
}
