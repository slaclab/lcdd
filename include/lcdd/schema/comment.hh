#ifndef LCDD_SCHEMA_COMMENT_HH_
#define LCDD_SCHEMA_COMMENT_HH_ 1

// GDML
#include "Saxana/SAXObject.h"

// LCDD
#include "CommentType.hh"

/**
 * @brief The comment element from the schema.
 */
class comment: public SAXObject, public CommentType {
public:

    /**
     * Class constructor.
     */
    comment() {
    }

    /**
     * Class destructor.
     */
    virtual ~comment() {
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
