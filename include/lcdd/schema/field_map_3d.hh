// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/field_map_3d.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $
#ifndef LCDD_SCHEMA_FIELD_MAP_3D_HH
#define LCDD_SCHEMA_FIELD_MAP_3D_HH 1

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
