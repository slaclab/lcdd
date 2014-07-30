#ifndef LCDD_ID_IDCOMPARATOR_HH_
#define LCDD_ID_IDCOMPARATOR_HH_ 1

// LCDD
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
