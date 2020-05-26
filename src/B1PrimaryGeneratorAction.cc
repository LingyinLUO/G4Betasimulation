//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B1PrimaryGeneratorAction.cc 94307 2015-11-11 13:42:46Z gcosmo $
//
/// \file B1PrimaryGeneratorAction.cc
/// \brief Implementation of the B1PrimaryGeneratorAction class

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
  //this function is called at the begining of ecah event
  //

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get Envelope volume
  // from G4LogicalVolumeStore.
  /*
  G4double envSizeXY = 0;
  G4double envSizeZ = 0;

  if (!fEnvelopeBox)
  {
    G4LogicalVolume* envLV
      = G4LogicalVolumeStore::GetInstance()->GetVolume("Envelope");
    if ( envLV ) fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());
  }

  if ( fEnvelopeBox ) {
    envSizeXY = fEnvelopeBox->GetXHalfLength()*2.;
    envSizeZ = fEnvelopeBox->GetZHalfLength()*2.;
  }  
  else  {
    G4ExceptionDescription msg;
    msg << "Envelope volume of box shape not found.\n"; 
    msg << "Perhaps you have changed geometry.\n";
    msg << "The gun will be place at the center.";
    G4Exception("B1PrimaryGeneratorAction::GeneratePrimaries()",
     "MyCode0002",JustWarning,msg);
  }

  G4double size = 0.8; 
  G4double x0 = size * envSizeXY * (G4UniformRand()-0.5);
  G4double y0 = size * envSizeXY * (G4UniformRand()-0.5);
  G4double z0 = -0.5 * envSizeZ;*/
  
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
    //double r = G4UniformRand()*2.2812834225; 
    //double u = G4UniformRand()*fmax; 
    //double z = 0.2606*pow(r,6) - 1.5439*pow(r,5) + 3.3465*pow(r,4) - 3.0866*pow(r,3)
     //      + 0.06*pow(r,2) + 1.5911*r + 0.735;
    double delta = 0.2;
    //if(u<z) {
    if (i==1){
      double temp = 2.9979*0.06555*(140-60)/20.;
      double center = sqrt(pow(temp,2) + pow(0.511,2))-0.511;
      double r = G4UniformRand()*delta+center;
      double u = G4UniformRand()*fmax;
      double z = -20.308*pow(r,6) +  146.64*pow(r,5) - 412.17*pow(r,4) + 581.69*pow(r,3)
           - 424.96*pow(r,2) + 102.77*r + 88.585;
      if (u < z){ return r;};
    }
   else if (i==2){
      double temp = 2.9979*0.06555*(165-60)/20.;
      double center = sqrt(pow(temp,2) + pow(0.511,2))-0.511;
      double r = G4UniformRand()*delta+center;
      double u = G4UniformRand()*fmax;
      double z = -20.308*pow(r,6) +  146.64*pow(r,5) - 412.17*pow(r,4) + 581.69*pow(r,3)
           - 424.96*pow(r,2) + 102.77*r + 88.585;
      if (u < z){ return r;};
    }
    else if (i==3){
      double temp = 2.9979*0.06555*(190-60)/20.;
      double center = sqrt(pow(temp,2) + pow(0.511,2))-0.511;
      double r = G4UniformRand()*delta+center;
      double u = G4UniformRand()*fmax;
      double z = -20.308*pow(r,6) +  146.64*pow(r,5) - 412.17*pow(r,4) + 581.69*pow(r,3)
           - 424.96*pow(r,2) + 102.77*r + 88.585;
      if (u < z){ return r;};
    }
    else if (i==4){
      double temp = 2.9979*0.06555*(215-60)/20.;
      double center = sqrt(pow(temp,2) + pow(0.511,2))-0.511;
      double r = G4UniformRand()*delta+center;
      double u = G4UniformRand()*fmax;
      double z = -20.308*pow(r,6) +  146.64*pow(r,5) - 412.17*pow(r,4) + 581.69*pow(r,3)
           - 424.96*pow(r,2) + 102.77*r + 88.585;
      if (u < z){ return r;};
    }
    else if (i==5){
      double temp = 2.9979*0.06555*(240-60)/20.;
      double center = sqrt(pow(temp,2) + pow(0.511,2))-0.511;
      double r = G4UniformRand()*delta+center;
      double u = G4UniformRand()*fmax;
      double z = -20.308*pow(r,6) +  146.64*pow(r,5) - 412.17*pow(r,4) + 581.69*pow(r,3)
           - 424.96*pow(r,2) + 102.77*r + 88.585;
      if (u < z){ return r;};
    }
    else if (i==6){
      double temp = 2.9979*0.06555*(265-60)/20.;
      double center = sqrt(pow(temp,2) + pow(0.511,2))-0.511;
      double r = G4UniformRand()*delta+center;
      double u = G4UniformRand()*fmax;
      double z = -20.308*pow(r,6) +  146.64*pow(r,5) - 412.17*pow(r,4) + 581.69*pow(r,3)
           - 424.96*pow(r,2) + 102.77*r + 88.585;
      if (u < z){ return r;};
    }
    else if (i==7){
      double temp = 2.9979*0.06555*(290-60)/20.;
      double center = sqrt(pow(temp,2) + pow(0.511,2))-0.511;
      double r = G4UniformRand()*delta+center;
      double u = G4UniformRand()*fmax;
      double z = -20.308*pow(r,6) +  146.64*pow(r,5) - 412.17*pow(r,4) + 581.69*pow(r,3)
           - 424.96*pow(r,2) + 102.77*r + 88.585;
      if (u < z){ return r;};
    }
    else if (i==8){
      double temp = 2.9979*0.06555*(315-60)/20.;
      double center = sqrt(pow(temp,2) + pow(0.511,2))-0.511;
      double r = G4UniformRand()*delta+center;
      double u = G4UniformRand()*fmax;
      double z = -20.308*pow(r,6) +  146.64*pow(r,5) - 412.17*pow(r,4) + 581.69*pow(r,3)
           - 424.96*pow(r,2) + 102.77*r + 88.585;
      if (u < z){ return r;};
    }
    else{
      return 0;
    }
  }
}
