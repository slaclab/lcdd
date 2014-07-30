#ifndef LCDD_SCHEMA_HEADERTYPE_HH_
#define LCDD_SCHEMA_HEADERTYPE_HH_ 1

// GDML
#include "Schema/ContentGroup.h"

// STL
#include <string>

/**
 * @brief The HeaderType from the schema.
 */
class HeaderType {
public:

    /**
     * Class constructor.
     */
    HeaderType() {
    }

    /**
     * Class destructor.
     */
    virtual ~HeaderType() {
    }

    /**
     * Add content.
     * @param tag The child tag.
     * @param so The SAXObject of the child.
     */
    void add_content(const std::string& tag, SAXObject* so) {
        ContentGroup::ContentItem ci = { tag, so };
        _sequence.add_content(ci);
    }

    /**
     * Get the child content.
     * @return The element's child content.
     */
    const ContentSequence* get_content() const {
        return &_sequence;
    }

private:

    ContentSequence _sequence;
};

#endif
