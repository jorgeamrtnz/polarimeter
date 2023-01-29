#include "action.hh"

MyActionInitialization::MyActionInitialization(G4String name)
 : G4VUserActionInitialization(),
  fname(name)
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::BuildForMaster() const
{
	SetUserAction(new MyRunAction(fname));
}

void MyActionInitialization::Build() const
{
	MyPrimaryGenerator *generator = new MyPrimaryGenerator();
	SetUserAction(generator);
	
	MyRunAction *runAction = new MyRunAction(fname);
	SetUserAction(runAction);
	
	MyEventAction *eventAction = new MyEventAction(runAction);
	SetUserAction(eventAction);
	
	MySteppingAction *steppingAction = new MySteppingAction(eventAction);
	SetUserAction(steppingAction);
}
