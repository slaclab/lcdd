#ifndef LCDD_CELLREADOUT2DSEGMENTATIONTYPE_HH_
#define LCDD_CELLREADOUT2DSEGMENTATIONTYPE_HH_ 1

// LCDD
#include "SegmentationType.hh"

// STL
#include <string>

/**
 * @brief The CellReadout2DSegmentationType from the schema.
 */
class CellReadout2DSegmentationType: public SegmentationType {

public:

    /**
     * Class constructor.
     */
    CellReadout2DSegmentationType() {
    }

    /**
     * Class destructor.
     */
    virtual ~CellReadout2DSegmentationType() {
    }

public:

    /**
     * Set the x cell size.
     * @param[i] cellSizeX The x cell size.
     */
    void setCellSizeX(const std::string& cellSizeX) {
        _cellSizeX = cellSizeX;
    }

    /**
     * Set the y cell size.
     * @param[i] cellSizeX The y cell size.
     */
    void setCellSizeY(const std::string& cellSizeY) {
        _cellSizeY = cellSizeY;
    }

    /**
     * Set the length unit for the cell sizes.
     * @param lengthUnit[i] The length unit of the cells.
     */
    void setLengthUnit(const std::string& lengthUnit) {
        _lengthUnit = lengthUnit;
    }

    /**
     * Get the cell size x.
     * @return The x cell size.
     */
    const std::string& getCellSizeX() {
        return _cellSizeX;
    }

    /**
     * Get the cell size y.
     * @return The y cell size.
     */
    const std::string& getCellSizeY() {
        return _cellSizeY;
    }

    /**
     * Get the cell size z.
     * @return The z cell size.
     */
    const std::string& getLengthUnit() {
        return _lengthUnit;
    }

protected:

    std::string _cellSizeX;
    std::string _cellSizeY;
    std::string _lengthUnit;
};

#endif
