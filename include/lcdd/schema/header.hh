#ifndef LCDD_SCHEMA_HEADER_HH_
#define LCDD_SCHEMA_HEADER_HH_ 1

// LCDD
#include "HeaderType.hh"

// GDML
#include "Saxana/SAXObject.h"

/**
 * @brief The header element from the schema.
 */
class header: public SAXObject, public HeaderType {
public:

    /**
     * Class constructor.
     */
    header() {
    }

    /**
     * Class destructor.
     */
    virtual ~header() {
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
