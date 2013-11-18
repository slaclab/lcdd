// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/ProjectiveZPlaneSegmentationType.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_PROJECTIVEZPLANESEGMENTATIONTYPE_HH
#define LCDD_SCHEMA_PROJECTIVEZPLANESEGMENTATIONTYPE_HH 1

// LCDD
#include "SegmentationType.hh"

// STL
#include <string>

/**
 * @brief The ProjectiveZPlaneSegmentationType from the schema.
 */
class ProjectiveZPlaneSegmentationType: public SegmentationType {
public:

    /**
     * Class constructor.
     */
    ProjectiveZPlaneSegmentationType() {
    }

    /**
     * Class destructor.
     */
    virtual ~ProjectiveZPlaneSegmentationType() {
    }

public:

    /**
     * Set the number of theta bins.
     * @param ntheta The number of theta bins.
     */
    void set_ntheta(const std::string& ntheta) {
        _ntheta = ntheta;
    }

    /**
     * Set the number of phi bins.
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
