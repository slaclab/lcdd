// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/grid_xyz.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_GRID_XYZ_HH
#define LCDD_SCHEMA_GRID_XYZ_HH 1

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
