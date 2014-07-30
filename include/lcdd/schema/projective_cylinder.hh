#ifndef LCDD_SCHEMA_PROJECTIVE_CYLINDER_HH_
#define LCDD_SCHEMA_PROJECTIVE_CYLINDER_HH_ 1

// LCDD
#include "ProjectiveCylinderSegmentationType.hh"

// GDML
#include "Saxana/SAXObject.h"

/**
 * @brief The projective_cylinder element from the schema.
 */
class projective_cylinder: public SAXObject, public ProjectiveCylinderSegmentationType {

public:

    /**
     * Class constructor.
     */
    projective_cylinder() {
    }

    /**
     * Class destructor.
     */
    virtual ~projective_cylinder() {
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
