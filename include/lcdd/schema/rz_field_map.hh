#ifndef LCDD_SCHEMA_RZ_FIELD_MAP_HH_
#define LCDD_SCHEMA_RZ_FIELD_MAP_HH_ 1

// LCDD
#include "RZFieldMapType.hh"

/**
 * @brief The rz_field_map element from the schema.
 */
class rz_field_map: public SAXObject, public RZFieldMapType {
public:

    /**
     * Class constructor.
     */
    rz_field_map() {
    }

    /**
     * Class destructor.
     */
    virtual ~rz_field_map() {
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
