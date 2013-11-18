// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/limit.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $
#ifndef LCDD_SCHEMA_LIMIT_HH
#define LCDD_SCHEMA_LIMIT_HH 1

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
