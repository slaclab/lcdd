// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/detectors/UnsegmentedCalorimeterHitProcessor.cc,v 1.4 2013-11-13 23:02:56 jeremy Exp $

// LCDD
#include "lcdd/detectors/UnsegmentedCalorimeterHitProcessor.hh"

// Geant4
#include "G4Geantino.hh"
#include "G4ChargedGeantino.hh"

UnsegmentedCalorimeterHitProcessor::UnsegmentedCalorimeterHitProcessor(CalorimeterSD* calorimeter) :
        CalorimeterHitProcessor(calorimeter) {
}

UnsegmentedCalorimeterHitProcessor::~UnsegmentedCalorimeterHitProcessor() {
}

bool UnsegmentedCalorimeterHitProcessor::processHits(G4Step* step) {
    // Get the energy deposition.
    G4double edep = step->GetTotalEnergyDeposit();

    // Check for Geantino particle type.
    G4ParticleDefinition* def = step->GetTrack()->GetDefinition();
    bool isGeantino = false;
    if (def == G4Geantino::Definition() || def == G4ChargedGeantino::Definition()) {
        isGeantino = true;
    }

    // This needs to be a <= comparison for cutting on 0,
    // but it allows geantinos, which always have 0 edep.
    if (edep <= _calorimeter->getEnergyCut() && isGeantino == false) {
        return false;
    }

    // Get the step mid position.
    G4ThreeVector position = (0.5 * (step->GetPreStepPoint()->GetPosition() + step->GetPostStepPoint()->GetPosition()));

    // Create a 64-bit ID.
    Id64bit id = _calorimeter->makeIdentifier(step);

    // Create a new hit.
    CalorimeterHit* newHit = new CalorimeterHit(id, edep, position);

    // Add the hit to the SD.
    _calorimeter->addHit(newHit);

    // Add an MCParticle contribution for this hit.
    newHit->addHitContribution(HitContribution(step));

    // Return true because added hit.
    return true;

}

