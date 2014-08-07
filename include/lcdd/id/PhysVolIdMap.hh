#ifndef LCDD_GEANT4_PHYSVOLTOIDMAP_HH_
#define LCDD_GEANT4_PHYSVOLTOIDMAP_HH_ 1

// LCDD
#include "PhysVolId.hh"

// G4
#include "G4VPhysicalVolume.hh"

// std
#include <vector>
#include <map>

/**
 * A map between volumes and their IDs.
 */
typedef std::map<G4VPhysicalVolume*, PhysVolId::PhysVolIds> PhysVolIdMapType;

/**
 * @brief Maps G4VPhysicalVolume pointers to a vector of associated ints for identification.
 */
class PhysVolIdMap: private PhysVolIdMapType {

public:

    /**
     * Class constructor.
     */
    PhysVolIdMap();

    /**
     * Class destructor.
     */
    virtual ~PhysVolIdMap();

    /**
     * Add an ID with a volume key.
     * @param[in] pv The G4VPhysicalVolume object.
     * @param[in] id The ID associated with the volume.
     */
    void addPhysVolId(G4VPhysicalVolume* pv, PhysVolId id);

    /**
     * Check whether the volume has a key in the map.
     * @param[in] pv The G4VPhysicalVolume object.
     * @return True if the volume has a key; false if not.
     */
    bool hasPhysVolIds(G4VPhysicalVolume* pv) const;

    /**
     * Get the PhysVolId objects associated with the volume key.
     * @return The list of PhysVolId objects associated with the volume key.
     */
    PhysVolId::PhysVolIds& getPhysVolIds(G4VPhysicalVolume* pv);

private:

    /**
     * Add an empty ID container for a volume key.
     * @param[in] pv The volume key.
     */
    void createPhysVolIds(G4VPhysicalVolume* pv);
};

#endif
