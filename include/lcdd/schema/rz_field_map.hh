// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/rz_field_map.hh,v 1.6 2013-11-14 00:47:22 jeremy Exp $

#ifndef LCDD_SCHEMA_RZ_FIELD_MAP_HH
#define LCDD_SCHEMA_RZ_FIELD_MAP_HH 1

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
