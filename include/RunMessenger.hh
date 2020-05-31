#ifndef RunMessenger_h
#define RunMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"
#include "B1DetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class Run;
class G4UIdirectory;
class G4UIcmdWithAString;
//class B1DetectorConstruction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class RunMessenger: public G4UImessenger
{
  public:
   RunMessenger(Run* run);
   ~RunMessenger();

   virtual void SetNewValue(G4UIcommand* ,G4String );
  private:
   Run*             fRun;
  // B1DetectorConstruction* fdetector;
   G4UIdirectory*         fFileNameDir;
   G4UIcmdWithAString*    fSetRootFileNameCmd;   
  // G4UIcmdWithAString*    fSetThickCmd;  
};

#endif

