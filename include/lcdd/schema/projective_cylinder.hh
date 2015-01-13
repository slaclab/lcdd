/*
 * projective_cylinder.hh
 *
 *  Created on: Aug 12, 2014
 *      Author: jeremym
 */

#ifndef LCDD_SCHEMA_PROJECTIVE_CYLINDER_HH_
#define LCDD_SCHEMA_PROJECTIVE_CYLINDER_HH_

// LCDD
#include "lcdd/schema/ProjectiveCylinderType.hh"

// GDML
#include "Saxana/SAXObject.h"


/**
 * @brief
 * The projective_cylinder type from the schema
 */
class projective_cylinder : public SAXObject, public ProjectiveCylinderType {

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

#endif /* PROJECTIVE_CYLINDER_HH_ */
