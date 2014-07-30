#ifndef LCDD_SCHEMA_PHYSVOLID_HH_
#define LCDD_SCHEMA_PHYSVOLID_HH_ 1

// GDML
#include "Saxana/SAXObject.h"

// LCDD
#include "PhysVolIdType.hh"

/**
 * @brief The physvolid element from the schema.
 */
class physvolidElem: public SAXObject, public PhysVolIdType {

public:

    /**
     * Class constructor.
     */
    physvolidElem() {
    }

    /**
     * Class destructor.
     */
    virtual ~physvolidElem() {
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
