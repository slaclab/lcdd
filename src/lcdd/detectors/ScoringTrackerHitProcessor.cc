#include "lcdd/detectors/ScoringTrackerHitProcessor.hh"

// Geant4
#include "G4ThreeVector.hh"

ScoringTrackerHitProcessor::ScoringTrackerHitProcessor(TrackerSD* tracker) :
        TrackerHitProcessor(tracker), _currentTrackId(-1) {
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

        // get track information
        //TrackInformation* trkInfo = TrackInformation::getTrackInformation(step);

        // set hit flag in trk info
        //trkInfo->setHasTrackerHit(true);

        // Get track ID.
        G4int trackID = step->GetTrack()->GetTrackID();

        // Get time from pre-step point.
        G4double tdep = step->GetPreStepPoint()->GetGlobalTime();

        // create hit
        TrackerHit* newHit = new TrackerHit();

        // create id vector
        Id64bit id64 = _tracker->makeIdentifier(step);

        // Get the start position from the pre-step point.
        G4ThreeVector startPosition = step->GetPreStepPoint()->GetPosition();

        // Get the end position from the post-step point.
        G4ThreeVector endPosition = step->GetPostStepPoint()->GetPosition();

        // Compute the step's path length.
        G4double length = sqrt(pow(startPosition.x() - endPosition.x(), 2) + pow(startPosition.y() - endPosition.y(), 2) + pow(startPosition.z() - endPosition.z(), 2));

        // Set the hit information.
        newHit->setTrackID(trackID);
        newHit->setEdep(edep);
        newHit->setPosition(startPosition);
        newHit->setMomentum(step->GetPreStepPoint()->GetMomentum());
        newHit->setTdep(tdep);
        newHit->setId(id64.getId0());
        newHit->setLength(length);

        // Add hit to SD.
        _tracker->addHit(newHit, false);
    }
    return true;
}

