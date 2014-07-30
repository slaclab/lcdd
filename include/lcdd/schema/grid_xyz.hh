#ifndef LCDD_SCHEMA_GRID_XYZ_HH_
#define LCDD_SCHEMA_GRID_XYZ_HH_ 1

// LCDD
#include "NonprojectiveSegmentationType.hh"

// GDML
#include "Saxana/SAXObject.h"

/**
 * @brief The grid_xyz element from the schema.
 */
class grid_xyz: public SAXObject, public NonprojectiveSegmentationType {

public:

    /**
     * Class constructor.
     */
    grid_xyz() {
    }

    /**
     * Class destructor.
     */
    virtual ~grid_xyz() {
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
