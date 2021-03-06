#ifndef LCDD_SCHEMA_SOLENOID_HH_
#define LCDD_SCHEMA_SOLENOID_HH_ 1

// LCDD
#include "SolenoidType.hh"

// GDML
#include "Saxana/SAXObject.h"

/**
 * @brief The solenoid element from the schema.
 */
class solenoid: public SAXObject, public SolenoidType {
public:

    /**
     * Class constructor.
     */
    solenoid() {
    }

    /**
     * Class destructor.
     */
    virtual ~solenoid() {
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
