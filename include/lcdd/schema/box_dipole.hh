// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/box_dipole.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_BOX_DIPOLE_HH
#define LCDD_SCHEMA_BOX_DIPOLE_HH 1

// LCDD
#include "BoxDipoleType.hh"

// GDML
#include "Saxana/SAXObject.h"

/**
 * @brief The box_dipole element from the schema.
 */
class box_dipole: public SAXObject, public BoxDipoleType {

public:

    /**
     * Class constructor.
     */
    box_dipole() {
    }

    /**
     * Class destructor.
     */
    virtual ~box_dipole() {
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
