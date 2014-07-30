#ifndef LCDD_SCHEMA_SENSITIVE_DETECTOR_HH_
#define LCDD_SCHEMA_SENSITIVE_DETECTOR_HH_ 1

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
