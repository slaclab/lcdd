// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/field.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_FIELD_HH
#define LCDD_SCHEMA_FIELD_HH 1

// GDML
#include "Saxana/SAXObject.h"

// LCDD
#include "FieldType.hh"

/**
 * @brief The field element from the schema.
 */
class field: public SAXObject, public FieldType {
public:

    /**
     * Class constructor.
     */
    field() {
    }

    /**
     * Class destructor.
     */
    virtual ~field() {
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
