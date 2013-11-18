// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/bfield/Dipole.hh,v 1.7 2013-11-14 00:47:19 jeremy Exp $

#ifndef LCDD_BFIELD_DIPOLE_HH
#define LCDD_BFIELD_DIPOLE_HH 1

// Geant4
#include "G4MagneticField.hh"

// STL
#include <vector>

/**
 * @brief The Geant4 implementation of a parameterized dipole B-field with one or more numerical cofficients.
 * @todo This class's algorithm for computing B-field components from coefficients needs to be documented.
 */
class Dipole: public G4MagneticField {
public:

    /**
     * Class constructor.
     */
    Dipole();

    /**
     * Class destructor.
     */
    virtual ~Dipole();

public:

    /**
     * Compute the field value at a point.
     * @param[in] Point  The global position.
     * @param[in] Bfield The computed B-field data.
     */
    void GetFieldValue(const double Point[3], double *Bfield) const;

    /**
     * Set the max Z.
     * @param[in] The max Z.
     */
    void setZMax(double zmax);

    /**
     * Get the max Z.
     * @return The max Z.
     */
    double getZMax();

    /**
     * Set the max R.
     * @param[in] rmax The max R.
     */
    void setRMax(double rmax);

    /**
     * Get the max R.
     * @return The max R.
     */
    double getRMax();

    /**
     * Set the Z min.
     * @param[in] zmin The min Z.
     */
    void setZMin(double zmin);

    /**
     * Get the Z min.
     * @return The Z min.
     */
    double getZMin();

    /**
     * Add a dipole coefficient.
     * @param[in] coeff The numerical coefficient.
     */
    void addCoeff(double coeff);

    /**
     * Get the list of coefficients.
     * @return The list of dipole coefficients.
     */
    const std::vector<double>& getCoeffs();

    /**
     * Set the field unit in CLHEP system of units.
     * Default is Tesla.
     * @param[in] unit The field unit.
     */
    void setFieldUnit(double unit);

    /**
     * Get the field unit.
     * @return The field unit.
     */
    double getFieldUnit();

    /**
     * Set the length unit in CLHEP system of units.
     * Default is mm.
     * @param[in] unit The length unit.
     */
    void setLengthUnit(double unit);

    /**
     * Get the length unit.
     * @return The length unit.
     */
    double getLengthUnit();

private:
    double _zmin;
    double _zmax;
    double _rmax;
    double _lunit;
    double _funit;
    std::vector<double> _coeffs;
};

#endif
