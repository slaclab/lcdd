#ifndef LCDD_SCHEMA_LIMIT_HH_
#define LCDD_SCHEMA_LIMIT_HH_ 1

// LCDD
#include "LimitParamType.hh"

// GDML
#include "Saxana/SAXObject.h"

/**
 * @brief The limit element from the subschema.
 */
class limit: public SAXObject, public LimitParamType {
public:

    /**
     * Class constructor.
     */
    limit() {
    }

    /**
     * Class destructor.
     */
    virtual ~limit() {
    }

    /**
     * Get the type of the object which is XML element.
     * @return The type of the object.
     */
    virtual SAXObject::Type type() {
        return SAXObject::element;
    }
};

#endif
