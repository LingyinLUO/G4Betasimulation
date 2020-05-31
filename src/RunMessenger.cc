#include "RunMessenger.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "Run.hh"
#include <sstream>


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

RunMessenger::RunMessenger(Run* run)
  : G4UImessenger(),  fRun(run)
{
  fFileNameDir = new G4UIdirectory("/rlt/");
  fFileNameDir->SetGuidance("provide the root file full name");
          
  fSetRootFileNameCmd = new G4UIcmdWithAString("/rlt/SetFileName",this);
  fSetRootFileNameCmd->SetGuidance("save the results in the root file");
  fSetRootFileNameCmd->SetParameterName("fileName",true);
  fSetRootFileNameCmd->SetDefaultValue ("test1.root");
  fSetRootFileNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

RunMessenger::~RunMessenger()
{
  delete fSetRootFileNameCmd; 
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void RunMessenger::SetNewValue(G4UIcommand* command, G4String newValues)
{
                 
  if (command == fSetRootFileNameCmd) {
    G4cout << "\n---> root name from file: " << newValues << G4endl;
    fRun->SetROOTFullName(newValues);
  } 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

   
