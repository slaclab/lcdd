#ifndef LCDD_SCHEMA_DIPOLE_HH_
#define LCDD_SCHEMA_DIPOLE_HH_

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
