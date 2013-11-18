// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/global_field.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_GLOBAL_FIELD_HH
#define LCDD_SCHEMA_GLOBAL_FIELD_HH 1

// GDML
#include "Saxana/SAXObject.h"

// LCDD
#include "GlobalFieldType.hh"

/**
 * @brief The global_field element from the schema.
 */
class global_field: public SAXObject, public GlobalFieldType {
public:

    /**
     * Class constructor.
     */
    global_field() {
    }

    /**
     * Class destructor.
     */
    virtual ~global_field() {
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
