// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/CalorimeterType.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_CALORIMETERTYPE_HH
#define LCDD_SCHEMA_CALORIMETERTYPE_HH 1

// GDML
#include "Schema/ContentGroup.h"

// LCDD
#include "SensitiveDetectorType.hh"

// STL
#include <iostream>

/**
 * @brief The CalorimeterType from the schema.
 */
class CalorimeterType: public SensitiveDetectorType {

public:

    /**
     * Class constructor.
     */
    CalorimeterType() {
    }

    /**
     * Class destructor.
     */
    virtual ~CalorimeterType() {
    }

public:

    /**
     * Get the child content of the element.
     * @return The child content.
     */
    const ContentSequence* get_content() const {
        return &_sequence;
    }

    /**
     * Add child content to the element.
     * @param tag The child tag to add.
     * @param so The SAXObject of the child.
     */
    void add_content(const std::string& tag, SAXObject* so) {
        ContentGroup::ContentItem ci = { tag, so };
        _sequence.add_content(ci);
    }

    /**
     * Set the comparison algorithm type.
     * @param compare The comparison algorithm type.
     */
    void set_compare(const std::string& compare) {
        _compare = compare;
    }

    /**
     * Get the comparison algorithm type.
     * @return The comparison algorithm type.
     */
    const std::string& get_compare() const {
        return _compare;
    }

private:

    ContentSequence _sequence;
    std::string _compare;
};

#endif
