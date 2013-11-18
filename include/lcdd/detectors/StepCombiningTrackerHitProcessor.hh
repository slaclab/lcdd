// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/detectors/StepCombiningTrackerHitProcessor.hh,v 1.3 2013-11-14 00:47:19 jeremy Exp $

#ifndef LCDD_DETECTORS_STEPCOMBININGTRACKERHITPROCESSOR_HH
#define LCDD_DETECTORS_STEPCOMBININGTRACKERHITPROCESSOR_HH 1

// LCDD
#include "lcdd/detectors/TrackerHitProcessor.hh"
#include "lcdd/detectors/HitProcessorFactory.hh"

// Geant4
#include "G4Track.hh"

/**
 * TrackerHitProcessor that combines information from multiple steps
 * into a single TrackerHit.
 */
class StepCombiningTrackerHitProcessor: public TrackerHitProcessor {
public:

    /**
     * Class constructor.
     * @param[in] tracker Pointer to TrackerSD.
     */
    StepCombiningTrackerHitProcessor(TrackerSD* tracker);

    /**
     * Class destructor.
     */
    virtual ~StepCombiningTrackerHitProcessor();

    /**
     * Process steps to produce hits.
     * @param[in] step A G4Step object.
     * @return True if hit was created or modified; false if not.
     */
    bool processHits(G4Step* step);

private:

    /**
     * Start a new hit.
     * @param[in] step      The G4Step for the new hit.
     * @param[in] stepPoint The G4StepPoint for the new hit.
     */
    void startHit(G4Step* step, G4StepPoint* aStepPoint);

    /**
     * Update an existing hit with current step data.
     * @param[in] step A G4Step object.
     */
    void updateHit(G4Step* step);

    /**
     * Insert a new hit after all data is added.
     */
    bool insertHit(G4Step* step);

    /**
     * Clear the current hit.
     */
    void clear();

private:

    int _currentTrackID;
    G4VPhysicalVolume* _currentPV;
    G4ThreeVector _entryPoint;
    G4ThreeVector _exitPoint;
    G4ThreeVector _entryMomentum;
    G4ThreeVector _exitMomentum;
    G4double _edepTotal;
    G4double _minTime;
    bool _startedHit;
    G4Track* _currentTrack;
};

/**
 * The factory for creating new BasicTrackerHitProcessor objects.
 */
class StepCombiningTrackerHitProcessorFactory: public HitProcessorFactory {

public:

    HitProcessor* createHitProcessor(SensitiveDetector* sd) {
        return new StepCombiningTrackerHitProcessor(dynamic_cast<TrackerSD*>(sd));
    }

    const std::string& handlesType() {
        static std::string typeName = "StepCombiningTrackerHitProcessor";
        return typeName;
    }
};

#endif
