#include "generator.hh"
#include "G4RunManager.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	pParticleGun = new G4ParticleGun(1);	
	gParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete pParticleGun;
	delete gParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String pparticleName="gamma";
	G4ParticleDefinition *pparticle = particleTable->FindParticle("gamma");
	G4String gparticleName="geantino";
	G4ParticleDefinition *gparticle = particleTable->FindParticle("geantino");
	
	// Particle position
	G4double size = 7*m;
	G4double x0 = size * (2*G4UniformRand()-1);
	G4double y0 = size * (2*G4UniformRand()-1);
	G4ThreeVector pos(x0, y0, -.75*m);
	
	// Particle direction
	G4ThreeVector momDir(0, 0, 1);
	G4double Cos=G4UniformRand();
	momDir.setTheta(acos(1*pow(Cos,0.5)));
	momDir.setPhi(360*degree*G4UniformRand());
	
	// Particle Energy
	G4double energy = 1.0/G4RandExponential::shoot(1)-0.2;
	
    // Photon defined
	pParticleGun->SetParticleMomentumDirection(momDir);
	pParticleGun->SetParticleEnergy(energy*GeV);
	pParticleGun->SetParticleDefinition(pparticle);
	pParticleGun->SetParticlePosition(pos);
	
    // Geantion defined
	gParticleGun->SetParticleMomentumDirection(momDir);
	gParticleGun->SetParticleEnergy(energy*GeV);
	gParticleGun->SetParticleDefinition(gparticle);
	gParticleGun->SetParticlePosition(pos);
	
    // Particles shot
	pParticleGun->GeneratePrimaryVertex(anEvent);
	gParticleGun->GeneratePrimaryVertex(anEvent);
	
	anEvent->Print();
}
