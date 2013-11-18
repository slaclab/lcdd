// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/segmentation/GridXYZSegmentation.cc,v 1.2 2013-11-13 23:02:58 jeremy Exp $

// LCDD
#include "lcdd/segmentation/GridXYZSegmentation.hh"
#include "lcdd/detectors/ReadoutUtil.hh"

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

    // Set the bins.
    int idx = 0;

    setBin(idx, binX);
    ++idx;

    setBin(idx, binY);
    ++idx;

    setBin(idx, binZ);
    ++idx;
}

int GridXYZSegmentation::computeBinX(const G4ThreeVector& localStepPos) {
    int ret;
    if (_gridSizeX != 0) {
        ret = Segmentation::computeBin(localStepPos.x(), _gridSizeX);
    } else {
        ret = 0;
    }
    return ret;
}

int GridXYZSegmentation::computeBinY(const G4ThreeVector& localStepPos) {
    int ret;
    if (_gridSizeY != 0) {
        ret = Segmentation::computeBin(localStepPos.y(), _gridSizeY);
    } else {
        ret = 0;
    }
    return ret;
}

int GridXYZSegmentation::computeBinZ(const G4ThreeVector& localStepPos) {
    int ret;
    if (_gridSizeZ != 0) {
        ret = Segmentation::computeBin(localStepPos.z(), _gridSizeZ);
    } else {
        ret = 0;
    }
    return ret;
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

/*
 G4ThreeVector GridXYZSegmentation::getGlobalHitPosPreStep(const G4StepPoint* aPreStepPoint)
 {
 G4ThreeVector globalStepPos = aPreStepPoint->GetPosition();

 // Figure out local step pos using touchable and global midpoint.
 G4ThreeVector localStepPos = ReadoutUtil::transformGlobalToLocal(aPreStepPoint, globalStepPos);

 // Compute local cell pos.
 G4ThreeVector localCellPos = this->getLocalHitPos(localStepPos);

 // Compute global cell pos.
 G4ThreeVector globalCellPos = ReadoutUtil::transformLocalToGlobal(aPreStepPoint, localCellPos);

 return globalCellPos;
 }
 */

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
