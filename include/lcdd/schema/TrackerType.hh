#ifndef LCDD_SCHEMA_TRACKERTYPE_HH_
#define LCDD_SCHEMA_TRACKERTYPE_HH_ 1

// LCDD
#include "SensitiveDetectorType.hh"

// STL
#include <iostream>

/**
 * @brief The TrackerType from the schema.
 */
class TrackerType: public SensitiveDetectorType {

public:

    /**
     * Class constructor.
     */
    TrackerType() {
    }

    /**
     * Class destructor.
     */
    virtual ~TrackerType() {
    }

    /**
     * Set whether to combine hits across steps.
     * @param c Set combine hits.
     */
    void set_combine_hits(const std::string& c) {
        _combineHits = c;
    }

    /**
     * Get whether to combine hits across steps.
     * @return This returns "true" if hits are combined and "false" if not.
     */
    const std::string& get_combine_hits() const {
        return _combineHits;
    }

private:
    std::string _combineHits;
};

#endif
