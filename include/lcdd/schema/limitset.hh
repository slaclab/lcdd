#ifndef LCDD_SCHEMA_LIMITSET_HH_
#define LCDD_SCHEMA_LIMITSET_HH_ 1

// LCDD
#include "LimitSetType.hh"

// GDML
#include "Saxana/SAXObject.h"

/**
 * @brief The limitset element from the schema.
 */
class limitset: public SAXObject, public LimitSetType {
public:

    /**
     * Class constructor.
     */
    limitset() {
    }

    /**
     * Class destructor.
     */
    virtual ~limitset() {
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
