
#include "B1DetectorConstructionMessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "B1DetectorConstruction.hh"
#include <stdlib.h>


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

B1DetectorConstructionMessenger::B1DetectorConstructionMessenger(B1DetectorConstruction* detector)
  : G4UImessenger(),  fdetector(detector)
{
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

   
