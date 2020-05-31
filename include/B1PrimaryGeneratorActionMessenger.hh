#ifndef B1PrimaryGeneratorActionMessenger_h
#define B1PrimaryGeneratorActionMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class B1PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
//class B1DetectorConstruction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class B1PrimaryGeneratorActionMessenger: public G4UImessenger
{
  public:
   B1PrimaryGeneratorActionMessenger(B1PrimaryGeneratorAction* generator);
   ~B1PrimaryGeneratorActionMessenger();

   virtual void SetNewValue(G4UIcommand* ,G4String );
  private:
   //Run*             fRun;
    B1PrimaryGeneratorAction* fgenerator;
  // B1DetectorConstruction* fdetector;
   G4UIdirectory*         fFileNameDir;
   G4UIcmdWithAString*    fCmd;  
   //G4UIcmdWithADoubleAndUnit* fCmd; 
  // G4UIcmdWithAString*    fSetThickCmd;  
};

#endif

