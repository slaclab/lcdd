#ifndef LCDD_SCHEMA_HITS_COLLECTION_HH_
#define LCDD_SCHEMA_HITS_COLLECTION_HH_ 1

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
    hits_collection() {
    }

    /**
     * Class destructor.
     */
    virtual ~hits_collection() {
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
