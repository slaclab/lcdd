#ifndef LCDD_SCHEMA_GLOBAL_FIELD_HH_
#define LCDD_SCHEMA_GLOBAL_FIELD_HH_ 1

// GDML
#include "Saxana/SAXObject.h"

// LCDD
#include "GlobalFieldType.hh"

/**
 * @brief The global_field element from the schema.
 */
class global_field: public SAXObject, public GlobalFieldType {
public:

    /**
     * Class constructor.
     */
    global_field() {
    }

    /**
     * Class destructor.
     */
    virtual ~global_field() {
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
