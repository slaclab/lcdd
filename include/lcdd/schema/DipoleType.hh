#ifndef LCDD_SCHEMA_DIPOLETYPE_HH_
#define LCDD_SCHEMA_DIPOLETYPE_HH_ 1

// LCDD
#include "FieldType.hh"

// GDML
#include "Schema/ContentGroup.h"

// STL
#include <string>

/**
 * @brief The DipoleType from the schema.
 */
class DipoleType: public FieldType {
public:

    /**
     * Class constructor.
     */
    DipoleType() {
    }

    /**
     * Class destructor.
     */
    virtual ~DipoleType() {
    }

public:

    /**
     * Set the maximum Z value.
     * @param s The max Z value.
     */
    void set_zmax(const std::string& s) {
        _zmax = s;
    }

    /**
     * Set the minimum Z value.
     * @param s
     */
    void set_zmin(const std::string& s) {
        _zmin = s;
    }

    /**
     * Set the maximum R value.
     * @param s
     */
    void set_rmax(const std::string& s) {
        _rmax = s;
    }

    /**
     * Get the minimum Z value.
     * @return The minimum Z value.
     */
    const std::string& get_zmin() const {
        return _zmin;
    }

    /**
     * Get the maximum Z value.
     * @return
     */
    const std::string& get_zmax() const {
        return _zmax;
    }

    /**
     * Get the maximum R value.
     * @return The maximum R value.
     */
    const std::string& get_rmax() const {
        return _rmax;
    }

    /**
     * Add child content.
     * @param tag The tag of the child.
     * @param so The SAXObject of the child.
     */
    void add_content(const std::string& tag, SAXObject* so) {
        ContentGroup::ContentItem ci = { tag, so };
        _sequence.add_content(ci);
    }

    /**
     * Get the content sequence of this element.
     * @return The content sequence of the element.
     */
    const ContentSequence* get_content() const {
        return &_sequence;
    }

private:

    std::string _zmax;
    std::string _zmin;
    std::string _rmax;
    ContentSequence _sequence;
};

#endif
