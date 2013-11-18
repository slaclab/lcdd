// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/color.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_COLOR_HH
#define LCDD_SCHEMA_COLOR_HH 1

// GDML
#include "Saxana/SAXObject.h"

// LCDD
#include "ColorType.hh"

/**
 * @brief The color element from the schema.
 */
class color: public SAXObject, public ColorType {
public:

    /**
     * Class constructor.
     */
    color() {
    }

    /**
     * Class destructor.
     */
    virtual ~color() {
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
