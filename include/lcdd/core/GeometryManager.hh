// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/core/GeometryManager.hh,v 1.6 2013-11-14 00:47:19 jeremy Exp $

#ifndef LCDD_GEOMETRYMANAGER_HH
#define LCDD_GEOMETRYMANAGER_HH 1

class G4Run;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4String;

/**
 * @brief Singleton geometry manager class with miscellaneous utility and management functions.
 */
class GeometryManager {
public:

    /**
     * Class destructor.
     */
    virtual ~GeometryManager();

    /**
     * Get the static instance of this class.
     * @return This class's singleton instance.
     */
    static GeometryManager* instance();

protected:

    /**
     * Class constructor which is protected.
     * @note Access an object of this class through its instance method.
     */
    GeometryManager();

public:

    /**
     * Get the world's logical volume from Geant4.
     * @return The current world's logical volume.
     */
    G4LogicalVolume* getWorldLogicalVolume() const;

    /**
     * Get the world's physical volume from Geant4.
     * @return The current world's physical volume.
     */
    G4VPhysicalVolume* getWorldPhysicalVolume() const;

    /**
     * Begin of run hook for geometry setup.
     * @param[in] run The G4Run that is starting.
     */
    void beginRun(const G4Run* run);

    /**
     * Attach the RegionInformation to the world's.
     */
    void setupWorldRegionInformation();

    /**
     * Check overlaps starting with the world volume and recursing to daughters.
     * @note Overlaps are printed to cout by Geant4.
     */
    void checkOverlaps() const;

    /**
     * Check for overlaps by calling CheckOverlaps on all daughters
     * of a given logical volume, with possible recursion to
     * daughters.
     * @note Overlaps are printed to cout by Geant4.
     */
    void checkOverlaps(G4LogicalVolume*, bool recurse = true) const;

    /**
     * Check for overlaps of a named logical volume by looking it
     * up in the volume store, with possible recursion to daughters.
     * @note Overlaps are print to cout by Geant4.
     */
    void checkOverlaps(const G4String&, bool recurse = true) const;

private:

    /** The static instance of this class. */
    static GeometryManager* m_instance;

    /** Indicates whether world region information was added or not. */
    bool m_worldRegionIsSetup;
};

#endif
