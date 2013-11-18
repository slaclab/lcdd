// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/bfield/Solenoid.hh,v 1.6 2013-11-14 00:47:19 jeremy Exp $

#ifndef LCDD_BFIELD_SOLENOID_HH
#define LCDD_BFIELD_SOLENOID_HH 1

// Geant4
#include "G4MagneticField.hh"

// STL
#include <iostream>

/**
 * @brief Implementation of a simple solenoidal field with fixed B-field values.
 * @todo Apply maximum Z value to cut-off field.
 */
class Solenoid: public G4MagneticField {

public:

    /**
     * Class constructor.
     * @todo Add fully qualified constructor.
     */
    Solenoid();

    /**
     * Class destructor.
     */
    virtual ~Solenoid();

public:

    /**
     * Implementation of G4MagneticField::Initialize to get B-field values from point.
     * @param[in]  Point  A 3D point in global coordinates.
     * @param[out] Bfield The B-field values at the point.
     * @todo Use the inner and outer Z values.  They are currently ignored!
     */
    void GetFieldValue(const double Point[3], double *Bfield) const;

    /**
     * Set the inner field value.
     * @param[in] d The inner field value.
     */
    void setInnerField(double d);

    /**
     * Set the outer field value.
     * @param[in] d The outer field value.
     */
    void setOuterField(double d);

    /**
     * Set the inner radius.
     * @param[in] d The inner radius.
     */
    void setInnerR(double d);

    /**
     * Set the outer radius.
     * @param[in] d The outer radius.
     */
    void setOuterR(double d);

    /**
     * Set the inner Z value.
     * @param[in] d The inner Z value.
     */
    void setInnerZ(double d);

    /**
     * Set the outer Z value.
     * @param[in] The outer Z value.
     */
    void setOuterZ(double d);

    /**
     * Get the B-field Z component within the inner radius.
     * @return The field value within the inner radius.
     */
    double getInnerField() const;

    /**
     * Get the B-field Z component between the inner and outer radii.
     * @return The field value outside the inner radius.
     */
    double getOuterField() const;

    /**
     * Get the inner radius.
     * @return The inner radius.
     */
    double getInnerR() const;

    /**
     * Get the outer radius.
     * @return The outer radius.
     */
    double getOuterR() const;

    /**
     * Get the inner Z value.
     * @return The inner Z value.
     *
     */
    double getInnerZ() const;

    /**
     * Get the outer Z value.
     * @return The outer Z value.
     */
    double getOuterZ() const;

    /**
     * Print the magnetic field's information to an output stream.
     * @param[in] os The output stream.
     */
    void printOut(std::ostream &os);

private:
    double _innerField;
    double _outerField;
    double _innerR;
    double _outerR;
    double _innerZ;
    double _outerZ;
};

#endif
