#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "generator.hh"
#include "run.hh"
#include "event.hh"
#include "stepping.hh"


class MyActionInitialization : public G4VUserActionInitialization
{
public:
	MyActionInitialization(G4String name);
	~MyActionInitialization();
	
	virtual void BuildForMaster() const;	
	virtual void Build() const;
	G4String fname;
};

#endif
