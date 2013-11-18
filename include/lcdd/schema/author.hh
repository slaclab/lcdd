// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/author.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_AUTHOR_HH
#define LCDD_SCHEMA_AUTHOR_HH 1

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
