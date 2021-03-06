#include "lcdd/detectors/BasicTrackerHitProcessor.hh"

// LCDD
#include "lcdd/detectors/CurrentTrackState.hh"
#include "lcdd/core/VUserTrackInformation.hh"

// Geant4
#include "G4Geantino.hh"
#include "G4ChargedGeantino.hh"
#include "globals.hh"

BasicTrackerHitProcessor::BasicTrackerHitProcessor() {
}

BasicTrackerHitProcessor::~BasicTrackerHitProcessor() {
}

bool BasicTrackerHitProcessor::processHits(G4Step* step) {

    TrackerSD* tracker = getTracker();

    // Get the total energy deposition.
    G4double edep = step->GetTotalEnergyDeposit();

    // Check for Geantino particle type.
    G4ParticleDefinition* def = step->GetTrack()->GetDefinition();
    bool isGeantino = false;
    if (def == G4Geantino::Definition() || def == G4ChargedGeantino::Definition()) {
        isGeantino = true;
    }

    // Check edep < cut and not Geantino.
    if (edep <= tracker->getEnergyCut() && isGeantino == false) {
        return false;
    }

    // Get the track.
    G4Track* track = step->GetTrack();

    // Get the pre-step point.
    G4StepPoint* pre = step->GetPreStepPoint();

    // Get the post-step point.
    G4StepPoint* post = step->GetPostStepPoint();

    // Get the track ID.
    //G4int trackId = track->GetTrackID();
    G4int trackID = CurrentTrackState::getCurrentTrackID();

    // Get the global time (ns).
    G4double time = track->GetGlobalTime();

    // Compute the midpoint.
    G4ThreeVector mid = (0.5 * (pre->GetPosition() + post->GetPosition()));

    // Get the start position from the pre-step point.
    G4ThreeVector start = step->GetPreStepPoint()->GetPosition();

    // Get the end position from the post-step point.
    G4ThreeVector end = step->GetPostStepPoint()->GetPosition();

    // Compute the average momentum.
    double averageMomentum = (pre->GetMomentum().mag() + post->GetMomentum().mag()) / 2;

    // Compute the momentum.
    G4ThreeVector momentum = (end - start);

    // If the momentum is > 0 then set to average momentum.
    if (momentum.mag() > 0) {
        momentum.setMag(averageMomentum);
    }

    // Compute the step's path length.
    G4double length = sqrt(pow(start.x() - end.x(), 2) + pow(start.y() - end.y(), 2) + pow(start.z() - end.z(), 2));

    // Create the new hit.
    TrackerHit* hit = new TrackerHit();

    // Create the hit's identifier.
    Id64bit id64 = tracker->makeIdentifier(step);

    VUserTrackInformation* trackInformation =
            dynamic_cast<VUserTrackInformation*>(step->GetTrack()->GetUserInformation());

    // Set the hit information from above.
    if (trackInformation != NULL) {
        trackInformation->setHasTrackerHit();

        // Use the ID from this track, as it has track info for creating the TrackSummary.
        hit->setTrackID(trackID);
    } else {
        // In the case where there is no track info, then we use the current global track ID.
        hit->setTrackID(CurrentTrackState::getCurrentTrackID());
    }
    hit->setEdep(edep);
    hit->setPosition(mid);
    hit->setMomentum(momentum);
    hit->setTdep(time);
    hit->setId(id64.getId0());
    hit->setLength(length);

    // Add the hit to the TrackerSD.
    tracker->addHit(hit, _collectionIndex);

    // Return true because created new hit.
    return true;
}
