#ifndef LCDD_SCHEMA_HIT_PROCESSOR_HH_
#define LCDD_SCHEMA_HIT_PROCESSOR_HH_ 1

// LCDD
#include "lcdd/schema/HitProcessorType.hh"

// GDML
#include "Saxana/SAXObject.h"

class hit_processor: public SAXObject, public HitProcessorType {

public:

    /**
     * Class constructor.
     */
    hit_processor() {
    }

    /**
     * Class destructor.
     */
    virtual ~hit_processor() {
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
