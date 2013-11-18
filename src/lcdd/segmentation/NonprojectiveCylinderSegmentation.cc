// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/segmentation/NonprojectiveCylinderSegmentation.cc,v 1.2 2013-11-13 23:02:58 jeremy Exp $

// LCDD
#include "lcdd/segmentation/NonprojectiveCylinderSegmentation.hh"
#include "lcdd/detectors/ReadoutUtil.hh"

// Geant4
#include "G4Tubs.hh"

// STL
#include <cmath>

NonprojectiveCylinderSegmentation::NonprojectiveCylinderSegmentation(double gridSizePhi, double gridSizeZ) :
        Segmentation(Segmentation::eNonprojective), _gridSizePhi(gridSizePhi), _gridSizeZ(gridSizeZ)

{
    setBinNames();
}

NonprojectiveCylinderSegmentation::~NonprojectiveCylinderSegmentation() {
}

void NonprojectiveCylinderSegmentation::setBinNames() {
    addBinName("phi");
    addBinName("z");
}

G4ThreeVector NonprojectiveCylinderSegmentation::getGlobalHitPosition(const G4Step* aStep) {
    // local cell pos
    G4ThreeVector localCellPos = getLocalHitPos(aStep);

    // global cell pos
    G4ThreeVector globalCellPos = ReadoutUtil::transformLocalToGlobal(aStep, localCellPos);

    return localCellPos;
}

/*
 G4ThreeVector NonprojectiveCylinderSegmentation::getGlobalHitPos(const G4StepPoint* aPreStepPoint)
 {
 // local cell pos
 G4ThreeVector localCellPos = getLocalHitPos(aPreStepPoint);

 // global cell pos
 G4ThreeVector globalCellPos = ReadoutUtil::transformLocalToGlobal(aPreStepPoint, localCellPos);

 // DEBUG: print local, global cell pos
 //G4cout << "localCellPos " << localCellPos << G4endl;
 //G4cout << "globalCellPos " << globalCellPos << G4endl;
 //

 return localCellPos;
 }
 */

G4ThreeVector NonprojectiveCylinderSegmentation::getLocalHitPos(const G4Step* aStep) {
    G4ThreeVector globalMidPos = ReadoutUtil::computeMidPos(aStep);

    // retrieve G4Tubs
    const G4Tubs* tubs = ReadoutUtil::getTubs(aStep);

    assert(tubs);

    // rcyl of cell = mid rad of current tubs
    double rcyl = ReadoutUtil::computeTubsMidRadius(tubs);

    // compute single delta phi in degrees
    double deltaPhi = computeDeltaPhi(aStep);

    // phi index
    int iphi = computeBinPhi(aStep);

    // z index in local
    int iz = computeBinZ(ReadoutUtil::transformGlobalToLocal(aStep, globalMidPos));

    // compute cell Z, phi
    double cellPhi = computeDim(iphi, deltaPhi);
    double cellZ = computeDim(iz, _gridSizeZ);

    // compute X, Y
    double cellX = rcyl * cos(cellPhi);
    double cellY = rcyl * sin(cellPhi);

    G4ThreeVector cellCenter(cellX, cellY, cellZ);

    return cellCenter;
}

G4ThreeVector NonprojectiveCylinderSegmentation::getLocalHitPos(const G4StepPoint* aPreStepPoint) {
    G4ThreeVector globalPos = aPreStepPoint->GetPosition();

    // retrieve G4Tubs
    const G4Tubs* tubs = ReadoutUtil::getTubs(aPreStepPoint);

    assert(tubs);

    // rcyl of cell = mid rad of current tubs
    double rcyl = ReadoutUtil::computeTubsMidRadius(tubs);

    // compute single delta phi in degrees
    double deltaPhi = computeDeltaPhi(aPreStepPoint);

    // phi index
    int iphi = computeBinPhi(aPreStepPoint);

    // z index in local
    int iz = computeBinZ(ReadoutUtil::transformGlobalToLocal(aPreStepPoint, globalPos));

    // compute cell Z, phi
    double cellPhi = computeDim(iphi, deltaPhi);
    double cellZ = computeDim(iz, _gridSizeZ);

    // compute X, Y
    double cellX = rcyl * cos(cellPhi);
    double cellY = rcyl * sin(cellPhi);

    G4ThreeVector cellCenter(cellX, cellY, cellZ);

    return cellCenter;
}

double NonprojectiveCylinderSegmentation::computeDeltaPhi(const G4Step* aStep) {
    // mid radius of current tubs
    double mid_rad_layer = ReadoutUtil::computeTubsMidRadius(aStep);

    // circumference of current tubs
    double circ = 2.0 * ReadoutUtil::PI * mid_rad_layer;

    // number of cells along phi in curr layer
    int nphi = (int) floor(circ / _gridSizePhi);

    // single phi division in degrees
    double deltaPhi = (360.0 * deg) / nphi;

    return deltaPhi;
}
double NonprojectiveCylinderSegmentation::computeDeltaPhi(const G4StepPoint* aPreStepPoint) {
    // mid radius of current tubs
    double mid_rad_layer = ReadoutUtil::computeTubsMidRadius(aPreStepPoint);

    // circumference of current tubs
    double circ = 2.0 * ReadoutUtil::PI * mid_rad_layer;

    // number of cells along phi in curr layer
    int nphi = (int) floor(circ / _gridSizePhi);

    // single phi division in degrees
    double deltaPhi = (360.0 * deg) / nphi;

    return deltaPhi;
}
void NonprojectiveCylinderSegmentation::setBins(const G4Step* aStep) {
    //G4cout << "G4NonprojectiveCylinderSegmentation::setBins()" << G4endl;

    G4ThreeVector globalMidPos = ReadoutUtil::computeMidPos(aStep);

    int bphi = computeBinPhi(aStep);
    int bz = computeBinZ(globalMidPos);

    setBin(0, bphi);
    setBin(1, bz);
}
//void NonprojectiveCylinderSegmentation::setBins(const G4StepPoint* aPreStepPoint)
//{
//    //G4cout << "G4NonprojectiveCylinderSegmentation::setBins()" << G4endl;
//
//    G4ThreeVector globalPos = aPreStepPoint->GetPosition();
//
//    int bphi = computeBinPhi(aPreStepPoint);
//    int bz = computeBinZ(globalPos);
//
//    setBin(0, bphi);
//    setBin(1, bz);
//}
int NonprojectiveCylinderSegmentation::computeBinPhi(const G4Step* aStep) {
    G4ThreeVector globalMidPos = ReadoutUtil::computeMidPos(aStep);

    const G4Tubs* tubs = ReadoutUtil::getTubs(aStep);
    assert(tubs);

    // compute single delta phi in degrees
    double deltaPhi = computeDeltaPhi(aStep);

    // step phi
    double stepPhi = globalMidPos.phi();

    if (stepPhi < 0) {
        stepPhi += 2.0 * ReadoutUtil::PI;
    }

    // phi index
    return computeBin(stepPhi, deltaPhi / radian);
}

int NonprojectiveCylinderSegmentation::computeBinPhi(const G4StepPoint* aPreStepPoint) {
    G4ThreeVector globalPos = aPreStepPoint->GetPosition();

    const G4Tubs* tubs = ReadoutUtil::getTubs(aPreStepPoint);
    assert(tubs);

    // compute single delta phi in degrees
    double deltaPhi = computeDeltaPhi(aPreStepPoint);

    // step phi
    double stepPhi = globalPos.phi();

    if (stepPhi < 0) {
        stepPhi += 2.0 * ReadoutUtil::PI;
    }

    // phi index
    return computeBin(stepPhi, deltaPhi / radian);
}

int NonprojectiveCylinderSegmentation::computeBinZ(const G4ThreeVector& localStepPos) {
    return computeBin(localStepPos.z(), _gridSizeZ);
}

bool NonprojectiveCylinderSegmentation::isValidSolid(G4VSolid* s) {
    bool valid = Segmentation::isValidSolid(s);

    if (valid) {
        if (s->GetEntityType() != "G4Tubs") {
            valid = false;
        }
    }

    return valid;
}
