// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/segmentation/CellReadout2D.hh,v 1.2 2013-11-14 00:47:23 jeremy Exp $

#ifndef LCDD_SEGMENTATION_CELLREADOUT2D_HH
#define LCDD_SEGMENTATION_CELLREADOUT2D_HH 1

// LCDD
#include "lcdd/segmentation/CellReadout.hh"

// STL
#include <vector>
#include <map>

/**
 * @brief
 * A concrete implementation of CellReadout using a 2D grid
 * with coordinate origin in the lower lefthand corner of the
 * readout volume.
 */
class CellReadout2D: public CellReadout {

public:

    /**
     * Class destructor.
     */
    virtual ~CellReadout2D();

    /**
     * Class constructor.
     */
    CellReadout2D(double cellSizeX, double cellSizeY);

    /**
     * ----------------------------------------------------------
     * Implementation of CellReadout
     * ----------------------------------------------------------
     */

    /**
     * Get the position of the cell.
     * @param[in] id The CellId.
     */
    Position2D position(CellId id);

    /**
     * Compute cell ID from local position.
     * @param[in] pos The 2D position.
     */
    CellId cellId(Position2D pos);

    /**
     * Create a list of neighbor cells from a cell ID.
     * @param[in] id The CellId.
     */
    Neighbors neighbors(CellId id);

    /**
     * ----------------------------------------------------------
     * Functionality specific to this implementation.
     * ----------------------------------------------------------
     */

    /**
     * Get the X cell size.
     * @return The cell size X.
     */
    double getCellSizeX();

    /**
     * Get the Y cell size.
     * @return The cell size Y.
     */
    double getCellSizeY();

    /**
     * Get the X index from a position.
     * @param[in] x The X coordinate.
     * @return The X bin value.
     */
    int getXIndex(double x);

    /**
     * Get the Y index from a position.
     * @param[in] y The Y coordinate.
     * @return The Y bin value.
     */
    int getYIndex(double y);

    /*
     * Get the X position from a cell index.
     * @param[in] ix The X index.
     * @return The X coordinate.
     */
    double getCellPositionX(int ix);

    /**
     * Get the Y position from a Y bin value.
     * @param[in] iy The Y index.
     * @return The Y coordinate.
     */
    double getCellPositionY(int iy);

    /**
     * Create a pair of indices representing a cell.
     * @param[in] x The X cell index.
     * @param[in] y The Y cell index.
     */
    CellId createCell(int x, int y);

    /**
     * Given an index and cell size, compute the corresponding coordinate.
     * @param[in] u        The cell index.
     * @param[in] cellSize The size of the cell in the corresponding dimension.
     */
    double getCellCoordinate(int u, double cellSize);

    /**
     * Given a coordinate and cell size, compute the corresponding cell index.
     * @param[in] x        The coordinate value.
     * @param[in] cellSize The size of the cell in the corresponding dimension.
     */
    int getCellIndex(double x, double cellSize);

    /**
     * Set the current X dimension.
     * @param[in] dimensionX The dimension in X.
     */
    void setDimensionX(double dimensionX);

    /**
     * Set the current Y dimension.
     * @param[in] dimensionY The dimension in Y.
     */

    void setDimensionY(double dimensionY);

    /**
     * Get the current dimension in X.
     * @return The dimension in X.
     */
    double getDimensionX();

    /**
     * Get the current dimension in Y.
     * @return The dimension in Y.
     */
    double getDimensionY();

    /**
     * Check if a CellId is valid.
     * @param[in] The CellId to check.
     * @return True if valid; false if not.
     */
    bool isValidCell(CellId cell);

    /**
     * Check if a Position2D is valid.
     * @param[in] The position to check.
     * @return True if valid; false if not.
     */
    bool isValidPosition(Position2D position);

private:

    double _cellSizeX;
    double _cellSizeY;

    double _dimensionX;
    double _dimensionY;
};

#endif
