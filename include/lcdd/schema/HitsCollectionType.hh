// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/HitsCollectionType.hh,v 1.4 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_HITSCOLLECTIONTYPE_HH
#define LCDD_SCHEMA_HITSCOLLECTIONTYPE_HH 1

// STL
#include <string>

// GDML
#include "Schema/ContentGroup.h"

/**
 * @brief
 * The HitsCollectionType from the XML schema.
 */
class HitsCollectionType {

public:

    /**
     * Class constructor.
     */
    HitsCollectionType();

    /**
     * Class destructor.
     */
    virtual ~HitsCollectionType();

    /**
     * Set the name of the HitsCollection.
     * @param s The name of the HitsCollection.
     */
    void set_name(const std::string& s);

    /**
     * Get the name of the HitsCollection.
     * @return The name of the HitsCollection.
     */
    const std::string& get_name() const;

private:
    std::string _name;
};

#endif
