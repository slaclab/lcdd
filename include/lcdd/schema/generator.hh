#ifndef LCDD_SCHEMA_GENERATOR_HH_
#define LCDD_SCHEMA_GENERATOR_HH_ 1

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
