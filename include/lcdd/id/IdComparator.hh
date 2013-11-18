// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/id/IdComparator.hh,v 1.8 2013-11-14 00:47:20 jeremy Exp $
#ifndef LCDD_IDCOMPARATOR_HH
#define LCDD_IDCOMPARATOR_HH 1

#include "lcdd/detectors/HitComparator.hh"

/**
 * @brief Compares the IDs of CalorimeterHit objects for equality.
 */
class IdComparator: public HitComparator {

public:

    /**
     * Class constructor.
     */
    IdComparator();

    /**
     * Class destructor.
     */
    virtual ~IdComparator();

public:

    /**
     * Compare the IDs of two CalorimeterHit objects.
     * @param[id] hit1 The first hit.
     * @param[id] hit2 The second hit.
     * @return True if the hit's IDs are equal; false if not.
     */
    bool compare(const CalorimeterHit& hit1, const CalorimeterHit& hit2) const;
};

#endif
