#ifndef B1DetectorConstructionMessenger_h
#define B1DetectorConstructionMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"
//#include "B1DetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class B1DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
//class B1DetectorConstruction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class B1DetectorConstructionMessenger: public G4UImessenger
{
  public:
   B1DetectorConstructionMessenger(B1DetectorConstruction* detector);
   ~B1DetectorConstructionMessenger();

   virtual void SetNewValue(G4UIcommand* ,G4String );
  private:
   B1DetectorConstruction* fdetector;
   G4UIdirectory*         fFileNameDir;
   G4UIcmdWithAString*    fCmd1;  
   G4UIcmdWithAString*    fCmd2; 
   G4UIcmdWithADoubleAndUnit* fAlthickCmd;
   //G4UIcmdWithADoubleAndUnit* fCmd; 
  // G4UIcmdWithAString*    fSetThickCmd;  
};

#endif

