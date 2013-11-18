// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/detectors/HitProcessor.hh,v 1.4 2013-11-14 00:47:19 jeremy Exp $

#ifndef LCDD_DETECTORS_HITPROCESSOR_HH
#define LCDD_DETECTORS_HITPROCESSOR_HH 1

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
