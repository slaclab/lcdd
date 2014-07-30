#ifndef LCDD_BFIELD_FIELDMANAGER_HH_
#define LCDD_BFIELD_FIELDMANAGER_HH_ 1

// LCDD
#include "lcdd/bfield/MagneticFieldOverlay.hh"

// Geant4
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

class LCDDProcessor;

/**
 * @brief The manager for B-field implementation classes defined by LCDD.
 */
class FieldManager {

public:

    /**
     * Class destructor.
     */
    virtual ~FieldManager();

    /**
     * Get the static instance of this class.
     */
    static FieldManager* instance();

    /**
     * Setup the fields for the simulation run, combining multiple fields into an overlay.
     */
    void setup();

    /**
     * Add a global magnetic field.
     * @param[in] f The magnetic field.
     */
    void addGlobalField(G4MagneticField* f);

private:

    /**
     * Create an overlay from multiple magnetic field objects.
     * @param[in] The list of magnetic fields.
     * @return The overlay created from the list of fields.
     */
    MagneticFieldOverlay* makeOverlay(std::vector<G4MagneticField*> fields);

    /**
     * Get the overlay as a Geant4 implementation class.
     * @param[in] fields The list of magnetic fields.
     * @return The overlay as a G4MagneticField.
     */
    G4MagneticField* setup(std::vector<G4MagneticField*> fields);

    /**
     * Setup a single field from the G4TransportationManager.
     * @param[in] field The magnetic field to setup.
     */
    void initialize(G4MagneticField* field);

    /**
     * Add a magnetic field.
     * @param[in] f The magnetic field.
     */
    void addField(G4MagneticField* f);

private:

    /**
     * Class constructor, which is private.
     */
    FieldManager();

private:

    std::vector<G4MagneticField*> _globalfields;
    std::vector<G4MagneticField*> _allfields;

    static FieldManager* _instance;
};

#endif
