// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/id/IdManager.hh,v 1.7 2013-11-14 00:47:20 jeremy Exp $

#ifndef LCDD_IDMANAGER_HH
#define LCDD_IDMANAGER_HH 1

// LCDD
#include "lcdd/id/IdSpec.hh"
#include "lcdd/id/IdVec.hh"
#include "lcdd/geant4/PhysVolId.hh"
#include "lcdd/geant4/PhysVolIdMap.hh"

// Geant4
#include "G4VPhysicalVolume.hh"

// STL
#include <map>
#include <string>
#include <iostream>

class G4LogicalVolume;

/**
 * @brief Singleton manager class for geometric ID objects.
 * @note It mainly provides utility functions based on G4VPhysicalVolume pointers.
 */
class IdManager {

public:
    typedef std::map<std::string, IdSpec*> IdSpecs;

public:

    /**
     * Class destructor.
     */
    virtual ~IdManager();

    /**
     * Get the class's singleton instance.
     * @return The singleton instance.
     */
    static IdManager* instance();

private:

    /**
     * Class constructor.
     * Private as access is through singleton.
     */
    IdManager();

public:

    /**
     * Add an IdSpec by name.
     * @param[in] name The name of the IdSpec.
     * @param[in] spec The IdSpec.
     */
    void addIdSpec(const std::string& name, IdSpec* spec);

    /**
     * Get an IdSpec by name.
     * @param[in] name The name of the IdSpec.
     * @return The IdSpec with name.
     */
    IdSpec* getIdSpec(const char* name);

    /**
     * Get an IdSpec by name.
     * @param[in] name The name of the IdSpec.
     * @return The IdSpec with name.
     */
    IdSpec* getIdSpec(const std::string& name);

    /**
     * Get an iterator pointing to the first IdSpec.
     * @return An iterator pointing to the first IdSpec.
     */
    IdSpecs::const_iterator getIdSpecsBegin();

    /**
     * Get an iterator pointing to the end of the IdSpec list.
     * @return An iterator pointing to the end of the IdSpec list.
     */
    IdSpecs::const_iterator getIdSpecsEnd();

    /**
     * Get the map of names to IdSpec objects.
     * @return The IdSpec map.
     */
    const IdSpecs* getIdSpecStore();

    /**
     * Add a PhysVolId.
     * @param[in] lvMom
     * @param[in] childIdx
     * @param[in] childId
     * @todo This method should be moved to another class.
     */
    void addPhysVolId(G4LogicalVolume* lvMom, int childIdx, PhysVolId childId);

    /**
     * Check if volume has PhysVolId.
     * @param[in] pv The G4VPhysicalVolume object.
     * @return True if volume has PhysVolId; false if not.
     * @todo This method should be moved to another class.
     */
    bool hasPhysVolIds(G4VPhysicalVolume* pv) const;

    /**
     * Get the map of PhysVolId objects.
     * @todo This method should be moved to another class.
     * @return The map of PhysVolId objects.
     */
    const PhysVolIdMap& getPhysVolIdMap() const;

    /**
     * Get the PhysVolId objects for a given physical volume.
     * @param[in] pv The G4VPhysicalVolume object.
     * @return The PhysVolId objects associated to the volume.
     */
    PhysVolId::PhysVolIds& getPhysVolIds(G4VPhysicalVolume* pv);

    /**
     * Print out the IdVec.
     * @param[in] os  The output stream.
     * @param[in] ids The list of IDs to print.
     */
    static void printIds(std::ostream& os, const IdVec& ids);

private:

    // static singleton instance
    static IdManager* _instance;

    // id specifications by name
    IdSpecs _idSpecs;

    // map of PV ids
    PhysVolIdMap _physVolIdMap;
};

#endif
