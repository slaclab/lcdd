#ifndef LCDD_SCHEMA_AUTHOR_HH_
#define LCDD_SCHEMA_AUTHOR_HH_ 1

#include "Saxana/SAXObject.h"

#include "AuthorType.hh"

/**
 * @brief The author element from the schema.
 */
class author: public SAXObject, public AuthorType {
public:

    /**
     * Class constructor.
     */
    author() {
    }

    /**
     * Class destructor.
     */
    virtual ~author() {
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
