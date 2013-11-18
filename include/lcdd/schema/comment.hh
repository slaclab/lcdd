// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/comment.hh,v 1.6 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_COMMENT_HH
#define LCDD_SCHEMA_COMMENT_HH 1

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
