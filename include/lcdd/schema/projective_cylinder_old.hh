#ifndef LCDD_SCHEMA_PROJECTIVE_CYLINDER_HH_
#define LCDD_SCHEMA_PROJECTIVE_CYLINDER_HH_ 1

// LCDD
#include "ProjectiveCylinderSegmentationType.hh"

// GDML
#include "Saxana/SAXObject.h"

/**
 * @brief
 * The projective_cylinder_old element from the schema.
 * @note
 * The projective_cylinder from DD4hep will replace this.
 */
class projective_cylinder_old: public SAXObject, public ProjectiveCylinderSegmentationType {

public:

    /**
     * Class constructor.
     */
    projective_cylinder_old() {
    }

    /**
     * Class destructor.
     */
    virtual ~projective_cylinder_old() {
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