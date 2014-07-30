#ifndef LCDD_SCHEMA_PROJECTIVECYLINDERSEGMENTATIONTYPE_HH_
#define LCDD_SCHEMA_PROJECTIVECYLINDERSEGMENTATIONTYPE_HH_ 1

// LCDD
#include "SegmentationType.hh"

// STL
#include <string>

/**
 * @brief The ProjectiveCylinderSegmentationType from the schema.
 */
class ProjectiveCylinderSegmentationType: public SegmentationType {
public:

    /**
     * Class constructor.
     */
    ProjectiveCylinderSegmentationType() {
    }

    /**
     * Class destructor.
     */
    virtual ~ProjectiveCylinderSegmentationType() {
    }

public:

    /**
     * Set the number of theta bins.  This divides 180 degrees in theta.
     * @param ntheta The number of theta bins.
     */
    void set_ntheta(const std::string& ntheta) {
        _ntheta = ntheta;
    }

    /**
     * Set the number of phi bins.  This divides 360 degrees in phi.
     * @param nphi The number of phi bins.
     */
    void set_nphi(const std::string& nphi) {
        _nphi = nphi;
    }

    /**
     * Get the number of theta bins.
     * @return The number of theta bins.
     */
    const std::string& get_ntheta() const {
        return _ntheta;
    }

    /**
     * Get the number of phi bins.
     * @return The number of phi bins.
     */
    const std::string& get_nphi() const {
        return _nphi;
    }

protected:

    std::string _ntheta, _nphi;
};

#endif
