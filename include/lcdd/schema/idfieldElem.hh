// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/idfieldElem.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $
#ifndef LCDD_SCHEMA_IDFIELDELEM_HH
#define LCDD_SCHEMA_IDFIELDELEM_HH 1

// GDML
#include "Saxana/SAXObject.h"

// LCDD
#include "IdFieldType.hh"

/**
 * @brief
 *  The idfield element from the schema.
 */
class idfieldElem: public SAXObject, public IdFieldType {
public:

    /**
     * Class constructor.
     */
    idfieldElem() {
    }

    /**
     * Class destructor.
     */
    virtual ~idfieldElem() {
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
