// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/sensitive_detector.hh,v 1.6 2013-11-14 00:47:22 jeremy Exp $

#ifndef LCDD_SCHEMA_SENSITIVE_DETECTOR_HH
#define LCDD_SCHEMA_SENSITIVE_DETECTOR_HH 1

// LCDD
#include "SensitiveDetectorType.hh"

// GDML
#include "Saxana/SAXObject.h"

/**
 * @brief The sensitive_detector element from the schema.
 */
class sensitive_detector: public SAXObject, public SensitiveDetectorType {
public:

    /**
     * Class constructor.
     */
    sensitive_detector() {
    }

    /**
     * Class destructor.
     */
    virtual ~sensitive_detector() {
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
