#ifndef B1ActionInitialization_h
#define B1ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "B1DetectorConstruction.hh"

/// Action initialization class.

class B1ActionInitialization : public G4VUserActionInitialization
{
  public:
    B1ActionInitialization();
    virtual ~B1ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
  private:
  	//B1DetectorConstruction * fdetector_construct; 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
