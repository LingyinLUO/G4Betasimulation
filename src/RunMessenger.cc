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

#include "RunMessenger.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "Run.hh"
#include <sstream>


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

RunMessenger::RunMessenger(Run* run)
  : G4UImessenger(),  fRun(run)
//  ,fdetector(detector)
{
  //G4cout<<"hehe"<<G4endl;
  fFileNameDir = new G4UIdirectory("/rlt/");
  fFileNameDir->SetGuidance("provide the root file full name");
          
  fSetRootFileNameCmd = new G4UIcmdWithAString("/rlt/SetFileName",this);
  fSetRootFileNameCmd->SetGuidance("save the results in the root file");
  fSetRootFileNameCmd->SetParameterName("fileName",true);
  fSetRootFileNameCmd->SetDefaultValue ("test1.root");
  fSetRootFileNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

 /* fSetThickCmd = new G4UIcmdWithAString("/rlt/SetThick",this);
  fSetThickCmd->SetGuidance("change the thick of Al");
  fSetThickCmd->SetParameterName("thick",true);
  fSetThickCmd->SetDefaultValue (0);
  fSetThickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);*/

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

RunMessenger::~RunMessenger()
{
  delete fSetRootFileNameCmd; 
  //delete fFileNameDir;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void RunMessenger::SetNewValue(G4UIcommand* command, G4String newValues)
{
                 
  if (command == fSetRootFileNameCmd) {
    G4cout << "\n---> root name from file: " << newValues << G4endl;
    fRun->SetROOTFullName(newValues);
  } 
 /* else if(command == fSetThickCmd) {
    G4cout << "\n---> the thick is: " << newValues << G4endl;
    std::istringstream iss(newValues);
    double thick=0;
    iss>>thick;
    fdetector->set_thick(thick);
  } */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

   
