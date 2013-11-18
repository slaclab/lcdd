// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/hit_processor.hh,v 1.4 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_HITPROCESSOR_HH
#define LCDD_SCHEMA_HITPROCESSOR_HH 1

// LCDD
#include "lcdd/schema/HitProcessorType.hh"

// GDML
#include "Saxana/SAXObject.h"

class hit_processor: public SAXObject, public HitProcessorType {

public:

    /**
     * Class constructor.
     */
    hit_processor();

    /**
     * Class destructor.
     */
    virtual ~hit_processor();

    /**
     * Get the type of this SAXObject.
     * @return The type of this SAXObject.
     */
    virtual SAXObject::Type type();
};

#endif
