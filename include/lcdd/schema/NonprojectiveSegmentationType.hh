// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/NonprojectiveSegmentationType.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_NONPROJECTIVESEGMENTATIONTYPE_HH
#define LCDD_SCHEMA_NONPROJECTIVESEGMENTATIONTYPE_HH 1

// LCDD
#include "SegmentationType.hh"

// STL
#include <string>

/**
 * @brief The NonprojectiveSegmentationType from the schema.
 */
class NonprojectiveSegmentationType: public SegmentationType {
public:

    /**
     * Class constructor.
     */
    NonprojectiveSegmentationType() {
    }

    /**
     * Class destructor.
     */
    virtual ~NonprojectiveSegmentationType() {
    }

public:

    /**
     * Set the grid size x.
     * @param gsx The grid size x.
     */
    void set_gridSizeX(const std::string& gsx) {
        _gridSizeX = gsx;
    }

    /**
     * Set the grid size y.
     * @param gsy The grid size y.
     */
    void set_gridSizeY(const std::string& gsy) {
        _gridSizeY = gsy;
    }

    /**
     * Set the grid size z.
     * @param gsz The grid size z.
     */
    void set_gridSizeZ(const std::string& gsz) {
        _gridSizeZ = gsz;
    }

    /**
     * Set the length unit.
     * @param lunit The length unit.
     */
    void set_lunit(const std::string& lunit) {
        _lunit = lunit;
    }

    /**
     * Get the grid size x.
     * @return The grid size x.
     */
    const std::string& get_gridSizeX() {
        return _gridSizeX;
    }

    /**
     * Get the grid size y.
     * @return The grid size y.
     */
    const std::string& get_gridSizeY() {
        return _gridSizeY;
    }

    /**
     * Get the grid size z.
     * @return The grid size z.
     */
    const std::string& get_gridSizeZ() {
        return _gridSizeZ;
    }

    /**
     * Get the length unit.
     * @return The length unit.
     */
    const std::string& get_lunit() {
        return _lunit;
    }

protected:

    std::string _gridSizeX;
    std::string _gridSizeY;
    std::string _gridSizeZ;
    std::string _lunit;
};

#endif
