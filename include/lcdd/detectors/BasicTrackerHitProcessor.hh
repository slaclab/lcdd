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
    BasicTrackerHitProcessor();

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
 * @brief
 * The factory for creating new BasicTrackerHitProcessor objects.
 */
class BasicTrackerHitProcessorFactory: public HitProcessorFactory {

public:

    HitProcessor* createHitProcessor() {
        return new BasicTrackerHitProcessor();
    }

    const std::string& handlesType() {
        static std::string typeName = "BasicTrackerHitProcessor";
        return typeName;
    }
};

#endif
