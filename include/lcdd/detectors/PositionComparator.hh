// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/detectors/PositionComparator.hh,v 1.7 2013-11-14 00:47:19 jeremy Exp $
#ifndef LCDD_DETECTORS_POSITIONCOMPARATOR_HH
#define LCDD_DETECTORS_POSITIONCOMPARATOR_HH 1

// LCDD
#include "HitComparator.hh"

/**
 * @brief HitComparator that compares CalorimeterHit objects for equality using their positions.
 */
class PositionComparator: public HitComparator {

public:

    /**
     * Class constructor.
     */
    PositionComparator();

    /**
     * Class destructor.
     */
    virtual ~PositionComparator();

public:

    /**
     * Compare two hits for equality by position.
     * @param[in] hit1 The first hit.
     * @param[in] hit2 The second hit.
     * @return True if positions are equal; false if not.
     */
    bool compare(const CalorimeterHit& hit1, const CalorimeterHit& hit2) const;
};

#endif
