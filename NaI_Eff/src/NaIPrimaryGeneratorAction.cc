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
/// \file NaIPrimaryGeneratorAction.cc
/// \brief Implementation of the NaIPrimaryGeneratorAction class

#include "NaIPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NaIPrimaryGeneratorAction::NaIPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
  {
    G4int n_particle = 1;
    fParticleGun  = new G4ParticleGun(n_particle);
  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NaIPrimaryGeneratorAction::~NaIPrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NaIPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4ParticleTable *particleTable = G4ParticleTable ::GetParticleTable();
  G4String particleName = "gamma";
  G4ParticleDefinition *particle = particleTable ->FindParticle("gamma");
  //G4ThreeVector pos (0. ,0. ,0.); //posision
  G4ThreeVector mom (0. ,0. ,1.); //momentum 

  //fParticleGun ->SetParticlePosition(pos);
  fParticleGun ->SetParticleMomentumDirection(mom);
  fParticleGun ->SetParticleMomentum(1.*MeV);
  fParticleGun ->SetParticleDefinition(particle);

  //G4double 





  fParticleGun ->GeneratePrimaryVertex(anEvent);


}
  
  