// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/region.hh,v 1.6 2013-11-14 00:47:22 jeremy Exp $

#ifndef LCDD_SCHEMA_REGION_HH
#define LCDD_SCHEMA_REGION_HH 1

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
