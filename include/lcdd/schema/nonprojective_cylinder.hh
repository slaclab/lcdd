// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/nonprojective_cylinder.hh,v 1.6 2013-11-14 00:47:22 jeremy Exp $

#ifndef LCDD_SCHEMA_NONPROJECTIVE_CYLINDER_HH
#define LCDD_SCHEMA_NONPROJECTIVE_CYLINDER_HH 1

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
