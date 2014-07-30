#ifndef LCDD_DETECTORS_POSITIONCOMPARATOR_HH_
#define LCDD_DETECTORS_POSITIONCOMPARATOR_HH_ 1

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
