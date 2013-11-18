// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/detectors/HitComparator.hh,v 1.7 2013-11-14 00:47:19 jeremy Exp $
#ifndef LCDD_DETECTORS_HITCOMPARATOR_HH
#define LCDD_DETECTORS_HITCOMPARATOR_HH 1

// LCDD
#include "lcdd/hits/CalorimeterHit.hh"

/**
 * @class HitComparator
 * @brief Interface for comparing two LCDD CalorimeterHit objects.
 */
class HitComparator {

public:

    /**
     * Class destructor.
     */
    virtual ~HitComparator() {
    }

public:

    /**
     * Compare two hits for equality.  The compared parameters depends on the implementation.
     * @param[in] hit1 The first hit to compare.
     * @param[in] hit2 The second hit to compare.
     */
    virtual bool compare(const CalorimeterHit& hit1, const CalorimeterHit& hit2) const = 0;
};

#endif
