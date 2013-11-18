// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/dipole_coeff.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $
#ifndef LCDD_SCHEMA_DIPOLE_COEFF_HH
#define LCDD_SCHEMA_DIPOLE_COEFF_HH 1

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
