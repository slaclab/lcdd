#ifndef LCDD_SCHEMA_GLOBALFIELDTYPE_HH_
#define LCDD_SCHEMA_GLOBALFIELDTYPE_HH_ 1

// GDML
#include "Schema/ContentGroup.h"

/**
 * @brief The GlobalFieldType from the schema.
 */
class GlobalFieldType {
public:

    /**
     * Class constructor.
     */
    GlobalFieldType() {
    }

    /**
     * Class destructor.
     */
    virtual ~GlobalFieldType() {
    }

    /**
     * Get the content of the field.
     * @return The content of the XML element.
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

private:

    ContentSequence _sequence;
};

#endif
