/**
 * @mainpage Linear Collider Detector Description (LCDD) Documentation
 *
 * @par
 * LCDD is a framework for description of %detector geometries and associated information
 * at runtime using a XML language and parser.
 */
#ifndef LCDD_CORE_LCDDDETECTORCONSTRUCTION_HH_
#define LCDD_CORE_LCDDDETECTORCONSTRUCTION_HH_ 1

// Geant4
#include "G4VUserDetectorConstruction.hh"
#include "G4UImessenger.hh"

// STL
#include <string>

class LCDDDetectorConstructionMessenger;
class LCDDObjectStoreInspector;

/**
 * @brief Implementation of G4VUserDetectorConstruction for LCDD geometries.
 * @note This class has minimal functionality; it mostly hands control to other LCDD classes.
 */
class LCDDDetectorConstruction: public G4VUserDetectorConstruction {

public:

    /**
     * Class constructor.
     */
    LCDDDetectorConstruction();

    /**
     * Class destructor.
     */
    ~LCDDDetectorConstruction();

public:

    /**
     * Construct the geometry.
     * @return The world physical volume.
     */
    virtual G4VPhysicalVolume* Construct();

    /**
     * Set the world volume of the built geometry.
     * @param[in] pv The world's physical volume.
     */
    void setWorldVolume(G4VPhysicalVolume *pv);

    /**
     * Get the world volume of this construction.
     * @return The world volume.
     */
    G4VPhysicalVolume* getWorldVolume();

private:

    G4UImessenger* _messenger;
    G4UImessenger* _writerMessenger;
    G4VPhysicalVolume* _world;
    LCDDObjectStoreInspector* _inspector;

    std::string _URI;
    std::string _setupName;
    std::string _version;
};

#endif
