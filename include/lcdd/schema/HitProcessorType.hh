#ifndef LCDD_SCHEMA_HITPROCESSORTYPE_HH_
#define LCDD_SCHEMA_HITPROCESSORTYPE_HH_ 1

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
