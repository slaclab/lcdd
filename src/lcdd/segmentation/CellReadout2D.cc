// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/segmentation/CellReadout2D.cc,v 1.2 2013-11-13 23:02:58 jeremy Exp $

// LCDD
#include "lcdd/segmentation/CellReadout2D.hh"

// STL
#include <cmath>
#include <iostream>
#include <stdexcept>

CellReadout2D::CellReadout2D(double cellSizeX, double cellSizeY) :
        _cellSizeX(cellSizeX), _cellSizeY(cellSizeY), _dimensionX(0.), _dimensionY(0.) {
}

CellReadout2D::~CellReadout2D() {
}

CellReadout2D::Position2D CellReadout2D::position(CellReadout2D::CellId cellId) {
    Position2D position;
    position.x = getCellPositionX(cellId.ix);
    position.y = getCellPositionY(cellId.iy);
    return position;
}

CellReadout::CellId CellReadout2D::cellId(Position2D position) {
    return createCell(getXIndex(position.x), getYIndex(position.y));
}

CellReadout::Neighbors CellReadout2D::neighbors(CellId cellId) {
    Neighbors neighbors;
    CellId cell;

    // Loop over delta Y.
    for (int i = -1; i <= 1; i++) {
        // Loop over delta X.
        for (int j = -1; j <= 1; j++) {
            // Ignore this cell.
            if (i != 0 || j != 0) {
                // Create CellId for this neighbor.
                //std::cout << "creating neighbor i, j: " << i << ", " << j << std::endl;
                cell = createCell(cellId.ix + j, cellId.iy + i);
                // Check if valid.
                if (isValidCell(cell)) {
                    // Add if cell is valid.
                    neighbors.push_back(cell);
                }
            }
        }
    }

    return neighbors;

}

double CellReadout2D::getCellSizeX() {
    return _cellSizeX;
}

double CellReadout2D::getCellSizeY() {
    return _cellSizeY;
}

int CellReadout2D::getXIndex(double x) {
    return getCellIndex(x, _cellSizeX);
}

int CellReadout2D::getYIndex(double y) {
    return getCellIndex(y, _cellSizeY);
}

double CellReadout2D::getCellCoordinate(int i, double cellSize) {
    return (i * cellSize) - cellSize / 2;
}

int CellReadout2D::getCellIndex(double c, double cellSize) {
    int v = std::ceil(c / cellSize);
    if (v == 0)
        v = 1;
    return v;
}

double CellReadout2D::getCellPositionX(int ix) {
    return getCellCoordinate(ix, _cellSizeX);
}

double CellReadout2D::getCellPositionY(int iy) {
    return getCellCoordinate(iy, _cellSizeY);
}

CellReadout2D::CellId CellReadout2D::createCell(int x, int y) {
    CellId cell;
    cell.ix = x;
    cell.iy = y;
    return cell;
}

void CellReadout2D::setDimensionX(double dimensionX) {
    _dimensionX = dimensionX;
}

void CellReadout2D::setDimensionY(double dimensionY) {
    _dimensionY = dimensionY;
}

double CellReadout2D::getDimensionX() {
    return _dimensionX;
}

double CellReadout2D::getDimensionY() {
    return _dimensionY;
}

bool CellReadout2D::isValidCell(CellId cell) {
    // DEBUG
    //std::cout << "isValidCell: " << cell.ix << ", " << cell.iy << std::endl;

    if (cell.ix <= 0 || cell.iy <= 0) {
        //std::cout << "field value < 0" << std::endl;
        return false;
    }
    int xmax = std::floor(getDimensionX() / getCellSizeX());
    //std::cout << "xmax: " << xmax << std::endl;
    if (cell.ix > xmax) {
        //std::cout << cell.ix << " exceeds max allowed X index" << std::endl;
        return false;
    }
    int ymax = std::floor(getDimensionY() / getCellSizeY());
    //std::cout << "ymax: " << ymax << std::endl;
    if (cell.iy > ymax) {
        //std::cout << cell.iy << " exceeds max allowed Y index" << std::endl;
        return false;
    }
    return true;
}

bool CellReadout2D::isValidPosition(Position2D position) {
    if (position.x > getDimensionX() || position.x < 0)
        return false;
    if (position.y > getDimensionY() || position.y < 0)
        return false;
    return true;
}

