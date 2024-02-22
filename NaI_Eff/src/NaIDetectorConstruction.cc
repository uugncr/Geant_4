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
//
/// \file NaIDetectorConstruction.cc
/// \brief Implementation of the NaIDetectorConstruction class

#include "NaIDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4SystemOfUnits.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NaIDetectorConstruction::NaIDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NaIDetectorConstruction::~NaIDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* NaIDetectorConstruction::Construct()
{  
  static const double     pi  = 3.14159265358979323846;
  G4double rot = pi * 1.5; 

  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Materials
  //
  G4Material* world_mat     = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* crystal_mat   = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  G4Material* window_mat  = nist->FindOrBuildMaterial("G4_Be");
  G4Material* cap_mat        = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  G4Material* marinelli_mat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material* fill_mat          = nist->FindOrBuildMaterial("G4_WATER");
    
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;
  
  // Size of Geometric Objects
  //
  G4double det_r  = 3.0 * 2.54*cm/2.;
  G4double det_h = 3.0 * 2.54*cm/2.;
  G4double det_cap_r_in   = det_r;
  G4double det_cap_r_out = det_cap_r_in + 0.8*mm;
  G4double det_win_r = det_cap_r_in;
  G4double det_win_h = 75.0 * um/2.;
  
  G4double mb_t     = 1.5*mm;
  G4double mb_r_in   = det_cap_r_out ;
  G4double mb_r_out = mb_r_in + 27*mm;
  G4double mb_h1  = 76*mm/2. ;
  G4double mb_h2  = 130*mm/2.;


 
 G4double world_sizeXY = 15.0*cm;
 G4double world_sizeZ   = 15.0*cm;
 
 // Object Positioning
 //
 
 G4ThreeVector pos_Ded  = G4ThreeVector(0., 0., det_h + det_win_h*2.);
 G4ThreeVector pos_Cap  = G4ThreeVector(0., 0., det_h + det_win_h);
 G4ThreeVector pos_Win  = G4ThreeVector(0., 0., det_win_h);
 
 G4ThreeVector pos_MBa = G4ThreeVector(0., 0., mb_h1 );
 G4ThreeVector pos_MBb = G4ThreeVector(0., 0., 2.*mb_h1-mb_t/2.);
 G4ThreeVector pos_MBc = G4ThreeVector(0., 0., 2.*mb_h1-mb_h2);
 G4ThreeVector pos_MBd = G4ThreeVector(0., 0., -2.*(mb_h2-mb_h1)-mb_t/2.);
 G4ThreeVector pos_MBm = G4ThreeVector(0., 0., -mb_t/2.);

 G4ThreeVector pos_Fa     = G4ThreeVector(0., 0., -mb_h1);
 G4ThreeVector pos_F      = G4ThreeVector(0., 0., 2.*mb_h1-mb_h2-mb_t);
 
 // Geometric Definitions --> Solids
 //

  G4Box* solidWorld = new G4Box("World", 0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ); 

  
  G4Tubs* Detector =  new G4Tubs("Detector", 0., det_r, det_h, 0., rot);    
  G4Tubs* Det_Cap =  new G4Tubs("Det_Cap", det_cap_r_in, det_cap_r_out, det_h+det_win_h, 0., rot);    
  G4Tubs* Det_Win =  new G4Tubs("Det_Win", 0., det_win_r, det_win_h, 0., rot);    
  
  G4Tubs* MB_a  =  new G4Tubs("MB_a", mb_r_in, mb_r_in+mb_t , mb_h1, 0., rot);    
  G4Tubs* MB_b  =  new G4Tubs("MB_b", mb_r_out-mb_t , mb_r_out, mb_h2, 0., rot);    
  G4Tubs* MB_c  =  new G4Tubs("MB_c", 0., mb_r_in+mb_t , mb_t/2., 0., rot);    
  G4Tubs* MB_d  =  new G4Tubs("MB_d", mb_r_in+mb_t, mb_r_out-mb_t , mb_t/2., 0., rot);    
  G4Tubs* MB_e  =  new G4Tubs("MB_e", 0., mb_r_out, mb_t/2., 0., rot);    

 G4UnionSolid * MB_ac = new G4UnionSolid("a+c", MB_c, MB_a, 0, pos_MBa);
 G4UnionSolid * MB_acd = new G4UnionSolid("ac+d", MB_ac, MB_d, 0, pos_MBb);
 G4UnionSolid * MB_acdb = new G4UnionSolid("acd+b", MB_acd, MB_b, 0, pos_MBc);
 G4UnionSolid * MB_mar = new G4UnionSolid("acdb+e", MB_acdb, MB_e, 0, pos_MBd);
 //
  G4Tubs* Fill_a =  new G4Tubs("Fill_a", mb_r_in+mb_t, mb_r_out-mb_t, mb_h2, 0., rot);    
  G4Tubs* Fill_b =  new G4Tubs("Fill_b", 0., mb_r_in+mb_t,  mb_h2-mb_h1, 0., rot);    
  G4UnionSolid * Fillinig = new G4UnionSolid("Fillinig", Fill_a, Fill_b, 0, pos_Fa);
 
  // World
  
 G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");                     
 G4VPhysicalVolume* physWorld = new G4PVPlacement( 0, G4ThreeVector(), logicWorld, "World",0, false, 0, checkOverlaps);
  
  // Detector
 
  G4LogicalVolume* lg_Detector = new G4LogicalVolume(Detector, crystal_mat, "Crystall");
  G4PVPlacement*  phys_Detector = new G4PVPlacement(0, pos_Ded, lg_Detector, "Crystall", logicWorld, false, 0, checkOverlaps);
 
  G4LogicalVolume* lg_Cap = new G4LogicalVolume(Det_Cap, cap_mat, "Ded_Cap");
  G4PVPlacement*  phys_Cap = new G4PVPlacement(0, pos_Cap, lg_Cap, "Ded_Cap", logicWorld, false, 0, checkOverlaps);

  G4LogicalVolume* lg_Win = new G4LogicalVolume(Det_Win, window_mat, "Det_Win");
  G4PVPlacement*  phys_Win = new G4PVPlacement(0, pos_Win, lg_Win, "Det_Win", logicWorld, false, 0, checkOverlaps);

 // Marinelli Beaker

  G4LogicalVolume* lg_MB = new G4LogicalVolume(MB_mar, marinelli_mat, "Marinelli");
  G4PVPlacement*  phys_MB = new G4PVPlacement(0, pos_MBm, lg_MB, "Marinelli", logicWorld, false, 0, checkOverlaps);

 // Filling Volume as Source

  G4LogicalVolume* lg_Fill = new G4LogicalVolume(Fillinig, fill_mat, "Source");
  G4PVPlacement*  phys_Fill = new G4PVPlacement(0, pos_F, lg_Fill, "Source", logicWorld, false, 0, checkOverlaps);

 
  // Set Detector as scoring volume
  //
  fScoringVolume = lg_Detector;
   
  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
