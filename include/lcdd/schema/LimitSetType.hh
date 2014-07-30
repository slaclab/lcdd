#ifndef LCDD_SCHEMA_LIMITSETTYPE_HH_
#define LCDD_SCHEMA_LIMITSETTYPE_HH_ 1

// GDML
#include "Schema/ContentGroup.h"
#include "Schema/ReferenceType.h"

// std
#include <string>

/**
 * @brief The LimitSetType type from the schema.
 */
class LimitSetType {

public:

    /**
     * @brief Reference to a limitset element.
     */
    class limitsetref: public SAXObject, public ReferenceType {
    public:

        /**
         * Class constructor.
         */
        limitsetref() {
        }

        /**
         * Class destructor.
         */
        virtual ~limitsetref() {
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
    LimitSetType() {
    }

    /**
     * Class destructor.
     */
    virtual ~LimitSetType() {
    }

    /**
     * Set the name of the limit set.
     * @param n The name of the limit set.
     */
    void set_name(const std::string& n) {
        _name = n;
    }

    /**
     * Get the name of the limit set.
     * @return The name of the limit set.
     */
    const std::string& get_name() const {
        return _name;
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

    /**
     * Get the child content.
     * @return The child content.
     */
    const ContentSequence* get_content() const {
        return &_sequence;
    }

private:

    ContentSequence _sequence;
    std::string _name;
};

#endif
