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
/// \file electromagnetic/TestEm10/src/RunMessenger.cc
/// \brief Implementation of the RunMessenger class
//
//
// $Id: RunMessenger.cc 94932 2015-12-18 09:21:29Z gcosmo $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//#include "RunMessenger.hh"
#include "B1DetectorConstructionMessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
//#include "Run.hh"
#include "B1DetectorConstruction.hh"
#include <stdlib.h>
//#include <sstream>


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

B1DetectorConstructionMessenger::B1DetectorConstructionMessenger(B1DetectorConstruction* detector)
  : G4UImessenger(),  fdetector(detector)
//  ,fdetector(detector)
{
  //G4cout<<"hehe"<<G4endl;
  fFileNameDir = new G4UIdirectory("/B1detector");
  fFileNameDir->SetGuidance("detector config");
          
  fCmd1 = new G4UIcmdWithAString("/B1detector/SetPosition",this);
  fCmd1->SetGuidance("set the config for different position");
  fCmd1->SetParameterName("position",true);
  fCmd1->SetDefaultValue ("1");
  fCmd1->AvailableForStates(G4State_PreInit,G4State_Idle); 

  fCmd2 = new G4UIcmdWithAString("/B1detector/SetMaterial",this);
  fCmd2->SetGuidance("set the matreial of box");
  fCmd2->SetParameterName("matreial",true);
  fCmd2->SetDefaultValue ("vacuum");
  fCmd2->AvailableForStates(G4State_PreInit,G4State_Idle); 

  fAlthickCmd = new G4UIcmdWithADoubleAndUnit("/B1detector/Althick",this);
  fAlthickCmd->SetGuidance("Set Al thickness");
  fAlthickCmd->SetParameterName("Althick",false);
  fAlthickCmd->SetRange("Althick>=0. && Althick<=2.");
  fAlthickCmd->SetUnitCategory("Length");
  fAlthickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fAlthickCmd->SetToBeBroadcasted(false);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

B1DetectorConstructionMessenger::~B1DetectorConstructionMessenger()
{
  delete fCmd1; 
  delete fAlthickCmd;
  //delete fFileNameDir;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void B1DetectorConstructionMessenger::SetNewValue(G4UIcommand* command, G4String newValues)
{               
  if (command == fCmd1) {
    fdetector->set_position( atoi(newValues.c_str() )) ;
  } 
  if (command == fCmd2) {
    fdetector->set_material( newValues );
  }
  if ( command == fAlthickCmd ){
    fdetector->set_Althick(fAlthickCmd->GetNewDoubleValue(newValues));
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

   
