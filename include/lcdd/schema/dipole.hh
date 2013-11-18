// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/dipole.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $
#ifndef LCDD_SCHEMA_DIPOLE_HH
#define LCDD_SCHEMA_DIPOLE_HH

// GDML
#include "Saxana/SAXObject.h"

// LCDD
#include "DipoleType.hh"

/**
 * @brief The dipole element from the schema.
 */
class dipole: public SAXObject, public DipoleType {
public:

    /**
     * Class constructor.
     */
    dipole() {
    }

    /**
     * Class destructor.
     */
    virtual ~dipole() {
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
