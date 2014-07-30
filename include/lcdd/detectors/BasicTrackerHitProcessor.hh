#ifndef LCDD_DETECTORS_BASICTRACKERHITPROCESSOR_HH_
#define LCDD_DETECTORS_BASICTRACKERHITPROCESSOR_HH_ 1

// LCDD
#include "lcdd/detectors/TrackerHitProcessor.hh"
#include "lcdd/detectors/HitProcessorFactory.hh"

/**
 * @brief Implements default TrackerSD hit processing behavior.
 */
class BasicTrackerHitProcessor: public TrackerHitProcessor {

public:

    /**
     * Class constructor.
     */
    BasicTrackerHitProcessor(TrackerSD* tracker);

    /**
     * Class destructor.
     */
    virtual ~BasicTrackerHitProcessor();

    /**
     * Process steps to produce hits.
     * @param[in] step A G4Step object.
     * @return True if hits were added or modified; false if not.
     */
    bool processHits(G4Step* step);
};

/**
 * The factory for creating new BasicTrackerHitProcessor objects.
 */
class BasicTrackerHitProcessorFactory: public HitProcessorFactory {

public:

    HitProcessor* createHitProcessor(SensitiveDetector* sd) {
        return new BasicTrackerHitProcessor(dynamic_cast<TrackerSD*>(sd));
    }

    const std::string& handlesType() {
        static std::string typeName = "BasicTrackerHitProcessor";
        return typeName;
    }
};

#endif
