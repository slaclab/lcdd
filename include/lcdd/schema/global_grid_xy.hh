#ifndef LCDD_SCHEMA_GLOBAL_GRID_XY_HH_
#define LCDD_SCHEMA_GLOBAL_GRID_XY_HH_ 1

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
