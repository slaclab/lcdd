// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/global_grid_xy.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $
#ifndef LCDD_SCHEMA_GLOBAL_GRID_XY_HH
#define LCDD_SCHEMA_GLOBAL_GRID_XY_HH 1

// LCDD
#include "GlobalGridXYSegmentationType.hh"

// GDML
#include "Saxana/SAXObject.h"

// STL
#include <string>

/**
 * @brief The global_grid_xy element from the schema.
 */
class global_grid_xy: public SAXObject, public GlobalGridXYSegmentationType {
public:

    /**
     * Class constructor.
     */
    global_grid_xy() {
    }

    /**
     * Class destructor.
     */
    virtual ~global_grid_xy() {
    }

public:

    /**
     * Get the type of this SAXObject.
     * @return The type of this SAXObject.
     */
    virtual SAXObject::Type type() {
        return SAXObject::element;
    }
};

#endif
