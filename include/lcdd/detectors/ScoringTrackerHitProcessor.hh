#ifndef LCDD_DETECTORS_SCORINGTRACKERHITPROCESSOR_HH_
#define LCDD_DETECTORS_SCORINGTRACKERHITPROCESSOR_HH_ 1

// LCDD
#include "lcdd/detectors/TrackerHitProcessor.hh"
#include "lcdd/detectors/HitProcessorFactory.hh"

/**
 * @brief
 * HitProcessor to implement scoring behavior, that only records a hit per track
 */
class ScoringTrackerHitProcessor: public TrackerHitProcessor {

public:

    /**
     * Class constructor.
     * @param[in] tracker The tracker SD.
     */
    ScoringTrackerHitProcessor();

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
 * @brief
 * The factory for creating new ScoringTrackerHitProcessor objects
 */
class ScoringTrackerHitProcessorFactory: public HitProcessorFactory {

public:

    HitProcessor* createHitProcessor() {
        return new ScoringTrackerHitProcessor();
    }

    const std::string& handlesType() {
        static std::string typeName = "ScoringTrackerHitProcessor";
        return typeName;
    }
};

#endif
