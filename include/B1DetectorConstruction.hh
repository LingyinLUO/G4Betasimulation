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
// $Id: B1DetectorConstruction.hh 69565 2013-05-08 12:35:31Z gcosmo $
//
/// \file B1DetectorConstruction.hh
/// \brief Definition of the B1DetectorConstruction class

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
    //double position_list[9]={60,140,165,190,215,230,255,280,305};
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

