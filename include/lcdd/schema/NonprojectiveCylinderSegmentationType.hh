// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/NonprojectiveCylinderSegmentationType.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_NONPROJECTIVECYLINDERSEGMENTATIONTYPE_HH
#define LCDD_SCHEMA_NONPROJECTIVECYLINDERSEGMENTATIONTYPE_HH 1

// LCDD
#include "SegmentationType.hh"

// STL
#include <string>

/**
 * @brief The NonprojectiveCylinderSegmentationType from the schema.
 */
class NonprojectiveCylinderSegmentationType: public SegmentationType {
public:

    NonprojectiveCylinderSegmentationType() {
    }

    virtual ~NonprojectiveCylinderSegmentationType() {
    }

public:

    /**
     * Set the grid size z.
     * @param gsz The grid size z.
     */
    void set_gridSizeZ(const std::string& gsz) {
        _gridSizeZ = gsz;
    }

    /**
     * Set the grid size phi.
     * @param gsp The grid size phi.
     */
    void set_gridSizePhi(const std::string& gsp) {
        _gridSizePhi = gsp;
    }

    /**
     * Set the length unit.
     * @param lunit The length unit.
     */
    void set_lunit(const std::string& lunit) {
        _lunit = lunit;
    }

    /**
     * Get the grid size z.
     * @return The grid size z.
     */
    const std::string& get_gridSizeZ() {
        return _gridSizeZ;
    }

    /**
     * Get the grid size phi.
     * @return The grid size phi.
     */
    const std::string& get_gridSizePhi() {
        return _gridSizePhi;
    }

    /**
     * Get the length unit.
     * @return The length unit.
     */
    const std::string& get_lunit() {
        return _lunit;
    }

protected:

    std::string _gridSizeZ;
    std::string _gridSizePhi;
    std::string _lunit;
};

#endif
