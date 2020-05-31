#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
//#include "B1DetectorConstructionMessenger.hh"
#include "globals.hh"
#include "G4RunManager.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class B1DetectorConstructionMessenger;

/// Detector construction class to define materials and geometry.

class B1DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    B1DetectorConstruction();
    virtual ~B1DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
    void set_position(int i);
    void set_material(G4String name);
    void set_Althick(G4double val);

  protected:
    G4LogicalVolume*  fScoringVolume;
    std::vector<double> position_list {60,140,165,190,215,240,265,290,315};
    double detector_position;
    //int fposition;
    B1DetectorConstructionMessenger* fDetectorConstructionMessenger;
    G4VPhysicalVolume* phy_cylinder;
    G4VPhysicalVolume* phy_left_plane_Al;
    G4VPhysicalVolume* phy_right_plane_Al;

    G4LogicalVolume* logicalwindow_vacuum;
    G4LogicalVolume* logicalvacuumBox;
    G4Material* world_mat;
    double chamberYPos;
    double cylinderZ;
    G4double fAlthick;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

