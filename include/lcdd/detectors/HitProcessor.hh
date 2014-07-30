#ifndef LCDD_DETECTORS_HITPROCESSOR_HH_
#define LCDD_DETECTORS_HITPROCESSOR_HH_ 1

// Geant4
#include "G4Step.hh"

/**
 * @brief Pure virtual class defining an interface for processing hits from within sensitive detectors.
 */
class HitProcessor {

protected:

    /**
     * Class constructor.
     */
    HitProcessor();

public:

    /**
     * Class destructor.
     */
    virtual ~HitProcessor();

    /**
     * Process steps to produce hits.
     * @param[in] step A G4Step object.
     * @return True if hits were created or modified; false if not.
     */
    virtual bool processHits(G4Step* step) = 0;
};

#endif
