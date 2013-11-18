// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/segmentation/CellReadout2DSegmentation.cc,v 1.3 2013-11-13 23:02:58 jeremy Exp $

// LCDD
#include "lcdd/segmentation/CellReadout2DSegmentation.hh"
#include "lcdd/detectors/ReadoutUtil.hh"

// Geant4
#include "G4Step.hh"
#include "G4Box.hh"

// STL
#include <cmath>

// Comment out to remove debug prints.
//#define CellReadout2DSegmentation_DEBUG 1

CellReadout2DSegmentation::CellReadout2DSegmentation(double cellSizeX, double cellSizeY) :
        Segmentation(Segmentation::eNonprojective, 2) {
    _readout = new CellReadout2D(cellSizeX, cellSizeY);
    setBinNames();
}

CellReadout2DSegmentation::~CellReadout2DSegmentation() {
    delete _readout;
}

G4ThreeVector CellReadout2DSegmentation::getGlobalHitPosition(const G4Step* aStep) {
#ifdef CellReadout2DSegmentation_DEBUG
    std::cout << "CellReadout2DSegmentation::getGlobalHitPosition" << std::endl;
#endif

    // Setup the readout with step dependent information.
    setup(aStep);

    // Compute the mid-point of the global step.
    G4ThreeVector globalStepPosition = ReadoutUtil::computeMidPos(aStep);

#ifdef CellReadout2DSegmentation_DEBUG
    std::cout << "globalStepPosition: " << globalStepPosition.x() << " " << globalStepPosition.y() << " " << globalStepPosition.z() << std::endl;
#endif

    // Compute the local step position.
    G4ThreeVector localStepPosition = ReadoutUtil::transformGlobalToLocal(aStep, globalStepPosition);

#ifdef CellReadout2DSegmentation_DEBUG
    std::cout << "localStepPosition: " << localStepPosition.x() << " " << localStepPosition.y() << " " << localStepPosition.z() << std::endl;
#endif

    // Convert into readout coordinates.
    CellReadout::Position2D readoutStepPosition = localToReadoutCoordinates(localStepPosition);

#ifdef CellReadout2DSegmentation_DEBUG
    std::cout << "readoutStepPosition: " << readoutStepPosition.x << " " << readoutStepPosition.y << std::endl;
#endif

    // Compute the cell indices from the position.
    CellReadout::CellId cell = _readout->cellId(readoutStepPosition);

#ifdef CellReadout2DSegmentation_DEBUG
    std::cout << "cell: " << cell.ix << " " << cell.iy << std::endl;
#endif

    // Get the cell's readout position from the cell ID.
    CellReadout::Position2D cellReadoutPosition = _readout->position(cell);

#ifdef CellReadout2DSegmentation_DEBUG
    std::cout << "cellReadoutPosition: " << cellReadoutPosition.x << " " << cellReadoutPosition.y << std::endl;
#endif

    // Convert from readout back to localcoordinates.
    G4ThreeVector localCellPosition = readoutToLocalCoordinates(cellReadoutPosition);

#ifdef CellReadout2DSegmentation_DEBUG
    std::cout << "localCellPosition: "<< localCellPosition.x() << " " << localCellPosition.y() << " " << localCellPosition.z() << std::endl;
#endif

    // Finally, convert from the local coordinates into global.
    G4ThreeVector globalCellPosition = ReadoutUtil::transformLocalToGlobal(aStep, localCellPosition);

#ifdef CellReadout2DSegmentation_DEBUG
    std::cout << "globalCellPosition: "
    << globalCellPosition.x() << " "
    << globalCellPosition.y() << " "
    << globalCellPosition.z() << std::endl;
    std::cout << std::endl;
#endif

    return globalCellPosition;
}

void CellReadout2DSegmentation::setBins(const G4Step* aStep) {
#ifdef CellReadout2DSegmentation_DEBUG
    std::cout << "CellReadout2DSegmentation::setBins" << std::endl;
#endif

    // Setup the readout with step dependent information.
    setup(aStep);

#ifdef CellReadout2DSegmentation_DEBUG
    G4ThreeVector prePosition = aStep->GetPreStepPoint()->GetPosition();
    std::cout << "step pos: " << prePosition.x() << " " << prePosition.y() << " " << prePosition.z() << std::endl;
#endif

    // Set state from current step.
    setup(aStep);

    // Compute the global mid-point of the step.
    G4ThreeVector globalStepPos = ReadoutUtil::computeMidPos(aStep);

#ifdef CellReadout2DSegmentation_DEBUG
    std::cout << "globalStepPos: " << globalStepPos.x() << " " << globalStepPos.y() << " " << globalStepPos.z() << std::endl;
#endif

    // Compute the local step position from the global mid-point.
    G4ThreeVector localStepPos = ReadoutUtil::transformGlobalToLocal(aStep, globalStepPos);

#ifdef CellReadout2DSegmentation_DEBUG
    std::cout << "localStepPos: " << localStepPos.x() << " " << localStepPos.y() << " " << localStepPos.z() << std::endl;
#endif

    // Compute the X and Y readout coordinates from the local position.
    CellReadout::Position2D readoutPosition = localToReadoutCoordinates(localStepPos);

#ifdef CellReadout2DSegmentation_DEBUG
    std::cout << "readoutPosition: " << readoutPosition.x << " " << readoutPosition.y << std::endl;
#endif

    // Get the cell for the position.
    CellReadout::CellId cell = _readout->cellId(readoutPosition);

#ifdef CellReadout2DSegmentation_DEBUG
    std::cout << "cellID: " << cell.ix << " " << cell.iy << std::endl;
#endif

    // Set the segmentation's bin values.
    this->setBin(0, readoutPosition.x);
    this->setBin(1, readoutPosition.y);

#ifdef CellReadout2DSegmentation_DEBUG
    // print the neighbor CellIds
    CellReadout::Neighbors neighbors = _readout->neighbors(cell);
    std::cout << "neighbors: " << std::endl;
    for (CellReadout::Neighbors::const_iterator it = neighbors.begin(); it != neighbors.end(); it++) {
        std::cout << "  " << (*it).ix << ", " << (*it).iy << std::endl;
    }
    std::cout << std::endl;
#endif
}

void CellReadout2DSegmentation::setBinNames() {
    addBinName("ix");
    addBinName("iy");
}

void CellReadout2DSegmentation::setup(const G4Step* aStep) {
    // Set dimensions from current box volume.
    G4VSolid* solid = ReadoutUtil::getSolidFromStepPoint(aStep->GetPreStepPoint());
    G4Box* box = dynamic_cast<G4Box*>(solid);
    if (box == 0) {
        std::cerr << "Current volume is not a box!!!" << std::endl;
        G4Exception("", "", FatalException, "CellReadout2D points to a shape that is not a G4Box.");
    }
    _readout->setDimensionX(box->GetXHalfLength() * 2);
    _readout->setDimensionY(box->GetYHalfLength() * 2);

#ifdef CellReadout2DSegmentation_DEBUG
    std::cout << "set readout dimensions XY: " << _readout->getDimensionX() << " " << _readout->getDimensionY() << std::endl;
#endif
}

CellReadout::Position2D CellReadout2DSegmentation::localToReadoutCoordinates(G4ThreeVector& vec) {
    CellReadout::Position2D position;
    position.x = vec.x() + _readout->getDimensionX() / 2.;
    position.y = vec.y() + _readout->getDimensionY() / 2.;
    return position;
}

G4ThreeVector CellReadout2DSegmentation::readoutToLocalCoordinates(CellReadout::Position2D position) {
    double x = position.x - _readout->getDimensionX() / 2.;
    double y = position.y - _readout->getDimensionY() / 2.;
    return G4ThreeVector(x, y, 0);
}
