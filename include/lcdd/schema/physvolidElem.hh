// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/physvolidElem.hh,v 1.6 2013-11-14 00:47:22 jeremy Exp $
#ifndef LCDD_SCHEMA_PHYSVOLID_HH
#define LCDD_SCHEMA_PHYSVOLID_HH 1

// GDML
#include "Saxana/SAXObject.h"

// LCDD
#include "PhysVolIdType.hh"

/**
 * @brief The physvolid element from the schema.
 */
class physvolidElem: public SAXObject, public PhysVolIdType {

public:

    /**
     * Class constructor.
     */
    physvolidElem() {
    }

    /**
     * Class destructor.
     */
    virtual ~physvolidElem() {
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
