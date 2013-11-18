// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/bfield/MagneticFieldOverlay.hh,v 1.8 2013-11-14 00:47:19 jeremy Exp $
#ifndef LCDD_BFIELD_MAGNETICFIELDOVERLAY_HH
#define LCDD_BFIELD_MAGNETICFIELDOVERLAY_HH 1

// Geant4
#include "G4MagneticField.hh"

// STL
#include <vector>

/**
 * @brief Overlays B-field values from multiple G4MagneticField objects.
 */
class MagneticFieldOverlay: public G4MagneticField {
public:

    /**
     * Class constructor.
     */
    MagneticFieldOverlay();

    /**
     * Class destructor.
     */
    virtual ~MagneticFieldOverlay();

public:

    /**
     * Add a G4MagneticField to the overlay.
     * @param[in] field The magnetic field to add.
     */
    void addMagneticField(G4MagneticField* field);

    /**
     * Get the combined B-field at a point.
     * @param[in]  Point   The 3D point.
     * @param[out] Bfield  The output B-field values.
     */
    void GetFieldValue(const double Point[3], double *Bfield) const;

private:
    std::vector<G4MagneticField*> _fields;
};

#endif
