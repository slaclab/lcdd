// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/generator.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_GENERATOR_HH
#define LCDD_SCHEMA_GENERATOR_HH 1

// GDML
#include "Saxana/SAXObject.h"

// LCDD
#include "GeneratorType.hh"

/**
 * @brief The generator element from the schema.
 */
class generator: public SAXObject, public GeneratorType {
public:

    /**
     * Class constructor.
     */
    generator() {
    }

    /**
     * Class destructor.
     */
    virtual ~generator() {
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
