#ifndef LCDD_SCHEMA_HITSCOLLECTIONTYPE_HH_
#define LCDD_SCHEMA_HITSCOLLECTIONTYPE_HH_ 1

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
    HitsCollectionType() {
    }

    /**
     * Class destructor.
     */
    virtual ~HitsCollectionType() {
    }

    /**
     * Set the name of the HitsCollection.
     * @param s The name of the HitsCollection.
     */
    void set_name(const std::string& s) {
        _name = s;
    }

    /**
     * Get the name of the HitsCollection.
     * @return The name of the HitsCollection.
     */
    const std::string& get_name() const {
        return _name;
    }

private:
    std::string _name;
};

#endif
