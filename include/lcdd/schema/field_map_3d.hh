#ifndef LCDD_SCHEMA_FIELD_MAP_3D_HH_
#define LCDD_SCHEMA_FIELD_MAP_3D_HH_ 1

// LCDD
#include "FieldMap3DType.hh"

/**
 * @brief The field_map_3d type from the schema.
 */
class field_map_3d: public SAXObject, public FieldMap3DType {

public:

    /**
     * Class constructor.
     */
    field_map_3d() {
    }

    /**
     * Class destructor.
     */
    virtual ~field_map_3d() {
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
