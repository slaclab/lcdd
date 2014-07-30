#ifndef LCDD_SCHEMA_NONPROJECTIVE_CYLINDER_HH_
#define LCDD_SCHEMA_NONPROJECTIVE_CYLINDER_HH_ 1

// LCDD
#include "NonprojectiveCylinderSegmentationType.hh"

// GDML
#include "Saxana/SAXObject.h"

/**
 * @brief The nonprojective_cylinder element from schema.
 */
class nonprojective_cylinder: public SAXObject, public NonprojectiveCylinderSegmentationType {

public:

    /**
     * Class constructor.
     */
    nonprojective_cylinder() {
    }

    /**
     * Class destructor.
     */
    virtual ~nonprojective_cylinder() {
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
