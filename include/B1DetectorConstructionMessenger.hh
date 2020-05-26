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
/// \file electromagnetic/TestEm10/include/RunMessenger.hh
/// \brief Definition of the RunMessenger class
//

//
// $Id: RunMessenger.hh 94932 2015-12-18 09:21:29Z gcosmo $
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//#ifndef RunMessenger_h
//#define RunMessenger_h 1
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
   //Run*             fRun;
   B1DetectorConstruction* fdetector;
   G4UIdirectory*         fFileNameDir;
   G4UIcmdWithAString*    fCmd1;  
   G4UIcmdWithAString*    fCmd2; 
   G4UIcmdWithADoubleAndUnit* fAlthickCmd;
   //G4UIcmdWithADoubleAndUnit* fCmd; 
  // G4UIcmdWithAString*    fSetThickCmd;  
};

#endif

