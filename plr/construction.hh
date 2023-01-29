#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();
	
	virtual G4VPhysicalVolume *Construct();
	
private:
	G4LogicalVolume *logicLayerSi;
    G4LogicalVolume *logicLayerWorld;
    
    /*G4LogicalVolume *logicConDet1;
    G4LogicalVolume *logicConDet2;
    G4LogicalVolume *logicConDet3;*/

	virtual void ConstructSDandField();
	
	
};

#endif
