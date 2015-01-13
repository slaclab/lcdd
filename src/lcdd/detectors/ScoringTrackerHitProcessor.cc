#include "lcdd/detectors/ScoringTrackerHitProcessor.hh"

// LCDD
#include "lcdd/core/VUserTrackInformation.hh"
#include "lcdd/detectors/CurrentTrackState.hh"

// Geant4
#include "G4ThreeVector.hh"

ScoringTrackerHitProcessor::ScoringTrackerHitProcessor() :
    _currentTrackId(-1) {
}

ScoringTrackerHitProcessor::~ScoringTrackerHitProcessor() {
}

bool ScoringTrackerHitProcessor::processHits(G4Step* step) {
    bool sameTrack = false;

    int trackId = step->GetTrack()->GetTrackID();

    if ((_currentTrackId == -1) || (_currentTrackId != trackId)) {
        _currentTrackId = trackId;
    } else {
        sameTrack = true;
    }

    if (!sameTrack) {

        // edep
        G4double edep = step->GetTotalEnergyDeposit();

        // Get track ID.
        G4int trackID = step->GetTrack()->GetTrackID();

        // Get time from pre-step point.
        G4double tdep = step->GetPreStepPoint()->GetGlobalTime();

        // create hit
        TrackerHit* newHit = new TrackerHit();

        // create id vector
        Id64bit id64 = getTracker()->makeIdentifier(step);

        // Get the start position from the pre-step point.
        G4ThreeVector startPosition = step->GetPreStepPoint()->GetPosition();

        // Get the end position from the post-step point.
        G4ThreeVector endPosition = step->GetPostStepPoint()->GetPosition();

        // Compute the midpoint.
        G4ThreeVector midPoint = (0.5 * (step->GetPreStepPoint()->GetPosition() + step->GetPostStepPoint()->GetPosition()));

        // Compute the step's path length.
        G4double length = sqrt(pow(startPosition.x() - endPosition.x(), 2) + pow(startPosition.y() - endPosition.y(), 2) + pow(startPosition.z() - endPosition.z(), 2));

        VUserTrackInformation* trackInformation = dynamic_cast<VUserTrackInformation*>(step->GetTrack()->GetUserInformation());

        // Set the hit information.
        if (trackInformation != NULL) {
            trackInformation->setHasTrackerHit();
            newHit->setTrackID(trackID);
        } else {
            newHit->setTrackID(CurrentTrackState::getCurrentTrackID());
        }
        newHit->setEdep(edep);
        newHit->setPosition(midPoint);
        newHit->setMomentum(step->GetPreStepPoint()->GetMomentum());
        newHit->setTdep(tdep);
        newHit->setId(id64.getId0());
        newHit->setLength(length);

        // Get the TrackInformation and flag track as having a tracker hit.

        //if (trackInformation)
        //    trackInformation->setHasTrackerHit();
        //else
        //    G4Exception("ScoringTrackerHitProcessor::processHits", "", FatalException, "Missing required VUserTrackInformation.");

        // Add hit to detector.
        getTracker()->addHit(newHit, getCollectionIndex());
    }
    return true;
}

