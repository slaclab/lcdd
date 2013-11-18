// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/rzb.hh,v 1.6 2013-11-14 00:47:22 jeremy Exp $
#ifndef LCDD_SCHEMA_RZB_HH
#define LCDD_SCHEMA_RZB_HH 1

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
