// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/segmentation/ProjectiveSegmentation.cc,v 1.2 2013-11-13 23:02:59 jeremy Exp $

// LCDD
#include "lcdd/segmentation/ProjectiveSegmentation.hh"
#include "lcdd/detectors/ReadoutUtil.hh"

// Geant4
#include "G4StepPoint.hh"
#include "G4NavigationHistory.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Tubs.hh"
#include "G4SystemOfUnits.hh"

ProjectiveSegmentation::ProjectiveSegmentation(G4int ntheta, G4int nphi) :
        Segmentation(Segmentation::eProjective), _ntheta(ntheta), _nphi(nphi) {
    computeDivisions();
    setBinNames();
}

ProjectiveSegmentation::~ProjectiveSegmentation() {
}

void ProjectiveSegmentation::setBinNames() {
    addBinName("theta");
    addBinName("phi");
}

G4ThreeVector ProjectiveSegmentation::getGlobalHitPosition(const G4Step* aStep) {
    // divide entire theta, phi range into bins; bins always positive
    // theta, phi coord of step midpoint
    // compute bin numbers
    // get dim from bins

    // get radius, z components (probably from subclass function)
    double rcyl = getRadius(aStep);
    double zcell = getZ(aStep);

    // get phi component
    double cphi = getPhiDim(aStep);

    // compute x, y cells
    double xcell = rcyl * cos(cphi);
    double ycell = rcyl * sin(cphi);

    G4ThreeVector pos(xcell, ycell, zcell);

    //G4ThreeVector midPos = ReadoutUtil::computeMidPos( aStep );

    return pos;
}

/*
 G4ThreeVector ProjectiveSegmentation::getGlobalHitPos(const G4StepPoint* aPreStepPoint)
 {
 // DEBUG
 //G4cout << "G4ProjectiveSegmentation::getGlobalHitPos()" << G4endl;
 //

 // divide entire theta, phi range into bins; bins always positive
 // theta, phi coord of step midpoint
 // compute bin numbers
 // get dim from bins

 // get radius, z components (probably from subclass function)
 double rcyl = getRadius(aPreStepPoint);
 double zcell = getZ(aPreStepPoint);

 // get phi component
 double cphi = getPhiDim(aPreStepPoint);

 // compute x, y cells
 double xcell = rcyl * cos(cphi);
 double ycell = rcyl * sin(cphi);

 G4ThreeVector pos(xcell, ycell, zcell);

 //G4ThreeVector midPos = ReadoutUtil::computeMidPos( aStep );

 // DEBUG: print all
 //G4cout << "sphi <" << midPos.phi() << ">" << G4endl;
 //G4cout << "cphi <" << cphi << ">" << G4endl;
 //G4cout << "sphi - cphi = " << midPos.phi() - cphi << G4endl;

 //G4cout << "stheta <" << midPos.theta() << ">" << G4endl;
 //G4cout << "ctheta <" << getThetaDim( aStep ) << ">" << G4endl;
 //G4cout << "stheta - ctheta = " << midPos.theta() - getThetaDim( aStep ) << G4endl;

 //G4cout << "rcyl <" << rcyl << ">" << G4endl;
 //G4cout << "zcell <" << zcell << ">" << G4endl;
 //G4cout << "globalCellPos <" << pos << ">" << G4endl;
 //

 return pos;
 }
 */

void ProjectiveSegmentation::setBins(const G4Step* aStep) {
    G4ThreeVector globalMidPos = ReadoutUtil::computeMidPos(aStep);

    setBin(0, getThetaBin(globalMidPos));
    setBin(1, getPhiBin(globalMidPos));
}

/*
 void ProjectiveSegmentation::setBins(const G4StepPoint* aPreStepPoint)
 {
 G4ThreeVector globalPos = aPreStepPoint->GetPosition();

 setBin(0, getThetaBin(globalPos));
 setBin(1, getPhiBin(globalPos));
 }
 */

G4int ProjectiveSegmentation::getNtheta() const {
    return _ntheta;
}

G4int ProjectiveSegmentation::getNphi() const {
    return _nphi;
}

void ProjectiveSegmentation::computeDivisions() {
    _divTheta = (180.0 * deg) / _ntheta;
    _divPhi = (360.0 * deg) / _nphi;
}

int ProjectiveSegmentation::getThetaBin(const G4ThreeVector& globalStepPos) {
    // theta needs to be in range 0 - PI
    return Segmentation::computeBin(globalStepPos.theta(), _divTheta / radian);
}

int ProjectiveSegmentation::getPhiBin(const G4ThreeVector& globalStepPos) {

    // adjust phi for < 0
    double sphi = globalStepPos.phi();

    if (sphi < 0.0) {
        sphi += 360.0 * deg;
    }

    // needs more checks, for phi in range 0 - TWOPI
    // if > TWOPI, then subtract TWOPI
    //
    // OR use X, Y for phi calc

    // compute and return bin
    return Segmentation::computeBin(sphi, _divPhi / radian);
}

// default impl. returns mag of pos 
double ProjectiveSegmentation::getRadius(const G4Step* aStep) {
    //G4cout << "G4ProjectiveSegmentation::getRadius()" << G4endl;

    return ReadoutUtil::computeMidPos(aStep).mag();
}

//double ProjectiveSegmentation::getRadius(const G4StepPoint* aPreStepPoint)
//{
//G4cout << "G4ProjectiveSegmentation::getRadius()" << G4endl;
//    return aPreStepPoint->GetPosition().mag();
//}

// default impl. returns z of pos
double ProjectiveSegmentation::getZ(const G4Step* aStep) {
    //G4cout << "G4ProjectiveSegmentation::getZ()" << G4endl;
    return ReadoutUtil::computeMidPos(aStep).z();
}

//double ProjectiveSegmentation::getZ(const G4StepPoint* aPreStepPoint)
//{
//G4cout << "G4ProjectiveSegmentation::getZ()" << G4endl;
//    return aPreStepPoint->GetPosition().z();
//}

double ProjectiveSegmentation::getThetaDim(const int &thetaBin) const {
    return Segmentation::computeDim(thetaBin, _divTheta);
}

double ProjectiveSegmentation::getPhiDim(const int &phiBin) const {
    return Segmentation::computeDim(phiBin, _divPhi);
}

double ProjectiveSegmentation::getThetaDim(const G4Step* aStep) {
    //G4cout << "G4ProjectiveSegmentation::getThetaDim(G4Step*)" << G4endl;
    G4ThreeVector globalStepPos = ReadoutUtil::computeMidPos(aStep);
    double ctheta = getThetaDim(getThetaBin(globalStepPos));
    return ctheta;
}

//double ProjectiveSegmentation::getThetaDim(const G4StepPoint* aPreStepPoint)
//{
//G4cout << "G4ProjectiveSegmentation::getThetaDim(G4Step*)" << G4endl;
//    G4ThreeVector globalStepPos = aPreStepPoint->GetPosition();
//    double ctheta = getThetaDim(getThetaBin(globalStepPos));
//    return ctheta;
//}

double ProjectiveSegmentation::getPhiDim(const G4Step* aStep) {
    //G4cout << "G4ProjectiveSegmentation::getPhiDim(G4Step*)" << G4endl;

    G4ThreeVector globalStepPos = ReadoutUtil::computeMidPos(aStep);
    double cphi = getPhiDim(getPhiBin(globalStepPos));
    return cphi;
}
//double ProjectiveSegmentation::getPhiDim(const G4StepPoint* aPreStepPoint)
//{
//G4cout << "G4ProjectiveSegmentation::getPhiDim(G4Step*)" << G4endl;

//    G4ThreeVector globalStepPos = aPreStepPoint->GetPosition();
//    double cphi = getPhiDim(getPhiBin(globalStepPos));
//    return cphi;
//}

