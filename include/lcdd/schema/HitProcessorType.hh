// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/HitProcessorType.hh,v 1.4 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_HITPROCESSORTYPE_HH
#define LCDD_SCHEMA_HITPROCESSORTYPE_HH 1

// STL
#include <string>

// GDML
#include "Schema/ContentGroup.h"

/**
 * @brief
 * The HitProcessor from the XML schema.
 */
class HitProcessorType {

public:

    /**
     * Class constructor.
     */
    HitProcessorType();

    /**
     * Class destructor.
     */
    virtual ~HitProcessorType();

    /**
     * Set the type of the HitProcessor.
     * @param s The type of the HitProcessor.
     */
    void set_type(const std::string& s);

    /**
     * Get the type of the HitProcessor.
     * @return The type of the HitProcessor.
     */
    const std::string& get_type() const;

    /**
     * Add child content.
     * @param tag The tag of the child.
     * @param so The SAXObject of the child.
     */
    void add_content(const std::string& tag, SAXObject* so);

private:
    std::string _type;
    ContentSequence _sequence;
};

#endif
