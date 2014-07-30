#ifndef LCDD_SCHEMA_VIS_HH_
#define LCDD_SCHEMA_VIS_HH_ 1

// GDML
#include "Saxana/SAXObject.h"

// LCDD
#include "VisType.hh"

/**
 * @brief The vis element from the schema.
 */
class vis: public SAXObject, public VisType {
public:

    /**
     * Class constructor.
     */
    vis() {
    }

    /**
     * Class destructor.
     */
    virtual ~vis() {
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
