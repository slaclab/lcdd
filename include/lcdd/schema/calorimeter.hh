#ifndef LCDD_SCHEMA_CALORIMETER_HH_
#define LCDD_SCHEMA_CALORIMETER_HH_ 1

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
