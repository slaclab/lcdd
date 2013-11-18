// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/header.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_HEADER_HH
#define LCDD_SCHEMA_HEADER_HH 1

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
