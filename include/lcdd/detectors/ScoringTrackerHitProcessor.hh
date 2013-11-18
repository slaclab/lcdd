// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/detectors/ScoringTrackerHitProcessor.hh,v 1.3 2013-11-14 00:47:19 jeremy Exp $

#ifndef LCDD_DETECTORS_SCORINGTRACKERHITPROCESSOR_HH
#define LCDD_DETECTORS_SCORINGTRACKERHITPROCESSOR_HH 1

// LCDD
#include "lcdd/detectors/TrackerHitProcessor.hh"
#include "lcdd/detectors/HitProcessorFactory.hh"

/**
 * HitProcessor to implement scoring behavior, that only records a hit per track.
 */
class ScoringTrackerHitProcessor: public TrackerHitProcessor {

public:

    /**
     * Class constructor.
     * @param[in] tracker The tracker SD.
     */
    ScoringTrackerHitProcessor(TrackerSD* tracker);

    /**
     * Class destructor.
     */
    virtual ~ScoringTrackerHitProcessor();

    /**
     * Process steps to produce hits.
     * @param[in] step The G4Step object.
     */
    bool processHits(G4Step* step);

private:

    int _currentTrackId;
};

/**
 * The factory for creating new BasicTrackerHitProcessor objects.
 */
class ScoringTrackerHitProcessorFactory: public HitProcessorFactory {

public:

    HitProcessor* createHitProcessor(SensitiveDetector* sd) {
        return new ScoringTrackerHitProcessor(dynamic_cast<TrackerSD*>(sd));
    }

    const std::string& handlesType() {
        static std::string typeName = "ScoringTrackerHitProcessor";
        return typeName;
    }
};

#endif
