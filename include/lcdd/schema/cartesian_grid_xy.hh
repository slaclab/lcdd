/*
 * cartesian_grid_xy.hh
 *
 *  Created on: Aug 7, 2014
 *      Author: jeremym
 */

#ifndef LCDD_SCHEMA_CARTESIAN_GRID_XY_HH_
#define LCDD_SCHEMA_CARTESIAN_GRID_XY_HH_ 1

// LCDD
#include "lcdd/schema/CartesianGridXYType.hh"

// GDML
#include "Saxana/SAXObject.h"

/**
 * @brief cartesian_grid_xy element from the schema.
 */
class cartesian_grid_xy: public SAXObject, public CartesianGridXYType {

public:

    /**
     * Class constructor.
     */
    cartesian_grid_xy() {
    }

    /**
     * Class destructor.
     */
    virtual ~cartesian_grid_xy() {
    }

    /**
     * Get the type of this SAXObject.
     * @return The type of this SAXObject.
     */
    virtual SAXObject::Type type() {
        return SAXObject::element;
    }
};

#endif /* CARTESIAN_GRID_XY_HH_ */
