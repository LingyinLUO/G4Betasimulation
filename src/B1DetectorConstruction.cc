#include "B1DetectorConstruction.hh"
#include "B1DetectorConstructionMessenger.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4Material.hh"
#include "G4RotationMatrix.hh"
#include "G4UniformMagField.hh"
#include "G4TransportationManager.hh"
#include "G4FieldManager.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4VisAttributes.hh"




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
    : G4VUserDetectorConstruction(),
    fScoringVolume(0),detector_position((position_list.at(1)-200)*mm)
{
    phy_cylinder = 0;
    chamberYPos = 0;
    cylinderZ = 0;
    logicalwindow_vacuum = 0;
    logicalvacuumBox = 0;
    world_mat =0;
    fAlthick = 0.2*mm ;
    fDetectorConstructionMessenger = new B1DetectorConstructionMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
    // Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* materialAl   = nist->FindOrBuildMaterial("G4_Al");


    //define the NaI
    G4Element* Na = new G4Element("Sodium"   ,"Na", 11., 22.99*g/mole);
    G4Element* I  = new G4Element("Iodine"   ,"I" , 53., 126.90*g/mole);
    G4Material* NaI = new G4Material("NaI", 3.67*g/cm3, 2);
    NaI->AddElement(Na, 1);
    NaI->AddElement(I , 1);
    NaI->GetIonisation()->SetMeanExcitationEnergy(452*eV);

    //switch of check overlap
    G4bool checkOverlaps = true;

    // ===================================================================================
    // World
    G4double world_sizeX  = 1.5*400*mm;
    G4double world_sizeY  = 1.5*250*mm;
    G4double world_sizeZ  = 1.5*60*mm;
    //world material
    world_mat = nist->FindOrBuildMaterial("G4_AIR");

    G4Box* solidWorld =    
        new G4Box("World",                       //its name
                0.5*world_sizeX, 0.5*world_sizeY, 0.5*world_sizeZ);     //its size    
    G4LogicalVolume* logicWorld =                         
        new G4LogicalVolume(solidWorld,          //its solid
                world_mat,           //its material
                "World");            //its name                                 
    G4VPhysicalVolume* physWorld = 
        new G4PVPlacement(0,                     //no rotation
                G4ThreeVector(),       //at (0,0,0)
                logicWorld,            //its logical volume
                "World",               //its name
                0,                     //its mother  volume
                false,                 //no boolean operation
                0,                     //copy number
                checkOverlaps);        //overlaps checking
    // ===================================================================================

    // ===================================================================================
    // Al_chamber 
    G4Box* chamber = new G4Box("chamber", 0.5*400*mm, 0.5*200*mm, 0.5*20*mm);
    G4LogicalVolume* logicalChamber =
        new G4LogicalVolume(chamber,          //its solid
                materialAl,           //its material
                "chamber");            //its name
    chamberYPos = 25./250.*world_sizeY;
    G4VPhysicalVolume* physChamber = 
        new G4PVPlacement(0,                     //no rotation
                G4ThreeVector(0,chamberYPos ,0),       //at (0,0,0)
                logicalChamber,            //its logical volume
                "chamber",               //its name
                logicWorld,                     //its mother  volume
                false,                 //no boolean operation
                0,                     //copy number
                checkOverlaps);        //overlaps checking
    // ===================================================================================

    // ===================================================================================
    // Fe plane
    G4Box* FePlane = new G4Box("FePlane", 0.5*400*mm, 0.5*200*mm, 0.5*5*mm);
    G4Material* materialFe   = nist->FindOrBuildMaterial("G4_Fe");
    G4LogicalVolume* logicalFePlane =
        new G4LogicalVolume(FePlane,          //its solid
                materialFe,           //its material
                "FePlane");            //its name
    new G4PVPlacement(0,                     //no rotation
            G4ThreeVector(0,chamberYPos,(20.+5.)*0.5*mm),       //at (0,0,0)
            logicalFePlane,            //its logical volume
            "FePlane1",               //its name
            logicWorld,                     //its mother  volume
            false,                 //no boolean operation
            0,                     //copy number
            checkOverlaps);        //overlaps checking    
    new G4PVPlacement(0,                     //no rotation
            G4ThreeVector(0,chamberYPos,-(20.+5.)*0.5*mm),       //at (0,0,0)
            logicalFePlane,            //its logical volume
            "FePlane2",               //its name
            logicWorld,                     //its mother  volume
            false,                 //no boolean operation
            0,                     //copy number
            checkOverlaps);        //overlaps checking 
    // =================================================================================== 

    // =================================================================================== 
    // vacuum box
    //G4Material* materialVacuum   = nist->FindOrBuildMaterial("G4_Galactic");
    double density     = CLHEP::universe_mean_density;
    double pressure    = 3.e-18*pascal;
    double temperature = 2.73*kelvin;
    G4Material* materialVacuum = new G4Material("Galactic", 1., 1.01*g/mole,                                                                       
            density,kStateGas,temperature,pressure);
    G4Box* vacuumBox = new G4Box("vacuumBox", (0.5*400-3.)*mm, (0.5*200-3.)*mm, (0.5*20-3)*mm);
    logicalvacuumBox =
        new G4LogicalVolume(vacuumBox,          //its solid
                materialVacuum,           //its material
                "vacuumBox");            //its name
    new G4PVPlacement(0,                     //no rotation
            G4ThreeVector(0,0,0),       //at (0,0,0)
            logicalvacuumBox,            //its logical volume
            "vacuumBox",               //its name
            logicalChamber,                     //its mother  volume
            false,                 //no boolean operation
            0,                     //copy number
            checkOverlaps);        //overlaps checking   
    // =================================================================================== 

    // =================================================================================== 
    // window air + Polystyrene 
    G4Element * elC=new G4Element("Carbon","C",6.,12.01*g/mole );
    G4Element * elH=new G4Element("Hydrogen", "H2", 1., 1.01*g/mole);
    G4Material * Polystyrene = new G4Material("Polystyrene",1.032*g/cm3,2);
    Polystyrene->AddElement(elC, 8);
    Polystyrene->AddElement(elH, 8);

    /*G4Tubs* window_vacuum = new G4Tubs("windows_vacuum", 
      0,               //Rmin
      (5)*mm,       //Rmax
      0.5*3*mm,   //deltaZ
      0,               //Phimin
      360*degree);     //Phimax
      */
    G4Box* window_vacuum = new G4Box("window_vacuum", 5*mm,  5*mm, 0.5*3*mm);
    logicalwindow_vacuum =
        new G4LogicalVolume(window_vacuum,          //its solid
                materialVacuum,           //its material
                "windows_vacuum");            //its name

    /*G4Tubs* window_Polystyrene = new G4Tubs("window_Polystyrene", 
      0,               //Rmin
      (5)*mm,       //Rmax
      0.5*0.2*mm,   //deltaZ
      0,               //Phimin
      360*degree);     //Phimax
      */
    G4Box* window_Polystyrene = new G4Box("window_vacuum", 5*mm,  5*mm, 0.5*0.2*mm);
    G4LogicalVolume* logicalwindow_Polystyrene =
        new G4LogicalVolume(window_Polystyrene,          //its solid
                Polystyrene,           //its material
                "window_Polystyrene");            //its name
    //put Polystyrene in window_vacuum
    new G4PVPlacement(  0,
            G4ThreeVector(0,0,(0.5*3-0.1)*mm),
            logicalwindow_Polystyrene,            //its logical volume
            "window_Polystyrene",               //its name
            logicalwindow_vacuum,                     //its mother  volume
            false,                 //no boolean operation
            0,                     //copy number
            checkOverlaps);        //overlaps checking  

    //place the window 
    for(unsigned int i=0; i<position_list.size(); i++){
        G4RotationMatrix rotm1 = G4RotationMatrix();
        rotm1.rotateX(90*degree);
        double window_position = (position_list.at(i)-200)*mm;
        G4ThreeVector position1(window_position,-((0.5*200-3./2))*mm,0);
        G4Transform3D transform1(rotm1,position1);    
        new G4PVPlacement( transform1,
                logicalwindow_vacuum,            //its logical volume
                "windows_vacuum",               //its name
                logicalChamber,                     //its mother  volume
                false,                 //no boolean operation
                0,                     //copy number
                checkOverlaps);        //overlaps checking   
    }
    // =================================================================================== 

    // ===================================================================================

    cylinderZ = (20+1+0.2)*mm;
    // Cylinder 
    G4Tubs*  solid_cylinder = 
        new G4Tubs("Cylinder",                        //its name
                0,                                //Rmin
                (20+1)*mm,                     //+1 is al surface        //Rmax
                0.5*(cylinderZ),                             //deltaZ
                0,                                //Phimin
                360*degree);                      //Phimax
    G4LogicalVolume* log_cylinder = 
        new G4LogicalVolume(solid_cylinder,
                materialVacuum,                      //material
                "Cylinder");                      //name  
    G4RotationMatrix rotm = G4RotationMatrix();
    rotm.rotateX(90*degree);
    G4ThreeVector position(detector_position,chamberYPos-100*mm-0.5*(cylinderZ)-20*0.5*mm,0);
    G4Transform3D transform(rotm,position);                                                                           
    phy_cylinder = new G4PVPlacement( transform,                       //no rotation
            log_cylinder,                //its logical volume
            "Cylinder",              //its name
            logicWorld,              //its mother  volume
            false,                   //no boolean operation
            0,                       //copy number
            checkOverlaps);          //overlaps checking
    // ===================================================================================

    // ===================================================================================

    // CylinderAl
    G4Tubs*  Alcylinder = 
        new G4Tubs("AlCylinder",                        //its name
                20,                                //Rmin
                (20+1)*mm,                     //+1 is al surface        //Rmax
                0.5*cylinderZ,                             //deltaZ
                0,                                //Phimin
                360*degree);                      //Phimax
    G4LogicalVolume* log_cylinder_Al = 
        new G4LogicalVolume(Alcylinder,
                materialAl,                      //material
                "CylinderAl");                      //name                                                                    
    new G4PVPlacement( 0,                       //no rotation
              G4ThreeVector(0,0,0),            
            log_cylinder_Al,                //its logical volume
            "CylinderAl",              //its name
            log_cylinder,              //its mother  volume
            false,                   //no boolean operation
            0,                       //copy number
            checkOverlaps);          //overlaps checking
    // ===================================================================================

    // ===================================================================================
    double NaIcylinderZ = (10)*mm; 
    G4Tubs*  solid_cylinder_NaI = 
        new G4Tubs("CylinderNaI",                        //its name
                0,                                //Rmin
                (20)*mm,                             //Rmax
                0.5*NaIcylinderZ,                             //deltaZ
                0,                                //Phimin
                360*degree);                      //Phimax
    G4LogicalVolume* log_cylinder_NaI = 
        new G4LogicalVolume(solid_cylinder_NaI,
                NaI,                      //material
                "CylinderNaI");                      //name                                                                   
    new G4PVPlacement( 0,                       //no rotation
            //G4ThreeVector(0,0.4*mm,0),
            G4ThreeVector(0,0,-0.4*mm),
            log_cylinder_NaI,                //its logical volume
            "CylinderNaI",              //its name
            log_cylinder,              //its mother  volume
            false,                   //no boolean operation
            0,                       //copy number
            checkOverlaps);          //overlaps checking
    // ===================================================================================

    // ===================================================================================
double Alslice_height=fAlthick;
 G4Tubs*  solidAlslice
    = new G4Tubs("Alslice",                        //its name                                               
                 0,                             //Rmin
                 20*mm,                             //Rmax
                 0.5*Alslice_height,                             //deltaZ
                 0.,                                //Phimin
                 CLHEP::twopi);                      //Phimax
  G4LogicalVolume* logicAlslice
    = new G4LogicalVolume(solidAlslice,                       
materialAl,                      //material
                          "Alslice");                      //name
  new G4PVPlacement( 0,
                         G4ThreeVector(0,0,-6*mm),
                         logicAlslice,                //its logical volume
                         "Alslice",              //its name
                         log_cylinder,              //its mother  volume
                         false,                   //no boolean operation
                         0,                       //copy number
                         checkOverlaps);          //overlaps checking
 // ===================================================================================

    // ===================================================================================

    // half plane before dectector
    //the other half
    G4Box* left_plane_Al = new G4Box("left_plane",                 //its name
            0.5*20*mm, 0.5*10*mm, 0.5*45*mm);     //its size 
    G4LogicalVolume* log_left_plane_Al = 
        new G4LogicalVolume(left_plane_Al,
                materialAl,                      //material
                "left_plane");                      //name                                                                            
    phy_left_plane_Al = new G4PVPlacement( 0,                       //no rotation
            G4ThreeVector(detector_position-11.5*mm,chamberYPos-100*mm-10*0.5*mm,0),
            log_left_plane_Al,                //its logical volume
            "left_plane",              //its name
            logicWorld,              //its mother  volume
            false,                   //no boolean operation
            0,                       //copy number
            checkOverlaps);          //overlaps checking

    //the other half
    G4Box* right_plane_Al = new G4Box("right_plane",                 //its name
            0.5*20*mm, 0.5*10*mm, 0.5*45*mm);     //its size 
    G4LogicalVolume* log_right_plane_Al = 
        new G4LogicalVolume(right_plane_Al,
                materialAl,                      //material
                "right_plane");                      //name                                                                            
    phy_right_plane_Al = new G4PVPlacement( 0,                       //no rotation
            G4ThreeVector(detector_position+11.5*mm,chamberYPos-100*mm-10*0.5*mm,0),
            log_right_plane_Al,                //its logical volume
            "right_plane",              //its name
            logicWorld,              //its mother  volume
            false,                   //no boolean operation
            0,                       //copy number
            checkOverlaps);          //overlaps checking
    // ===================================================================================

    // ===================================================================================
    //PMT_glass after NaI
G4Material* materialGlass   = nist->FindOrBuildMaterial("G4_GLASS_PLATE");
    double PMTcylinderZ = (2)*mm; 
    G4Tubs*  solid_cylinder_PMT = 
        new G4Tubs("CylinderPMT",                        //its name
                0,                                //Rmin
                (20)*mm,                             //Rmax
                0.5*PMTcylinderZ,                             //deltaZ
                0,                                //Phimin
                360*degree);                      //Phimax
    G4LogicalVolume* log_cylinder_PMT = 
        new G4LogicalVolume(solid_cylinder_PMT,
                materialGlass,                      //material
                "CylinderPMT");                      //name                                                                   
    new G4PVPlacement( 0,                       //no rotation
            //G4ThreeVector(0,-8*mm,0),
            G4ThreeVector(0,0,8*mm),
            log_cylinder_PMT,                //its logical volume
            "CylinderPMT",              //its name
            log_cylinder,              //its mother  volume
            false,                   //no boolean operation
            0,                       //copy number
            checkOverlaps);          //overlaps checking



    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ===================================================================================
    // magnetic

    G4UniformMagField* magField = 
        new G4UniformMagField(G4ThreeVector(0.,0.,-655.5*gauss)); //define the magnetic.
    G4FieldManager* fieldMgr =new G4FieldManager(); 
    fieldMgr->SetDetectorField(magField);
    fieldMgr->CreateChordFinder(magField);

    G4bool allLocal = true; 
    logicalChamber->SetFieldManager(fieldMgr, allLocal);
    logicalFePlane->SetFieldManager(fieldMgr, allLocal);


   G4GlobalMagFieldMessenger* fMagFieldMessenger=new G4GlobalMagFieldMessenger();
   G4ThreeVector fieldValue = G4ThreeVector();
   fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
   fMagFieldMessenger->SetVerboseLevel(1);
  
   // Register the field messenger for deleting
   G4AutoDelete::Register(fMagFieldMessenger);



  //===================================================================================  
  // Visualization 
  //===================================================================================  

    G4VisAttributes* boxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0)); //white
    G4VisAttributes* hatVisAtt= new G4VisAttributes(G4Colour(1.0,0.0,0.0)); //red
    G4VisAttributes* chamberVisAtt = new G4VisAttributes(G4Colour(0.5,0.5,0.5));//gray
    G4VisAttributes* AbsorborVisAtt = new G4VisAttributes(G4Colour(0.0,0.0,1.0));//blue
    G4VisAttributes* WindowVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));//yellow

    logicWorld->SetVisAttributes(boxVisAtt);
    logicalvacuumBox->SetVisAttributes(boxVisAtt);
    log_left_plane_Al->SetVisAttributes(boxVisAtt);
    log_right_plane_Al->SetVisAttributes(boxVisAtt);
    logicAlslice->SetVisAttributes(WindowVisAtt);
    logicalChamber->SetVisAttributes(chamberVisAtt);
    logicalFePlane->SetVisAttributes(hatVisAtt);
    log_cylinder_NaI->SetVisAttributes(AbsorborVisAtt);
    logicalwindow_vacuum->SetVisAttributes(WindowVisAtt);
    log_cylinder_PMT->SetVisAttributes(chamberVisAtt);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ===================================================================================
    // the volume which we want to record.                              
    fScoringVolume = log_cylinder_NaI;

    //always return the physical World
    return physWorld;
}


void B1DetectorConstruction::set_position(int i){
    if ( !( i>0 and i<9 ) ){
        G4cout << "the position is not in [1,8], use 1 instead."<<G4endl;
        detector_position = (position_list.at(1)-200-G4UniformRand()*5)*mm;
    }
    else{
        detector_position = (position_list.at(i)-200-G4UniformRand()*5)*mm;
    }
    phy_cylinder->SetTranslation(G4ThreeVector(detector_position,chamberYPos-100*mm-0.5*(cylinderZ)-10*mm,0));
    phy_left_plane_Al->SetTranslation(G4ThreeVector(detector_position-15.75*mm,chamberYPos-100*mm-10*0.5*mm,0));        
    phy_right_plane_Al->SetTranslation(G4ThreeVector(detector_position+15.75*mm,chamberYPos-100*mm-10*0.5*mm,0));        
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::set_material(G4String name){
    if (name == "air"){
        logicalwindow_vacuum->SetMaterial(world_mat);
        logicalvacuumBox-> SetMaterial(world_mat);
        G4RunManager::GetRunManager()->PhysicsHasBeenModified();
    }
}


void B1DetectorConstruction::set_Althick(G4double val)
{ 
  fAlthick = val;
  if(fScoringVolume) { G4RunManager::GetRunManager()->PhysicsHasBeenModified(); }
}


