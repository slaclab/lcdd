// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/detectors/ScoringTrackerHitProcessor.cc,v 1.4 2013-11-13 23:02:56 jeremy Exp $

// LCDD
#include "lcdd/detectors/ScoringTrackerHitProcessor.hh"
#include "lcdd/hits/TrackInformation.hh"

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
        G4double e = step->GetTotalEnergyDeposit();

        // get track information
        TrackInformation* trkInfo = TrackInformation::getTrackInformation(step);

        // set hit flag in trk info
        trkInfo->setHasTrackerHit(true);

        // hit data
        G4int trkID = trackId;
        G4double tdep = step->GetTrack()->GetGlobalTime();
        G4ThreeVector prePosition = step->GetPreStepPoint()->GetPosition();
        G4ThreeVector meanMomentum = 0.5 * (step->GetPreStepPoint()->GetPosition() + step->GetPostStepPoint()->GetPosition());

        // create hit
        TrackerHit* newHit = new TrackerHit();

        // create id vector
        Id64bit id64 = _tracker->makeIdentifier(step);

        // Get the start position from the pre-step point.
        G4ThreeVector start = step->GetPreStepPoint()->GetPosition();

        // Get the end position from the post-step point.
        G4ThreeVector end = step->GetPostStepPoint()->GetPosition();

        // Compute the step's path length.
        G4double length = sqrt(pow(start.x() - end.x(), 2) + pow(start.y() - end.y(), 2) + pow(start.z() - end.z(), 2));

        // Set the hit information.
        newHit->setTrackID(trkID);
        newHit->setEdep(e);
        newHit->setPosition(prePosition);
        newHit->setMomentum(meanMomentum);
        newHit->setTdep(tdep);
        newHit->setId(id64.getId0());
        newHit->setLength(length);

        // Add hit to SD.
        _tracker->addHit(newHit, false);
    }
    return true;
}

