// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/segmentation/GridXYZSegmentation.cc,v 1.2 2013-11-13 23:02:58 jeremy Exp $

// LCDD
#include "lcdd/segmentation/GridXYZSegmentation.hh"
#include "lcdd/detectors/ReadoutUtil.hh"
//#include "lcdd/util/TimeUtil.hh"

// Geant4
#include "G4NavigationHistory.hh"

GridXYZSegmentation::GridXYZSegmentation(double gridSizeX, double gridSizeY, double gridSizeZ) :
        Segmentation(Segmentation::eNonprojective), _gridSizeX(gridSizeX), _gridSizeY(gridSizeY), _gridSizeZ(gridSizeZ) {
    setBinNames();
}

GridXYZSegmentation::~GridXYZSegmentation() {
}

void GridXYZSegmentation::setBinNames() {
    addBinName("x");
    addBinName("y");
    addBinName("z");
}

G4ThreeVector GridXYZSegmentation::getGlobalHitPosition(const G4Step* aStep) {

    // compute midpoint
    G4ThreeVector globalStepPos = ReadoutUtil::computeMidPos(aStep);

    // figure local step pos using touchable and global midpoint
    G4ThreeVector localStepPos = ReadoutUtil::transformGlobalToLocal(aStep, globalStepPos);

    // local cell pos
    G4ThreeVector localCellPos = this->getLocalHitPos(localStepPos);

    // global cell pos
    G4ThreeVector globalCellPos = ReadoutUtil::transformLocalToGlobal(aStep, localCellPos);

    return globalCellPos;
}

void GridXYZSegmentation::setBins(const G4Step* aStep) {

    // Compute the midpoint of the step.
    G4ThreeVector globalStepPos = ReadoutUtil::computeMidPos(aStep);

    // Transform from global coordinate system to local coordinate system of volume pointed to by this step.
    G4ThreeVector localStepPos = ReadoutUtil::transformGlobalToLocal(aStep, globalStepPos);

    // Compute the bin values.
    int binX = computeBinX(localStepPos);
    int binY = computeBinY(localStepPos);
    int binZ = computeBinZ(localStepPos);

    // Set the bin values.
    setBin(0, binX);
    setBin(1, binY);
    setBin(2, binZ);
}

int GridXYZSegmentation::computeBinX(const G4ThreeVector& localStepPos) {
    if (_gridSizeX != 0) {
        return Segmentation::computeBin(localStepPos.x(), _gridSizeX);
    } else {
        return 0;
    }
}

int GridXYZSegmentation::computeBinY(const G4ThreeVector& localStepPos) {
    if (_gridSizeY != 0) {
        return Segmentation::computeBin(localStepPos.y(), _gridSizeY);
    } else {
        return 0;
    }
}

int GridXYZSegmentation::computeBinZ(const G4ThreeVector& localStepPos) {
    if (_gridSizeZ != 0) {
        return Segmentation::computeBin(localStepPos.z(), _gridSizeZ);
    } else {
        return 0;
    }
}

double GridXYZSegmentation::computeDimX(int bin) {
    return Segmentation::computeDim(bin, _gridSizeX);
}

double GridXYZSegmentation::computeDimY(int bin) {
    return Segmentation::computeDim(bin, _gridSizeY);
}

double GridXYZSegmentation::computeDimZ(int bin) {
    return Segmentation::computeDim(bin, _gridSizeZ);
}

G4ThreeVector GridXYZSegmentation::getLocalHitPos(const G4ThreeVector& localStepPos) {
    G4ThreeVector localHitPos;

    if (_gridSizeX > 0) {
        localHitPos.setX(computeDimX(computeBinX(localStepPos)));
    }

    if (_gridSizeY > 0) {
        localHitPos.setY(computeDimY(computeBinY(localStepPos)));
    }

    if (_gridSizeZ > 0) {
        localHitPos.setZ(computeDimZ(computeBinZ(localStepPos)));
    }

    return localHitPos;
}
