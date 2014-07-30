#ifndef LCDD_SCHEMA_GLOBALGRIDXYSEGMENTATIONTYPE_HH_
#define LCDD_SCHEMA_GLOBALGRIDXYSEGMENTATIONTYPE_HH_ 1

// LCDD
#include "lcdd/schema/SegmentationType.hh"

// GDML
#include "Saxana/SAXObject.h"

// STL
#include <string>

/**
 * @brief The GlobalGridXYSegmentation from the schema.
 */
class GlobalGridXYSegmentationType: public SegmentationType {
public:

    /**
     * Class constructor.
     */
    GlobalGridXYSegmentationType() {
    }

    /**
     * Class destructor.
     */
    virtual ~GlobalGridXYSegmentationType() {
    }

public:

    /**
     * Set the x grid size.
     * @param gsx The x grid size.
     */
    void set_grid_size_x(const std::string& gsx) {
        _gridSizeX = gsx;
    }

    /**
     * Set the y grid size.
     * @param gsy The y grid size.
     */
    void set_grid_size_y(const std::string& gsy) {
        _gridSizeY = gsy;
    }

    /**
     * Set the length unit.
     * @param lunit The length unit.
     */
    void set_lunit(const std::string& lunit) {
        _lunit = lunit;
    }

    /**
     * Get the x grid size.
     * @return The x grid size.
     */
    const std::string& get_grid_size_x() {
        return _gridSizeX;
    }

    /**
     * Get the y grid size.
     * @return The y grid size.
     */
    const std::string& get_grid_size_y() {
        return _gridSizeY;
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
    std::string _lunit;
};

#endif
