// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/PhysVolIdType.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_PHYSVOLIDTYPE_HH
#define LCDD_SCHEMA_PHYSVOLIDTYPE_HH 1

// STL
#include <string>

/**
 * @brief The PhysVolIdType from the schema.
 */
class PhysVolIdType {

public:

    /**
     * Class constructor.
     */
    PhysVolIdType() {
    }

    /**
     * Class destructor.
     */
    virtual ~PhysVolIdType() {
    }

    /**
     * Set the value of the ID.
     * @param v The value of the ID.
     */
    void set_value(const std::string& v) {
        _value = v;
    }

    /**
     * Set the field name.
     * @param f The field name.
     */
    void set_field_name(const std::string& f) {
        _fieldName = f;
    }

    /**
     * Get the value of the ID.
     * @return The value of the ID.
     */
    const std::string& get_value() {
        return _value;
    }

    /**
     * Get the field name.
     * @return The field name.
     */
    const std::string& get_field_name() {
        return _fieldName;
    }

private:

    std::string _value;
    std::string _fieldName;
};

#endif
