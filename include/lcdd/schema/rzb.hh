#ifndef LCDD_SCHEMA_RZB_HH_
#define LCDD_SCHEMA_RZB_HH_ 1

// LCDD
#include "RZBType.hh"

// GDML
#include "Saxana/SAXObject.h"

/**
 * @brief The rzB element from the schema.
 */
class rzb: public SAXObject, public RZBType {
public:

    /**
     * Class constructor.
     */
    rzb() {
    }

    /**
     * Class destructor.
     */
    virtual ~rzb() {
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
