// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/IdSpecType.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_IDSPECTYPE_HH
#define LCDD_SCHEMA_IDSPECTYPE_HH 1

// GDML
#include "Processes/ReferenceTypeProcess.h"
#include "Schema/ContentGroup.h"

// STL
#include <string>

/**
 * @brief The IdSpecType from the schema.
 */
class IdSpecType {
public:

    /**
     * @class IdSpecType::idspecref
     * @brief A reference to an idspec element.
     *
     */
    class idspecref: public SAXObject, public ReferenceType {
    public:

        /**
         * Class constructor.
         */
        idspecref() {
        }

        /**
         * Class destructor.
         */
        virtual ~idspecref() {
        }

        /**
         * Get the type of this object which is XML element.
         * @return The type of this object.
         */
        virtual SAXObject::Type type() {
            return SAXObject::element;
        }
    };

public:

    /**
     * Class constructor.
     */
    IdSpecType() {
    }

    /**
     * Class destructor.
     */
    virtual ~IdSpecType() {
    }

    /**
     * Set the name of the IdSpec.
     * @param The name of the IdSpec.
     */
    void set_name(const std::string& n) {
        _name = n;
    }

    /**
     * Set the length.
     * @param The length.
     */
    void set_length(const std::string& l) {
        _length = l;
    }

    /**
     * Get the name.
     * @return The name.
     */
    const std::string& get_name() const {
        return _name;
    }

    /**
     * Get the length.
     * @return The length.
     */
    const std::string& get_length() const {
        return _length;
    }

    /**
     * Get the child content.
     * @return The child content.
     */
    const ContentSequence* get_content() const {
        return &_sequence;
    }

    /**
     * Add child content.
     * @param tag The child XML tag.
     * @param so The SAXObject of the child.
     */
    void add_content(const std::string& tag, SAXObject* so) {
        ContentGroup::ContentItem ci = { tag, so };
        _sequence.add_content(ci);
    }

private:

    std::string _name;
    std::string _length;
    ContentSequence _sequence;
};

#endif
