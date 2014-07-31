#include "lcdd/detectors/LegacyCalorimeterHitProcessor.hh"

// LCDD
#include "lcdd/detectors/CurrentTrackState.hh"
#include "lcdd/util/TimerUtil.hh"

// Geant4
#include "G4Geantino.hh"
#include "G4ChargedGeantino.hh"

LegacyCalorimeterHitProcessor::LegacyCalorimeterHitProcessor(CalorimeterSD* calorimeter) :
        CalorimeterHitProcessor(calorimeter) {
}

LegacyCalorimeterHitProcessor::~LegacyCalorimeterHitProcessor() {
}

bool LegacyCalorimeterHitProcessor::processHits(G4Step* step) {

    // Get the energy deposition.
    G4double edep = step->GetTotalEnergyDeposit();

    // Check for Geantino particle type.
    G4ParticleDefinition* def = step->GetTrack()->GetDefinition();
    bool isGeantino = false;
    if (def == G4Geantino::Definition() || def == G4ChargedGeantino::Definition()) {
        isGeantino = true;
    }

    // Cut on energy deposition <= cut but allow Geantinos.
    if (edep <= _calorimeter->getEnergyCut() && isGeantino == false) {
        return false;
    }

    // Get the Segmentation from the CalorimeterSD.
    Segmentation* segmentation = _calorimeter->getSegmentation();

    // Get the global cell position from the Segmentation.
    G4ThreeVector globalCellPosition = segmentation->getGlobalHitPosition(step);

    // Set the segmentation bin values from the step.
    //segmentation->resetBins();
    segmentation->setBins(step);

    // Create a 64-bit ID from the step information.
    Id64bit id = _calorimeter->makeIdentifier(step);

    // Check for an existing hit with this identifier.
    CalorimeterHit* hit = _calorimeter->findHit(id);

    // Was there a hit found with this identifier?
    if (hit == NULL) {

        // No hit was found, so a new one is created.
        hit = new CalorimeterHit(id, edep, globalCellPosition);

        // Add the new hit to the calorimeter.
        _calorimeter->addHit(hit);

    } else {

        // Add energy deposition to an existing hit.
        hit->addEdep(edep);
    }

    // Add hit contribution to the hit.
    // FIXME: This should pass a pointer to a new object.  It is copied, which is inefficient.
    hit->addHitContribution(HitContribution(CurrentTrackState::getCurrentTrackID(), step));

    // Return true, indicating that a hit was added or modified.
    return true;
}
