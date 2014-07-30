#ifndef LCDD_SCHEMA_FIELDMAPTYPE_HH_
#define LCDD_SCHEMA_FIELDMAPTYPE_HH_ 1

// LCDD
#include "FieldType.hh"

// GDML
#include "Schema/ContentGroup.h"
#include "Schema/ReferenceType.h"

/**
 * @brief The FieldMapType from the schema.
 */
class FieldMapType: public FieldType {
public:

    /**
     * Class constructor.
     */
    FieldMapType() {
    }

    /**
     * Class destructor.
     */
    virtual ~FieldMapType() {
    }

public:

    /**
     * Get the element content.
     * @return The element's content.
     */
    const ContentSequence* get_content() const {
        return &_sequence;
    }

    /**
     * Add content.
     * @param tag The tag of the child.
     * @param so The SAXObject of the child.
     */
    void add_content(const std::string& tag, SAXObject* so) {
        ContentGroup::ContentItem ci = { tag, so };
        _sequence.add_content(ci);
    }

public:

    ContentSequence _sequence;

};

#endif
