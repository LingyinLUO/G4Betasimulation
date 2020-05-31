#include "B1PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "B1PrimaryGeneratorActionMessenger.hh"
//#include ""
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PrimaryGeneratorAction::B1PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0) 
  ,fposition(1)
// fEnvelopeBox(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="e-");
  fParticleGun->SetParticleDefinition(particle);

  fB1PrimaryGeneratorActionMessenger = new B1PrimaryGeneratorActionMessenger(this);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  
  G4double x0 = -140*mm;
  G4double y0 = 25./250.*1.2*250*mm - 100*mm;
  G4double z0 = 0*mm; //the distance to the surface of cylinder is 5cm.
  
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,1.,0.));
  double energy = generate_energy(fposition);
  fParticleGun->SetParticleEnergy(energy*MeV);
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


double B1PrimaryGeneratorAction::generate_energy(int i){
  double fmax = 100.1804;
  while (1){
    double delta = 0.2;
      double temp = 2.9979*0.06555*(140+(i-1)*25-60)/20.;
      double center = sqrt(pow(temp,2) + pow(0.511,2))-0.511;
      double r = G4UniformRand()*delta+center;
      double u = G4UniformRand()*fmax;
      double z = -20.308*pow(r,6) +  146.64*pow(r,5) - 412.17*pow(r,4) + 581.69*pow(r,3)
           - 424.96*pow(r,2) + 102.77*r + 88.585;
      double left = 2.9979*0.06555*(140+(i-1)*25-60-1.5)/20.;
      double min = sqrt(pow(left,2) + pow(0.511,2))-0.511;
      double right =  2.9979*0.06555*(140+(i-1)*25-60+1.5)/20.;
      double max = sqrt(pow(right,2) + pow(0.511,2))-0.511;
    if(u<z){
       if(u>min&&u<max){return r;}
       else if(u>max){return max;}
       else if(u<min){return min;}
      }
    else {return 0;}
  }
}
