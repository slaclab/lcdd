#include "lcdd/detectors/StepCombiningTrackerHitProcessor.hh"

// Geant
#include "G4Geantino.hh"
#include "G4ChargedGeantino.hh"

StepCombiningTrackerHitProcessor::StepCombiningTrackerHitProcessor(TrackerSD* tracker) :
        TrackerHitProcessor(tracker), _currentTrackID(-1), _currentPV(0), _edepTotal(0.), _minTime(0.), _startedHit(false), _currentTrack(0) {
}

StepCombiningTrackerHitProcessor::~StepCombiningTrackerHitProcessor() {
}

G4bool StepCombiningTrackerHitProcessor::processHits(G4Step* step) {
    // The return value indicating whether a hit was inserted.
    bool r = false;

    // Started a hit already?
    if (!_startedHit) {

        // Start a new hit on the pre-step.
        startHit(step, step->GetPreStepPoint());
    }

    // Check if the cached trackID is valid.
    if (_currentTrackID != -1) {

        // Is this step's trackID different from the cached trackID?
        if (step->GetTrack()->GetTrackID() != _currentTrackID) {

            // Insert the hit on the old track.
            r = insertHit(step);

            // Start a new hit on the pre-step.
            startHit(step, step->GetPreStepPoint());
        }
    }

    // Update the hit.
    updateHit(step);

    // Check whether a new volume is being entered on this step.
    G4VPhysicalVolume* preVolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
    G4VPhysicalVolume* postVolume = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume();
    if (preVolume != postVolume) {

        // Insert the current hit.
        r = insertHit(step);

        // Check if pre and post steps have the same detector.
        G4VSensitiveDetector* preSD = preVolume->GetLogicalVolume()->GetSensitiveDetector();
        G4VSensitiveDetector* postSD = postVolume->GetLogicalVolume()->GetSensitiveDetector();
        if (preSD == postSD) {
            // Start a new hit for the adjacent volume.
            startHit(step, step->GetPostStepPoint());
        }
    } else if (_currentTrack->GetTrackStatus() == fStopAndKill) {
        // Special case where the track status is StopAndKill.
        // We won't see this track again, so need to insert the hit on this step.
        r = insertHit(step);
    }

    return r;
}

void StepCombiningTrackerHitProcessor::updateHit(G4Step* step) {
    // Update can only happen if a hit has been started.
    if (_startedHit) {

        // incr edep
        _edepTotal += step->GetTotalEnergyDeposit();

        // first time only
        if (_minTime == 0) {
            _minTime = step->GetTrack()->GetGlobalTime();
        }

        // exit point and momentum
        _exitPoint = step->GetPostStepPoint()->GetPosition();
        _exitMomentum = step->GetPostStepPoint()->GetMomentum();
    }
}

void StepCombiningTrackerHitProcessor::clear() {
    _minTime = 0;
    _edepTotal = 0;
    _currentPV = 0;
    _currentTrackID = -1;
    _startedHit = false;
}

bool StepCombiningTrackerHitProcessor::insertHit(G4Step* step) {
    // Another hit was not started.
    if (!_startedHit) {
        G4cerr << "StepCombiningTrackerHitProcessor::insertHit - Never started a hit!" << G4endl;
        return false;
    }

    // Check for Geantino particle type.
    G4ParticleDefinition* def = step->GetTrack()->GetDefinition();
    bool isGeantino = false;
    if (def == G4Geantino::Definition() || def == G4ChargedGeantino::Definition()) {
        isGeantino = true;
    }

    // Total energy is below cut.
    if (_edepTotal <= _tracker->getEnergyCut() && isGeantino == false) {
        clear();
        return false;
    }

    // Compute the mid point.
    G4ThreeVector midpoint = (0.5 * (_entryPoint + _exitPoint));

    // Compute the mean momentum.
    G4ThreeVector meanMomentum = (0.5 * (_entryMomentum + _exitMomentum));

    // Compute distance from entry to exit points.
    G4double pathlength = sqrt(
            pow(_entryPoint.x() - _exitPoint.x(), 2) +
            pow(_entryPoint.y() - _exitPoint.y(), 2) +
            pow(_entryPoint.z() - _exitPoint.z(), 2));

    // Set the hit data from the cache.
    TrackerHit* hit = new TrackerHit();
    hit->setTdep(_minTime);
    hit->setEdep(_edepTotal);
    hit->setPosition(midpoint);
    hit->setMomentum(meanMomentum);
    hit->setTrackID(_currentTrackID);
    hit->setLength(pathlength);

    // Set the hit's identifier.
    Id64bit id64 = _tracker->makeIdentifier(step);
    hit->setId(id64.getId0());

    // Add the hit to the TrackerSD.
    _tracker->addHit(hit);

    // Set tracker hit flag on track information.
    //TrackInformation* trackInfo = TrackInformation::getTrackInformation(_currentTrack);
    //if (trackInfo != 0) {
    //    trackInfo->setHasTrackerHit(true);
    //}

    // Clear the cached hit data.
    clear();

    return true;
}

void StepCombiningTrackerHitProcessor::startHit(G4Step* step, G4StepPoint* stepPoint) {
    _currentTrack = step->GetTrack();
    _currentPV = stepPoint->GetPhysicalVolume();
    _entryPoint = _exitPoint = stepPoint->GetPosition();
    _entryMomentum = _exitMomentum = stepPoint->GetMomentum();
    _currentTrackID = step->GetTrack()->GetTrackID();
    _startedHit = true;
}

