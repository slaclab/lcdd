#ifndef LCDD_SCHEMA_BOX_DIPOLE_HH_
#define LCDD_SCHEMA_BOX_DIPOLE_HH_ 1

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
