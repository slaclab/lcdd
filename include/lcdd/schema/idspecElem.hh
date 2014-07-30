#ifndef LCDD_SCHEMA_IDSPECELEM_HH_
#define LCDD_SCHEMA_IDSPECELEM_HH_ 1

// LCDD
#include "IdSpecType.hh"

// GDML
#include "Saxana/SAXObject.h"

/**
 * @brief The idspec element from the schema.
 */
class idspecElem: public SAXObject, public IdSpecType {

public:

    /**
     * Class constructor.
     */
    idspecElem() {
    }

    /**
     * Class destructor.
     */
    virtual ~idspecElem() {
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
