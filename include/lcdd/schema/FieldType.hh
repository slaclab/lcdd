// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/FieldType.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $
#ifndef LCDD_SCHEMA_FIELDTYPE_HH
#define LCDD_SCHEMA_FIELDTYPE_HH 1

// GDML
#include "Schema/ReferenceType.h"
#include "Saxana/SAXObject.h"

// STL
#include <string>

/**
 * @brief The FieldType from the schema.
 */
class FieldType {
public:

    /**
     * @class FieldType::fieldref
     * @brief A reference to a field element.
     */
    class fieldref: public SAXObject, public ReferenceType {

    public:

        /**
         * Class constructor.
         */
        fieldref() {
        }

        /**
         * Class destructor.
         */
        virtual ~fieldref() {
        }

        /**
         * Get the type of this SAXObject.
         * @return The type of this SAXObject.
         */
        virtual SAXObject::Type type() {
            return SAXObject::element;
        }
    };

public:

    /**
     * Class constructor.
     */
    FieldType() {
    }

    /**
     * Class destructor.
     */
    virtual ~FieldType() {
    }

    /**
     * Set the name of the field.
     * @param n The name of the field.
     */
    void set_name(const std::string& n) {
        _name = n;
    }

    /**
     * Get the name of the field.
     * @return The name of the field.
     */
    const std::string& get_name() const {
        return _name;
    }

    /**
     * Set the field unit.
     * @param s The field unit.
     */
    void set_funit(const std::string& s) {
        _funit = s;
    }

    /**
     * Set the length unit.
     * @param s The length unit.
     */
    void set_lunit(const std::string& s) {
        _lunit = s;
    }

    /**
     * Get the field unit.
     * @return The field unit.
     */
    const std::string& get_funit() const {
        return _funit;
    }

    /**
     * Get the length unit.
     * @return The length unit.
     */
    const std::string& get_lunit() const {
        return _lunit;
    }

private:

    std::string _name;
    std::string _funit;
    std::string _lunit;
};

#endif
