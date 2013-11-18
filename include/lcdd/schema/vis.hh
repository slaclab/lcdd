// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/vis.hh,v 1.6 2013-11-14 00:47:22 jeremy Exp $

#ifndef LCDD_SCHEMA_VIS_HH
#define LCDD_SCHEMA_VIS_HH 1

// GDML
#include "Saxana/SAXObject.h"

// LCDD
#include "VisType.hh"

/**
 * @brief The vis element from the schema.
 */
class vis: public SAXObject, public VisType {
public:

    /**
     * Class constructor.
     */
    vis() {
    }

    /**
     * Class destructor.
     */
    virtual ~vis() {
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
