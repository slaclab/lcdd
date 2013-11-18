// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/idspecElem.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $
#ifndef LCDD_SCHEMA_IDSPECELEM_HH
#define LCDD_SCHEMA_IDSPECELEM_HH

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
