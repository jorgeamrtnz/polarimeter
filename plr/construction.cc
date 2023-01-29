#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

	
G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	// Material definitions
	G4NistManager *nist = G4NistManager::Instance();
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");
	G4Material *Si = nist->FindOrBuildMaterial("G4_Si");
	
	// Sandbox construction
	G4Box *solidWorld = new G4Box("solidWorld", 27.05*m, 27.05*m, 2.05*m);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	
	// Layer construction
	G4Tubs *solidLayer = new G4Tubs("solidLayer", .0*m, .5*m, .006*cm, 0, 360*deg);
	logicLayerSi = new G4LogicalVolume(solidLayer, Si, "logicLayer");
    logicLayerWorld = new G4LogicalVolume(solidLayer, worldMat, "logicLayer");
	G4double zc;
	for (G4int b = 1; b < 31; b++)
	{
		zc = -43.5 + ((b-1)*3);
		for (G4int sz = 1; sz < 3; sz++)
		{
            if (b <= 27) {
                G4VPhysicalVolume *physLayerSi = new G4PVPlacement(0, G4ThreeVector(0., 0., (zc+(2*sz-3)*.106)*cm), logicLayerSi, "physLayerSi", logicWorld, false, 2*(b-1)+sz, true);
            } else {
                G4VPhysicalVolume *physLayerWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., (zc+(2*sz-3)*.106)*cm), logicLayerWorld, "physLayerWorld", logicWorld, false, 2*(b-1)+sz, true);
            }
			
		}
		
	}
    
    
    /*G4Tubs *solidConDet1 = new G4Tubs("conDet1", .7*m, .71*m, .75*m, 0*deg, 360.*deg);
    logicConDet1 = new G4LogicalVolume(solidConDet1, worldMat, "logicConDet1");
    G4VPhysicalVolume *physConDet1 = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicConDet1, "physConDet1", logicWorld, false, 61, true);
    
    G4Tubs *solidConDet2 = new G4Tubs("conDet2", 0., .7*m, .1*cm, 0.*deg, 360.*deg);
    logicConDet2 = new G4LogicalVolume(solidConDet1, worldMat, "logicConDet2");
    G4VPhysicalVolume *physConDet2 = new G4PVPlacement(0, G4ThreeVector(0, 0, .7*m), logicConDet2, "physConDet2", logicWorld, false, 62, true);
    
    G4Tubs *solidConDet3 = new G4Tubs("conDet3", 0., .7*m, .1*cm, 0*deg, 360.*deg);
    logicConDet3 = new G4LogicalVolume(solidConDet1, worldMat, "logicConDet3");
    G4VPhysicalVolume *physConDet3 = new G4PVPlacement(0, G4ThreeVector(0, 0, -.7*m), logicConDet3, "physConDet3", logicWorld, false, 63, true);*/
	
	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
	
	logicLayerSi->SetSensitiveDetector(sensDet);
    logicLayerWorld->SetSensitiveDetector(sensDet);
    
    /*logicConDet1->SetSensitiveDetector(sensDet);
    logicConDet1->SetSensitiveDetector(sensDet);
    logicConDet1->SetSensitiveDetector(sensDet);
    logicConDet1->SetSensitiveDetector(sensDet);*/
}
