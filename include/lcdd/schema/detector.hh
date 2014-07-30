#ifndef LCDD_SCHEMA_DETECTOR_HH_
#define LCDD_SCHEMA_DETECTOR_HH_ 1

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
