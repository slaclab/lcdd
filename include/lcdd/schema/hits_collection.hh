// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/hits_collection.hh,v 1.4 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_HITS_COLLECTION_HH
#define LCDD_SCHEMA_HITS_COLLECTION_HH 1

// LCDD
#include "lcdd/schema/HitsCollectionType.hh"

// GDML
#include "Saxana/SAXObject.h"

/**
 * @brief
 * The hits_collection element from the XML schema.
 */
class hits_collection: public SAXObject, public HitsCollectionType {

public:

    /**
     * Class constructor.
     */
    hits_collection();

    /**
     * Class destructor.
     */
    virtual ~hits_collection();

    /**
     * Get the type of this SAXObject.
     * @return The type of this SAXObject.
     */
    virtual SAXObject::Type type();
};

#endif
