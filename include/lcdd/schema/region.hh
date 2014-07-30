#ifndef LCDD_SCHEMA_REGION_HH_
#define LCDD_SCHEMA_REGION_HH_ 1

// GDML
#include "Saxana/SAXObject.h"

// LCDD
#include "RegionType.hh"

/**
 * @brief The region element from the schema.
 */
class region: public SAXObject, public RegionType {
public:

    /**
     * Class constructor.
     */
    region() {
    }

    /**
     * Class destructor.
     */
    virtual ~region() {
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
