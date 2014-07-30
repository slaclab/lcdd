#ifndef LCDD_SCHEMA_PROJECTIVE_ZPLANE_HH_
#define LCDD_SCHEMA_PROJECTIVE_ZPLANE_HH_ 1

// LCDD
#include "ProjectiveZPlaneSegmentationType.hh"

// GDML
#include "Saxana/SAXObject.h"

/**
 * @brief The projective_zplane element from the schema.
 */
class projective_zplane: public SAXObject, public ProjectiveZPlaneSegmentationType {

public:

    /**
     * Class constructor.
     */
    projective_zplane() {
    }

    /**
     * Class destructor.
     */
    virtual ~projective_zplane() {
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
