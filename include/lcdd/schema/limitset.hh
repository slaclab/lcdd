// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/limitset.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $
#ifndef LCDD_SCHEMA_LIMITSET_HH
#define LCDD_SCHEMA_LIMITSET_HH 1

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
