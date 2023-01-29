#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

#include "G4AnalysisManager.hh"
// #include "g4root.hh"

#include "run.hh"

#include "G4EventManager.hh"

#include <iostream>
#include <vector>

#include "G4SystemOfUnits.hh"


class MyEventAction : public G4UserEventAction
{
public:
	MyEventAction(MyRunAction*);
	~MyEventAction();
	
	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);
	
	void AddlayerNum(G4String particleName, G4int layerNum) 
	{ 
		if (particleName == "geantino")
		{
			layersHit.push_back(layerNum); 
		}
	}
	
	void AddName(G4String particleName, G4int layerNum)
	{
		if (particleName != "gamma" && particleName != "geantino")
		{
			converted = true;
		}
	}
	
private:
	std::vector<G4int> layersHit;
	G4bool converted;
};

#endif
