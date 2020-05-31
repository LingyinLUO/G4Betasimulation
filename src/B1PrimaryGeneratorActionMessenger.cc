
#include "B1PrimaryGeneratorActionMessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "B1PrimaryGeneratorAction.hh"
#include <stdlib.h>



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

B1PrimaryGeneratorActionMessenger::B1PrimaryGeneratorActionMessenger(B1PrimaryGeneratorAction* generator)
  : G4UImessenger(),  fgenerator(generator)
//  ,fdetector(detector)
{
  //G4cout<<"hehe"<<G4endl;
  fFileNameDir = new G4UIdirectory("/B1generator");
  fFileNameDir->SetGuidance("generator config");
          
  fCmd = new G4UIcmdWithAString("/B1generator/SetPosition",this);
  fCmd->SetGuidance("set the config for different position");
  fCmd->SetParameterName("position",true);
  fCmd->SetDefaultValue ("1");
  fCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

B1PrimaryGeneratorActionMessenger::~B1PrimaryGeneratorActionMessenger()
{
  delete fCmd; 
  //delete fFileNameDir;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void B1PrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command, G4String newValues)
{               
  if (command == fCmd) {
    fgenerator->set_position( atoi(newValues.c_str() )) ;
  } 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

   
