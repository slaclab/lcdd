// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/calorimeter.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $
#ifndef LCDD_SCHEMA_CALORIMETER_HH
#define LCDD_SCHEMA_CALORIMETER_HH 1

// GDML
#include "Saxana/SAXObject.h"

// LCDD
#include "CalorimeterType.hh"

/**
 * @brief The calorimeter element from the schema.
 */
class calorimeter: public SAXObject, public CalorimeterType {
public:

    /**
     * Class constructor.
     */
    calorimeter() {
    }

    /**
     * Class destructor.
     */
    virtual ~calorimeter() {
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
