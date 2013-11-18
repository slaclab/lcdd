// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/detector.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_DETECTOR_HH
#define LCDD_SCHEMA_DETECTOR_HH 1

// GDML
#include "Saxana/SAXObject.h"

// LCDD
#include "DetectorType.hh"

/**
 * @brief The detector element from the schema, within the header block.
 */
class detector: public SAXObject, public DetectorType {
public:

    /**
     * Class constructor.
     */
    detector() {
    }

    /**
     * Class destructor.
     */
    virtual ~detector() {
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
