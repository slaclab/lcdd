#ifndef LCDD_DETECTORS_TRACKERHITPROCESSOR_HH_
#define LCDD_DETECTORS_TRACKERHITPROCESSOR_HH_ 1

#include "lcdd/detectors/TrackerSD.hh"

/**
 * @brief The interface for hit processing in trackers.
 */
class TrackerHitProcessor: public HitProcessor {
public:

    /**
     * Class constructor.
     * @param[in] tracker Pointer to TrackerSD.
     */
    TrackerHitProcessor(TrackerSD* tracker);

    /**
     * Class destructor.
     */
    virtual ~TrackerHitProcessor();

    /**
     * Process hits to produce steps.
     * @param[in] step The G4Step object.
     * @return True if hits were created or modified; false if not.
     */
    virtual bool processHits(G4Step* step) = 0;

protected:

    TrackerSD* _tracker;
};

#endif
