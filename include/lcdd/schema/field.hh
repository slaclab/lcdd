#ifndef LCDD_SCHEMA_FIELD_HH_
#define LCDD_SCHEMA_FIELD_HH_ 1

// GDML
#include "Saxana/SAXObject.h"

// LCDD
#include "FieldType.hh"

/**
 * @brief The field element from the schema.
 */
class field: public SAXObject, public FieldType {
public:

    /**
     * Class constructor.
     */
    field() {
    }

    /**
     * Class destructor.
     */
    virtual ~field() {
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
