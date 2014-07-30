// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/hits/CalorimeterHitMap.hh,v 1.3 2013-11-14 00:47:20 jeremy Exp $

#ifndef LCDD_HITS_CALORIMETER_HITMAP_HH_
#define LCDD_HITS_CALORIMETER_HITMAP_HH_ 1

// LCDD
#include "lcdd/id/Id64bit.hh"
#include "lcdd/hits/CalorimeterHit.hh"

// STL
#include <map>

/**
 * @brief
 * This class maps CalorimeterHit objects to their 64-bit identifiers
 * for fast lookup with O(1) performance.
 */
class CalorimeterHitMap {

    /**
     * Type definition for map.
     */
    typedef std::map<Id64bit::ValueType, CalorimeterHit*> MapType;

public:

    /**
     * Class constructor.
     */
    CalorimeterHitMap();

    /**
     * Class destructor.
     */
    virtual ~CalorimeterHitMap();

    /**
     * Add a hit.
     * @param hit The hit to add.
     */
    void add(CalorimeterHit* hit);

    /**
     * Get a hit by its 64-bit identifier.
     * @param id The identifier of the hit.
     * @return The matching hit or 0 if does not exist.
     */
    CalorimeterHit* get(const Id64bit& id);

    /**
     * Get the size of the map.
     * @return The size of the map.
     */
    int size();

    /**
     * Clear all entries from this hit map.
     */
    void clear();

private:

    MapType _map;
};

#endif
