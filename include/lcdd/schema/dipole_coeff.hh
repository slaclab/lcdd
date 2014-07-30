#ifndef LCDD_SCHEMA_DIPOLE_COEFF_HH_
#define LCDD_SCHEMA_DIPOLE_COEFF_HH_ 1

// LCDD
#include "DipoleCoeffType.hh"

/**
 * @brief The dipole_coeff element from the schema.
 */
class dipole_coeff: public SAXObject, public DipoleCoeffType {
public:

    /**
     * Class constructor.
     */
    dipole_coeff() {
    }

    /**
     * Class destructor.
     */
    virtual ~dipole_coeff() {
    }

    /**
     * Get the type of this SAXObject.
     * @return The type of this SAXObject.
     */
    virtual SAXObject::Type type() {
        return SAXObject::element;
    }
};

#endif
